#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    int mid = (argc - 1) / 2;
    char* args[5]; // max 4 + NULL

    if ((argc - 1) % 2 == 0) { // even number of args
        args[0] = "echo";
        args[1] = (char*)argv[mid];
        args[2] = (char*)argv[mid + 1];
        args[3] = NULL;
    } else { // odd number of args
        args[0] = "echo";
        args[1] = (char*)argv[mid + 1];
        args[2] = NULL;
    }

    execv("/bin/echo", args);

    perror("exec failed");
    return 1;
}
