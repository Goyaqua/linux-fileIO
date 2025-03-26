#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sparse.txt", O_WRONLY | O_CREAT, 0644);
    lseek(fd, 1024 * 1024 * 1024, SEEK_SET);  // 1 GB file size
    write(fd, "X", 1); // write 1 byte to the end of the file
    close(fd); // close the file
    return 0;
}

// Compile:
// $ gcc sparse_file_example.c -o sparse_file_example
// Run:
// $ ./sparse_file_example
// Check the file size:
// $ ls -lh sparse.txt
// Check the disk usage:
// $ du -h sparse.txt

