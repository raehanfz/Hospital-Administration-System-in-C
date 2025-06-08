#ifndef JADWAL_H
#define JADWAL_H

#include <stdbool.h>
#include "dokter.h" //include semua fungsi di header dokter

//struktur data dokter untuk shift tertentu pada suatu tanggal
typedef struct DokterPadaShift {
    char nama[MAX_NAME_LENGTH];
    struct DokterPadaShift* next;
} DokterPadaShift;

//struktur data mengenai suatu shift
typedef struct Shift {
    DokterPadaShift* head;
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
//input: nama dokter dari linked-list dokter
//output: node dokter pada shift untuk linked-list dokter pada suatu shift
DokterPadaShift* CreateNodeDokterDiShift(char nama[MAX_NAME_LENGTH]);

//inisialisasi array jadwal kosong
//input: ArrayJadwal (dideklarasikan di main)
//output: ArrayJadwal (dideklarasikan di main) (sebenernya void jadi gak return apa-apa)
void InisialisasiJadwal(Jadwal ArrayJadwal[]);

//fungsi ini akan mengiterasi linked-list dokter pada tanggal tertentu.
//dicek apakah beberapa kondisi terpenuhi: 
//  Makshift dokter belum nol (artinya dalam seminggu belum di batas shift dokternya)
//  Kebutuhan dokter pada shift tersebut belum terpenuhi
//  Preferensi shift dokter sesuai dengan shift yang lagi butuh dokter
//Jika semua kondisi terpenuh maka dokternya akan di-assign di shift itu

//input: Linked-list dokter (head nya aja, lalu ditransversal) dan address dari element array jadwal (contoh: &ArrayJadwal[0])
//output: Gak ada, fungsinya cuman memperbarui element array jadwal (makanya yang dipass itu addressnya juga, bukan value aja)
void CekMaksShiftKebutuhanPreferensiLaluAssign(NodeDokter* head, Jadwal* jadwal);

#endif
