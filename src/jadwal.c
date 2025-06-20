#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dokter.h"
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
//inisialisasi array jadwal kosong
DokterPadaShift* CreateNodeDokterDiShift(char nama[MAX_NAME_LENGTH]){
    DokterPadaShift* temp = (DokterPadaShift*)malloc(sizeof(DokterPadaShift));
    strcpy(temp->nama, nama);
    temp->next = NULL;
    return temp;
}

//fungsi ini akan mengiterasi linked-list dokter pada tanggal tertentu.
//dicek apakah beberapa kondisi terpenuhi: 
//  Makshift dokter belum nol (artinya dalam seminggu belum di batas shift dokternya)
//  Kebutuhan dokter pada shift tersebut belum terpenuhi
//  Preferensi shift dokter sesuai dengan shift yang lagi butuh dokter
//Jika semua kondisi terpenuh maka dokternya akan di-assign di shift itu
void CekMaksShiftKebutuhanPreferensiLaluAssign(NodeDokter* head, Jadwal* jadwal){
    bool shift_in_day_full = false;
    DokterPadaShift* temp;
    DokterPadaShift* head_pagi = NULL, *current_pagi = NULL;
    DokterPadaShift* head_siang = NULL, *current_siang = NULL;
    DokterPadaShift* head_malam = NULL, *current_malam = NULL;
    while (!shift_in_day_full && head != NULL){
        //cek apakah dokter pada node sekarang mau shift pagi, apakah shift pagi lagi butuh orang, dan apakah dokter di node sekarang udah sampai batas shiftnya
        if (head->shiftPagi == true && jadwal->pagi.kebutuhanTerpenuhi == false && head->maksShiftPerMinggu != 0){
            temp = CreateNodeDokterDiShift(head->nama);
            if (jadwal->pagi.head == NULL){
                jadwal->pagi.head = temp;
            } else {
                current_pagi->next = temp;
            }
            current_pagi = temp;
            
            head->maksShiftPerMinggu--; //dokter sudah menempati satu shift, jadi tinggal sisanya
            jadwal->pagi.kebutuhanDokter--; //sisa dokter yang masih dibutuhkan

            if (jadwal->pagi.kebutuhanDokter == 0){
                jadwal->pagi.kebutuhanTerpenuhi = true;
            }
        }
        //sama kayak yang atas, tapi kalo dokternya bisa siang juga, siang juga, gas!
        if (head->shiftSiang == true && jadwal->siang.kebutuhanTerpenuhi == false && head->maksShiftPerMinggu != 0){
            temp = CreateNodeDokterDiShift(head->nama);
            if (jadwal->siang.head == NULL){
                jadwal->siang.head = temp;
            } else {
                current_siang->next = temp;
            }
            current_siang = temp;
            
            head->maksShiftPerMinggu--; //dokter sudah menempati satu shift, jadi tinggal sisanya
            jadwal->siang.kebutuhanDokter--; //sisa dokter yang masih dibutuhkan

            if (jadwal->siang.kebutuhanDokter == 0){
                jadwal->siang.kebutuhanTerpenuhi = true;
            }
        }
        //sama kayak yang atas, tapi kalo dokternya bisa malem juga, siang juga, gas!
        if (head->shiftMalam == true && jadwal->malam.kebutuhanTerpenuhi == false && head->maksShiftPerMinggu != 0){
            temp = CreateNodeDokterDiShift(head->nama);
            if (jadwal->malam.head == NULL){
                jadwal->malam.head = temp;
            } else {
                current_malam->next = temp;
            }
            current_malam = temp;
            
            head->maksShiftPerMinggu--; //dokter sudah menempati satu shift, jadi tinggal sisanya
            jadwal->malam.kebutuhanDokter--; //sisa dokter yang masih dibutuhkan

            if (jadwal->malam.kebutuhanDokter == 0){
                jadwal->malam.kebutuhanTerpenuhi = true;
            }
        }
        //cek apakah kebutuhan shift pagi, siang, malam sudah terpenuhi 
        if (jadwal->pagi.kebutuhanTerpenuhi == true && jadwal->siang.kebutuhanTerpenuhi == true && jadwal->malam.kebutuhanTerpenuhi == true){
            shift_in_day_full = true;
        }
        head = head->next;
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
        DokterPadaShift* temp = arrayJadwal[i].pagi.head;
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

