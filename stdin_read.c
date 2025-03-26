#include <unistd.h>
#include <stdio.h>

// read from stdin(keyboard) and print the input
int main() {
    char buffer[128];

    ssize_t reading = read(0, buffer, sizeof(buffer) - 1); // read from stdin

    if (reading < 0) {
        perror("read failed");
        return 1;
    }

    buffer[reading] = '\0'; // null-terminate the string
    printf("Entered:\n%s", buffer); // print the input to the console from buffer

    return 0;
}
