#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>

int main() {
    // 3 parts of the message buffer
    const char *parts[] = {
        "Hello World!\n",
        "Something beautiful is going to happen.\n",
        "This example uses writev.\n"
    };
    // iovec structure array
    struct iovec iov[3];
    for (int i = 0; i < 3; i++) {
        iov[i].iov_base = (void*) parts[i]; // cast to void* because iov_base is void*
        iov[i].iov_len = strlen(parts[i]); // length of the message
    }

    // open file for writing, write only, create if not exists, truncate if exists
    int fd = open("writev_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // write the message buffer array to the file
    ssize_t written = writev(fd, iov, 3);
    if (written < 0) {
        perror("writev");
        return 1;
    }

    // print the total byte written
    printf("Total %ld byte is written.\n", written);
    close(fd);
    return 0;
}