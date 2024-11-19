/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Christopher Myers
 * 
 * Brief summary of modifications:

    Commented out the exit(1) in the handle_signal function

    Notes:
        Some ways of sending the SIGINT signal include:
        kill -SIGINT 'pid'
        CTRL + C
        These trigger the handle_signal function
            Commenting out the exit(1) means that any SIGINT signal won't
        actually stop the program, and it continues saying sleeping after
        CTRL + C or kill -SIGINT 'pid'. Both kill 'pid' and kill -SIGKILL 'pid'
        seem to stop the program.
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Signal handler for SIGINT - prints a message
 */
void handle_signal() {
    printf("Received a signal\n");
    //exit(1);
}

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}