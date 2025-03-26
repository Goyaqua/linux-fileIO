#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>

int main() {
    char header[32];
    char body[128];

    struct iovec iov[2];
    iov[0].iov_base = header;
    iov[0].iov_len = sizeof(header) - 1;
    iov[1].iov_base = body;
    iov[1].iov_len = sizeof(body) - 1;

    int fd = open("writev_output.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    ssize_t read_bytes = readv(fd, iov, 2);
    if (read_bytes < 0) {
        perror("readv");
        return 1;
    }

    header[iov[0].iov_len] = '\0';
    body[iov[1].iov_len] = '\0';

    printf("Title: %s\n", header);
    printf("Content: %s\n", body);

    close(fd);
    return 0;
}
