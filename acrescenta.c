#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int original_file, copied_file;
    ssize_t read_size;
    char buffer[BUFFER_SIZE];

    if (argc < 3) {
        write(STDERR_FILENO, "insuficient arguments\n", 22);
        return 0;
    };

    for (int i=2; i < argc; i++) {
        original_file = open(argv[1], O_RDONLY);

        if (original_file == -1) {
            write(STDERR_FILENO, "fail opening file\n", 18);
            return 0;
        };

        copied_file = open(argv[i], O_WRONLY);

        if (copied_file == -1) {
            write(STDERR_FILENO, "fail opening file\n", 18);
            return 0;
        };

        while((read_size = read(original_file, buffer, read_size)) > 0)  {
            if(read_size == -1) {
                write(STDERR_FILENO, "fail reading file\n", 18);
                return 0;
            }

            write(copied_file, buffer, read_size);
        }
    };

    return 1;
};