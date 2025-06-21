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
    int jumlahPelanggaran = 0;
    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    // Jalankan antarmuka (user bisa menambah/menghapus dokter)
    antarmuka(ArrayJadwal, &daftarDokter, jumlahPelanggaran);

    // Simpan daftar dokter terbaru ke CSV
    ExportDokterToCSV(daftarDokter, "data/contoh_daftar_dokter.csv");

    // Hitung ulang jumlah dokter
    jumlahDokter = HitungJumlahDokter(daftarDokter);

    // Inisialisasi ulang jadwal (karena daftar dokter berubah)
    InisialisasiArrayJadwal(ArrayJadwal);

    // Jadwalkan ulang dengan data terbaru
    jumlahPelanggaran = 0;
    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    // Simpan jadwal ke file
    ExportJadwalKeCSV("data/jadwal_dokter.csv", ArrayJadwal);

    // Free memory
    FreeListDokter(daftarDokter);

    return 0;
}
