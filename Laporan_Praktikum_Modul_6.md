# <h1 align="center">Laporan Praktikum Modul 6 - Doubly Linked List (Bagian Pertama)</h1>
<p align="center">Hafis Saputra - 109082500087</p>

## Dasar Teori

### A. Doubly Linked List

Doubly linked list merupakan salah satu bentuk struktur data linked list yang setiap nodenya memiliki dua pointer penghubung, yaitu `next` dan `prev`. Pointer `next` digunakan untuk menunjuk node setelahnya, sedangkan pointer `prev` menunjuk node sebelumnya. Dengan adanya dua pointer tersebut, data dapat ditelusuri dari depan ke belakang maupun dari belakang ke depan [1].

### B. Komponen Doubly Linked List

Dalam doubly linked list terdapat beberapa komponen utama. `First` merupakan pointer yang menunjuk node pertama, sedangkan `Last` menunjuk node terakhir. Setiap node memiliki `info` untuk menyimpan data, `next` untuk menunjuk node selanjutnya, dan `prev` untuk menunjuk node sebelumnya. Pada list kosong, pointer `First` dan `Last` bernilai `nullptr`. Pada node pertama, `prev` bernilai `nullptr`, sedangkan pada node terakhir, `next` bernilai `nullptr` [1].

### C. Operasi pada Doubly Linked List

Operasi dasar pada doubly linked list meliputi pembuatan list, alokasi memori, dealokasi memori, penyisipan, pencarian, penampilan, dan penghapusan node. Operasi `CreateList()` digunakan untuk membuat list kosong. `alokasi()` membuat node baru, sedangkan `dealokasi()` membebaskan memori node yang sudah tidak digunakan. `insertLast()` menambahkan node pada bagian akhir list dengan menghubungkan pointer `prev` dan `next` secara tepat [1].

Operasi pencarian dilakukan dengan menelusuri node dari salah satu ujung list hingga data yang dicari ditemukan. Penghapusan dapat dilakukan pada node pertama, node terakhir, atau node setelah posisi tertentu. Setelah node dihapus, hubungan pointer pada node yang tersisa harus diperbarui agar list tetap tersambung dengan benar [1].

### D. Penerapan Doubly Linked List pada C++

Pada praktikum ini, doubly linked list diterapkan untuk menyimpan data buku. Setiap data buku memiliki kode buku, judul, dan tahun terbit. Struktur data tersebut dibuat menggunakan `struct`, sedangkan hubungan antarnode dikelola menggunakan pointer. Program dibagi menjadi file header `Buku.h`, file implementasi `Buku.cpp`, dan file utama `main.cpp` agar deklarasi, proses fungsi, dan jalannya program tersusun lebih rapi [1], [2].

## Guided

### 1. Struktur Data Buku pada Buku.h

```cpp
#ifndef BUKU_H_INCLUDED
#define BUKU_H_INCLUDED

#include <string>
using namespace std;

struct buku {
    string kodeBuku;
    string judul;
    int thnTerbit;
};

typedef buku infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address First;
    address Last;
};

void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(const List &L);
void insertLast(List &L, address P);
address findElm(const List &L, const string &kode);
void deleteFirst(List &L, address &P);
void deleteLast(List &L, address &P);
void deleteAfter(address Prec, address &P);
void deleteList(List &L);

#endif
```

File `Buku.h` digunakan untuk mendefinisikan data buku dan struktur doubly linked list. Struktur `buku` berisi kode buku, judul, dan tahun terbit. Struktur `ElmList` menyimpan informasi buku serta dua pointer, yaitu `next` dan `prev`. Sementara itu, struktur `List` memiliki `First` dan `Last` sebagai penunjuk node pertama dan terakhir.

### 2. Implementasi Fungsi pada Buku.cpp

```cpp
#include <iostream>
#include "Buku.h"
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
    L.Last = nullptr;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void printInfo(const List &L) {
    address P = L.Last;
    while (P != nullptr) {
        cout << "Kode Buku    : " << P->info.kodeBuku << endl;
        cout << "Judul        : " << P->info.judul << endl;
        cout << "Tahun Terbit : " << P->info.thnTerbit << endl;
        P = P->prev;
    }
}

void insertLast(List &L, address P) {
    if (P == nullptr) return;

    if (L.First == nullptr) {
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;
        L.Last->next = P;
        L.Last = P;
    }
}

address findElm(const List &L, const string &kode) {
    address P = L.First;
    while (P != nullptr) {
        if (P->info.kodeBuku == kode) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void deleteFirst(List &L, address &P) {
    if (L.First == nullptr) {
        P = nullptr;
        return;
    }

    P = L.First;
    L.First = L.First->next;

    if (L.First != nullptr) {
        L.First->prev = nullptr;
    } else {
        L.Last = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

void deleteLast(List &L, address &P) {
    if (L.Last == nullptr) {
        P = nullptr;
        return;
    }

    P = L.Last;
    L.Last = L.Last->prev;

    if (L.Last != nullptr) {
        L.Last->next = nullptr;
    } else {
        L.First = nullptr;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

void deleteAfter(address Prec, address &P) {
    if (Prec == nullptr || Prec->next == nullptr) {
        P = nullptr;
        return;
    }

    P = Prec->next;
    Prec->next = P->next;

    if (P->next != nullptr) {
        P->next->prev = Prec;
    }

    P->next = nullptr;
    P->prev = nullptr;
}

void deleteList(List &L) {
    address P;
    while (L.First != nullptr) {
        deleteFirst(L, P);
        dealokasi(P);
    }
}
```

File `Buku.cpp` berisi proses dari fungsi-fungsi yang telah dideklarasikan pada header. `CreateList()` mengatur `First` dan `Last` menjadi `nullptr`. Fungsi `alokasi()` membuat node baru dan mengisi informasi buku. Fungsi `insertLast()` memasukkan node di akhir list dengan menghubungkan `P->prev` ke node terakhir sebelumnya dan mengubah `Last` menjadi node baru.

Fungsi `findElm()` mencari buku berdasarkan kode buku. Fungsi `deleteFirst()`, `deleteLast()`, dan `deleteAfter()` digunakan untuk menghapus node sesuai posisinya. Setelah node dilepas dari list, fungsi `dealokasi()` membebaskan memori yang digunakan node tersebut. Pada fungsi `printInfo()`, data ditelusuri dari `Last` menuju `First` menggunakan pointer `prev` agar urutan tampilannya sesuai contoh output pada soal latihan.

## Unguided

### 1. Pembuatan ADT Dasar dan Insert Data

Soal pertama meminta pembuatan ADT doubly linked list untuk menyimpan data buku yang terdiri dari kode buku, judul, dan tahun terbit. Program juga harus memeriksa apakah kode buku sudah pernah dimasukkan sebelum membuat node baru. Jika kode sudah terdaftar, data tidak dimasukkan dan program menampilkan pesan `kode buku sudah terdaftar`.

Pada `main.cpp`, program menerima empat kali masukan data. Data pertama adalah B001 dengan judul Algoritma dan tahun 2020. Data kedua adalah B003 dengan judul Struktur_Data dan tahun 2018. Masukan ketiga menggunakan kode B001 kembali sehingga ditolak sebagai data duplikat. Data terakhir adalah B004 dengan judul Jaringan_Komputer dan tahun 2022.

### 2. Pencarian Elemen (Searching)

Soal kedua meminta pencarian data buku dengan kode B001 menggunakan fungsi `findElm()`. Fungsi tersebut memulai pencarian dari node pertama dan membandingkan kode buku pada setiap node. Jika kode yang dicari ditemukan, fungsi mengembalikan alamat node tersebut. Program kemudian menampilkan kode buku, judul, dan tahun terbit dari node yang ditemukan.

### 3. Penghapusan Elemen (Delete)

Soal ketiga meminta penghapusan data dengan kode B003. Program terlebih dahulu mencari alamat node yang akan dihapus menggunakan `findElm()`. Karena B003 berada di tengah list, penghapusan dilakukan dengan `deleteAfter()` menggunakan node sebelumnya sebagai `Prec`. Setelah hubungan pointer diperbaiki, memori node B003 dibebaskan menggunakan `dealokasi()`. Program kemudian menampilkan kembali data yang tersisa, yaitu B004 dan B001 sesuai urutan tampilan pada contoh soal.

### 4. Program Utama main.cpp

```cpp
#include <iostream>
#include <string>
#include "Buku.h"
using namespace std;

int main() {
    List L;
    CreateList(L);

    int jumlah;
    cout << "Masukkan jumlah data buku: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++) {
        buku data;
        cout << "\nMasukkan kode buku: ";
        cin >> data.kodeBuku;

        cout << "Masukkan judul buku: ";
        cin >> data.judul;

        cout << "Masukkan tahun terbit: ";
        cin >> data.thnTerbit;

        if (findElm(L, data.kodeBuku) != nullptr) {
            cout << "kode buku sudah terdaftar" << endl;
        } else {
            insertLast(L, alokasi(data));
        }
    }

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    string kodeCari;
    cout << "\nMasukkan Kode Buku yang dicari : ";
    cin >> kodeCari;

    address hasil = findElm(L, kodeCari);
    if (hasil != nullptr) {
        cout << "\nKode Buku    : " << hasil->info.kodeBuku << endl;
        cout << "Judul        : " << hasil->info.judul << endl;
        cout << "Tahun Terbit : " << hasil->info.thnTerbit << endl;
    } else {
        cout << "Data buku tidak ditemukan." << endl;
    }

    string kodeHapus;
    cout << "\nMasukkan Kode Buku yang akan dihapus : ";
    cin >> kodeHapus;

    address target = findElm(L, kodeHapus);
    if (target == nullptr) {
        cout << "Data dengan kode buku " << kodeHapus
             << " tidak ditemukan." << endl;
    } else {
        address Hapus = nullptr;

        if (target == L.First) {
            deleteFirst(L, Hapus);
        } else if (target == L.Last) {
            deleteLast(L, Hapus);
        } else {
            deleteAfter(target->prev, Hapus);
        }

        dealokasi(Hapus);
        cout << "Data dengan kode buku " << kodeHapus
             << " berhasil dihapus." << endl;
    }

    cout << "\nDATA LIST 1" << endl;
    printInfo(L);

    deleteList(L);
    return 0;
}
```

Kode pada `main.cpp` menjadi pengendali jalannya program. Program membuat list kosong, menerima data buku, memeriksa duplikasi kode, menampilkan isi list, mencari kode B001, dan menghapus kode B003. Setelah seluruh proses selesai, `deleteList()` dipanggil untuk membebaskan seluruh node yang masih tersimpan.

### 5. Hasil Output Program

**Link foto output: https://github.com/apinghapis29-code/modul-6/blob/6aa07250959d3347c2fde838d688949db23f86c8/Cuplikan%20layar%202026-11-01%20175641.png

```text
Masukkan jumlah data buku: 4

Masukkan kode buku: B001
Masukkan judul buku: Algoritma
Masukkan tahun terbit: 2020

Masukkan kode buku: B003
Masukkan judul buku: Struktur_Data
Masukkan tahun terbit: 2018

Masukkan kode buku: B001
Masukkan judul buku: Basis_Data
Masukkan tahun terbit: 2021
kode buku sudah terdaftar

Masukkan kode buku: B004
Masukkan judul buku: Jaringan_Komputer
Masukkan tahun terbit: 2022

DATA LIST 1
Kode Buku    : B004
Judul        : Jaringan_Komputer
Tahun Terbit : 2022
Kode Buku    : B003
Judul        : Struktur_Data
Tahun Terbit : 2018
Kode Buku    : B001
Judul        : Algoritma
Tahun Terbit : 2020
```

Pada output pertama, tiga data buku berhasil dimasukkan ke dalam list. Ketika kode B001 dimasukkan kembali, program menolak data tersebut karena kode sudah terdaftar. Penampilan data dilakukan dari node terakhir menuju node pertama menggunakan pointer `prev`, sehingga urutan yang terlihat adalah B004, B003, dan B001 sesuai contoh pada soal latihan [2].

**Output 2 — Pencarian Buku B001 dan SS :https://github.com/apinghapis29-code/modul-6/blob/6aa07250959d3347c2fde838d688949db23f86c8/Cuplikan%20layar%202026-11-01%20175810.png

```text
Masukkan Kode Buku yang dicari : B001

Kode Buku    : B001
Judul        : Algoritma
Tahun Terbit : 2020
```

Output kedua menunjukkan bahwa fungsi `findElm()` berhasil menemukan buku dengan kode B001. Program kemudian menampilkan informasi buku yang sesuai, yaitu judul Algoritma dan tahun terbit 2020.

**Output 3 — Penghapusan Buku B003 dan SS : https://github.com/apinghapis29-code/modul-6/blob/6aa07250959d3347c2fde838d688949db23f86c8/Cuplikan%20layar%202026-11-01%20175810.png

```text
Masukkan Kode Buku yang akan dihapus : B003
Data dengan kode buku B003 berhasil dihapus.

DATA LIST 1
Kode Buku    : B004
Judul        : Jaringan_Komputer
Tahun Terbit : 2022
Kode Buku    : B001
Judul        : Algoritma
Tahun Terbit : 2020
```

Output ketiga memperlihatkan bahwa buku B003 berhasil dihapus dari list. Node sebelum dan sesudahnya kembali terhubung melalui pointer `next` dan `prev`. Setelah penghapusan, data yang tersisa adalah B004 dan B001.

## Kesimpulan

1. Doubly linked list menggunakan dua pointer, yaitu `next` dan `prev`, sehingga penelusuran data dapat dilakukan dari depan maupun belakang.
2. Program ADT buku berhasil melakukan penyisipan data di akhir list dan mencegah kode buku yang sama dimasukkan lebih dari satu kali.
3. Fungsi `findElm()` berhasil mencari buku B001, sedangkan operasi `deleteAfter()` berhasil menghapus buku B003 tanpa memutus hubungan node lainnya.

## Referensi

[1] Tim Penyusun, *Modul 6: Doubly Linked List (Bagian Pertama)*, Buku Ajar Praktikum Struktur Data, hlm. 51–58, t.t.

[2] Tim Penyusun, *Soal Latihan Modul 6 Praktikum Struktur Data*, hlm. 1–3, t.t.
