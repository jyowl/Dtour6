#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct akun
{
    char username[100], password[100];
} inp;

void regis(){
    printf("Registrasi Akun!\n");
    printf("Masukkan Username\t: "); scanf("%s", inp.username);
    printf("Masukkan Password\t: "); scanf("%s", inp.password);
    system("pause");
    system("cls");
}
void login(){
    char inputus[100], inputpas[100];
    int i;
    printf("Login Akun!\n");
    printf("Masukkan Username\t: "); scanf("%s", inputus);
    printf("Masukka Password\t: "); scanf("%s", inputpas);
    if (strcmp(inputus,inp.username)== 0 && strcmp(inputpas,inp.password)== 0){
        printf("Selamat Datang di D'Tour!\n");
    } else
    {
    }
}

int main(){
    int n;
    printf("Pilih menu (1. Admin/ 2. User) : "); scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("Menu admin :");
        break;
    case 2:
        regis();
        login();
    default:
        break;
    }

}
