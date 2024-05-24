#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *directory;
    struct dirent *dir;

    directory = opendir(argv[1]);

    readdir(directory);
    if (directory) {
        while ((dir = readdir(directory)) != NULL) {
            write(1, dir->d_name, strlen(dir->d_name));
            write(1, " ", 1);
            switch (dir->d_type) {
                case 0:
                    write(1, "(Unknown) ", 10);
                    break;
                case 1:
                    write(1, "(FIFO/pipe) ", 12);
                    break;
                case 2:
                    write(1, "(Character device) ", 19);
                    break;
                case 4:
                    write(1, "(Directory) ", 12);
                    break;
                case 6:
                    write(1, "(Block device) ", 15);
                    break;
                case 8:
                    write(1, "(Regular file) ", 15);
                    break;
                case 10:
                    write(1, "(Symbolic link) ", 16);
                    break;
                case 12:
                    write(1, "(Socket) ", 9);
                    break;
                case 14:
                    write(1, "(Whiteout) ", 11);
                    break;
                default:
                    write(1, "(Unknown)\n", 10);
                    break;
            }
        }
        write(1, "\n", 1);
    }
    closedir(directory);
    return 0;
}
