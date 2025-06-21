#include <stdio.h>
#include <stdbool.h>
#include "dokter.h"
#include "jadwal.h"
#include "antarmuka.h"

int main(void) {
    // Baca daftar dokter dari file CSV
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data/contoh_daftar_dokter.csv");

    // Optimalisasi urutan linked-list
    PrioritizeDokterList(&daftarDokter);
    
    // Inisialisasi array jadwal kosong
    Jadwal ArrayJadwal[30];
    InisialisasiArrayJadwal(ArrayJadwal); 
    
    // Hitung jumlah dokter
    int jumlahDokter = HitungJumlahDokter(daftarDokter); 
    
    // Hitung penjadwalan awal
    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter);

    // Hitung pelanggaran awal
    int jumlahPelanggaran = HitungTotalPelanggaran(daftarDokter);

    // Jalankan antarmuka (yang kini sudah otomatis handle semua perubahan & CSV update)
    antarmuka(ArrayJadwal, &daftarDokter, jumlahPelanggaran);

    // Free memory
    FreeListDokter(daftarDokter);
    return 0;
}
