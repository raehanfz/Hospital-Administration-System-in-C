#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "jadwal.h"

void LoopTanggal(Jadwal arrayJadwal[30], NodeDokter* head, int jumlahDokter, int *jumlahPelanggaran) {
    int pelanggaran = 0;
    int week = 0;
    MaksShift arrayMaksShift[jumlahDokter];

    AmbilMaksShift(head, arrayMaksShift); // Ambil data maks shift dari dokter
    for (int tanggal = 1; tanggal <= 30; tanggal++) {
        CekMaksShiftKebutuhanPreferensiLaluAssign(head, &arrayJadwal[tanggal - 1]);

        // First handle special case: Day 29 and 30 (incomplete week)
        if (tanggal == 29 || tanggal == 30) {
            for (int j = 0; j < 2; j++) {
                int index = j + 7 * week;
                if (index >= 30) break;

                if (!arrayJadwal[index].pagi.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "pagi");
                    pelanggaran++;
                }
                if (!arrayJadwal[index].siang.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "siang");
                    pelanggaran++;
                }
                if (!arrayJadwal[index].malam.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "malam");
                    pelanggaran++;
                }
            }
        }

        // Then handle weekly assignment after every 7 days
        else if (tanggal % 7 == 0) {
            for (int j = 0; j < 7; j++) {
                int index = j + 7 * week;
                if (index >= 30) break;

                if (!arrayJadwal[index].pagi.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "pagi");
                    pelanggaran++;
                }
                if (!arrayJadwal[index].siang.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "siang");
                    pelanggaran++;
                }
                if (!arrayJadwal[index].malam.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "malam");
                    pelanggaran++;
                }
            }

            week++;
            ResetMaksShift(head, arrayMaksShift); // Reset maks shift dokter setiap minggu
        }
    }

    *jumlahPelanggaran = pelanggaran; // Simpan jumlah pelanggaran ke variabel yang diberikan
}

