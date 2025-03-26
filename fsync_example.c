#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd = open("ver.txt", O_WRONLY | O_CREAT, 0644);

    if (fd < 0) {
        perror("File could not be opened");
        return 1;
    }

    const char *ver = "Data is written to dis.\n"; 
    write(fd, ver, strlen(ver)); // write the data to the file

    if (fsync(fd) < 0) { // write the data to the disk
        perror("fsync failed");
    }

    close(fd);
    return 0;
}
