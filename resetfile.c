#include<stdio.h>

int main(){
FILE *data_akun = fopen("data_akun.dat", "wb");
if (data_akun != NULL) {
    fclose(data_akun);
    printf("File berhasil direset (kosong).\n");
} else {
    printf("Gagal membuka file.\n");
}
}