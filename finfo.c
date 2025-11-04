/**
* @file finfo.c
*
* Course: CPE2600
* Section: 111
* Assignment: Lab 9
* Name: Megan Cranston
*
*/

#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // check for filename argument
    if (argc != 2) {
        printf("Error: No filename entered\n");
        return 0;
    }

    char *filename = argv[1];
    struct stat info;

    if (stat(filename, &info) != 0) {
        printf("Error getting file information\n");
        return 0;
    }
    
    // File type (regular file, directory, symbolic link, etc.)
    if (S_ISREG(info.st_mode)) printf("File type: Regular\n");
    else if (S_ISDIR(info.st_mode)) printf("File type: Directory\n");
    else if (S_ISCHR(info.st_mode)) printf("File type: Character Device\n");
    else if (S_ISBLK(info.st_mode)) printf("File type: Block Device\n");
    else if (S_ISFIFO(info.st_mode)) printf("File type: FIFO\n");
    else if (S_ISLNK(info.st_mode)) printf("File type: Symbolic Link\n");
    else if (S_ISSOCK(info.st_mode)) printf("File type: Socket\n");
    else printf("Error: File type not available\n");

    // File permissions (read/write/execute for user, group, others)
    if (info.st_mode & S_IRUSR) printf("Permission type: User, Read\n");
    else if (info.st_mode & S_IWUSR) printf("Permission type: User, Write\n");
    else if (info.st_mode & S_IXUSR) printf("Permission type: User, Execute\n");
    else if (info.st_mode & S_IRGRP) printf("Permission type: Group, Read\n");
    else if (info.st_mode & S_IWGRP) printf("Permission type: Group, Write\n");
    else if (info.st_mode & S_IXGRP) printf("Permission type: Group, Execute\n");
    else if (info.st_mode & S_IROTH) printf("Permission type: Other, Write\n");
    else if (info.st_mode & S_IWOTH) printf("Permission type: Other, Read\n");
    else if (info.st_mode & S_IXOTH) printf("Permission type: Other, Execute\n");
    else printf("Error: Permission type not available\n");

    // File owner UID
    if (info.st_uid) printf("Owner UID: %d\n", info.st_uid);
    else printf("Error: Owner UID not found\n");
    
    // File size in bytes
    if (info.st_size) printf("File size: %ld bytes\n", info.st_size);
    else printf("Error: File size not found\n");

    // File last modification time (formatted nicely)
    char timebuf[64];
    struct tm *tm_info = localtime(&info.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    if (tm_info) printf("Last modified: %s\n", timebuf);
    else printf("Error: Last modification time not found\n");

    return 0;
}