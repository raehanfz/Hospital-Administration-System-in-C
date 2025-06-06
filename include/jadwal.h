#ifndef JADWAL_H
#define JADWAL_H

#include <stdbool.h>
#include "dokter.h" //include semua fungsi di header dokter

//struktur data dokter untuk shift tertentu pada suatu tanggal
typedef struct DokterPadaTanggal {
    char nama[MAX_NAME_LENGTH];
    struct DokterPadaTanggal* next;
} DokterPadaTanggal;

//struktur data mengenai sebuah shift
typedef struct Shift {
    DokterPadaTanggal* head;
    unsigned short int kebutuhanDokter;
    bool kebutuhanTerpenuhi;
} Shift;

//struktur data mengenai suatu jadwal dalam 1 hari
typedef struct Jadwal {
    unsigned short int tanggal;
    Shift pagi;
    Shift siang;
    Shift malam;
} Jadwal;

//buat node dokter untuk shift tertentu pada suatu tanggal
DokterPadaTanggal* CreateNodeDokterTanggal(char nama[MAX_NAME_LENGTH]);

// Inisialisasi array jadwal kosong
void InisialisasiJadwal(Jadwal ArrayJadwal[], unsigned short int jumlahHari);

#endif
