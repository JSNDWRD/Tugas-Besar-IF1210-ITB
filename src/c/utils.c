#include "../header/utils.h"


void ToLower(char *target, char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            target[i] = str[i] + ('a' - 'A');
        } else {
            target[i] = str[i];
        }
    }
    target[i] = '\0';
}

void ToLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += ('a' - 'A');
        }
    }
}

void ToUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= ('a' - 'A');
        }
    }
}

// Mengembalikan float dalam bentuk string
char* FloatToStr(float x){
    static char bilangan[32];
    snprintf(bilangan,sizeof(bilangan),"%.2f",x);
    return bilangan;
}

// Mengembalikan integer dalam bentuk string
char* IntToStr(int x){
    static char bilangan[32];
    snprintf(bilangan,sizeof(bilangan),"%d",x);
    return bilangan;
}

void Help(Session session){
    printf("========== HELP ==========\n\n");
    if(session.loggedIn == 1){
        if(strcmp(session.currentUser.role,"manager") == 0){
            printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n",session.currentUser.username);
        } else if(strcmp(session.currentUser.role, "pasien") == 0){
            printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n",session.currentUser.username);
        } else if(strcmp(session.currentUser.role, "dokter") == 0){
            printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n",session.currentUser.username);
        }
        printf("   1. LOGOUT: Keluar dari akun yang sedang digunakan\n   2. LUPA_PASSWORD: Reset password akun\n");
        if(strcmp(session.currentUser.role,"manager") == 0){
            printf("   3. LIHAT_USER / LIHAT_PASIEN / LIHAT_DOKTER: Melihat data user secara ascending / descending berdasarkan Nama atau ID\n   4. CARI_USER / CARI_PASIEN / CARI_DOKTER: Mencari user secara spesifik berdasarkan Nama, ID, atau Penyakit (Khusus Pasien)\n   5. TAMBAH_DOKTER: Menambahkan dokter baru di rumah sakit\n   6. LIHAT_DENAH: Menampilkan denah rumah sakit\n   7. LIHAT_RUANGAN: Menampilkan isi ruangan rumah sakit\n");
        } else if(strcmp(session.currentUser.role, "pasien") == 0){
            printf("   3. LIHAT_DENAH: Menampilkan denah rumah sakit\n   4. LIHAT_RUANGAN: Menampilkan isi ruangan rumah sakit\n");
        } else if(strcmp(session.currentUser.role, "dokter") == 0){
            printf("   3. LIHAT_DENAH: Menampilkan denah rumah sakit\n   4. LIHAT_RUANGAN: Menampilkan isi ruangan rumah sakit\n");
        }
        printf("   -> EXIT: Keluar dari dunia Nimons :D");
        printf("\n");
    } else {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("   1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n   2. REGISTER: Membuat akun baru\n   3. LUPA_PASSWORD: Reset password akun\n   -> EXIT: Keluar dari dunia Nimons :D\n\n");
    }
    printf("Footnote:\n   1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n   2. Jangan lupa untuk memasukkan input yang valid\n\n");
}

void RunLenEncode(char* str, char* encoded) {
    int count = 1, index = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == str[i + 1]) {
            count++;
        } else {
            if (count > 1) {
                // konversi int ke string
                char num[12];
                sprintf(num, "%d", count);
                
                for (int j = 0; num[j]; j++) {
                    encoded[index] = num[j];
                    index++;
                }
            }
            encoded[index] = str[i];
            index++;
            count = 1;  // reset count
        }
    }

    encoded[index] = '\0'; // null-terminate string
}
