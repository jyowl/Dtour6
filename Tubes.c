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
    float nominal;
} user, aktif;

struct TopUp {
    float nominal;
};

struct trip{
    char namaTrip[100];
    float hargaTrip;
    char deskripsiTrip[300];
    int idTrip;
};

struct pesanan {
    char username[30];
    int idTrip;
    char namaTrip[100];
    float hargaTrip;
};

struct pembayaran {
    char username[30];
    int idTrip;
    char namaTrip[50];
    float hargaTrip;
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
void lihatTripUs();
int pembayaran(float hargaTrip);
void MemesanTrip();
void RiwayatTrip();
void tampilkanSaldoUser();
void GantiPassword();

//fungsi utama
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
    printf("Selamat datang %s di D'Tour!!\n", aktif.username);
    tampilkanSaldoUser();
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
        lihatTripUs();
        break;
    case 2:
        MemesanTrip();
        break;
    case 3:
        break;
    case 4:
        TopUp();
        break;
    case 5:
        RiwayatTrip();
        break;
    case 6:
        Feedback();
        break;
    case 7:
        GantiPassword();
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
    FILE *jenis_trip;
    struct trip trip;

    jenis_trip = fopen("jenis_trip.dat", "ab");
    if (jenis_trip == NULL) {
        printf("Gagal membuka file jenis_trip.dat\n");
        return;
    }

    printf("\n== Tambah Jenis Trip ==\n");
    
    printf("Masukkan ID Trip         : ");
    scanf("%d", &trip.idTrip);
    getchar(); 

    printf("Masukkan Nama Trip       : ");
    fgets(trip.namaTrip, sizeof(trip.namaTrip), stdin);
    trip.namaTrip[strcspn(trip.namaTrip, "\n")] = '\0';

    printf("Masukkan Deskripsi Trip  : ");
    fgets(trip.deskripsiTrip, sizeof(trip.deskripsiTrip), stdin);
    trip.deskripsiTrip[strcspn(trip.deskripsiTrip, "\n")] = '\0';

    printf("Masukkan Harga Trip (Rp) : ");
    scanf("%f", &trip.hargaTrip);
    getchar(); 

    fwrite(&trip, sizeof(struct trip), 1, jenis_trip);
    fclose(jenis_trip);

    printf("Trip berhasil ditambahkan!\n");
    printf("Tekan Enter untuk kembali ke menu admin...\n");
    system("pause");
    system("cls");
    menuAdmin();
    getchar();
}

void lihatTrip(){
    system("cls");
    jenis_trip = fopen("jenis_trip.dat", "rb");
    FILE *jenis_trip = fopen("jenis_trip.dat", "rb");
    struct trip daftar[100];
    int n = 0;

    if (jenis_trip == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }

    while (fread(&daftar[n], sizeof(struct trip), 1, jenis_trip)) {
        n++;
    }
    fclose(jenis_trip);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftar[j].hargaTrip > daftar[j + 1].hargaTrip) {
                struct trip temp = daftar[j];
                daftar[j] = daftar[j + 1];
                daftar[j + 1] = temp;
            }
        }
    }

  
    printf("== Daftar Trip Berdasarkan Harga Termurah ==\n");
    for (int i = 0; i < n; i++) {
        printf("\nID Trip       : %d\n", daftar[i].idTrip);
        printf("Nama Trip     : %s\n", daftar[i].namaTrip);
        printf("Deskripsi     : %s\n", daftar[i].deskripsiTrip);
        printf("Harga Trip    : Rp %.2f\n", daftar[i].hargaTrip);
    }

    printf("\nTekan Enter untuk kembali...\n");
    system("pause");
    system("cls");
    menuAdmin();
    getchar();
    getchar();

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
void lihatTripUs(){
    system("cls");
    jenis_trip = fopen("jenis_trip.dat", "rb");
    struct trip daftar[100];
    int n = 0;

    if (jenis_trip == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }

    while (fread(&daftar[n], sizeof(struct trip), 1, jenis_trip)) {
        n++;
    }
    fclose(jenis_trip);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftar[j].hargaTrip > daftar[j + 1].hargaTrip) {
                struct trip temp = daftar[j];
                daftar[j] = daftar[j + 1];
                daftar[j + 1] = temp;
            }
        }
    }

  
    printf("== Daftar Trip Berdasarkan Harga Termurah ==\n");
    for (int i = 0; i < n; i++) {
        printf("\nID Trip       : %d\n", daftar[i].idTrip);
        printf("Nama Trip     : %s\n", daftar[i].namaTrip);
        printf("Deskripsi     : %s\n", daftar[i].deskripsiTrip);
        printf("Harga Trip    : Rp %.2f\n", daftar[i].hargaTrip);
    }

    printf("\nTekan Enter untuk kembali...\n");
    system("pause");
    system("cls");
    menuUser();
}

void MemesanTrip(){
    FILE *jenis_trip;
    struct trip trip;
    int idCari, ketemu = 0;

    jenis_trip = fopen("jenis_trip.dat", "rb");
    if (jenis_trip == NULL) {
        printf("Gagal membuka data trip.\n");
        return;
    }

    printf("\n== Pesan Trip ==\n");
    printf("Masukkan ID Trip yang ingin dipesan: ");
    scanf("%d", &idCari);
    getchar();

    while (fread(&trip, sizeof(struct trip), 1, jenis_trip)) {
        if (trip.idTrip == idCari) {
            ketemu = 1;

            printf("\n--- Detail Trip ---\n");
            printf("Nama Trip     : %s\n", trip.namaTrip);
            printf("Deskripsi     : %s\n", trip.deskripsiTrip);
            printf("Harga         : Rp %.2f\n", trip.hargaTrip);

            printf("\nIngin langsung bayar sekarang? (y/n): ");
            char pilihan;
            scanf(" %c", &pilihan);
            getchar();

            if (pilihan == 'y' || pilihan == 'Y') {
                int berhasil = pembayaran(trip.hargaTrip);
                if (berhasil) {
                    FILE *pesanan = fopen("pesanan_trip.dat", "ab");
                    if (pesanan != NULL) {
                        struct pesanan riwayat;
                        strcpy(riwayat.username, user.username);
                        riwayat.idTrip = trip.idTrip;
                        strcpy(riwayat.namaTrip, trip.namaTrip);
                        riwayat.hargaTrip = trip.hargaTrip;
                        fwrite(&riwayat, sizeof(struct pesanan), 1, pesanan);
                        fclose(pesanan);
                    }
                    printf("Trip '%s' berhasil dipesan dan dibayar.\n", trip.namaTrip);
                }
            } else {
                printf("Trip disimpan tanpa pembayaran.\n");
            }

            break;
        }
    }

    fclose(jenis_trip);

    if (!ketemu) {
        printf("Trip dengan ID %d tidak ditemukan.\n", idCari);
    }

    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
    system("cls");
    menuUser();
    
}

int pembayaran(float hargaTrip){
    FILE *top_up = fopen("top_up.dat", "rb");
    FILE *top_up2 = fopen("top_up2.dat", "wb");
    struct akun data;
    int ditemukan = 0;

    if (!top_up || !top_up2) {
        printf("Gagal membuka file saldo.\n");
        if (top_up) fclose(top_up);
        if (top_up2) fclose(top_up2);
        return 0;
    }

    while (fread(&data, sizeof(struct akun), 1, top_up)) {
        if (strcmp(data.username, user.username) == 0) {
            if (data.nominal >= hargaTrip) {
                data.nominal -= hargaTrip;
                printf("Pembayaran berhasil. Sisa saldo: Rp %.2f\n", data.nominal);
                ditemukan = 1;
            } else {
                printf("Saldo tidak cukup. Silakan top up terlebih dahulu.\n");
                fclose(top_up);
                fclose(top_up2);
                remove("temp_top_up.dat");
                printf("Tekan Enter untuk kembali ke menu user...\n");
                getchar();
                system("cls");
                menuUser();
                return 0;
            }
        }
        fwrite(&data, sizeof(struct akun), 1, top_up2);
    }

    fclose(top_up);
    fclose(top_up2);
    remove("top_up.dat");
    rename("top_up2.dat", "top_up.dat");

    return ditemukan;
}
void tampilkanSaldoUser() {
    FILE *top_up = fopen("top_up.dat", "rb");
    struct akun data;
    int ditemukan = 0;

    if (top_up == NULL) {
        printf("Saldo Anda saat ini: Rp 0.00\n");
        return;
    }

    while (fread(&data, sizeof(struct akun), 1, top_up)) {
        if (strcmp(data.username, user.username) == 0) {
            printf("Saldo Anda saat ini: Rp %.2f\n", data.nominal);
            ditemukan = 1;
            break;
        }
    }

    fclose(top_up);

    if (!ditemukan) {
        printf("Saldo Anda saat ini: Rp 0.00\n");
    }
}

void TopUp(){
    struct akun data;
    int ditemukan = 0;
    FILE *top_up = fopen("top_up.dat", "rb");
    FILE *top_up2 = fopen("top_up2.dat", "wb");

    float saldo_sekarang = 0.0;

    if (top_up != NULL) {
        while (fread(&data, sizeof(struct akun), 1, top_up)) {
            if (strcmp(data.username, user.username) == 0) {
                saldo_sekarang = data.nominal;
            }
        }
        fclose(top_up);
    }

    printf("Saldo saat ini: Rp %.2f\n", saldo_sekarang);
    printf("Masukkan nominal top-up: Rp ");
    if (scanf("%f", &user.nominal) != 1 || user.nominal <= 0) {
        puts("Nominal tidak valid.");
        while (getchar() != '\n');
        return;
    }
    getchar();

    top_up = fopen("top_up.dat", "rb");
    if (top_up != NULL) {
        while (fread(&data, sizeof(struct akun), 1, top_up)) {
            if (strcmp(data.username, user.username) == 0) {
                data.nominal += user.nominal;
                ditemukan = 1;
            }
            fwrite(&data, sizeof(struct akun), 1, top_up2);
        }
        fclose(top_up);
    }

    if (!ditemukan) {
        strcpy(data.username, user.username);
        data.nominal = user.nominal;
        fwrite(&data, sizeof(struct akun), 1, top_up2);
    }

    fclose(top_up2);
    remove("top_up.dat");
    rename("top_up2.dat", "top_up.dat");

    printf("Top-up berhasil! Saldo Anda sekarang: Rp %.2f\n", saldo_sekarang + user.nominal);
    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
    system("cls");
    menuUser();
}

void RiwayatTrip(){
    system("cls");
    FILE *RiwayatTrip;
    struct pesanan data;
    int ditemukan = 0;

    RiwayatTrip = fopen("pesanan_trip.dat", "rb");
    if (RiwayatTrip == NULL) {
        printf("Tidak ada riwayat pesanan.\n");
        return;
    }

    printf("== Riwayat Trip Anda ==\n");
    while (fread(&data, sizeof(struct pesanan), 1, RiwayatTrip)) {
        if (strcmp(data.username, user.username) == 0) {
            printf("Trip  : %s\n", data.namaTrip);
            printf("Harga : Rp %.2f\n\n", data.hargaTrip);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Anda belum pernah memesan trip.\n");
    }

    fclose(RiwayatTrip);
    printf("Tekan Enter untuk kembali...\n");
    system("pause");
    system("cls");
    menuUser();
    getchar();
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
    system("cls");
    printf("== Ganti Password ==\n");
    FILE *data_akun;
    FILE *data_akun2;

    struct akun user;
    char username[50], password[50];
    char newPassword[50];
    int found = 0;

    data_akun = fopen("data_akun.dat", "rb");
    data_akun2 = fopen("data_akun2.dat", "wb");
    if (data_akun == NULL || data_akun2 == NULL) {
        printf("Gagal membuka file data_akun.dat\n");
        return;
    }

    printf("Masukkan username Anda: ");
    gets(username);
    printf("Masukkan password lama Anda: ");
    gets(password);
    printf("Masukkan password baru Anda: ");
    gets(newPassword);
    printf("\n");

    while (fread(&user, sizeof(struct akun), 1, data_akun)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            strcpy(user.password, newPassword);
            found = 1;
        }
        fwrite(&user, sizeof(struct akun), 1, data_akun2);
    }
    fclose(data_akun);
    fclose(data_akun2);
    remove("data_akun.dat");
    rename("data_akun2.dat", "data_akun.dat");
    if (found) {
        printf("Password berhasil diubah.\n");
    } else {
        printf("Username atau password lama salah.\n");
    }
    printf("Tekan Enter untuk kembali ke menu user...\n");
    system("pause");
    system("cls");
    menuUser();
}