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


void printJadwalMingguan(Jadwal ArrayJadwal[30], int minggu) {
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                JADWAL MINGGU KE-%d                                   ║\n", minggu);
    printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (minggu == 5) {
        minggu = 4; // week 5 is just 2 days
    } else {
        minggu -= 1;
    }

    const int hariMax = (minggu == 4) ? 2 : 7;

    for (int i = 0; i < hariMax; i++) {
        int idx = i + 7 * minggu;

        printf("╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ Tanggal: %2d                                                                         ║\n", idx + 1);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");

        // Print Pagi
        printf("║ Shift Pagi                                                                           ║\n");
        DokterPadaShift* pagi = ArrayJadwal[idx].pagi.head;
        if (!pagi) {
            printf("║   (Kosong)                                                                           ║\n");
        } else {
            while (pagi) {
                printf("║   - %-80s║\n", pagi->nama);
                pagi = pagi->next;
            }
        }

        // Print Siang
        printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ Shift Siang                                                                          ║\n");
        DokterPadaShift* siang = ArrayJadwal[idx].siang.head;
        if (!siang) {
            printf("║   (Kosong)                                                                           ║\n");
        } else {
            while (siang) {
                printf("║   - %-80s║\n", siang->nama);
                siang = siang->next;
            }
        }

        // Print Malam
        printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ Shift Malam                                                                          ║\n");
        DokterPadaShift* malam = ArrayJadwal[idx].malam.head;
        if (!malam) {
            printf("║   (Kosong)                                                                           ║\n");
        } else {
            while (malam) {
                printf("║   - %-80s║\n", malam->nama);
                malam = malam->next;
            }
        }

        printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");
    }
}

void printJadwal(Jadwal ArrayJadwal[30]) {
    printf("\n╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                JADWAL BULANAN                                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");

    for (int minggu = 1; minggu <= 5; minggu++) {
        printJadwalMingguan(ArrayJadwal, minggu);
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
        printf("║   MANAJEMEN RUMAH SAKIT ALEXANDER KNALPOT  ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("Pilih menu (masukkan angka):\n");
        printf("  1. Lihat Jadwal Dokter\n");
        printf("  2. Tambah Dokter\n");
        printf("  3. Hapus Dokter\n");
        printf("  4. Lihat Pelanggaran Preferensi\n");
        printf("  5. Keluar\n");
        printf(">> ");

        if(scanf("%d", &menu) == 1){
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
                    if (minggu >= 1 && minggu <= 5)
                        printJadwalMingguan(arrayJadwal, minggu);
                    else
                        printf("Minggu tidak valid!\n");
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

                if (scanf("%hu", &pelanggaranMenu)==1){
                    if(pelanggaranMenu == 2) {
                        PrintPelanggaranPerDokter(*head);
                    } else if (pelanggaranMenu == 1) {
                        printf("Total pelanggaran preferensi: %d\n", jumlahPelanggaran);
                    } else {
                        printf("input tidak valid!");
                    }
                } else {
                    printf("input tidak valid!");                    
                }
                
            }

            else if (menu == 5) {
                exitmessege();
                exit = true;
            }

            else {
                printf("Menu tidak tersedia. Silakan pilih antara 1-5.\n");
            }
        } else {
            printf("Input tidak valid! masukkan integer.\n");

            while (getchar() != '\n');
        }
    }
}

