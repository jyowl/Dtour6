#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIP 100
#define FILE_NAME "jenis_trip.dat"

typedef struct {
    char jenis[50];
    int harga;
} Trip;

// Fungsi untuk menambahkan trip baru
void tambahTrip() {
    FILE *file;
    Trip trip;

    file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return;
    }

    printf("Masukkan jenis trip: ");
    scanf(" %[^\n]", trip.jenis);
    printf("Masukkan harga trip: ");
    scanf("%d", &trip.harga);

    fwrite(&trip, sizeof(Trip), 1, file);
    fclose(file);

    printf("Trip berhasil ditambahkan!\n");
}

// Fungsi untuk melihat dan menampilkan trip (disortir berdasarkan harga - bubble sort)
void lihatTrip() {
    FILE *file;
    Trip trips[MAX_TRIP];
    int n = 0;

    file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return;
    }

    // Membaca data trip ke array
    while (fread(&trips[n], sizeof(Trip), 1, file)) {
        n++;
    }
    fclose(file);

    // Proses bubble sort berdasarkan harga trip (ascending)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (trips[j].harga > trips[j + 1].harga) {
                Trip temp = trips[j];
                trips[j] = trips[j + 1];
                trips[j + 1] = temp;
            }
        }
    }

    // Menampilkan hasil sorting
    printf("\n--- Daftar Trip (Harga Termurah - Termahal) ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s - Rp %d\n", i + 1, trips[i].jenis, trips[i].harga);
    }
}

// Menu admin
void menuAdmin() {
    int pilihan;

    do {
        printf("\n====== MENU ADMIN ======\n");
        printf("1. Tambah Trip Baru\n");
        printf("2. Lihat Daftar Trip\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1-3): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahTrip();
                break;
            case 2:
                lihatTrip();
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 3);
}

// Fungsi utama
int main() {
    menuAdmin();
    return 0;
}
