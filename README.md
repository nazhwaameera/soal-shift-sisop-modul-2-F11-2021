# soal-shift-sisop-modul-2-F11-2021
Repository Modul 2 Kelompok F11

## Soal 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacarana. Ketika dia galau memikirkan mantan, ia selalu menonton sebuah video untuk menghilangkan kesedihannya. Di lain hal, Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal ayng disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai ekstensi.

### Bagian a
Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg. 

### Bagian b
Untuk music Steven mendownloadnya dari link dibawah ini, film dari link dibawahnya lagi, dan foto dari link dibawahnya juga.

### Bagian c
Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu dilakukan extract setelah file didownload serta..

### Bagian d
..memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan).

### Bagian e
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany.

### Bagian f
Setelah itu, pada waktu ulang tahunnya, semua folder akan dizip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete sehingga hanya menyisakan .zip saja.

**NOTE :** Dari soal di atas dapat diketahui bahwa kita diminta untuk:
1.	Membuat folder dengan nama Musyik, Fylm, dan Pyoto
2.	Mendownload file-file yang dibutuhkan dari link yang sudah disediakan
3.	Mengextract file yang telah didownload
4.	Memindahkan file-file tersebut ke dalam folder yang telah dibuat
5.	Membuat program berjalan otomatis pada 09 April 16:22
6.	Membuat zip dari ketiga folder yang ada dan menghapus folder terkait

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
