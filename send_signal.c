/**
 * File: send_signal.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Takes one command line argument of a pid value.
        Then sends a SIGUSR1 signal with a random int value to the process.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    int pid;
    if(argc == 1) { // If no argument check for this process
        printf("Please enter a pid in the command argument\n");
        return -1;
    } else { // Parse the pid argument
        pid = strtol(argv[1], NULL, 10);
    }

    if(kill(pid, 0) == -1) {
        if(errno == ESRCH) {
            printf("This process does not exist\n");
        }
        return -1;
    } else {
        srand(time(NULL));
        const union sigval sendValue = {.sival_int = rand()};
        printf("Sent Value: %d\n", sendValue.sival_int);

        sigqueue(pid, SIGUSR1, sendValue);
    }

    return 0;
}