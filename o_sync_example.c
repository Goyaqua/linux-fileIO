#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// O_SYNC flag is used to write data synchronously
int main() {
    // open file for writing, create if not exists, write only, synchronous write always
    int fd = open("sync_yazi.txt", O_WRONLY | O_CREAT | O_SYNC, 0644); 
    if (fd < 0) {
        perror("Dosya açılamadı");
        return 1;
    }

    const char *veri = "Senkronize yazma denemesi.\n"; // synchronous write test
    write(fd, veri, strlen(veri)); // write the data to the file

    close(fd);
    return 0;
}
