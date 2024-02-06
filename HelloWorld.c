#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void delete_cotation(char* word)
{
    int indx = 0;
    char new_word[50];
    int num = strlen(word);
    for(int i=0 ; i<=num ; i++)
    {
        if(word[i] != '"')
        {
            new_word[indx] = word[i];
            indx++;
        }
    }
    strcpy(word , new_word);
}

int main()
{
    char commit[100];
    int flag_for_git_init = 0;
    int flag_config_global_name = 0;
    int flag_config_global_email = 0;
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
        // neogit config
        if (strncmp(commit, "neogit config -global user.", 27) == 0)
        {
            if(flag_for_git_init == 0)
            {
                printf("ERROR : You have not created a repository!\n");
                continue;
            }
            char NameOrEmail[50];
            char name_email[50];
            sscanf(commit, "neogit config -global user.%s %s", NameOrEmail, name_email);
            delete_cotation(name_email); 
            if (strcmp(NameOrEmail, "name") == 0)
            {
                if (flag_config_global_name == 1)
                {
                    printf("ERROR: you cannot set a new name for your project!\n");
                    continue;
                }
                FILE* file = fopen("config.txt", "a"); 
                fprintf(file, "username : %s\n", name_email);
                fclose(file);
                flag_config_global_name = 1;
            }
            else if (strcmp(NameOrEmail, "email") == 0)
            {
                if (flag_config_global_email == 1)
                {
                    printf("ERROR: you cannot set a new email for your project!\n");
                    continue;
                }
                FILE* file = fopen("config.txt", "a"); 
                fprintf(file, "useremail : %s\n", name_email);
                fclose(file);
                flag_config_global_email = 1;
            }
        }
        if(strncmp(commit , "neogit config user." , 19) == 0)
        {
            if(flag_for_git_init == 0)
            {
                printf("ERROR : You have not created a repository!\n");
                continue;
            }
            char NameOrEmail[50];
            char name_email[50];
            sscanf(commit , "neogit config user.%s %s" ,NameOrEmail ,name_email);
            delete_cotation(name_email);
            if(strcmp(NameOrEmail, "name") == 0)
            {
                FILE* file = fopen("config.txt", "a"); 
                fprintf(file, "username : %s\n", name_email);
                fclose(file);
            }
            else if(strcmp(NameOrEmail , "email") == 0)
            {
                FILE* file = fopen("config.txt", "a"); 
                fprintf(file, "useremail : %s\n", name_email);
                fclose(file);
            }
        }
    }
}