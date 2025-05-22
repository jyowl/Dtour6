#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct akun {
    char username[100], password[100];
    char nama[100];
    char alamat[100];
    char no_hp[100];
    char email[100];
    char feedback[300];
} user, aktif;

struct TopUp {
    float nominal;
};

//deklarasi nama File
FILE *data_akun;
FILE *data_akun2; //untuk hapus akun customer
FILE *jenis_trip;
FILE *pesanan_trip;
FILE *pembayaran_trip;
FILE *top_up;
FILE *feedback;

//fungsi admin
void loginAdmin();
void jenisTrip();
void lihatTrip();
void menuAdmin();
void lihatPenghasilan();
void lihatAkun();
void hapusAkun();
void feedbackAdmin();

//fungsi user
void regisUser();
int loginUser(int attempt);
void menuUser();
void TopUp();
void Feedback();

int main();


void loginAdmin(){
    printf("== Login Admin ==\n");
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
    int attempt = 3;
    int n;

    system("cls");
    data_akun = fopen("data_akun.dat", "ab");
    struct akun regisUs;

    printf("==Registrasi Akun User==\n\n");
    printf("Masukkan Username : "); gets(regisUs.username);
    printf("Masukkan Password : "); gets(regisUs.password);
    printf("Masukkan Nama : "); gets(regisUs.nama);
    printf("Masukkan Alamat : "); gets(regisUs.alamat);
    printf("Masukkan No HP : "); gets(regisUs.no_hp);
    printf("Masukkan Email : "); gets(regisUs.email);
    printf("\n");

    fwrite(&regisUs , sizeof(struct akun), 1 , data_akun);
    printf("\n");
    printf("Akun berhasil ditambahkan!!\n");
    system("pause");

    fclose(data_akun);

    printf("\n");
    printf("1. Login User\n");
    printf("2. Kembali ke Menu Utama\n");
    printf("Pilih Menu : "); scanf("%d", &n);
    getchar();
    switch (n)
    {
    case 1:
        system("cls");
        loginUser(attempt);
        break;
    case 2:
        main();
        break;
    default:
        printf("Pilihan tidak valid!!\n");
        break;
    }
    
}

int loginUser(int attempt){ 
    data_akun = fopen("data_akun.dat", "rb");
    char username[50], password[50];

    printf("== Login User ==\n");
    printf("Username : "); gets(username);
    printf("Password : "); gets(password);

    while (fread(&user, sizeof(struct akun), 1, data_akun))
    {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0)
        {
            aktif = user;
            printf("Selamat datang %s di D'Tour!!\n", aktif.username);
            fclose(data_akun);
            menuUser();
            return 0;
        }
    }
    
    attempt--;
    fclose(data_akun);

    if (attempt > 0) {
        system("cls");
        printf("Username atau password salah, silahkan coba lagi!!\n");
        printf("Kesempatan anda tersisa %d\n", attempt);
        system("pause");
        system("cls");
        loginUser(attempt);
    } else{
        printf("Kesempatan anda sudah habis, silahkan refresh.\n");
        system("pause");
        system("cls");
        main();
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
    printf("5. Melihat Feedback\n");
    printf("6. Hapus Data Customer\n");
    printf("7. Log Out\n");

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
        lihatAkun();
        break;
    case 5:
        feedbackAdmin();
        break;
    case 6:
        hapusAkun();
        break;
    case 7:
        printf("Anda berhasil logout sampai jumpa kembali..\n");
        system("cls");
        main();
        break;
    default:
        break;
    }

}

int main(){
    int n, attempt = 3;
    
    //system("cls");
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
        system("cls");
        loginUser(attempt);
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
    printf("6. Feedback\n");
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
        TopUp();
        break;
    case 5:
        break;
    case 6:
        Feedback();
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


//fungsi Admin
void jenisTrip(){
    jenis_trip = fopen("jenis_trip.dat", "rb");

}

void lihatTrip(){
    jenis_trip = fopen("jenis_trip.dat", "rb");
}

void lihatPenghasilan(){
    pembayaran_trip = fopen("pembayaran_trip.dat", "rb");
    top_up = fopen("top_up.dat", "rb");
}

void feedbackAdmin(){
    FILE *feedback;
    system("cls");
    feedback = fopen("feedback.dat", "rb");
    if (feedback == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    printf("== Daftar Feedback Usser ==\n");
    while (fread(&user, sizeof(struct akun), 1, feedback)) {
        printf("Username : %s\n", user.username);
        printf("Feedback : %s\n", user.feedback);
        printf("\n");
    }
    fclose(feedback);
    printf("\n");

    printf("Tekan Enter untuk kembali ke menu admin...\n");
    system("pause");
    system("cls");
    menuAdmin();
}

void lihatAkun(){
    FILE *data_akun;
    struct akun user[100];
    int count = 0;

    data_akun = fopen("data_akun.dat", "rb");
    if(data_akun == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }

    while (fread(&user[count], sizeof(struct akun), 1, data_akun)) {
        count++;
    }
    fclose(data_akun);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(user[j].username, user[j + 1].username) > 0) {
                struct akun temp = user[j];
                user[j] = user[j + 1];
                user[j + 1] = temp;
            }
        }
    }   
    printf("\n== Daftar Akun User ==\n");
    for (int i = 0; i < count; i++) {
        printf("Username : %s\n", user[i].username);
        printf("Nama : %s\n", user[i].nama);
        printf("Alamat : %s\n", user[i].alamat);
        printf("No HP : %s\n", user[i].no_hp);
        printf("Email : %s\n", user[i].email);
        printf("\n");
    }

    printf("Tekan Enter untuk kembali ke menu admin...\n");
    system("pause");
    menuAdmin();
}

void hapusAkun(){
    system("cls");
    struct akun user;
    char usnhapus[50];
    bool found = false;
    
    printf("Masukkan username yang ingin dihapus : "); gets(usnhapus);
    data_akun = fopen("data_akun.dat", "rb");
    data_akun2 = fopen("data_akun2.dat", "wb");

    if (data_akun == NULL || data_akun2 == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    
    while (fread(&user, sizeof(struct akun), 1, data_akun)) {
        if (strcmp(user.username, usnhapus) != 0) {
            fwrite(&user, sizeof(struct akun), 1, data_akun2);
        } else {
            found = true;
        }
    }

    fclose(data_akun);
    fclose(data_akun2);

    if(found){
        remove("data_akun.dat");
        rename("data_akun2.dat", "data_akun.dat");
        printf("Akun dengan username %s berhasil dihapus.\n", usnhapus);
    } else {
        remove("data_akun2.dat");
        printf("Akun dengan username %s tidak ditemukan.\n", usnhapus);
    }

    printf("\n");
    printf("Tekan Enter untuk kembali ke menu admin...\n");
    system("pause");
    menuAdmin();
}

//fungsi User
void MemesanTrip(){
    
}

void Pembayaran(){

}

void TopUp(){
    top_up = fopen("top_up.dat", "ab");
    if (!top_up) {                       
        perror("File tidak bisa dibuka");
        return;
    }

    float nominal;
    printf("\nMasukkan nominal saldo yang akan di-top-up (Rp): ");
    if (scanf("%f", &nominal) != 1 || nominal <= 0) {
        puts("Nominal tidak valid – proses dibatalkan.");
        fclose(top_up);
        while (getchar() != '\n');
        return;
    }
    getchar();

    struct TopUp rek;
    rek.nominal = nominal;
    if (fwrite(&rek, sizeof(struct TopUp), 1, top_up) != 1) {
        puts("Gagal menyimpan data top-up!");
    } else {
        printf("Tekan Enter untuk kembali ke menu user...\n");
        system("cls");
        system("pause");
        printf("Top-up sebesar Rp %.2f berhasil disimpan.\n", nominal);
    }
}

void RiwayatTrip(){
    FILE *RiwayatTrip;
     struct{
        char namaTrip[50];
        float hargaTrip;
     }pesananTrip;

    int ditemukan = 0;

     RiwayatTrip = fopen("pesanan_trip.dat", "rb");

    if(RiwayatTrip == NULL) {
        printf("Tidak ada riwayat pesanan\n");
        return 1;
    }
     printf("== Riwayat Trip ==\n");
     while(fread(&user, sizeof(pesananTrip), 1, RiwayatTrip) == 1){
        printf("Trip : %s\n", pesananTrip.namaTrip);
        printf("Harga : Rp %.2f\n\n", pesananTrip.hargaTrip);
        ditemukan = 1;
     }

     if(!ditemukan){
        printf("Tidak ada riwayat pesanan\n");
     }

     fclose(RiwayatTrip);
     printf("Kembali ke menu user\n");

    }

void Feedback(){
    FILE *feedback;

    printf("\n");
    printf("== Feedback ==\n");
    feedback = fopen("feedback.dat", "ab");
    if (feedback == NULL){
        printf("Tidak ada feedback user\n");
    } else {
        printf("Masukkan pesan feedback Anda: ");
        fgets(user.feedback, sizeof(user.feedback), stdin);
        user.feedback[strcspn(user.feedback, "\n")] = '\0';

        fwrite(&user, sizeof(struct akun), 1, feedback);
    
        fclose(feedback);
    }
    printf("Feedback berhasil disimpan.\n");
    printf("Tekan Enter untuk kembali ke menu user...\n");
    system("pause");
    system("cls");
    menuUser(); 
}

void GantiPassword(){

}