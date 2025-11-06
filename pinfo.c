/**
* @file pinfo.c
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
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

// Function to convert scheduler policy number to string
const char* get_scheduler_name(int policy) {
    switch(policy) {
        case SCHED_OTHER:
            return "SCHED_OTHER (normal time-sharing)";
        case SCHED_FIFO:
            return "SCHED_FIFO (real-time FIFO)";
        case SCHED_RR:
            return "SCHED_RR (real-time round-robin)";
        case SCHED_BATCH:
            return "SCHED_BATCH (batch processing)";
        case SCHED_IDLE:
            return "SCHED_IDLE (very low priority)";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;
    int priority;
    int scheduler;
    
    // Determine process
    if (argc == 1) {
        // No argument provided
        pid = getpid();
        printf("No process ID specified. Using current process (PID: %d)\n\n", pid);
    } else if (argc == 2) {
        // Convert argument to process ID
        pid = atoi(argv[1]);
        if (pid <= 0) {
            fprintf(stderr, "Error: Invalid process ID '%s'\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return 1;
    }
    
    // Get process priority
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        fprintf(stderr, "Error: Could not get priority for process %d: %s\n", 
                pid, strerror(errno));
        if (errno == ESRCH) {
            fprintf(stderr, "Process %d does not exist.\n", pid);
        }
        return 1;
    }
    
    // Get scheduling method
    scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        fprintf(stderr, "Error: Could not get scheduler for process %d: %s\n", 
                pid, strerror(errno));
        if (errno == ESRCH) {
            fprintf(stderr, "Process %d does not exist.\n", pid);
        }
        return 1;
    }
    
    // Print the information
    printf("Process Information for PID %d:\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduling Method: %s\n", get_scheduler_name(scheduler));
    
    return 0;
}