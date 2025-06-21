#include <stdio.h>
#include <stdbool.h>
#include "dokter.h"
#include "jadwal.h"
#include "antarmuka.h"

int main(void) {
    // 1. Baca daftar dokter dari file CSV
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data/contoh_daftar_dokter.csv");
    
    // 2. Inisialisasi array jadwal kosong
    Jadwal ArrayJadwal[30];
    InisialisasiArrayJadwal(ArrayJadwal); 
    
    // 3. Hitung jumlah dokter
    int jumlahDokter = HitungJumlahDokter(daftarDokter); 
    
    // 4. Hitung penjadwalan awal
    int jumlahPelanggaran = 0;
    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    // 5. Jalankan antarmuka (user bisa menambah/menghapus dokter)
    antarmuka(ArrayJadwal, &daftarDokter, jumlahPelanggaran);

    // 6. Simpan daftar dokter terbaru ke CSV
    ExportDokterToCSV(daftarDokter, "data/contoh_daftar_dokter.csv");

    // 7. Hitung ulang jumlah dokter
    jumlahDokter = HitungJumlahDokter(daftarDokter);

    // 8. Inisialisasi ulang jadwal (karena daftar dokter berubah)
    InisialisasiArrayJadwal(ArrayJadwal);

    // 9. Jadwalkan ulang dengan data terbaru
    jumlahPelanggaran = 0;
    LoopTanggal(ArrayJadwal, daftarDokter, jumlahDokter, &jumlahPelanggaran);

    // 10. Simpan jadwal ke file
    ExportJadwalKeCSV("data/jadwal_dokter.csv", ArrayJadwal);

    // 11. Free memory
    FreeListDokter(daftarDokter);

    return 0;
}
