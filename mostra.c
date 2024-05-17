#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int file;
    ssize_t read_size;
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        write(STDERR_FILENO, "insuficient arguments\n", 22);
        return 0;
    };

    for (int i=1; i < argc; i++) {
        file = open(argv[i], O_RDONLY);

        if (file == -1) {
            write(STDERR_FILENO, "fail opening file\n", 18);
            return 0;
        };

        while((read_size = read(file, buffer, BUFFER_SIZE)) > 0) {
            if(read_size == -1) {
                write(STDERR_FILENO, "fail reading file\n", 18);
                return 0;
            }

            write(STDOUT_FILENO, buffer, read_size);
        };
    };

    return 1;
}
