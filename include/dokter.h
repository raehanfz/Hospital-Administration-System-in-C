#ifndef DOKTER_H
#define DOKTER_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 30

//struktur data informasi dokter
typedef struct NodeDokter {
    char nama[MAX_NAME_LENGTH];
    unsigned short int maksShiftPerMinggu;
    bool shiftPagi;
    bool shiftSiang;
    bool shiftMalam;
    struct NodeDokter* next;
} NodeDokter;

//membuat Node baru dokter
//input: nama dokter, makshift, dan preferensi. Semuanya disimpan pada variabel di program
//output: Node untuk linked-list dokter yang memuat informasi dari input
NodeDokter* CreateNodeDokter(char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam);

//membaca file CSV dan membentuk linked list dokter
//input: nama file csv
//output: Linked-list dokter, yang direturn adalah head dari linked-listnya
NodeDokter* BacaDaftarDokterDariFile(const char* filename);

// Fungsi debug (opsional, buat testing aja)
void PrintListDokter(NodeDokter* head);

#endif
