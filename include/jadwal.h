#ifndef JADWAL_H
#define JADWAL_H

#include <stdbool.h>
#include "dokter.h" 
#define MAX_SHIFT_NAME 10

//header untuk mendefinisikan seluruh fungsi-fungsi yang berkaitan dengan penjadwalan dokter

//struktur data dokter untuk shift tertentu pada suatu tanggal
typedef struct DokterPadaShift {
    char nama[MAX_NAME_LENGTH];
    struct DokterPadaShift* next;
} DokterPadaShift;

//struktur data mengenai suatu shift
typedef struct Shift {
    DokterPadaShift* head;
    unsigned short int kebutuhanDokter;
    bool kebutuhanTerpenuhi;
} Shift;

//struktur data mengenai suatu jadwal dalam 1 hari
typedef struct Jadwal {
    unsigned short int tanggal;
    Shift pagi;
    Shift siang;
    Shift malam;
} Jadwal;

typedef struct MaksShift {
    char nama[MAX_NAME_LENGTH];
    unsigned short int maksShiftPerMinggu;
} MaksShift;

//buat node dokter untuk shift tertentu pada suatu tanggal
//input: nama dokter dari linked-list dokter
//output: node dokter pada shift untuk linked-list dokter pada suatu shift
DokterPadaShift* CreateNodeDokterDiShift(char nama[MAX_NAME_LENGTH]);

//inisialisasi array jadwal kosong
//input: ArrayJadwal (dideklarasikan di main)
//output: ArrayJadwal (dideklarasikan di main) (sebenernya void jadi gak return apa-apa)
void InisialisasiArrayJadwal(Jadwal ArrayJadwal[30]);

//fungsi ini akan mengiterasi linked-list dokter pada tanggal tertentu.
//dicek apakah beberapa kondisi terpenuhi: 
//  Makshift dokter belum nol (artinya dalam seminggu belum di batas shift dokternya)
//  Kebutuhan dokter pada shift tersebut belum terpenuhi
//  Preferensi shift dokter sesuai dengan shift yang lagi butuh dokter
//Jika semua kondisi terpenuh maka dokternya akan di-assign di shift itu

//input: Linked-list dokter (head nya aja, lalu ditransversal) dan address dari element array jadwal (contoh: &ArrayJadwal[0])
//output: Gak ada, fungsinya cuman memperbarui element array jadwal (makanya yang dipass itu addressnya juga, bukan value aja)
void CekMaksShiftKebutuhanPreferensiLaluAssign(NodeDokter* head, Jadwal* jadwal);

//fungsi untuk looping setiap tanggal dan mengecek ketersediaan dokter untuk tanggal tersebut dengan algoritma tertentu
//input: array of Jadwal, head linked-list NodeDokter*, JumlahDokter yang tersedia
//output: void
void LoopTanggal(Jadwal arrayJadwal[30], NodeDokter* head, int jumlahDokter);

//fungsi ini akan mengiterasi linked-list dokter pada tanggal tertentu.
//dicek apakah beberapa kondisi terpenuhi: 
//  Makshift dokter belum nol (artinya dalam seminggu belum di batas shift dokternya)
//  Kebutuhan dokter pada shift tersebut belum terpenuhi
//Jika semua kondisi terpenuh maka dokternya akan di-assign di shift itu

//input: element dari array of Jadwal, head dari linked-list NodeDokter*, jenis shift yang akan dialokasikan
//output: void
void AssignDokterTanpaPreferensi(Jadwal* jadwal, NodeDokter* head, const char* shiftName);

//fungsi untuk mengekstrak maksimal shift dari setiap dokter
//input: head linked-list NodeDokter*, array of MaksShift
//output: void
void AmbilMaksShift(NodeDokter* head, MaksShift arrayMaksShift[]);

//fungsi menentukan dan menampilkan pelanggaran yang dialami setiap dokter
//input: head linked-list NodeDokter*
//output: void
void PrintPelanggaranPerDokter(NodeDokter* head);

//fungsi untuk mereset shift dokter setelah satu minggu (menggunakaan data dari AmbilMaksShift)
//input: head linked-list NodeDokter*, array of MaksShift
//output: void
void ResetMaksShift(NodeDokter* head, MaksShift arrayMaksShift[]);

//fungsi untuk menghitung jumlah dokter yang tersedia
//input: head linked-list NodeDokter*, array of MaksShift
//output: void
int HitungJumlahDokter(NodeDokter* head);

//fungsi untuk free-memory dari linked-list NodeDokter*
//input: head linked-list NodeDokter*, array of MaksShift
//output: void
void FreeListDokter(NodeDokter* head);

//fungsi export jadwal yang sudah digenerate program ke CSV
//input: nama file, array of Jadwal
//output: void
void ExportJadwalKeCSV(const char* filename, Jadwal arrayJadwal[30]);

//fungsi untuk menambahkan dokter pada linked-list NodeDokter*
//input: address dari head linked-list dokter, nama dokter, Maksimal shift dokter, serta preferensi dokter dalam shift pagi, siang, dan malam
//output: void
void AddDokterToDaftarDokter(NodeDokter** daftarDokter, char nama[MAX_NAME_LENGTH], unsigned short int maksShift, bool pagi, bool siang, bool malam);

//fungsi untuk menghapus dokter dari linked-list NodeDokter*
//input: Address dari linked-list NodeDokter*, nama dokter
//output: void
void DeleteDokter(NodeDokter** daftarDokter, char nama[MAX_NAME_LENGTH]);

//fungsi export list dokter yang sudah diperbarui (setelah penambahan atau penghapusan dokter)
//input: nama file, head linked-list daftarDokter
//output: void
void ExportDokterToCSV(NodeDokter* daftarDokter, const char* filename);
#endif
