/**
 * File: recv_signal.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Runs an infinite loop.
        When it recieves a SIGUSR1 signal it prints out the sival_int
        recieved from the signal and continues running.

 */

#include <stdio.h>
#include <signal.h>
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
    printf("%d\n", info->si_value.sival_int);
}