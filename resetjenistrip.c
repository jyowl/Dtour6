#include<stdio.h>

int main(){
    FILE *jenis_trip;
    jenis_trip = fopen("jenis_trip.dat", "wb");
    if (jenis_trip != NULL) {
        fclose(jenis_trip);
        printf("File feedback berhasil direset (kosong).\n");
    } else {
        printf("Gagal membuka file feedback.\n");
    }


}