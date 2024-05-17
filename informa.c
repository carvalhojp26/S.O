#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void int_to_str(int num, char* str) {
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num > 0) {
            str[i++] = (num % 10) + '0';
            num /= 10;                   
        }
    }

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = str[j];
        str[j] = str[k];
        str[k] = tmp;
    }

    str[i] = '\0';
}

int main(int argc, char *argv[]) {
    struct stat statbuf;
    char output[1024];
    int output_len = 0;

    if(argc != 2) {
        write(STDERR_FILENO, "Wrong number of arguments\n", 27);
        return 1;
    }

    if (stat(argv[1], &statbuf) == -1) {
        write(STDERR_FILENO, "Failed to get file info\n", 24);
        return 1;
    }

    // File type and permissions
    if (S_ISREG(statbuf.st_mode))
        write(STDOUT_FILENO, "Type: Regular File\n", 19);
    else if (S_ISDIR(statbuf.st_mode))
        write(STDOUT_FILENO, "Type: Directory\n", 16);
    else if (S_ISLNK(statbuf.st_mode))
        write(STDOUT_FILENO, "Type: Symbolic Link\n", 20);

    // i-node
    write(STDOUT_FILENO, "i-node: ", 8);
    int_to_str(statbuf.st_ino, output);
    write(STDOUT_FILENO, output, strlen(output));
    write(STDOUT_FILENO, "\n", 1);

    // Owner
    struct passwd *pwd = getpwuid(statbuf.st_uid);
    struct group *grp = getgrgid(statbuf.st_gid);
    if (pwd) {
        write(STDOUT_FILENO, "Owner: ", 7);
        write(STDOUT_FILENO, pwd->pw_name, strlen(pwd->pw_name));
        write(STDOUT_FILENO, "\n", 1);
    }
    
    if (grp) {
        write(STDOUT_FILENO, "Group: ", 7);
        write(STDOUT_FILENO, grp->gr_name, strlen(grp->gr_name));
        write(STDOUT_FILENO, "\n", 1);
    }

    // Dates
    struct tm *tm;
    char datestring[256];

    tm = localtime(&statbuf.st_mtime);
    strftime(datestring, sizeof(datestring), "Last modified: %c\n", tm);
    write(STDOUT_FILENO, datestring, strlen(datestring));

    tm = localtime(&statbuf.st_atime);
    strftime(datestring, sizeof(datestring), "Last accessed: %c\n", tm);
    write(STDOUT_FILENO, datestring, strlen(datestring));

    tm = localtime(&statbuf.st_ctime);
    strftime(datestring, sizeof(datestring), "Creation time: %c\n", tm);
    write(STDOUT_FILENO, datestring, strlen(datestring));

    return 0;
}
