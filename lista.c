#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
    DIR *directory;
    struct dirent *dir;

    directory = opendir(argv[1]);

    readdir(directory);
    if (directory) {
        while ((dir = readdir(directory)) != NULL) {
            printf("%s ", dir->d_name);
            switch (dir->d_type) {
                case 0:
                    printf("(Unknown) ");
                    break;
                case 1:
                    printf("(FIFO/pipe) ");
                    break;
                case 2:
                    printf("(Character device) ");
                    break;
                case 4:
                    printf("(Directory) ");
                    break;
                case 6:
                    printf("(Block device) ");
                    break;
                case 8:
                    printf("(Regular file) ");
                    break;
                case 10:
                    printf("(Symbolic link) ");
                    break;
                case 12:
                    printf("(Socket) ");
                    break;
                case 14:
                    printf("(Whiteout) ");
                    break;
                default:
                    printf("(Unknown)\n");
                    break;
            }
        }
        printf("\n");
    }
    //printf("abri\n");
    closedir(directory);
    //printf("fechei\n");
    return 0;
}
