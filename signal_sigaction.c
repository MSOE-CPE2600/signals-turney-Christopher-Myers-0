/**
 * File: signal_sigaction.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Runs an infinite loop that prints out the pid 
        of any SIGUSR1 signal that it recieves.
        Use kill -SIGUSR1 'pid' to send the signal.
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_usr1(int sig, siginfo_t *info, void *context);

int main(void) {

    struct sigaction new_action;
    new_action.sa_flags = SA_SIGINFO;
    new_action.sa_sigaction = handle_usr1;

    sigaction(SIGUSR1, &new_action, NULL);

    // Infinite loop
    while(1) {
        sleep(1);
    }

    return 0;
}

void handle_usr1(int sig, siginfo_t *info, void *context) {
    printf("%d\n", info->si_pid);
}