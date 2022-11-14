#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int find_size(char *dir)
{
    int size = 0;
    struct stat finfo;
    struct dirent *de;

    DIR *d = opendir(dir);
    if (d == NULL)
    {
        perror(dir);
        exit(1);
    }

    for (de = readdir(d); de != NULL; de = readdir(d))
    {
        if (strcmp(de->d_name, "..") == 0)
        {
            continue;
        }

        if (stat(de->d_name, &finfo) != 0)
        {
            perror(de->d_name);
            continue;
        }

        if (S_ISDIR(finfo.st_mode) && (strcmp(de->d_name, ".") != 0))
        {
            size += find_size(de->d_name);
        }
        size += finfo.st_size;
    }
    if (closedir(d) != 0)
    {
        perror("closedir");
    }

    return size;
}

int main()
{
    printf("%d\n", find_size("."));
    return 0;
}
