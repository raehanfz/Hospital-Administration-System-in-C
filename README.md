# Sistem Penjadwalan Dokter – Tubes PMP Kelompok 9 (2025)

Proyek ini merupakan implementasi **Sistem Penjadwalan Dokter berbasis terminal (command-line)** yang ditulis menggunakan bahasa pemrograman C. Sistem ini dikembangkan sebagai bagian dari Tugas Besar Mata Kuliah *Pememcahan Masalah dengan Pemrograman (PMP)*.

Program ini memungkinkan pihak rumah sakit untuk mengelola data dokter dan menghasilkan jadwal shift selama 30 hari berdasarkan preferensi dan batasan masing-masing dokter.

---

## Struktur Proyek
Tubes-PMP-Kelompok-9-2025/
├── data/ # File CSV (input & output)
│ ├── contoh_daftar_dokter.csv # Contoh input daftar dokter
│ └── jadwal_dokter.csv # Output hasil penjadwalan
├── include/ # File header (.h)
│ ├── antarmuka.h
│ ├── dokter.h
│ └── jadwal.h
├── obj/ # File objek hasil kompilasi
├── src/ # File sumber utama (.c)
│ ├── antarmuka.c
│ ├── dokter.c
│ ├── jadwal.c
│ └── looping.c
├── testing.c # File testing (tidak utama)
├── Makefile # File konfigurasi build
└── README.md # Dokumentasi proyek ini

## Fitur

- Membaca data dokter dari file CSV (`data/contoh_daftar_dokter.csv`)
- Menyusun jadwal shift 30 hari berdasarkan:
  - Preferensi waktu kerja (pagi, siang, malam)
  - Batas maksimal jumlah shift per dokter
- Menyimpan hasil penjadwalan ke file CSV (`data/jadwal_dokter.csv`)
- Menggunakan struktur modular dengan header dan source terpisah
- Mengimplementasikan penyimpanan dinamis menggunakan linked list

---

## Instalasi & Kompilasi

### Prasyarat

- Compiler GCC
- `make` (tersedia di Linux/Mac atau MinGW untuk Windows)

### Kompilasi

Untuk membangun program:

```bash
make
./main.exe
