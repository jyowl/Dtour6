#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct akun {
    char username[100], password[100];
};
FILE *data_akun;
FILE *data_akun2; //untuk hapus akun customer
FILE *jenis_trip;
FILE *pesanan_trip;
FILE *pembayaran_trip;
FILE *top_up;
FILE *feedback;

//deklarasi nama File
void regisUser();
void loginUser();
void menuUser();
void jenisTrip();
void lihatTrip();
void menuAdmin();
void lihatPenghasilan();
void lihatAkun();

//fungsi user
void regisUser();
int loginUser(int attempt);
void menuUser();

int main();

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

void loginUser(){ //cara while loop
    data_akun = fopen("data_akun.dat", "rb");
    struct akun login, data_acc;
    bool found = false;
    int kesempatan = 3;
    
    system("cls");
    if (data_akun == NULL) {
        printf("File tidak bisa dibuka.\n");
         return;
     }
    
    system("cls");
    printf("==Login Akun User==\n\n");
    printf("Masukkan Username : "); gets(login.username);
    printf("Masukkan Password : "); gets(login.password);
    printf("\n");

    while (fread(&data_acc, sizeof(struct akun), 1 , data_akun) != 0) {
        if (strcmp(login.username, data_acc.username) == 0 &&
            strcmp(login.password, data_acc.password)== 0) {
            found = true;
            printf("Login berhasil! Selamat datang di DTour %s!! \n", login.username);
            fclose(data_akun);
            system("pause");
            menuUser();  
            break;
        } 
    } 
    fclose(data_akun);
    
    if (!found){
        printf("Username atau password salah, silahkan coba lagi!!\n");
        system("pause");
    }
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
        jenisTrip();
        break;
    case 2:
        lihatTrip();
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        printf("Anda berhasil logout sampai jumpa kembali..\n");
        system("cls");
        main();
    default:
        break;
    }

}


void jenisTrip(){
    jenis_trip = fopen("jenis_trip.dat", "ab");

}

void lihatTrip(){
    jenis_trip = fopen("jenis_trip.dat", "rb");
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

void menuUser(){
    int mU;
    system("cls");
    printf("Menu User :\n");
    printf("1. Melihat Jenis Trip\n");
    printf("2. Memesan Trip\n");
    printf("3. Pembayaran\n");
    printf("4. Top Up Saldo\n");
    printf("5. Riwayat Trip\n");
    printf("6. Feedback");
    printf("7. Ganti Password\n");
    printf("8. Log Out\n");

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
        break;
    case 7:
        break;
    case 8:
        printf("Anda berhasil logout sampai jumpa kembali..\n");
        system("cls");
        main();
    default:
        break;
    }

}

void MjenisTrip(){
    jenis_trip = fopen("jenis_trip.dat", "rb");
}

void lihatPenghasilan(){
    pembayaran_trip = fopen("pembayaran_trip.dat", "rb");
    top_up = fopen("top_up.dat", "rb");
}

void lihatAkun(){
    data_akun = fopen("data_akun.dat", "rb");
    while (fread(&user, sizeof(struct akun), 1, data_akun)) {
        printf("Username : %s\n", user.username);
        printf("Nama : %s\n", user.nama);
        printf("Alamat : %s\n", user.alamat);
        printf("No HP : %s\n", user.no_hp);
        printf("Email : %s\n", user.email);
        printf("\n");
    }
    fclose(data_akun);
}


//fungsi User
void MemesanTrip(){

}

void Pembayaran(){

}

void TopUp(){

}

void RiwayatTrip(){

}

void Feedback(){

}

void GantiPassword(){

}