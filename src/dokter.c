#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dokter.h"

#define FILE_NEWLINE_BUFFER 100

//fungsi untuk membuat node mengenai informasi dokter
NodeDokter* CreateNodeDokter(char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam) {
    NodeDokter* temp = (NodeDokter*)malloc(sizeof(NodeDokter));
    strncpy(temp->nama, nama, MAX_NAME_LENGTH - 1);
    temp->nama[MAX_NAME_LENGTH - 1] = '\0';
    temp->maksShiftPerMinggu = maksShift;
    temp->shiftPagi = pagi;
    temp->shiftSiang = siang;
    temp->shiftMalam = malam;
    temp->next = NULL;
    return temp;
}
 //fungis membaca file csv berisi data dokter
NodeDokter* BacaDaftarDokterDariFile(const char* filename) {
    FILE* fileDokter = fopen(filename, "r");
    if (!fileDokter) {
        perror("File tidak ditemukan");
        exit(EXIT_FAILURE);
    }

    char buffer[FILE_NEWLINE_BUFFER];
    fgets(buffer, FILE_NEWLINE_BUFFER, fileDokter); // skip header

    NodeDokter* head = NULL;
    NodeDokter* current = NULL;

    while (fgets(buffer, FILE_NEWLINE_BUFFER, fileDokter)) {
        char* token;
        char nama[MAX_NAME_LENGTH];
        unsigned short int maksShift;
        bool pagi, siang, malam;

        token = strtok(buffer, ",");
        strncpy(nama, token, MAX_NAME_LENGTH - 1); nama[MAX_NAME_LENGTH - 1] = '\0';
        maksShift = (unsigned short int)atoi(strtok(NULL, ","));
        pagi = strcmp(strtok(NULL, ","), "true") == 0;
        siang = strcmp(strtok(NULL, ","), "true") == 0;
        malam = strcmp(strtok(NULL, ",\n"), "true") == 0;

        NodeDokter* newNode = CreateNodeDokter(nama, maksShift, pagi, siang, malam);
        if (head == NULL) head = newNode;
        else current->next = newNode;
        current = newNode;
    }

    fclose(fileDokter);
    return head;
}

//fungsi debug (opsinonal, buat print aja)
void PrintListDokter(NodeDokter* head) {
    while (head) {
        printf("Nama: %s, Maks: %d, Pagi: %d, Siang: %d, Malam: %d\n",
            head->nama, head->maksShiftPerMinggu,
            head->shiftPagi, head->shiftSiang, head->shiftMalam);
        head = head->next;
    }
}
