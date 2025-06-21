#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "jadwal.h"

void LoopTanggal(Jadwal arrayJadwal[30], NodeDokter* head, int jumlahDokter) {
    int week = 0;
    MaksShift arrayMaksShift[jumlahDokter];

    AmbilMaksShift(head, arrayMaksShift); // Ambil data maks shift dari dokter
    for (int tanggal = 1; tanggal <= 30; tanggal++) {
        CekMaksShiftKebutuhanPreferensiLaluAssign(head, &arrayJadwal[tanggal - 1]);

        if (tanggal == 29 || tanggal == 30) {
            for (int j = 0; j < 2; j++) {
                int index = j + 7 * week;
                if (index >= 30) break;

                if (!arrayJadwal[index].pagi.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "pagi");
                }
                if (!arrayJadwal[index].siang.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "siang");
                }
                if (!arrayJadwal[index].malam.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "malam");
                }
            }
        }

        else if (tanggal % 7 == 0) {
            for (int j = 0; j < 7; j++) {
                int index = j + 7 * week;
                if (index >= 30) break;

                if (!arrayJadwal[index].pagi.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "pagi");
                }
                if (!arrayJadwal[index].siang.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "siang");
                }
                if (!arrayJadwal[index].malam.kebutuhanTerpenuhi) {
                    AssignDokterTanpaPreferensi(&arrayJadwal[index], head, "malam");
                }
            }

            week++;
            ResetMaksShift(head, arrayMaksShift); // Reset maks shift dokter setiap minggu
        }
    }
    ResetMaksShift(head, arrayMaksShift);
}

