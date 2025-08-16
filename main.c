#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

/* This code reads the /proc filesystem to list all running processes along with their command lines.
It checks each directory in /proc to see if it is a PID (a number)
and then reads the corresponding cmdline file to get the command line used to start the process.
The command lines are printed with the PID in a formatted output.
The code handles errors in opening the /proc directory and reading cmdline files gracefully.
The output is formatted to show the PID and command line in a readable manner.
The program is designed to run on Unix-like systems where the /proc filesystem is available.
It is a simple utility that can be used for process monitoring or debugging purposes.
The code is written in C and adheres to the C17 standard, ensuring compatibility with modern C compilers.
It is efficient and straightforward, focusing on clarity and functionality.  */


/**
 * Checks if a given string is a number.
 *
 * @param str The string to be checked.
 * @return 1 if the string is a number, 0 otherwise.
 */
int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}


/**
 * Main function that reads PIDs and command lines from /proc and prints them.
 *
 * @return 0 if successful, 1 if there was an error opening /proc.
 */
int main() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("Failed to open /proc");
        return 1;
    }
    struct dirent *entry;

    if (!proc) {
        perror("opendir /proc");
        return 1;
    }

    printf("%5s %s\n", "PID", "CMD");

    while ((entry = readdir(proc)) != NULL) {
        // Get the directories named with numbers (PIDs)
        if (is_number(entry->d_name)) {
            char cmdline_path[256];
            FILE *cmdline_file;
            char cmdline[1024];

            snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);
            cmdline_file = fopen(cmdline_path, "r");
            if (cmdline_file) {
                if (fgets(cmdline, sizeof(cmdline), cmdline_file)) {
                    // cmdline is null-separated, replace with spaces
                    for (int i=0; i < strlen(cmdline); i++) {
                        if (cmdline[i] == '\0') cmdline[i] = ' ';
                    }
                    printf("%5s %s\n", entry->d_name, cmdline);
                }
                fclose(cmdline_file);
            }
        }
    }

    closedir(proc);
    return 0;
}

