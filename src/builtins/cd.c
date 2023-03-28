#include "../headers/cd.h"

int cd(char *path)
{
    if (!path)
    {
        chdir("/");
        return 0;
    }
    if (chdir(path) != 0)
    {
        return 4;
    }
    return 0;
}
