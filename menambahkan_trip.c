#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk jenis trip
typedef struct {
    char jenis[50];
    int harga;
} Trip;

void tambahTripBaru() {
    FILE *file;
    Trip tripBaru;

    // Deklarasi file dan variabel
    const char *namaFile = "jenis_trip.dat";

    // Buka file dengan mode append binary
    file = fopen(namaFile, "ab");
    
    // Cek apakah file bisa dibuka
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return;
    }

    // Input jenis trip dan harga
    printf("Masukkan jenis trip: ");
    fflush(stdin);
    fgets(tripBaru.jenis, sizeof(tripBaru.jenis), stdin);
    tripBaru.jenis[strcspn(tripBaru.jenis, "\n")] = 0;  // Hapus newline
    printf("Masukkan harga trip: ");
    scanf("%d", &tripBaru.harga);

    // Simpan data ke file
    fwrite(&tripBaru, sizeof(Trip), 1, file);
    printf("Trip berhasil ditambahkan.\n");

    // Tutup file
    fclose(file);

    // Kembali ke menu admin
    printf("Kembali ke Menu Admin...\n");
}

int main() {
    // Fungsi utama sebagai admin
    int pilihan;
    
    do {
        printf("=== Menu Admin ===\n");
        printf("1. Tambah Trip Baru\n");
        printf("2. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahTripBaru();
                break;
            case 2:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

        printf("\n");
    } while (pilihan != 2);

    return 0;
}
