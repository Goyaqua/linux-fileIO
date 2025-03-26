#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>

int main() {
    struct pollfd fds[2]; // 2 file descriptors

    fds[0].fd = 0; // stdin
    fds[0].events = POLLIN; // POLLIN: data to read

    int pipe_fd = open("pipe", O_RDONLY | O_NONBLOCK); // open pipe for reading only, non-blocking
    if (pipe_fd < 0) {
        perror("pipe could not be opened");
        return 1;
    }

    fds[1].fd = pipe_fd; // pipe
    fds[1].events = POLLIN; // POLLIN: data to read

    printf("Waiting for data from keyboard or pipe...\n"); // waiting for data from keyboard or pipe

    while (1) { // infinite loop
        int ret = poll(fds, 2, -1); // wait indefinitely

        if (ret < 0) {
            perror("poll error");
            break;
        }

        if (fds[0].revents & POLLIN) { // if there is data to read from stdin
            char input[128];
            int n = read(0, input, sizeof(input) - 1); // read from stdin
            input[n] = '\0';
            printf("[Keyboard]: %s", input); // print the input
            if (strncmp(input, "exit", 4) == 0) break; // if the input is "exit", break the loop
        }

        if (fds[1].revents & POLLIN) { // if there is data to read from pipe
            char pipe_input[128]; 
            int n = read(pipe_fd, pipe_input, sizeof(pipe_input) - 1); // read from pipe
            pipe_input[n] = '\0';
            printf("[Pipe]: %s", pipe_input); // print the input
        }
    }

    close(pipe_fd);
    return 0;
}
