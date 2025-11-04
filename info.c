/**
* @file info.c
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 9
* Name: Megan Cranston
*
*/
#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>
 
int main(int argc, char* argv[])
{
    struct timespec ts;
    struct utsname sys;
 
    // The current time of day - in nanoseconds
    int clock_time = clock_gettime(CLOCK_REALTIME, &ts);
    if (clock_time != 0) {
        printf("Error getting time\n");
    } else {
        printf("Current time of day: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
    }
 
    // The system's network name
    // The operating system name
    // The operating system release and version
    // The system's hardware type
    if (uname(&sys) != 0) {
        printf("Error getting system information\n");
    } else {
        if (sys.nodename[0]) printf("Network Name: %s\n", sys.nodename);
        else printf("Error: Network name not available\n");
       
        if (sys.sysname[0]) printf("OS Name: %s\n", sys.sysname);
        else printf("Error: OS name not available\n");
       
        if (sys.release[0]) printf("OS Release: %s\n", sys.release);
        else printf("Error: OS release not available\n");
       
        if (sys.version[0]) printf("OS Version: %s\n", sys.version);
        else printf("Error: OS version not available\n");
       
        if (sys.machine[0]) printf("Hardware Type: %s\n", sys.machine);
        else printf("Error: Hardware type not available\n");
    }
 
    // The number of CPUs on the system
    int num_cpus = get_nprocs();
    if (num_cpus <= 0) {
        printf("Error: Could not get number of CPUs\n");
    } else {
        printf("Num CPUs: %d\n", num_cpus);
    }
 
    // The total amount of physical memory IN BYTES
    // The total amount of free memory IN BYTES
    long page_size = sysconf(_SC_PAGESIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long free_pages = sysconf(_SC_AVPHYS_PAGES);
 
    if (page_size == -1 || total_pages == -1 || free_pages == -1) {
        printf("Error: Could not get memory information\n");
    } else {
        unsigned long long total_bytes = (unsigned long long)total_pages * page_size;
        unsigned long long free_bytes = (unsigned long long)free_pages * page_size;
        printf("Total physical memory: %llu bytes\n", total_bytes);
        printf("Free physical memory:  %llu bytes\n", free_bytes);
    }
 
    return 0;
}