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

// Membuat Node baru dokter
NodeDokter* CreateNodeDokter(char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam);

// Membaca file CSV dan membentuk linked list dokter
NodeDokter* BacaDaftarDokterDariFile(const char* filename);

// Fungsi debug (opsional, buat testing aja)
void PrintListDokter(NodeDokter* head);

#endif
