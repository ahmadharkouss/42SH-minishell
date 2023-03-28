#define _POSIX_C_SOURCE 200809L
#include "../headers/kill.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kill_command(char **argv)
{
    // Check arguments
    if (argv[1] == NULL)
    {
        fprintf(stderr,
                "kill: usage: kill [-s sigspec | -n signum | -sigspec] pid | "
                "jobspec ... or kill -l [sigspec]\n");
        return 1;
    }
    int sig = SIGTERM; // default signal
    int i = 1;
    if (argv[1][0] == '-')
    {
        // Parse signal option
        sig = atoi(argv[1] + 1);
        if (sig == 0)
        {
            fprintf(stderr, "kill: invalid signal '%s'\n", argv[1]);
            free(argv);
            return 1;
        }
        i++;
    }
    // Send signal to each PID
    while (argv[i] != NULL)
    {
        int pid = atoi(argv[i]);
        if (pid == 0)
        {
            fprintf(stderr, "kill: invalid PID '%s'\n", argv[i]);
            free(argv);
            return 1;
        }
        if (kill(pid, sig) == -1)
        {
            fprintf(stderr, "kill: %s\n", strerror(errno));
            free(argv);
            return 1;
        }
        i++;
    }
    free(argv);
    return 0;
}
