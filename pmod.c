/**
* @file pmod.c
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 9
* Name: Megan Cranston
*
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(void) {
    int result;
    struct timespec sleep_time;
    
    printf("Current PID: %d\n\n", getpid());
    
    // Reduce priority by 10
    result = nice(10);
    if (result == -1 && errno != 0) {
        fprintf(stderr, "Error: Could not modify priority: %s\n", strerror(errno));
        return 1;
    }
    printf("New nice value: %d\n", result);
    
    // Sleep for 1,837,272,638 nanoseconds
    sleep_time.tv_sec = 1;  // 1 second
    sleep_time.tv_nsec = 837272638;  // 837,272,638 nanoseconds
    
    printf("Sleeping for 1,837,272,638 nanoseconds...\n");
    
    result = nanosleep(&sleep_time, NULL);
    if (result == -1) {
        fprintf(stderr, "Error: nanosleep failed: %s\n", strerror(errno));
        return 1;
    }
    
    printf("\nGoodbye!\n");
    
    return 0;
}