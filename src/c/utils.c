#include "../header/utils.h"

void ToLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
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
        printf("   1. LOGOUT: Keluar dari akun yang sedang digunakan\n\n");
    } else {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("   1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n   2. REGISTER: Membuat akun baru\n\n");
    }
    printf("Footnote:\n   1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n   2. Jangan lupa untuk memasukkan input yang valid\n\n");
}

void RunLenEncode(char* str, char* encoded) {
    int count = 1, index = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == str[i + 1]) {
            count++;
        } else {
            encoded[index] = str[i];
            index++;
            if (count > 1) {
                // konversi int ke string
                char num[10];
                sprintf(num, "%d", count);

                for (int j = 0; num[j]; j++) {
                    encoded[index] = num[j];
                    index++;
                }
            }
            count = 1;  // reset count
        }
    }

    encoded[index] = '\0'; // null-terminate string
}


void Exit(){
    char input[10];
    do {
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
        scanf("%s", input);
        ToLowerCase(input); // Ubah ke huruf kecil
    } while(strcmp(input, "y") != 0 && strcmp(input, "n") != 0);
    if(strcmp(input,"y") == 0){
        printf("Simpan Perubahan.\n");
    } else { // input = 'n'
        printf("Tidak Menyimpan Perubahan.\n");
    }
}