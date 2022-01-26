# Tugas-Kecil-1-STIMA
Penyelesaian Word Search Puzzle menggunakan algoritma brute force. Program ditulis menggunakan bahasa C. 
Sebelum menjalankan program, pastikan sudah terinstall c compiler pada komputer.

## How To Run
Untuk compile program, buka folder src kemudian jalankan command
```
gcc wordsearchfinal.c -o wordsearchfinal
```
Untuk menjalankan program, bisa menggunakan file executable yang ada pada folder bin, atau jalankan program yang baru saja dicompile sendiri
```
./wordsearchfinal
```

## How To Use
Ketika sukses dijalankan, program akan meminta masukan berupa input nama file yang akan dijadikan puzzle
```
Masukkan nama file yang ingin digunakan (contoh : ../test/test.txt) :
```

Program akan menganggap setiap masukan nama file satu level direktori dengan dirinya. Sehingga jika ingin menggunakan file di folder lain, harus di spesifikkan.
<br /> <br />
Setelah file diterima, program akan menjalankan algoritmanya dan mengeluarkan luaran berupa letak tiap kata pada layar sesuai urutan yang ada pada file masukan. Setelah semua selesai ditampilkan pada layar, program akan menampilkan waktu, dan jumlah perbandingan yang dilakukan oleh program.

## Author
Ilham Prasetyo Wibowo 13520013
