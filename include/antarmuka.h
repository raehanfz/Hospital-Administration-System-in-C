#ifndef ANTARMUKA_H
#define ANTARMUKA_H
#include "jadwal.h"

void printJadwalHarian(Jadwal hari, int tanggal);
void printJadwalMingguan(Jadwal ArrayJadwal[30], int minggu);
void printJadwal(Jadwal ArrayJadwal[30]);
void antarmuka(Jadwal arrayJadwal[30], int jumlahPelanggaran);

void exitmessege();

#endif