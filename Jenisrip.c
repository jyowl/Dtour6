#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxJenis 50

/* Tidak menggunakan typedef struct */
struct Trip {
    char jenis[MaxJenis];
    double harga;
};

void tambahTrip(void)
{
    /* Deklarasi variabel dan membuka file */
    FILE *fp = fopen("jenis_trip.dat", "ab");

    if (fp == NULL) {
        puts("file tidak bisa dibuka");
        return;
    }

    /* Input data trip */
    struct Trip dataBaru;

    printf("Masukkan jenis trip  : ");
    fgets(dataBaru.jenis, sizeof(dataBaru.jenis), stdin);
    dataBaru.jenis[strcspn(dataBaru.jenis, "\n")] = '\0';  // Hapus newline

    printf("Masukkan harga trip : ");
    while (scanf("%lf", &dataBaru.harga) != 1) {
        puts("Input tidak valid! Masukkan angka.");
        while (getchar() != '\n');  // Bersihkan buffer
    }
    getchar();  // Buang newline sisa

    /* Simpan ke file */
    fwrite(&dataBaru, sizeof(struct Trip), 1, fp);
    fclose(fp);

    puts("Data trip berhasil disimpan!");
}

int main(void)
{
    int pilih;

    do {
        puts("\n=== MENU ADMIN ===");
        puts("1. Tambah Trip baru");
        puts("0. Keluar");
        printf("Pilihan Anda: ");
        if (scanf("%d", &pilih) != 1) {
            puts("Input tidak valid!");
            while (getchar() != '\n');
            continue;
        }
        getchar();  // Buang newline

        switch (pilih) {
            case 1:
                tambahTrip();
                break;
            case 0:
                puts("Terima kasih!");
                break;
            default:
                puts("Pilihan tidak tersedia!");
        }
    } while (pilih != 0);

    return 0;
}
