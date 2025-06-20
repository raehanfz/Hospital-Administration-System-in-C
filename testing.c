#include <stdio.h>
#include <stdbool.h>
#include "dokter.h"
#include "jadwal.h"
#include "antarmuka.h"

int main(void) {
    //deklarasi dan inisialisasi
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data/contoh_daftar_dokter.csv");
    int jumlahDokter = HitungJumlahDokter(daftarDokter); 

    Jadwal ArrayJadwal[30];
    InisialisasiArrayJadwal(ArrayJadwal); 
    int jumlahPelanggaran = 0;

    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    //antarmuka
    antarmuka(ArrayJadwal, jumlahPelanggaran);

    //tulis hasil jadwal ke CSV
    ExportJadwalKeCSV("data/jadwal_dokter.csv", ArrayJadwal);
    FreeListDokter(daftarDokter);
    
    return 0;
}
