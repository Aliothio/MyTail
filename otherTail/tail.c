#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
#define MAX_LINES 100

void tail(const char *filename, int num_lines) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    char buffer[LINE_LENGTH];
    off_t offset = lseek(fd, 0, SEEK_END);
    int lines_read = 0;
    
    // Read file backwards to find the last lines
    for (off_t i = offset - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        read(fd, buffer, 1);
        
        if (buffer[0] == '\n') {
            lines_read++;
            if (lines_read > num_lines) {
                break;
            }
        }

        // Print the character (buffer[0]) if it's not the first line
        if (lines_read <= num_lines) {
            lseek(fd, i, SEEK_SET);
            read(fd, buffer, 1);
            write(STDOUT_FILENO, buffer, 1);
        }
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [num_lines]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int num_lines = (argc > 2) ? atoi(argv[2]) : 10;

    tail(filename, num_lines);
    return 0;
}
