#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
    if(argc != 2) {
        write(STDERR_FILENO, "Wrong number of arguments\n", 27);
        return 1;
    }

    if (unlink(argv[1]) == -1) {
        write(STDERR_FILENO, "fail deleting file\n", 20);
        return 1;
    }

    return 0;
}