# soal-shift-sisop-modul-2-F11-2021
Repository Modul 2 Kelompok F11

## Soal 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton sebuah video untuk menghilangkan kesedihannya. Di lain hal, Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany.

Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai ekstensi. **(a)** Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg, **(b)** untuk music Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link di bawahnya juga. **(c)** Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu dilakukan extract setelah file didownload serta **(d)** memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan). **(e)** Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany. **(f)** Setelah itu, pada waktu ulang tahunnya, semua folder akan dizip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete sehingga hanya menyisakan .zip saja.

**NOTE :** Dari soal di atas dapat diketahui bahwa kita diminta untuk:
1.	Membuat folder dengan nama Musyik, Fylm, dan Pyoto
2.	Mendownload file-file yang dibutuhkan dari link yang sudah disediakan
3.	Mengextract file yang telah didownload
4.	Memindahkan file-file tersebut ke dalam folder yang telah dibuat
5.	Membuat program berjalan otomatis pada 09 April 16:22
6.	Membuat zip dari ketiga folder yang ada dan menghapus folder terkait

Dari apa yang sudah saya kerjakan sebelumnya, terdapat beberapa perubahan yakni.
•	Link download ketiga file yang dibutuhkan menjadi
```
char *drive[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
```
Perubahan ini dilakukan karena format yang sebelumnya salah (proses download tidak berhasil dilakukan).

•	Penambahan variable ```char *dwnld[ ]``` yang menyimpan format nama file yang akan didownload. Format nama ini dibutuhkan untuk proses extract nantinya.
```
char *dwnld[] = {"mp3.zip", "mp4.zip", "jpg.zip"};
```
Penambahan variable di atas berdampak juga pada perubahan penulisan line yang menggunakan variable terkait, seperti perintah exec untuk extract.
```
char *argv[] = {"unzip", dwnld[i], NULL};
execv("/usr/bin/unzip", argv);
```

•	Penyederhanaan fungsi function1( ) yang dipanggil 6 jam sebelum jam ulang tahun Stevany menjadi :
```
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
```
Pada versi function1() di atas, fork tidak dilakukan di setiap stepnya seperti pada versi function1() yang sebelumnya. Program semata melakukan iterasi sebanyak 3 kali dan melakukan 3 proses di setiap iterasinya.

Dengan menggabungkan semua perubahan yang telah dilakukan, dihasikan program seperti berikut.
```#include <time.h>
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
```
Berikut adalah foto hasil eksekusi program.
![nazhwa punya](https://user-images.githubusercontent.com/74484044/115996728-b0bd1e80-a60a-11eb-9a50-b1bfdc42433f.png)

Gambar 1. Eksekusi program pertama, set date 2021-04-09 16:21:59

![nazhwa punya2](https://user-images.githubusercontent.com/74484044/115996730-b581d280-a60a-11eb-821a-0938f0476f2b.png)

Gambar 2. Eksekusi program kedua, set date 2021-04-09 22:21:59

Kesulitan yang dialami selama pengerjaan yakni tidak berhasilnya eksekusi program saat pembuatan yang ternyata dikarenakan 3 hal. Pertama, kesalahan peletakkan program yang kana dieksekusi sehingga program mengeksekusi command exit(EXIT_FAILURE) sebelum program dapat berjalan; kedua, kesalahan input tanggal saat proses set date dilakukan sehingga program tidak tereksekusi sama sekali; ketiga, kesalahan link yang menyebabkan proses download gagal.

## Soal 2

## Soal 3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program. Disini kami menggunakan **Program Daemon** yakni sebagai berikut.
```
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
    
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    while(1)
    {
        sleep(40); // program berjalan setiap 40 detik
    }
}
```

### Bagian a
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai format timestamp [YYYY-mm-dd_HH:ii:ss]. Berikut adalah programnya, terletak di dalam fungsi loop yaitu **While**.
```
    pid_t child_id;
    int status;
    child_id = fork();
    time_t raw;
    struct tm *timeinfo;
    char tanggal[40];
    time(&raw);
    timeinfo = localtime(&raw);
    strftime(tanggal, sizeof(tanggal), "%Y-%m-%d_%H:%M:%S", timeinfo); // format penamaan folder sesuai dengan waktu saat folder tersebut terbentuk
        
    if(child_id < 0)
    {
        exit(EXIT_FAILURE);
    }
    if(child_id == 0)
    {
        char *argv[4] = {"mkdir", "-p", tanggal, NULL};
        execv("/bin/mkdir", argv);
    }
```
Setelah itu, diakhir program while, kami meletakkan fungsi sebagai berikut agar loop berjalan sesuai perintah soal, yakni folder terbentuk setiap 40 detik.
```
sleep(40); // program berjalan setiap 40 detik
```
Berikut adalah hasil direktori yang sudah terbentuk dengan nama sesuai format timestamp, dan juga akan terzip otomatis jika gambar di dalamnya sudah mencapai total 10 gambar.
<img width="706" alt="Screen Shot 2021-04-25 at 14 25 01" src="https://user-images.githubusercontent.com/74484044/115984642-6ae46400-a5d2-11eb-9273-04e741210e10.png">

### Bagian b
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang di download dari https://picsum.photos/, dimana setiap gambar akan di download setiap 5 detik. Setiap gambar yang di download akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n % 1000) + 50 pixel dimana n adalah detik Epoch Unix.
```
for(i = 1; i <= 10; i++) // total gambar yang di download adalah 10 gambar
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
        char *f[] = {"wget", "-bq", alamat, "-O" , tanggal2, NULL};
        execv("/usr/bin/wget", f); // agar berhasil mendownload dan menyimpan gambar ke dalam folder
    }
    sleep(5); // gambar di download tiap 5 detik
}
```

### Bagian c
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Dan setelah file tersebut dibuat, direktori akan di zip dan direktori akan di delete, sehingga menyisakan hanya file zip saja.
```
// isi file status.txt
char kata[50] = "Download Success";
char word;
```
```
// caesar cipher
for(int i = 0; i < strlen(kata); i++)
{
    word = kata[i];
    if(word == ' ')
    {
        continue;
    }
    if(word >= 'a' && word <= 'z')
    {
        word += 5;
        if(word > 'z')
        {
            word = word - 'z' + 'a' - 1;
        }
        kata[i] = word;
    }
    else if(word >= 'A' && word <= 'Z')
    {
        word += 5;
        if(word > 'Z')
        {
            word = word - 'Z' + 'A' - 1;
        }
        kata[i] = word;
    }
}
```
```
// untuk membuat file bernama status.txt
char file[100];
sprintf(file, "%s/status.txt", tanggal);
FILE *status = fopen(file, "w");
fputs(kata, status);
fclose(status);
                
// untuk mengubah folder menjadi bentuk zip sekaligus menghapus folder tersebut
char zip[50];
sprintf(zip, "%s.zip", tanggal);
char *argv2[5] = {"zip", "-rm", zip, tanggal, NULL};
execv("/usr/bin/zip", argv2);
```
Karena menggunakan **Caesar Cipher** juga dengan shift 5, maka kalimat "Download Success" akan berubah menjadi "Itbsqtfi Xzhhjxx". Dimana 5 huruf setelah huruf D adalah I, 5 huruf setelah huruf o adalah t, dan seterusnya.
```
word += 5;
```
Di dalam direktori yang sudah terzip, maka isinya akan ada 10 gambar + 1 file status.txt seperti berikut ini.
<img width="432" alt="Screen Shot 2021-04-25 at 14 26 55" src="https://user-images.githubusercontent.com/74484044/115984810-273e2a00-a5d3-11eb-86d6-584c3ba511ad.png">
<img width="679" alt="Screen Shot 2021-04-25 at 14 27 07" src="https://user-images.githubusercontent.com/74484044/115984813-29a08400-a5d3-11eb-8f59-90966bd8e0f4.png">

### Bagian d
Program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan **program bash**.
```
// 3d untuk membuat file killer.sh
FILE *kill = fopen("killer.sh", "w");
fprintf(kill, "#/bin/bash\n");
```
Berikut adalah file killer.sh, dimana jika dijalankan (bash killer.sh), semua proses akan langsung berhenti dan file killer.sh tersebut akan menghapus dirinya sendiri.

<img width="709" alt="Screen Shot 2021-04-25 at 14 35 45" src="https://user-images.githubusercontent.com/74484044/115984922-a16eae80-a5d3-11eb-87de-5935704916f8.png">

### Bagian e
Program utama yang dibuat Ranora nantinya harus dapat dijalankan dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
```
// 3e
// arg -z untuk menghentikan semua operasi
if(strcmp(argv[1], "-z") == 0)
{ 
    fprintf(kill, "killall -9 soal3\n");
}

// arg -x untuk kill proses utama --> pid
else if(strcmp(argv[1], "-x") == 0)
{
    fprintf(kill, "kill -9 %d\n", pid);
}

// delete folder setelah selesai di zip
fprintf(kill, "rm killer.sh\n");
fclose(kill);
```
**NOTE :** Untuk no 3 d dan 3 e diletak di dalam satu fungsi void yang sama, yakni void killer, yang nantinya akan dipanggil di dalam int main, seperti berikut.
```
// untuk menjalankan argumen -z dan -x
killer(argv, (int)getpid());
```
Berikut jika dijalankan dengan argumen -x dan setelah itu menjalankan bash killer.sh
<img width="570" alt="Screen Shot 2021-04-25 at 14 47 34" src="https://user-images.githubusercontent.com/74484044/115985257-32925500-a5d5-11eb-84e9-a643d47ff924.png">
<img width="624" alt="Screen Shot 2021-04-25 at 14 45 17" src="https://user-images.githubusercontent.com/74484044/115985199-eba45f80-a5d4-11eb-8129-d01d64ea9de7.png">

Program yang tadinya masih dalam bentuk direktori, akan menyelesaikan proses nya dahulu hingga menjadi bentuk zip, walaupun kita sudah menjalankan bash killer.sh. Sedangkan jika kita jalankan dengan argumen -z, maka tidak ada hasil yang keluar karena program akan langsung berhenti memproses.

Adapun kesulitan yang saya alami saat mengerjakan program ini ialah, gambar tidak berhasil di download serta adanya wget path yang salah.
