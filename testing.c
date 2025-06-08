#include <stdio.h>
#include "include/dokter.h"
#include "include/jadwal.h"

int main(void) {
    NodeDokter* daftarDokter = BacaDaftarDokterDariFile("data_dummy/contoh_daftar_dokter.csv");
    PrintListDokter(daftarDokter);

    return 0;
}
