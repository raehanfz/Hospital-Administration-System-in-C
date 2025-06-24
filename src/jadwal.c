#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dokter.h"
#include "jadwal.h"

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

DokterPadaShift* CreateNodeDokterDiShift(char nama[MAX_NAME_LENGTH]){
    DokterPadaShift* temp = (DokterPadaShift*)malloc(sizeof(DokterPadaShift));
    strcpy(temp->nama, nama);
    temp->next = NULL;
    return temp;
}

void CekMaksShiftKebutuhanPreferensiLaluAssign(NodeDokter* head, Jadwal* jadwal){
    bool shift_in_day_full = false;
    DokterPadaShift* temp;
    DokterPadaShift* current_pagi = NULL;
    DokterPadaShift* current_siang = NULL;
    DokterPadaShift* current_malam = NULL;
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

void AssignDokterTanpaPreferensi(Jadwal* jadwal, NodeDokter* head, const char* shiftName) {
    DokterPadaShift* temp;
    DokterPadaShift* current;
    bool flag = false;

    while (!flag && head != NULL) {
        if (strcmp(shiftName, "pagi") == 0 && head->maksShiftPerMinggu > 0) {
            if (!head->shiftPagi) head->pelanggaran++;
            temp = CreateNodeDokterDiShift(head->nama);
            if (jadwal->pagi.head == NULL) {
                jadwal->pagi.head = temp;
            } else {
                current = jadwal->pagi.head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }
            head->maksShiftPerMinggu--;
            jadwal->pagi.kebutuhanDokter--;
            if (jadwal->pagi.kebutuhanDokter == 0) {
                jadwal->pagi.kebutuhanTerpenuhi = true;
                flag = true;
            }
        } else if (strcmp(shiftName, "siang") == 0 && head->maksShiftPerMinggu > 0) {
            temp = CreateNodeDokterDiShift(head->nama);
            if (!head->shiftSiang) head->pelanggaran++;
            if (jadwal->siang.head == NULL) {
                jadwal->siang.head = temp;
            } else {
                current = jadwal->siang.head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }
            head->maksShiftPerMinggu--;
            jadwal->siang.kebutuhanDokter--;
            if (jadwal->siang.kebutuhanDokter == 0) {
                jadwal->siang.kebutuhanTerpenuhi = true;
                flag = true;
            }
        } else if (strcmp(shiftName, "malam") == 0 && head->maksShiftPerMinggu > 0) {
            temp = CreateNodeDokterDiShift(head->nama);
            if (!head->shiftMalam) head->pelanggaran++;
            if (jadwal->malam.head == NULL) {
                jadwal->malam.head = temp;
            } else {
                current = jadwal->malam.head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }
            head->maksShiftPerMinggu--;
            jadwal->malam.kebutuhanDokter--;
            if (jadwal->malam.kebutuhanDokter == 0) {
                jadwal->malam.kebutuhanTerpenuhi = true;
                flag = true;
            }
        }
        head = head->next;
    }
}
void PrintPelanggaranPerDokter(NodeDokter* head){
    printf("\n== Daftar Pelanggaran Preferensi per Dokter ==\n");
    while (head != NULL) {
        printf("Nama: %s - Pelanggaran: %d\n", head->nama, head->pelanggaran);
        head = head->next;
    }
}

void AmbilMaksShift(NodeDokter* head, MaksShift arrayMaksShift[]){
    int ID = 0;
    while(head != NULL){
        strcpy(arrayMaksShift[ID].nama, head->nama);
        arrayMaksShift[ID].maksShiftPerMinggu = head->maksShiftPerMinggu;
        head = head->next;
        ID++;
    }
}

void ResetMaksShift(NodeDokter* head, MaksShift arrayMaksShift[]){
    int ID = 0;
    while(head != NULL){
        if(strcmp(arrayMaksShift[ID].nama, head->nama) == 0){
            head->maksShiftPerMinggu = arrayMaksShift[ID].maksShiftPerMinggu;
            head = head->next;
            ID++;
        }
    }
}

int HitungJumlahDokter(NodeDokter* head){
    int jumlahDokter = 0;
    while (head != NULL){
        jumlahDokter++;
        head = head->next;
    }
    return jumlahDokter;
}

void AddDokterToDaftarDokter(NodeDokter** daftarDokter, char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam){
    NodeDokter *newNodeDokter = CreateNodeDokter(nama, maksShift, pagi, siang, malam); // Node dokter baru
    newNodeDokter->next = *daftarDokter; // Sambung newnode di paling depan linked list
    *daftarDokter = newNodeDokter; // ubah alamat head dari daftarDokter
}

void DeleteDokter(NodeDokter** daftarDokter, char nama[MAX_NAME_LENGTH]){
    NodeDokter *ptr = *daftarDokter;
    NodeDokter *before = NULL;
    NodeDokter *after = ptr->next;

    int compare;
    while(ptr != NULL){
        compare = strcmp(nama, ptr->nama);
        if(compare == 0){ // Kalau nama current pointer sama dengan nama yang dicari, maka delete
            NodeDokter *temp = ptr;
            if(ptr == *daftarDokter){ // Kasus yang didelete ada di head, maka ubah alamat head
                *daftarDokter = (*daftarDokter)->next;
            }
            else{ // Kasus biasa, ubah alamat next dari before
                before->next = after; // Sambung ke elemen setelah current pointer
            }
            free(temp);
            return;
        }
        before = ptr;
        ptr = ptr->next;
        if(after == NULL){ // Untuk menghindari error kalau after sudah menjadi NULL
            after = NULL;
        }
        else{
            after = ptr->next;
        }
    }
    printf("Nama %s tidak ditemukan!\n", nama);
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

void ExportDokterToCSV(NodeDokter* daftarDokter, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Gagal membuka file untuk menulis");
        return;
    }

    // Tulis header CSV
    fprintf(file, "Nama,MaksShiftPerMinggu,ShiftPagi,ShiftSiang,ShiftMalam\n");

    // Tulis data tiap dokter
    NodeDokter* current = daftarDokter;
    while (current != NULL) {
        fprintf(
            file, "%s,%hu,%s,%s,%s\n",
            current->nama,
            current->maksShiftPerMinggu,
            current->shiftPagi ? "true" : "false",
            current->shiftSiang ? "true" : "false",
            current->shiftMalam ? "true" : "false"
        );
        current = current->next;
    }
    fclose(file);
}
