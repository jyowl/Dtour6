#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void menuAdmin(){
    int mU;
    system("cls");
    printf("Menu Utama :\n");
    printf("1. Melihat Jenis Trip\n");
    printf("2. Memesan Trip\n");
    printf("3. Pembayaran\n");
    printf("4. Top Up Saldo\n");
    printf("5. Riwayat Trip\n");
    printf("6. Log Out\n");

    printf("Pilih Menu : "); scanf("%d", &mU);
    getchar();
    switch (mU)
    {
    case 1:
        break;
    case 2:
        break;
    
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        printf("Anda berhasil logout sampai jumpa kembali..\n");
        system("cls");
        main();
    default:
        break;
    }

}