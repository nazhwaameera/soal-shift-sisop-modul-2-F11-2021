#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
 

 

void makedire(char base[])
{
    pid_t child_id;
    int fl;
 
    child_id=fork();
 
    if(child_id==0)
    {
         char *folder[]={"mkdir","-p",base,NULL};
        execv("/bin/mkdir", folder);
    }
 
    else
    {
        while ((wait(&fl))>0);
    }
}

void unzippers(char source[],char dest[])
{
    pid_t child_id;
    int fl;
 
    child_id=fork();
 
    if(child_id==0)
    {
         char *unzipper[] = {"unzip","-q",source,"-x","*/*","-d",dest,NULL};
        execv("/bin/unzip", unzipper);
    }
 
    else
    {
        while ((wait(&fl))>0);
    }
}


void cpy(char source[],char dest[])
{
    pid_t child_id;
    int fl;
 
    child_id=fork();
 
    if(child_id==0)
    {
         char *movetofolder[]={"cp","-r", source, dest, NULL};
                        execv("/bin/cp",movetofolder);
    }
 
    else
    {
        while ((wait(&fl))>0);
    }
}


void ren(char pertama[],char terakhir[])
{
    pid_t child_id;
    int fl;
 
    child_id=fork();
 
    if(child_id==0)
    {
        char *rename[]={"mv",pertama,terakhir,NULL};
        execv("/bin/mv",rename);
    }
 
    else
    {
        while ((wait(&fl))>0);
    }
}

void rem(char source[])
{
    pid_t child_id;
    int fl;
 
    child_id=fork();
 
    if(child_id==0)
    {
        char *removefile[]={"rm","-rf",source,NULL};
        execv("/bin/rm",removefile);
    }
 
    else
    {
        while ((wait(&fl))>0);
    }
}


char* cutter (char* string){
    char* hasil;
    int i;
    int n;
    for (i = 0; string[i] != '\0'; i++);
    // lenght of the new string
    n = i - 4 + 1;
    if (n < 1)
        return NULL;
    hasil = (char*) malloc (n * sizeof(char));

    i=0;
    while(i<n-1){
        hasil[i] = string[i];
        i++;
    }

   
    hasil[i] = '\0';
    return hasil;
} 
void unzip(char dest[],char source[])
{   
    int fl;
    pid_t child_id;
    child_id = fork();
    
    
 
    if(child_id<0)
    {
       exit(EXIT_FAILURE); 
    }
 
    if (child_id==0)
    {
        
       
        makedire(dest);
    }
 
    else {
        while ((wait(&fl))>0);
        
        unzippers(source,dest);
        
    }
}
 
void BCDE(char dest[])
{
    pid_t child;
    child= fork();
    
    
    char path[100] ;
    strcpy(path,dest);
    int kons;
    if(child<0)
    {
       exit(EXIT_FAILURE); 
    }
 
    if (child==0)
    {
    DIR *dp;
    
    dp = opendir(path);
        if (dp != NULL)
        {
            struct dirent *ep;
            while((ep = readdir(dp))!= NULL)
            {   
                if(ep->d_type == DT_REG)
                {
                    
                    char *sem1,*sem2,*sem3,*sem4;
                    
                    char *namapic=cutter(ep->d_name);
                    
                    char copy1[100];
                    char copy2[100];
                    char copy3[100];
                    
                    char data2[100];
                    char data3[100];
                   
                    char hewan[100];
                    char nama[100];
                    
                    char umur[100];
                    for(sem1=strtok_r(namapic,"_",&sem3) ; sem1!=NULL; sem1=strtok_r(NULL,"_",&sem3))
                    {
                        int i;
                       
                        char data[100];
                        strcpy(data,dest);
                        strcat(data,"/");
                        strcpy(copy1, ep->d_name);
                        // printf("%s\n",copy1);

                        strcpy(data2, data);
                        

                        strcpy(data3, data);
                        

                        strcpy(copy2, ep->d_name);
                        

                        strcpy(copy3, ep->d_name);
                       
                        int flag=0;
                        for(sem2=strtok_r(sem1,";",&sem4);sem2!=NULL; sem2=strtok_r(NULL,";",&sem4))
                            {
                                if(flag==0)
                                strcpy(hewan,sem2);
                                if(flag==1)
                                strcpy(nama,sem2);
                                if(flag==2)
                                strcpy(umur,sem2);
                                
                                flag++;
                            }
                        
 
                        //2b
                        strcat(data,hewan);
                        
                        makedire(data);
                        
                        
                        char textdir[100];
                        
                        stpcpy(textdir,data);
                        strcat(textdir,"/keterangan.txt");
                        char namatext[100];
                        
                        strcpy(namatext,nama);
                    
                        //2c
                        
                        strcat(nama,".jpg");
                        
                        strcat(data2,copy2);
                        
                    
                        cpy(data2,data);
                        
                        //rename
                        strcpy(data3,data);
                        

                        strcat(data3,"/");
                        

                        strcat(data3,copy2);
                        

                        strcat(data,"/");
                        
                        strcat(data,nama);
                        
                        ren(data3,data);
                        
                        //2e(sudah)
                        char  isi[300];
                        
                        sprintf(isi,"nama : %s \numur :%s tahun \n \n",namatext,umur);
                       
                        FILE *fptr=fopen(textdir,"a");
                        fputs(isi,fptr);
                        fclose(fptr);
                        
                    }
                }
                
                if(ep->d_type == DT_REG)
                {
                    
                    char source[200];
                    strcpy(source,dest);
                    strcat(source,"/");
                    strcat(source,ep->d_name);
                    rem(source);//penghapusan file yang telah dipindah
                }
            }
        }
    (void) closedir (dp);
    }
    else {
        while ((wait(&kons))>0);
    }
}
 
int main()
{
    pid_t child_id;
    int kons;
    child_id=fork();
    char source[100] = "/home/rayhan12/soal2/pets.zip";
    char dest[100] = "/home/rayhan12/soal2/petshop";
    if(child_id<0)
    {
        exit(EXIT_FAILURE);
    }
 
    if(child_id == 0)
    {
        unzip(dest,source);
        BCDE(dest);
    }
 
    else{
        
       while ((wait(&kons))>0);
       
    }
    
    
    return 0;
}

