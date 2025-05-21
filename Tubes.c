#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct akun
{
    char username[100], password[100];
};
FILE *data_akun;



//deklarasi nama File
void regisUser();
void loginUser();
void menuUser();
int main();


void regisUser(){
    system("cls");
    data_akun = fopen("data_akun.dat", "ab");
    struct akun regisUs;
    printf("==Registrasi Akun User==\n\n");
    printf("Masukkan Username : "); gets(regisUs.username);
    printf("Masukkan Password : "); gets(regisUs.password);

    fwrite(&regisUs , sizeof(struct akun), 1 , data_akun);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(data_akun);
    loginUser();
}

void loginUser(){
    data_akun = fopen("data_akun.dat", "rb");
    struct akun login, data_acc;

    system("cls");
    printf("==Login Akun User==\n\n");
    printf("Masukkan Username : "); gets(login.username);
    printf("Masukkan Password : "); gets(login.password);
    printf("\n");

    while (fread(&data_acc, sizeof(struct akun), 1 , data_akun) != 0) {
        if (strcmp(login.username, data_acc.username) == 0 &&
            strcmp(login.password, data_acc.password)== 0) {
            printf("Login berhasil! Selamat datang di DTour %s!!!\n", login.username);
            system("pause");
            menuUser();
            break;
        } 
    } 
    
    printf("Username tidak ditemukan, silahkan registrasi terlebih dahulu!!\n");
    system("pause");    
    fclose(data_akun);
}

void menuAdmin(){
    int mA;
    system("cls");
    printf("Menu Utama :\n");
    printf("1. Menambah Trip\n");
    printf("2. Melihat Jenis Trip\n");
    printf("3. Melihat Penghasilan\n");
    printf("4. Melihat Akun Customer\n");
    printf("5. Melihat Penghasilan\n");
    printf("6. Log Out\n");

    printf("Pilih Menu : "); scanf("%d", &mA);
    getchar();
    switch (mA)
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

void loginAdmin(){
    char usAdmin[50], pasAdmin[50];
    const char Adminusn[50]  = "admin";
    const char Adminpas[50]  = "admin123";
    int chance = 3;

    printf("Username Admin : "); gets(usAdmin);
    printf("Password Admin : "); gets(pasAdmin);

    if (strcmp(usAdmin, Adminusn)== 0 && strcmp(pasAdmin, Adminpas)== 0)
    {
        printf("Selamat datang Admin di D'Tour!!\n");
        menuAdmin();
    } else {
        while (chance >= 0)
        {
            if (chance == 0){
                printf("Kesempatan anda sudah habis, silahkan refresh.\n");
                break;
            } 
            printf("Username dan password anda salah silahkan coba lagi!!\n");
            printf("Kesempatan anda tersisa %d\n", chance); 
            printf("Username Admin : "); gets(usAdmin);
            printf("Password Admin : "); gets(pasAdmin);
            if (strcmp(usAdmin, Adminusn)== 0 && strcmp(pasAdmin, Adminpas)== 0){
            printf("Selamat datang Admin di D'Tour!!");
            menuAdmin();
            } 
            chance--;
            printf("\n");
        }
    }
}

void jenisTrip(){
    
}

int main(){
    int n;

    system("cls");
    printf("Menu Utama :\n");
    printf("1. Login Admin\n");
    printf("2. Registrasi User\n");
    printf("3. Login User\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();
    switch (n)
    {
    case 1:
        loginAdmin();
        break;
    case 2:
        regisUser();
        break;
    case 3:
        loginUser();
        break;
    default:
        break;
    }
}

