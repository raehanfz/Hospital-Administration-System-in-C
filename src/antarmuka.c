#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "jadwal.h"

#include <stdio.h>

void printShift(const char* namaShift, DokterPadaShift* head) {
    printf("│  %-10s\n", namaShift);
    printf("├────────────\n");

    if (head == NULL) {
        printf("│  (Kosong)\n");
    } else {
        int i = 1;
        while (head != NULL) {
            printf("│  %d. %s\n", i++, head->nama);
            head = head->next;
        }
    }

    printf("├────────────\n\n");
}

void printJadwalHarian(Jadwal hari, int tanggal) {
    printf("\n╔════════════════════════════╗\n");
    printf("║      JADWAL DOKTER HARIAN  ║\n");
    printf("╚════════════════════════════╝\n");
    printf("Tanggal: %2d\n\n", tanggal);

    printShift("Pagi", hari.pagi.head);
    printShift("Siang", hari.siang.head);
    printShift("Malam", hari.malam.head);
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

void antarmuka(Jadwal arrayJadwal[30], NodeDokter** head, int jumlahPelanggaran) {
    bool exit = false;
    int menu;

    while (!exit) {
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║   MANAJEMEN RUMAH SAKIT ALEXANDER KNALPOT ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("Pilih menu (masukkan angka):\n");
        printf("  1. Lihat Jadwal Dokter\n");
        printf("  2. Tambah Dokter\n");
        printf("  3. Hapus Dokter\n");
        printf("  4. Lihat Pelanggaran Preferensi\n");
        printf("  5. Keluar\n");
        printf(">> ");
        scanf("%d", &menu);

        if (menu == 1) {
            int jadwal;
            printf("\n╔═════ LIHAT JADWAL DOKTER ═════╗\n");
            printf("Pilih jenis jadwal:\n");
            printf("  1. Jadwal Harian\n");
            printf("  2. Jadwal Mingguan\n");
            printf("  3. Jadwal Bulanan\n");
            printf(">> ");
            scanf("%d", &jadwal);

            if (jadwal == 1) {
                int tanggal;
                printf("Pilih tanggal (1-30): ");
                scanf("%d", &tanggal);
                if (tanggal >= 1 && tanggal <= 30)
                    printJadwalHarian(arrayJadwal[tanggal - 1], tanggal);
                else
                    printf("Tanggal tidak valid!\n");
            } else if (jadwal == 2) {
                int minggu;
                printf("Pilih minggu (1-5): ");
                scanf("%d", &minggu);
                printJadwalMingguan(arrayJadwal, minggu);
            } else if (jadwal == 3) {
                printJadwal(arrayJadwal);
            } else {
                printf("Input tidak valid.\n");
            }
        }

        else if (menu == 2 || menu == 3) {
            if (menu == 2) {
                char nama[MAX_NAME_LENGTH];
                unsigned short int MaksShift1Minggu;
                bool shiftPagi, shiftSiang, shiftMalam;

                printf("\n╔═════ TAMBAH DOKTER ═════╗\n");
                getchar(); // clear buffer
                printf("Nama Dokter: ");
                fgets(nama, MAX_NAME_LENGTH, stdin);
                nama[strcspn(nama, "\n")] = '\0';

                printf("Maksimal shift per minggu: ");
                scanf("%hu", &MaksShift1Minggu);

                int input;
                printf("Preferensi shift pagi (1/0): ");
                scanf("%d", &input); shiftPagi = input;
                printf("Preferensi shift siang (1/0): ");
                scanf("%d", &input); shiftSiang = input;
                printf("Preferensi shift malam (1/0): ");
                scanf("%d", &input); shiftMalam = input;

                AddDokterToDaftarDokter(head, nama, MaksShift1Minggu, shiftPagi, shiftSiang, shiftMalam);
            }

            else if (menu == 3) {
                char nama[MAX_NAME_LENGTH];
                printf("\n╔═════ HAPUS DOKTER ═════╗\n");
                getchar(); // flush newline
                printf("Nama Dokter: ");
                fgets(nama, MAX_NAME_LENGTH, stdin);
                nama[strcspn(nama, "\n")] = '\0';

                DeleteDokter(head, nama);
            }

            // === Recalculate and Save ===
            int jumlahDokter = HitungJumlahDokter(*head);
            InisialisasiArrayJadwal(arrayJadwal);

            NodeDokter* curr = *head;
            while (curr != NULL) {
                curr->pelanggaran = 0;
                curr = curr->next;
            }

            LoopTanggal(arrayJadwal, *head, jumlahDokter);

            ExportDokterToCSV(*head, "data/contoh_daftar_dokter.csv");
            ExportJadwalKeCSV("data/jadwal_dokter.csv", arrayJadwal);
        }

        else if (menu == 4) {
            unsigned short int pelanggaranMenu;
            printf("\n╔═════ LIHAT PELANGGARAN ═════╗\n");
            printf("  1. Total pelanggaran\n");
            printf("  2. Per dokter\n");
            printf(">> ");
            scanf("%hu", &pelanggaranMenu);

            if (pelanggaranMenu == 2) {
                PrintPelanggaranPerDokter(*head);
            } else {
                printf("Total pelanggaran preferensi: %d\n", jumlahPelanggaran);
            }
        }

        else if (menu == 5) {
            exitmessege();
            exit = true;
        }

        else {
            printf("Menu tidak tersedia. Silakan pilih antara 1-5.\n");
        }
    }
}

