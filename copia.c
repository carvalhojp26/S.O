#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int original_file, copied_file;
    ssize_t read_size;
    char buffer[BUFFER_SIZE];
    char newFile[1024];

    if (argc != 2) {
        write(STDERR_FILENO, "insuficient arguments\n", 22);
        return 0;
    };

    original_file = open(argv[1], O_RDONLY);
    
    if (original_file == -1) {
        write(STDERR_FILENO, "fail opening file\n", 18);
        return 0;
    };

        int i;
    for (i = 0; argv[1][i] != '\0'; i++) {
        newFile[i] = argv[1][i];
    }
    newFile[i++] = '.';
    newFile[i++] = 'c';
    newFile[i++] = 'o';
    newFile[i++] = 'p';
    newFile[i++] = 'i';
    newFile[i++] = 'a';
    newFile[i] = '\0';

    copied_file = open(newFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);

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

    return 1;
};