#include "../header/utils.h"

void ToLower(char *target, char *str)
{
    int i;
    for (i = 0; str[i]; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            target[i] = str[i] + ('a' - 'A');
        }
        else
        {
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

void ToUpperCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] -= ('a' - 'A');
        }
    }
}

// Mengembalikan float dalam bentuk string
char *FloatToStr(float x)
{
    static char bilangan[32];
    snprintf(bilangan, sizeof(bilangan), "%.2f", x);
    return bilangan;
}

// Mengembalikan integer dalam bentuk string
char *IntToStr(int x)
{
    static char bilangan[32];
    snprintf(bilangan, sizeof(bilangan), "%d", x);
    return bilangan;
}

void Help(Session session)
{
    // Diurutkan sesuai dengan fitur pada tubes
    // 0: Tidak login, 1: Pasien, 2: Dokter, 3: Manager, 4: All Logged In Role, 5: All
    char CommandAccess[17] = {
        0, 0, 4, 5, 5, 4, 3, 3, 3, 3, 2, 2, 1, 1, 1, 1, 1}; // F01 sampai F17, untuk EXIT dan SAVE dilakukan hardcode
    char arrayCommand[17][1000];
    strcpy(arrayCommand[0], "LOGIN: Masuk ke badan Nimons");
    strcpy(arrayCommand[1], "REGISTER: Mendaftarkan diri Anda untuk menjadi Nimons");
    strcpy(arrayCommand[2], "LOGOUT: Keluar dari badan Nimons");
    strcpy(arrayCommand[3], "LUPA_PASSWORD: Mengupdate password untuk masuk ke badan Nimons");
    strcpy(arrayCommand[4], "HELP: Menampilkan hal apa saja yang dapat Anda lakukan dalam badan Nimons");
    strcpy(arrayCommand[5], "LIHAT_DENAH / LIHAT_RUANGAN: Menampilkan denah rumah sakit / Menampilkan detail ruangan rumah sakit Nimons");
    strcpy(arrayCommand[6], "LIHAT_USER / LIHAT_PASIEN / LIHAT_DOKTER: Menampilkan data seluruh pasien dan dokter dalam rumah sakit Nimons");
    strcpy(arrayCommand[7], "CARI_USER / CARI_PASIEN / CARI_DOKTER: Menampilkan user sesuai dengan masukan ID / Nama");
    strcpy(arrayCommand[8], "LIHAT_SEMUA_ANTRIAN: Menampilkan seluruh antrian pada rumah sakit Nimons");
    strcpy(arrayCommand[9], "TAMBAH_DOKTER / ASSIGN_DOKTER: Menambahkan Nimons dengan role dokter / Meng-assign dokter pada suatu ruangan yang kosong di rumah sakit Nimons");
    strcpy(arrayCommand[10], "DIAGNOSIS: Mendiagnosis pasien Nimons pada antrian terdepan ruangan Anda");
    strcpy(arrayCommand[11], "NGOBATIN: Mengobati pasien Nimons yang sudah didiagnosis pada antrian terdepan ruangan Anda");
    strcpy(arrayCommand[12], "PULANGDOK: Meminta izin kepada dokter Nimons untuk pulang");
    strcpy(arrayCommand[13], "DAFTAR_CHECKUP: Mendaftar checkup di rumah sakit Nimons");
    strcpy(arrayCommand[14], "ANTRIAN: Melihat antrian pasien Nimons di luar ruangan checkup Anda");
    strcpy(arrayCommand[15], "MINUM_OBAT: Meminum obat untuk menyembuhkan diri Anda");
    strcpy(arrayCommand[16], "PENAWAR: Mengeluarkan obat terakhir yang Anda minum");
    printf("========== HELP ==========\n\n");

    if (strcmp(session.currentUser.role, "manager") == 0)
    {
        printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", session.currentUser.username);
    }
    else if (strcmp(session.currentUser.role, "pasien") == 0)
    {
        printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", session.currentUser.username);
    }
    else if (strcmp(session.currentUser.role, "dokter") == 0)
    {
        printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", session.currentUser.username);
    }
    int currentRole = 0;
    if (strcmp(session.currentUser.role, "manager") == 0)
    {
        currentRole = 3;
    }
    else if (strcmp(session.currentUser.role, "pasien") == 0)
    {
        currentRole = 1;
    }
    else if (strcmp(session.currentUser.role, "dokter") == 0)
    {
        currentRole = 2;
    }
    int idx = 1;
    for (int i = 0; i < 17; i++)
    {
        if (
            CommandAccess[i] == currentRole ||             // khusus pasien / dokter / manager
            (CommandAccess[i] == 4 && currentRole != 0) || // role logged in
            CommandAccess[i] == 5                          // semua role
        )
        {
            printf("\t%d. %s.\n", idx, arrayCommand[i]);
            idx++;
        }
    }
    printf("\t-> SAVE: Menyimpan perubahan pada file eksternal\n");
    printf("\t-> EXIT: Keluar dari dunia Nimons :D");
    printf("\n");
    printf("Footnote:\n   1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n   2. Jangan lupa untuk memasukkan input yang valid\n\n");
}
// else
// {
//     printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
//     printf("   1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n   2. REGISTER: Membuat akun baru\n   3. LUPA_PASSWORD: Reset password akun\n   -> EXIT: Keluar dari dunia Nimons :D\n\n");
// }

void RunLenEncode(char *str, char *encoded)
{
    int count = 1, index = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == str[i + 1])
        {
            count++;
        }
        else
        {
            if (count > 1)
            {
                // konversi int ke string
                char num[12];
                sprintf(num, "%d", count);

                for (int j = 0; num[j]; j++)
                {
                    encoded[index] = num[j];
                    index++;
                }
            }
            encoded[index] = str[i];
            index++;
            count = 1; // reset count
        }
    }

    encoded[index] = '\0'; // null-terminate string
}
