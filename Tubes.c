#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//List fungsi
void loginAdmin(); 
void menuAdmin();

void loginAdmin(){
    int n = 3;
    char usrAdmin[100], passAdmin[100];
    getchar();
    system("cls");
    while (n > 0){
        printf("Masukkan Username : "); gets(usrAdmin);
        printf("Masukkan Password : "); gets(passAdmin);
        if (strcmp(usrAdmin, "admin") == 0 && strcmp(passAdmin, "admin123") == 0){
            printf("Login Berhasil! Silahkan masuk! ");
            break;
        }
        else {
            printf("Login Gagal! Silahkan coba lagi\n");
            n--;
            if (n == 0) {
                printf("Kesempatan login sudah habis!!");
                break;
            }
            printf("Kesempatan login tersisa %d \n", n);
            printf("\n");
        }
    }
}



//Menu Main
int main(){
    int n;

    system("cls");
    printf("Pilih Menu : \n");
    printf("1. Login Admin\n");
    printf("2. Registrasi User\n");
    printf("3. Login User\n");
    printf("Input Pilihan : "); scanf("%d", &n);
    
    switch (n)
    {
    case 1 :
        loginAdmin();
        break;
    case 2 :
        printf("2. Registrasi User");
        break;
    case 3 :
        printf("3. Login User");
        break;    
    default:
        printf("Pilihan tidak ada dimenu, silahkan pilih ulang!");
        system("pause");
        system("cls");
        break;
    }
}   