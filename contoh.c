#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
 
// Struktur data untuk Trip
typedef struct {
    int id;
    char nama[100];
    float harga;
    char deskripsi[500];
} Trip;

// Struktur data untuk User
typedef struct {
    int id;
    char username[50];
    char password[50];
    float saldo;
    bool is_admin;
} User;

// Struktur data untuk Pemesanan
typedef struct {
    int id;
    int user_id;
    int trip_id;
    char tanggal[20];
    char status[20]; // "pending", "paid", "canceled"
} Pemesanan;

// Struktur data untuk Feedback
typedef struct {
    int id;
    int user_id;
    char isi[500];
} Feedback;

// Variabel global
User users[100];
Trip trips[100];
Pemesanan pemesanans[1000];
Feedback feedbacks[100];
int user_count = 0;
int trip_count = 0;
int pemesanan_count = 0;
int feedback_count = 0;
User *current_user = NULL;

// Deklarasi fungsi
void init_data();
void main_menu();
void user_menu();
void admin_menu();
void register_user();
bool login_user();
void change_password();
void view_trips_by_price();
void pesan_trip();
void top_up_saldo();
void bayar_pemesanan();
void view_pemesanan_history();
void give_feedback();
void admin_add_trip();
void admin_view_users();
void admin_delete_user();
void admin_view_income_report();
void admin_view_feedbacks();
void bubble_sort_trips_by_price(Trip arr[], int n);
void clear_input_buffer();

int main() {
    init_data();
    main_menu();
    return 0;
}

void init_data() {
    // Inisialisasi data admin
    users[0].id = 1;
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin123");
    users[0].saldo = 0;
    users[0].is_admin = true;
    user_count = 1;
    
    // Inisialisasi beberapa trip contoh
    trips[0].id = 1;
    strcpy(trips[0].nama, "Wisata Gunung Bromo");
    trips[0].harga = 500000;
    strcpy(trips[0].deskripsi, "Perjalanan 2 hari 1 malam ke Gunung Bromo");
    
    trips[1].id = 2;
    strcpy(trips[1].nama, "Liburan ke Bali");
    trips[1].harga = 2500000;
    strcpy(trips[1].deskripsi, "Paket liburan 4 hari 3 malam ke Bali");
    
    trip_count = 2;
}

void clear_input_buffer() {
    while (getchar() != '\n');
}

void main_menu() {
    int choice;
    while(1) {
        printf("\n=== SELAMAT DATANG DI DTOUR ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1:
                if(login_user()) {
                    if(current_user->is_admin) {
                        admin_menu();
                    } else {
                        user_menu();
                    }
                }
                break;
            case 2:
                register_user();
                break;
            case 3:
                printf("Terima kasih telah menggunakan DTour!\n");
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

bool login_user() {
    char username[50], password[50];
    int attempts = 0;
    
    while(attempts < 3) {
        printf("\n=== LOGIN ===\n");
        printf("Username: ");
        scanf("%49s", username);
        printf("Password: ");
        scanf("%49s", password);
        clear_input_buffer();
        
        for(int i = 0; i < user_count; i++) {
            if(strcmp(users[i].username, username) == 0 && 
               strcmp(users[i].password, password) == 0) {
                current_user = &users[i];
                printf("Login berhasil!\n");
                return true;
            }
        }
        
        attempts++;
        printf("Username atau password salah. Percobaan %d/3\n", attempts);
    }
    
    printf("Anda telah melebihi batas percobaan login.\n");
    return false;
}

void register_user() {
    if(user_count >= 100) {
        printf("Kapasitas user penuh!\n");
        return;
    }
    
    User new_user;
    new_user.id = user_count + 1;
    new_user.is_admin = false;
    new_user.saldo = 0;
    
    printf("\n=== REGISTRASI USER BARU ===\n");
    
    // Input username
    while(1) {
        printf("Username: ");
        scanf("%49s", new_user.username);
        clear_input_buffer();
        
        bool username_exists = false;
        for(int i = 0; i < user_count; i++) {
            if(strcmp(users[i].username, new_user.username) == 0) {
                username_exists = true;
                break;
            }
        }
        
        if(username_exists) {
            printf("Username sudah digunakan. Silakan coba username lain.\n");
        } else {
            break;
        }
    }
    
    // Input password
    printf("Password: ");
    scanf("%49s", new_user.password);
    clear_input_buffer();
    
    users[user_count++] = new_user;
    printf("Registrasi berhasil! Silakan login.\n");
}

void user_menu() {
    int choice;
    while(current_user != NULL && !current_user->is_admin) {
        printf("\n=== MENU USER ===\n");
        printf("Selamat datang, %s!\n", current_user->username);
        printf("Saldo Anda: Rp%.2f\n", current_user->saldo);
        printf("1. Ganti Password\n");
        printf("2. Lihat Daftar Trip (urut harga termurah)\n");
        printf("3. Pesan Trip\n");
        printf("4. Top-up Saldo\n");
        printf("5. Bayar Pemesanan\n");
        printf("6. Lihat Riwayat Pemesanan\n");
        printf("7. Berikan Feedback\n");
        printf("8. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1:
                change_password();
                break;
            case 2:
                view_trips_by_price();
                break;
            case 3:
                pesan_trip();
                break;
            case 4:
                top_up_saldo();
                break;
            case 5:
                bayar_pemesanan();
                break;
            case 6:
                view_pemesanan_history();
                break;
            case 7:
                give_feedback();
                break;
            case 8:
                current_user = NULL;
                printf("Anda telah logout.\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

void admin_menu() {
    int choice;
    while(current_user != NULL && current_user->is_admin) {
        printf("\n=== MENU ADMIN ===\n");
        printf("Selamat datang, Admin %s!\n", current_user->username);
        printf("1. Tambahkan Trip\n");
        printf("2. Lihat Data User\n");
        printf("3. Hapus Akun User\n");
        printf("4. Lihat Laporan Penghasilan\n");
        printf("5. Lihat Feedback\n");
        printf("6. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1:
                admin_add_trip();
                break;
            case 2:
                admin_view_users();
                break;
            case 3:
                admin_delete_user();
                break;
            case 4:
                admin_view_income_report();
                break;
            case 5:
                admin_view_feedbacks();
                break;
            case 6:
                current_user = NULL;
                printf("Anda telah logout.\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}

void change_password() {
    if(current_user == NULL) return;
    
    char old_password[50], new_password[50], confirm_password[50];
    
    printf("\n=== GANTI PASSWORD ===\n");
    printf("Password lama: ");
    scanf("%49s", old_password);
    clear_input_buffer();
    
    if(strcmp(current_user->password, old_password) != 0) {
        printf("Password lama salah!\n");
        return;
    }
    
    printf("Password baru: ");
    scanf("%49s", new_password);
    clear_input_buffer();
    
    printf("Konfirmasi password baru: ");
    scanf("%49s", confirm_password);
    clear_input_buffer();
    
    if(strcmp(new_password, confirm_password) != 0) {
        printf("Konfirmasi password tidak cocok!\n");
        return;
    }
    
    strcpy(current_user->password, new_password);
    printf("Password berhasil diubah!\n");
}

void bubble_sort_trips_by_price(Trip arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j].harga > arr[j+1].harga) {
                Trip temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void view_trips_by_price() {
    if(trip_count == 0) {
        printf("Belum ada trip tersedia.\n");
        return;
    }
    
    // Buat salinan array trips untuk diurutkan
    Trip sorted_trips[trip_count];
    for(int i = 0; i < trip_count; i++) {
        sorted_trips[i] = trips[i];
    }
    
    // Urutkan berdasarkan harga
    bubble_sort_trips_by_price(sorted_trips, trip_count);
    
    // Tampilkan hasil
    printf("\n=== DAFTAR TRIP (Harga Termurah) ===\n");
    for(int i = 0; i < trip_count; i++) {
        printf("ID: %d\n", sorted_trips[i].id);
        printf("Nama: %s\n", sorted_trips[i].nama);
        printf("Harga: Rp%.2f\n", sorted_trips[i].harga);
        printf("Deskripsi: %s\n", sorted_trips[i].deskripsi);
        printf("---------------------------\n");
    }
}

void pesan_trip() {
    if(current_user == NULL) return;
    
    if(trip_count == 0) {
        printf("Belum ada trip tersedia.\n");
        return;
    }
    
    view_trips_by_price();
    
    int trip_id;
    char tanggal[20];
    
    printf("\n=== PEMESANAN TRIP ===\n");
    printf("Masukkan ID Trip yang ingin dipesan: ");
    scanf("%d", &trip_id);
    clear_input_buffer();
    
    // Cari trip
    Trip *selected_trip = NULL;
    for(int i = 0; i < trip_count; i++) {
        if(trips[i].id == trip_id) {
            selected_trip = &trips[i];
            break;
        }
    }
    
    if(selected_trip == NULL) {
        printf("ID Trip tidak valid!\n");
        return;
    }
    
    printf("Masukkan tanggal perjalanan (DD-MM-YYYY): ");
    scanf("%19s", tanggal);
    clear_input_buffer();
    
    // Buat pemesanan baru
    Pemesanan new_pemesanan;
    new_pemesanan.id = pemesanan_count + 1;
    new_pemesanan.user_id = current_user->id;
    new_pemesanan.trip_id = selected_trip->id;
    strcpy(new_pemesanan.tanggal, tanggal);
    strcpy(new_pemesanan.status, "pending");
    
    pemesanans[pemesanan_count++] = new_pemesanan;
    
    printf("Pemesanan berhasil dibuat!\n");
    printf("ID Pemesanan: %d\n", new_pemesanan.id);
    printf("Total yang harus dibayar: Rp%.2f\n", selected_trip->harga);
    printf("Silakan lakukan pembayaran melalui menu 'Bayar Pemesanan'.\n");
}

void top_up_saldo() {
    if(current_user == NULL) return;
    
    float jumlah;
    printf("\n=== TOP-UP SALDO ===\n");
    printf("Saldo saat ini: Rp%.2f\n", current_user->saldo);
    printf("Masukkan jumlah top-up: Rp");
    scanf("%f", &jumlah);
    clear_input_buffer();
    
    if(jumlah <= 0) {
        printf("Jumlah top-up harus lebih dari 0.\n");
        return;
    }
    
    current_user->saldo += jumlah;
    printf("Top-up berhasil! Saldo baru: Rp%.2f\n", current_user->saldo);
}

void bayar_pemesanan() {
    if(current_user == NULL) return;
    
    if(pemesanan_count == 0) {
        printf("Belum ada pemesanan.\n");
        return;
    }
    
    // Tampilkan pemesanan pending user ini
    printf("\n=== PEMBAYARAN PESANAN ===\n");
    printf("Daftar pesanan pending Anda:\n");
    
    bool found_pending = false;
    for(int i = 0; i < pemesanan_count; i++) {
        if(pemesanans[i].user_id == current_user->id && 
           strcmp(pemesanans[i].status, "pending") == 0) {
            found_pending = true;
            
            // Cari info trip
            Trip *trip_info = NULL;
            for(int j = 0; j < trip_count; j++) {
                if(trips[j].id == pemesanans[i].trip_id) {
                    trip_info = &trips[j];
                    break;
                }
            }
            
            if(trip_info != NULL) {
                printf("ID Pemesanan: %d\n", pemesanans[i].id);
                printf("Trip: %s\n", trip_info->nama);
                printf("Tanggal: %s\n", pemesanans[i].tanggal);
                printf("Harga: Rp%.2f\n", trip_info->harga);
                printf("---------------------------\n");
            }
        }
    }
    
    if(!found_pending) {
        printf("Tidak ada pesanan yang perlu dibayar.\n");
        return;
    }
    
    int pemesanan_id;
    printf("Masukkan ID Pemesanan yang ingin dibayar: ");
    scanf("%d", &pemesanan_id);
    clear_input_buffer();
    
    // Cari pemesanan
    Pemesanan *selected_pemesanan = NULL;
    Trip *trip_info = NULL;
    
    for(int i = 0; i < pemesanan_count; i++) {
        if(pemesanans[i].id == pemesanan_id && 
           pemesanans[i].user_id == current_user->id &&
           strcmp(pemesanans[i].status, "pending") == 0) {
            selected_pemesanan = &pemesanans[i];
            
            // Cari info trip
            for(int j = 0; j < trip_count; j++) {
                if(trips[j].id == pemesanans[i].trip_id) {
                    trip_info = &trips[j];
                    break;
                }
            }
            break;
        }
    }
    
    if(selected_pemesanan == NULL || trip_info == NULL) {
        printf("ID Pemesanan tidak valid atau sudah dibayar.\n");
        return;
    }
    
    if(current_user->saldo < trip_info->harga) {
        printf("Saldo tidak cukup. Silakan lakukan top-up terlebih dahulu.\n");
        printf("Saldo Anda: Rp%.2f\n", current_user->saldo);
        printf("Total yang harus dibayar: Rp%.2f\n", trip_info->harga);
        return;
    }
    
    // Lakukan pembayaran
    current_user->saldo -= trip_info->harga;
    strcpy(selected_pemesanan->status, "paid");
    
    printf("Pembayaran berhasil!\n");
    printf("Saldo tersisa: Rp%.2f\n", current_user->saldo);
}

void view_pemesanan_history() {
    if(current_user == NULL) return;
    
    if(pemesanan_count == 0) {
        printf("Belum ada riwayat pemesanan.\n");
        return;
    }
    
    printf("\n=== RIWAYAT PEMESANAN ===\n");
    
    bool found = false;
    for(int i = 0; i < pemesanan_count; i++) {
        if(pemesanans[i].user_id == current_user->id) {
            found = true;
            
            // Cari info trip
            Trip *trip_info = NULL;
            for(int j = 0; j < trip_count; j++) {
                if(trips[j].id == pemesanans[i].trip_id) {
                    trip_info = &trips[j];
                    break;
                }
            }
            
            if(trip_info != NULL) {
                printf("ID Pemesanan: %d\n", pemesanans[i].id);
                printf("Trip: %s\n", trip_info->nama);
                printf("Tanggal: %s\n", pemesanans[i].tanggal);
                printf("Harga: Rp%.2f\n", trip_info->harga);
                printf("Status: %s\n", pemesanans[i].status);
                printf("---------------------------\n");
            }
        }
    }
    
    if(!found) {
        printf("Belum ada riwayat pemesanan.\n");
    }
}

void give_feedback() {
    if(current_user == NULL) return;
    
    if(feedback_count >= 100) {
        printf("Kapasitas feedback penuh!\n");
        return;
    }
    
    Feedback new_feedback;
    new_feedback.id = feedback_count + 1;
    new_feedback.user_id = current_user->id;
    
    printf("\n=== BERIKAN FEEDBACK ===\n");
    printf("Masukkan feedback Anda (maks 500 karakter):\n");
    scanf(" %[^\n]", new_feedback.isi);
    clear_input_buffer();
    
    feedbacks[feedback_count++] = new_feedback;
    printf("Terima kasih atas feedback Anda!\n");
}

void admin_add_trip() {
    if(current_user == NULL || !current_user->is_admin) {
        printf("Akses ditolak!\n");
        return;
    }
    
    if(trip_count >= 100) {
        printf("Kapasitas trip penuh!\n");
        return;
    }
    
    Trip new_trip;
    new_trip.id = trip_count + 1;
    
    printf("\n=== TAMBAH TRIP BARU ===\n");
    printf("Nama Trip: ");
    scanf(" %[^\n]", new_trip.nama);
    clear_input_buffer();
    
    printf("Harga: ");
    scanf("%f", &new_trip.harga);
    clear_input_buffer();
    
    printf("Deskripsi: ");
    scanf(" %[^\n]", new_trip.deskripsi);
    clear_input_buffer();
    
    trips[trip_count++] = new_trip;
    printf("Trip berhasil ditambahkan!\n");
}

void admin_view_users() {
    if(current_user == NULL || !current_user->is_admin) {
        printf("Akses ditolak!\n");
        return;
    }
    
    if(user_count <= 1) { // Hanya admin yang ada
        printf("Belum ada user terdaftar.\n");
        return;
    }
    
    printf("\n=== DAFTAR USER ===\n");
    for(int i = 1; i < user_count; i++) { // Skip admin
        printf("ID: %d\n", users[i].id);
        printf("Username: %s\n", users[i].username);
        printf("Saldo: Rp%.2f\n", users[i].saldo);
        printf("---------------------------\n");
    }
}

void admin_delete_user() {
    if(current_user == NULL || !current_user->is_admin) {
        printf("Akses ditolak!\n");
        return;
    }
    
    if(user_count <= 1) { // Hanya admin yang ada
        printf("Belum ada user yang bisa dihapus.\n");
        return;
    }
    
    admin_view_users();
    
    int user_id;
    printf("Masukkan ID User yang ingin dihapus: ");
    scanf("%d", &user_id);
    clear_input_buffer();
    
    if(user_id == current_user->id) {
        printf("Tidak bisa menghapus akun admin sendiri.\n");
        return;
    }
    
    int index = -1;
    for(int i = 1; i < user_count; i++) { // Skip admin
        if(users[i].id == user_id) {
            index = i;
            break;
        }
    }
    
    if(index == -1) {
        printf("ID User tidak valid.\n");
        return;
    }
    
    // Geser semua user setelah index ke depan
    for(int i = index; i < user_count - 1; i++) {
        users[i] = users[i+1];
    }
    
    user_count--;
    printf("User berhasil dihapus.\n");
}

void admin_view_income_report() {
    if(current_user == NULL || !current_user->is_admin) {
        printf("Akses ditolak!\n");
        return;
    }
    
    float total_income = 0;
    
    printf("\n=== LAPORAN PENGHASILAN ===\n");
    
    if(pemesanan_count == 0) {
        printf("Belum ada pemesanan yang dibayar.\n");
        return;
    }
    
    for(int i = 0; i < pemesanan_count; i++) {
        if(strcmp(pemesanans[i].status, "paid") == 0) {
            // Cari info trip
            for(int j = 0; j < trip_count; j++) {
                if(trips[j].id == pemesanans[i].trip_id) {
                    total_income += trips[j].harga;
                    break;
                }
            }
        }
    }
    
    printf("Total penghasilan dari pemesanan: Rp%.2f\n", total_income);
}

void admin_view_feedbacks() {
    if(current_user == NULL || !current_user->is_admin) {
        printf("Akses ditolak!\n");
        return;
    }
    
    if(feedback_count == 0) {
        printf("Belum ada feedback.\n");
        return;
    }
    
    printf("\n=== DAFTAR FEEDBACK ===\n");
    
    for(int i = 0; i < feedback_count; i++) {
        // Cari username user
        char username[50] = "Unknown";
        for(int j = 0; j < user_count; j++) {
            if(users[j].id == feedbacks[i].user_id) {
                strcpy(username, users[j].username);
                break;
            }
        }
        
        printf("ID Feedback: %d\n", feedbacks[i].id);
        printf("User: %s\n", username);
        printf("Isi Feedback:\n%s\n", feedbacks[i].isi);
        printf("---------------------------\n");
    }
}