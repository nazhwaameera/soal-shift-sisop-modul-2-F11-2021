#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

char *drive[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};

char *dir[] = {"/home/nazhwaameera/Praktikum/Musyik", "/home/nazhwaameera/Praktikum/Fylm", "/home/nazhwaameera/Praktikum/Pyoto"};

char *xtrctd[] = {"/home/nazhwaameera/Praktikum/MUSIK", "/home/nazhwaameera/Praktikum/FILM", "/home/nazhwaameera/Praktikum/FOTO"};

char *nama[] = {"Musyik", "Fylm", "Pyoto", "MUSIK", "FILM", "FOTO"};

char *dwnld[] = {"mp3.zip", "mp4.zip", "jpg.zip"};

void createDir()
{
    pid_t stepcreate;
    int statuscreate;
    
    stepcreate = fork();
    
    if(stepcreate < 0) exit(EXIT_FAILURE);
    
    if(stepcreate == 0)
    {
        char *argv[] = {"mkdir", "-p", nama[0], nama[1], nama[2], NULL};
        execv("/usr/bin/mkdir", argv);
    }
    else
    {
        while((wait(&statuscreate)) > 0);
        return;
    }
}

void extractZip(int i)
{
    pid_t stepextract;
    int statusextract;
    
    stepextract = fork();
    
    if(stepextract < 0) exit(EXIT_FAILURE);
    
    if(stepextract == 0)
    {
        char *argv[] = {"unzip", dwnld[i], NULL};
        execv("/usr/bin/unzip", argv);
    }
    else
    {
        while((wait(&statusextract)) > 0);
        return;
    }
}

void move(int isFolder)
{
    pid_t stepmove;
    int statusmove;
    
    stepmove = fork();
    
    if(stepmove < 0) exit(EXIT_FAILURE);
    
    if(stepmove == 0)
    {
        char *argv[] = {"find", xtrctd[isFolder-1], "-type", "f", "-exec", "mv", "{}", dir[isFolder-1], ";", NULL};
        execv("/usr/bin/find", argv);
    }
    else
    {
        while((wait(&statusmove)) > 0);
        return;
    }
}

void Download(int download)
{
    pid_t stepdownload;
    int statusdownload;
    
    stepdownload = fork();
    
    if(stepdownload < 0) exit(EXIT_FAILURE);
                
    if(stepdownload == 0)
    {
        char *argv[] = {"wget", "-q", "--no-check-certificate", drive[download-1], "-O", dwnld[download-1], NULL};
        execv("/usr/bin/wget", argv);
    }
    else
    {
        while((wait(&statusdownload)) > 0);
        return;
    }
}

void function1()
{
    int i;
    createDir();
    for(i = 1; i <= 3; i++)
    {
        Download(i);
        extractZip(i);
        move(i);
    }
}

void function2()
{
    pid_t function2;
    int statusfunction2;
            
    function2 = fork();
            
    if(function2 < 0) exit(EXIT_FAILURE);
            
    if(function2 == 0)
    {
        pid_t step9;
        int status9;
                
        step9 = fork();
                
        if(step9 < 0) exit(EXIT_FAILURE);
                        
        if(step9 == 0) // zip folder Lopyu_Stefany
        {
            char *argv[] = {"zip", "-mr", "/home/nazhwaameera/Praktikum/Lopyu_Stevany", nama[0], nama[1], nama[2], NULL};
            execv("/usr/bin/zip", argv);
        }
        else // remove folder
        {
            while((wait(&status9)) > 0);
            char *argv[] = {"rm", "-r", nama[3], nama[4], nama[5], NULL};
            execv("/usr/bin/rm", argv);
        }
    }
    else
    {
        while((wait(&statusfunction2)) > 0);
        return;
    }
}

int main()
{
    pid_t pid, sid;
    pid = fork();
    
    if(pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if(pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    umask(0);
    sid = setsid();
    
    if(sid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if((chdir("/home/nazhwaameera/Praktikum")) < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    while(1)
    {
        time_t waktu;
        struct tm* tm_now;
        waktu = time(NULL);
        tm_now = localtime(&waktu);
        
        if(tm_now->tm_mon == 3 && tm_now->tm_mday == 9 && tm_now->tm_hour == 16 && tm_now->tm_min == 22 && tm_now->tm_sec == 0)
        {
            function1();
        }
        else if(tm_now->tm_mon == 3 && tm_now->tm_mday == 9 && tm_now->tm_hour == 22 && tm_now->tm_min == 22 && tm_now->tm_sec == 0)
        {
            function2();
        }
    }
    sleep(1);
}
