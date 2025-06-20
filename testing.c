#include <stdio.h>
#include <stdbool.h>
#include "dokter.h"
#include "jadwal.h"
#include "antarmuka.h"

int main(void) {
    //deklarasi dan inisialisasi
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data_dummy/contoh_daftar_dokter.csv");
    int jumlahDokter = HitungJumlahDokter(daftarDokter); 

    Jadwal ArrayJadwal[30];
    InisialisasiArrayJadwal(ArrayJadwal); 
    int jumlahPelanggaran = 0;

    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    //antarmuka
    antarmuka(ArrayJadwal, jumlahPelanggaran);
    //to debug
    //PrintListDokter(daftarDokter);

    //tulis hasil jadwal ke CSV


    ExportJadwalKeCSV("jadwal_dokter.csv", ArrayJadwal);
    FreeListDokter(daftarDokter);
    
    return 0;
}
