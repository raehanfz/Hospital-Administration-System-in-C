#ifndef ANTARMUKA_H
#define ANTARMUKA_H
#include "jadwal.h"

//header untuk fungsi-fungsi yang berhubungan dengan antarmuka dari user

//fungsi untuk print jadwal pada suatu hari
//input: Element dari array of Jadwal dan tanggal yang dituju
//output: void
void printJadwalHarian(Jadwal hari, int tanggal);

//fungsi untuk print jadwal pada minggu tertentu
//input: array of Jadwal dan minggu yang dituju
//output: void
void printJadwalMingguan(Jadwal ArrayJadwal[30], int minggu);

//fungsi untuk print jadwal dalam 1 bulan
//input: array of Jadwal
//output: void
void printJadwal(Jadwal ArrayJadwal[30]);

//fungsi untuk memungkinkan interaksi antar user dan program. berguna agar user dapat mengakses menu-menu dari program
//input: array of Jadwal, address dari head linked-list NodeDokter*, jumlah pelanggaran yang terjadi
//output: void 
void antarmuka(Jadwal arrayJadwal[30], NodeDokter** head, int jumlahPelanggaran);

//fungsi untuk memberikan messege setelah program berakhir
void exitmessege();

#endif