#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "jadwal.h"

void printJadwalHarian(Jadwal hari, int tanggal){
    printf("\n==Jadwal==\n");
    printf("Tanggal: %d\n", tanggal);

    printf("\nShift pagi:\n");
    DokterPadaShift* temp = hari.pagi.head;
    while (temp != NULL){
        printf("%s\n", temp->nama);
        temp = temp->next;
    }

    printf("\nShift siang:\n");
    temp = hari.siang.head;
    while (temp != NULL){
        printf("%s\n", temp->nama);
        temp = temp->next;
    }

    printf("\nShift malam:\n");
    temp = hari.malam.head;
    while (temp != NULL){
        printf("%s\n", temp->nama);
        temp = temp->next;
    }
}

void printJadwalMingguan(Jadwal ArrayJadwal[30], int minggu){
    if (minggu == 5){
        printJadwalHarian(ArrayJadwal[28], 29);
        printJadwalHarian(ArrayJadwal[29], 30);
    } else {
        minggu -= 1;
        for (int i = 0; i < 7; i++){
            printJadwalHarian(ArrayJadwal[i+7*minggu], 1+i+7*minggu);
        }
    }
    
}
void printJadwal(Jadwal ArrayJadwal[30]){
    for (int i = 0; i < 30; i++){
        printJadwalHarian(ArrayJadwal[i], i+1);
    }
    
}
void exitmessege(){
    printf("TUBES PMP SELESAIIII (YIPPIEEE)");
}

void antarmuka(Jadwal arrayJadwal[30], NodeDokter** head,int jumlahPelanggaran){
    bool exit = false;
    int menu;
    while (!exit){
        printf("\n==MANAJEMEN RUMAH SAKIT ALEXANDER KNALPOT==\n");
        printf("pilih menu: (masukkan angka saja)\n");
        printf("1. lihat Jadwal Dokter\n2. tambah dokter\n3. hapus dokter\n4. lihat pelanggaran preferensi\n5. exit\n");
        printf("pilih menu (masukkan angka saja): ");
        scanf("%d", &menu);

        if (menu == 1){
            int jadwal;
            printf("\n==JADWAL DOKTER==\n");
            printf("pilih menu: (masukkan angka saja)\n");
            printf("1. Jadwal harian\n2. Jadwal mingguan\n3. Jadwal satu bulan\n");
            printf("pilih jadwal (masukkan angka saja): ");
            scanf("%d", &jadwal);
            if (jadwal == 1){
                int tanggal;
                printf("pilih tanggal (1-30): ");
                scanf("%d", &tanggal);
                printJadwalHarian(arrayJadwal[tanggal-1], tanggal);
            } else if (jadwal == 2) {
                int minggu;
                printf("pilih minggu (1-5): ");
                scanf("%d", &minggu);
                printJadwalMingguan(arrayJadwal, minggu);
            } else if (jadwal == 3) {
                printJadwal(arrayJadwal);
            } else {
                printf("input tidak valid");
            }
        }
        else if (menu == 2) {
            char nama[MAX_NAME_LENGTH];
            unsigned short int MaksShift1Minggu;
            bool shiftPagi, shiftSiang, shiftMalam;

            printf("\n==Tambah Dokter==\n");

            getchar(); 
            printf("Nama Dokter: ");
            fgets(nama, MAX_NAME_LENGTH, stdin);
            nama[strcspn(nama, "\n")] = '\0';  // Hapus newline

            printf("Maksimal shift dokter per minggu: ");
            scanf("%hu", &MaksShift1Minggu);

            int input;

            printf("Preferensi shift pagi (1 untuk iya, 0 untuk tidak): ");
            scanf("%d", &input);
            shiftPagi = input;

            printf("Preferensi shift siang (1 untuk iya, 0 untuk tidak): ");
            scanf("%d", &input);
            shiftSiang = input;

            printf("Preferensi shift malam (1 untuk iya, 0 untuk tidak): ");
            scanf("%d", &input);
            shiftMalam = input;

            AddDokterToDaftarDokter(head, nama, MaksShift1Minggu, shiftPagi, shiftSiang, shiftMalam);
        }

        else if (menu == 3){
            char nama[MAX_NAME_LENGTH];

            printf("\n==Hapus Dokter==\n");
            printf("nama Dokter: ");
            getchar(); // flush newline after scanf
            fgets(nama, MAX_NAME_LENGTH, stdin);
            nama[strcspn(nama, "\n")] = '\0';

            DeleteDokter(head, nama);
        }
        else if (menu == 4){
            unsigned short int pelanggaran;
            printf("\n==Pelanggaran==\n");
            printf("1. Total pelanggaran\n2. Pelanggaran setiap dokter\n");
            printf("pilih menu pelanggaran (pilih angka saja): ");
            scanf("%hu", &pelanggaran);
            if (pelanggaran == 2){
                PrintPelanggaranPerDokter(*head);
            } else {
                printf("total pelanggaran preferensi dokter: %d", jumlahPelanggaran);
            }
        }else if (menu == 5){
            exitmessege();
            exit = true;
        }
    }
}