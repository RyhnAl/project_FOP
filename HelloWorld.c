#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    char commit[100];
    int flag_for_git_init = 0;
    while(1)
    {
        fgets(commit  , sizeof(commit) , stdin);
        // خارج شدن از برنامه
        if(strncmp(commit , "end" , 3) == 0)
        {
            return 0;
        }
        //neogit init
        if(strncmp(commit , "neogit init" , 11) == 0)
        {
            if(flag_for_git_init == 1)
            {
                printf("ERROR : You have a repository and you cannot rebuild it!\n");
                continue;
            }
            mkdir("neogit");
            printf("neogit init was successful\n");
            flag_for_git_init = 1;
        }
    }
}