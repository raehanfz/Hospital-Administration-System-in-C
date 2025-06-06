#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jadwal.h" 

//fungsi inisialisasi 30 hari dalam 1 bulan
void InisialisasiArrayJadwal(Jadwal arrayJadwal[30]) {
    for (int i = 0; i < 30; i++) {
        arrayJadwal[i].tanggal = i + 1;

        arrayJadwal[i].pagi.head = NULL;
        arrayJadwal[i].pagi.kebutuhanDokter = 2;
        arrayJadwal[i].pagi.kebutuhanTerpenuhi = false;

        arrayJadwal[i].siang.head = NULL;
        arrayJadwal[i].siang.kebutuhanDokter = 3;
        arrayJadwal[i].siang.kebutuhanTerpenuhi = false;

        arrayJadwal[i].malam.head = NULL;
        arrayJadwal[i].malam.kebutuhanDokter = 3;
        arrayJadwal[i].malam.kebutuhanTerpenuhi = false;
    }
}

//ubah jadwal yang telah dibuat ke CSV
void ExportJadwalKeCSV(const char* filename, Jadwal arrayJadwal[30]) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Gagal membuka file untuk menulis");
        return;
    }

    // Tulis header
    fprintf(file, "tanggal,"
                  "dokter_1_shift_pagi,dokter_2_shift_pagi,"
                  "dokter_1_shift_siang,dokter_2_shift_siang,dokter_3_shift_siang,"
                  "dokter_1_shift_malam,dokter_2_shift_malam,dokter_3_shift_malam\n");

    for (int i = 0; i < 30; i++) {
        fprintf(file, "%d", arrayJadwal[i].tanggal);

        // Tulis nama dokter untuk shift pagi (2 dokter)
        DokterPadaTanggal* temp = arrayJadwal[i].pagi.head;
        for (int j = 0; j < 2; j++) {
            if (temp != NULL) {
                fprintf(file, ",%s", temp->nama);
                temp = temp->next;
            } else {
                fprintf(file, ",");
            }
        }

        // Tulis nama dokter untuk shift siang (3 dokter)
        temp = arrayJadwal[i].siang.head;
        for (int j = 0; j < 3; j++) {
            if (temp != NULL) {
                fprintf(file, ",%s", temp->nama);
                temp = temp->next;
            } else {
                fprintf(file, ",");
            }
        }

        // Tulis nama dokter untuk shift malam (3 dokter)
        temp = arrayJadwal[i].malam.head;
        for (int j = 0; j < 3; j++) {
            if (temp != NULL) {
                fprintf(file, ",%s", temp->nama);
                temp = temp->next;
            } else {
                fprintf(file, ",");
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
}
