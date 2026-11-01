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
