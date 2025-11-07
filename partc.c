#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    // TODO: Complete and document
     if (argc != 3) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process: run grep
        char* args[] = {"grep", "-s", "-q", (char*)argv[1], (char*)argv[2], NULL};
        execv("/usr/bin/grep", args);
        perror("exec grep");
        exit(1);
    } else {
        // Parent process: wait for child
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf("FOUND: %s\n", argv[1]);
                return 0;
            } else if (exit_code == 1) {
                printf("NOT FOUND: %s\n", argv[1]);
                return 0;
            } else if (exit_code == 2) {
                printf("ERROR: %s doesn't exist\n", argv[2]);
                return 2;
            }
        }
    }
    return 0;
}
