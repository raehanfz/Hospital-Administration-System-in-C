#include <stdio.h>
#include "include/dokter.h"
#include "include/jadwal.h"

int main(void) {
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data_dummy/contoh_daftar_dokter.csv");
    PrintListDokter(daftarDokter);

    // Jadwal ArrayJadwal[30];
    // InisialisasiJadwal(ArrayJadwal, 30);
    return 0;
}
