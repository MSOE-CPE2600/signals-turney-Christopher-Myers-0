/**
 * File: recv_ball.c
 * Modified by: Christopher Myers
 * 
 * Brief summary of program:
        Start this first. Note the pid it prints.
        Then start send_ball.out with the pid as a command line argument.

        Simulates a game of ping pong. First to 11
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void handle_ball(int sig, siginfo_t *info, void *context);

 int main(void) {

    // Prepare for 'ball' signal
    printf("PID: %d\n", getpid());

    struct sigaction ball;
    ball.sa_flags = SA_SIGINFO;
    ball.sa_sigaction = handle_ball;

    sigaction(SIGUSR1, &ball, NULL);

    // Infinite loop
    while(1) {
        usleep(200);
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
    printf("Player2:\n");
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

    // srand(time(NULL));
    // int randValue = 1E6 + rand()%(int)(1E6);
    // printf("\tHit Time: %f\n", randValue/1E6);
    // usleep(randValue);

    // info->si_value.sival_int++;
    // const union sigval sendValue = {.sival_int = info->si_value.sival_int};
    // sigqueue(info->si_pid, SIGUSR1, sendValue);

    // if(info->si_value.sival_int >= 9) {
    //     exit(1);
    // }
}