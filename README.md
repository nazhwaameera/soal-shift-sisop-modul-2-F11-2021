# soal-shift-sisop-modul-2-F11-2021
Repository Modul 2 Kelompok F11

## Soal 1

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
    
    // untuk menjalankan argumen -z dan -x
    killer(argv, (int)getpid());
    
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
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss]. Berikut adalah programnya, terletak di dalam fungsi loop yaitu **While**
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

### Bagian d
Program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan **program bash**.

### Bagian e
Program utama yang dibuat Ranora nantinya harus dapat dijalankan dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).
