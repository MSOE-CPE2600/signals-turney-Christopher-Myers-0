/**
 * File: send_ball.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Start this after recv_ball.out. Use the pid listed
        there as a command line argument when running this program.

        Simulates a game of ping pong. First to 11
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

void handle_ball(int sig, siginfo_t *info, void *context);

int main(int argc, char *argv[]) {

    int pid;
    if(argc == 1) { // If no argument check for this process
        printf("Please enter a pid in the command argument\n");
        return -1;
    } else { // Parse the pid argument
        pid = strtol(argv[1], NULL, 10);
    }

    if(kill(pid, 0) == -1) { // Attempt to find the process
        if(errno == ESRCH) {
            printf("This process does not exist\n");
        }
        return -1;
    } else { // Run if process found

        // Prepare for ball signal
        struct sigaction ball;
        ball.sa_flags = SA_SIGINFO;
        ball.sa_sigaction = handle_ball;

        sigaction(SIGUSR1, &ball, NULL);


        printf("Player1:\n");
        printf("\tHit Number: %d\n\n", 0);
        const union sigval sendValue = {.sival_int = 0};
        sigqueue(pid, SIGUSR1, sendValue);

        while(1) { // Infinite Loop
            usleep(200);
        }
    }

    return 0;
}

void handle_ball(int sig, siginfo_t *info, void *context) {

    static int ownScore = 0;
    static int opponentScore = 0;

    if(info->si_value.sival_int == -1) {
        ownScore++;
        //info->si_value.sival_int = 0;
        printf("Opponent MISSED\n");
        printf("\tOwn Score: %d\n", ownScore);
        printf("\tOpponent Score: %d\n", opponentScore);
        if(ownScore >= 11) {
            exit(1);
        }
    }

    info->si_value.sival_int++;
    // Print INFO
    printf("Player1:\n");
    printf("\tHit Number: %d\n", info->si_value.sival_int);

    // Attempt hit
    //srand(time(NULL));
    int chance = rand()%100;
    //printf("%d\n", chance);
    if(chance < 75) { // 75 percent chance to hit
        int randTime = 1E6 + rand()%(int)(1E6);
        printf("\tHit Time: %f\n", randTime/1E6);
        usleep(randTime);
        const union sigval sendValue = {.sival_int = info->si_value.sival_int};
        sigqueue(info->si_pid, SIGUSR1, sendValue);
    } else { // Otherwise send miss info to other player
        opponentScore++;
        printf("\tMISSED\n");
        printf("\tOwn Score: %d\n", ownScore);
        printf("\tOpponent Score: %d\n", opponentScore);
        const union sigval sendValue = {.sival_int = -1};
        sigqueue(info->si_pid, SIGUSR1, sendValue);
        if(opponentScore >= 11) {
            exit(1);
        }
    }

    printf("\n");

    // if(info->si_value.sival_int >= 9) {
    //     exit(1);
    // }
}