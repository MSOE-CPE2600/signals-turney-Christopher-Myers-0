/**
 * File: signal_alarm.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Sets an alarm to go off after 5 seconds.
        Catches the SIGALRM with a signal handler and
        indicates the signal was recieved.
        Runs for a total of 10 seconds.
 */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handle_alarm();

int main(void) {

    signal(SIGALRM, handle_alarm);
    alarm(5);

    // Wait
    int i = 0;
    while(i < 10) {
        printf("Sleeping\n");
        sleep(1);
        i++;
    }
    
    return 0;
}

void handle_alarm() {
    printf("SIGALRM recieved\n");
}