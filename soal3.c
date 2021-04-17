#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

void killer(char arr[]);
int main(int argc, char *argv[])
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
    killer(argv[1]);
    sid = setsid();
    
    if(sid < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    while(1)
    {
        pid_t child_id;
        int status;
        child_id = fork();
        time_t raw;
        struct tm *timeinfo;
        char tanggal[40];
        time(&raw);
        timeinfo = localtime(&raw);
        strftime(tanggal, sizeof(tanggal), "%Y-%m-%d_%H:%M:%S", timeinfo); // format penamaan folder sesuai dengan waktu saat folder tersebut berjalan
        
        if(child_id < 0)
        {
            exit(EXIT_FAILURE);
        }
        if(child_id == 0)
        {
            char *argv[4] = {"mkdir", "-p", tanggal, NULL};
            execv("/bin/mkdir", argv);
        }
        else
        {
            while((wait(&status)) > 0);
            pid_t child_id_2;
            int i = 0;
            child_id_2 = fork();
            
            if(child_id_2 == 0)
            {
                for(i = 1; i <= 10; i++)
                {
                    time_t raw2;
                    struct tm *timeinfo2;
                    char tanggal2[40];
                    time(&raw2);
                    timeinfo2 = localtime(&raw2);
                    strftime(tanggal2, sizeof(tanggal2), "%Y-%m-%d_%H:%M:%S", timeinfo2); // format penamaan file gambar yang telah di download sesuai dengan waktu pada saat mendownload
                    
                    char alamat[50];
                    sprintf(alamat, "https://picsum.photos/%ld", ((raw2 % 1000) + 50)); // link gambar beserta ukurannya
                    pid_t child_id_3;
                    child_id_3 = fork();
                    
                    if(child_id_3 == 0)
                    {
                        chdir(tanggal);
                        execl("/usr/bin/wget", "wget", "-O", tanggal2, alamat, NULL);
                    }
                    sleep(5); // gambar di download tiap 5 detik
                }
                char zip[50]; // untuk mengubah folder menjadi bentuk zip
                sprintf(zip, "%s.zip", tanggal);
                char *argv2[5] = {"zip", "-rm", zip, tanggal, NULL};
                execv("/usr/bin/zip", argv2);
            }
        }
        // program berjalan setiap 40 detik
        sleep(40);
    }
}

void killer(char arr[])
{
    FILE *kill;
    kill = fopen("killer.sh", "w");
    if(strcmp(arr, "-z") == 0)
        fprintf(kill, "rm $0\n#!/bin/bash\nkill -9 -%d", getpid());
    else if(strcmp(arr, "-x") == 0)
        fprintf(kill, "rm $0\n#!/bin/bash\nkill %d", getpid());
    fclose(kill);
}
