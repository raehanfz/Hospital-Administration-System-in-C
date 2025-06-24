#ifndef DOKTER_H
#define DOKTER_H

#include <stdbool.h>
#define MAX_NAME_LENGTH 64

//header berisi fungsi-fungsi yang secara eksklusif hanya berhubungan dengan dokter (tidak dengan jadwal ataupun antarmuka)

//struktur data informasi dokter
typedef struct NodeDokter {
    char nama[MAX_NAME_LENGTH];
    unsigned short int maksShiftPerMinggu;
    bool shiftPagi;
    bool shiftSiang;
    bool shiftMalam;
    unsigned short int pelanggaran;
    struct NodeDokter* next;
} NodeDokter;

//fungsi membuat Node baru dokter
//input: nama dokter, Maksimal shift dokter, serta preferensi dokter dalam shift pagi, siang, dan malam
//output: Node untuk linked-list dokter yang memuat informasi dari input
NodeDokter* CreateNodeDokter(char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam);

//fungsi untuk menyusun ulang linked-list NodeDokter* untuk minimalisasi pelanggaran preferensi dokter ketika penyusunan jadwal
//fungsi menyusun dokter dengan dokter yang memiliki preferensi lebih luas diletakkan di bagian belakang linked-list (diakses belakangan saat iterasi)
//input: address dari head linked-list NodeDokter*
//output: void
void PrioritizeDokterList(NodeDokter** head);

//fungsi untuk mengakumilasi pelanggaran yang dialami setiap dokter
//input: head linked-list NodeDokter*
//output: total pelanggaran dalam integer
int HitungTotalPelanggaran(NodeDokter* head);

//membaca file CSV dan membentuk linked list dokter
//input: nama file csv
//output: Linked-list dokter, yang direturn adalah head dari linked-listnya
NodeDokter* BacaDaftarDokterDariFile(const char* filename);

// Fungsi debug (opsional, buat testing aja)
void PrintListDokter(NodeDokter* head);

#endif
