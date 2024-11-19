/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Christopher Myers
 * 
 * Brief summary of modifications:
        Added a SIGSEGV handler function that prints
        that a SIGSEGV was recieved. This creates an infinite loop
        since the program returns from the handler and keeps trying to run
        the line of code that causes the segfault.
 */

#include <signal.h>
#include <stdio.h>

void handle_segv();

int main (int argc, char* argv[]) {

    signal(SIGSEGV, handle_segv);
    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}

void handle_segv() {
    printf("SIGSEGV recieved\n");
}