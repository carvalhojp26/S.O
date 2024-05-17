#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
    int file;
    char buffer[BUFFER_SIZE];
    int line_count = 0;
    ssize_t read_size;
    char line_count_str[12];

    if(argc != 2) {
        write(STDERR_FILENO, "Wrong number of arguments\n", 27);
        return 1;
    }

    file = open(argv[1], O_RDONLY);

    if (file == -1) {
        write(STDERR_FILENO, "fail opening file\n", 18);
        return 0;
    };

    while ((read_size = read(file, buffer, BUFFER_SIZE)) > 0) {
        if (buffer[0] == '\n') {
        line_count++;
        }
    }

    int n = line_count, i = 0;
    if (n == 0) {
        line_count_str[i++] = '0';
    } else {
        while (n > 0) {
            line_count_str[i++] = (n % 10) + '0';
            n /= 10;
        }
    }

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = line_count_str[j];
        line_count_str[j] = line_count_str[k];
        line_count_str[k] = tmp;
    }

    line_count_str[i++] = '\n';

    write(STDOUT_FILENO, line_count_str, i);

    return 0;
}