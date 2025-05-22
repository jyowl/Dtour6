#include<stdio.h>

int main(){

    FILE *feedback = fopen("feedback.dat", "wb");
    if (feedback != NULL) {
        fclose(feedback);
        printf("File feedback berhasil direset (kosong).\n");
    } else {
        printf("Gagal membuka file feedback.\n");
    }
}