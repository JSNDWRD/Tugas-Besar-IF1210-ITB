#include <stdio.h>
#include "./header/user.h"
#include "./header/auth.h"
#include "./header/utils.h"
#include "./header/manager.h"
#include "./header/hospital.h"
#include "./header/command.h"
#include "./header/dokter.h"
#include "./header/checkup.h"
#include "./header/diagnosis.h"
#include "./header/ngobatin.h"

int main(int argc, char *argv[])
{
    UserList userList; // Daftar pengguna
    char folder[50];
    if (argc < 2)
    {
        printf("Tidak ada nama folder yang diberikan!\n");
        return 0;
    }
    strcpy(folder, argv[1]);
    LoadUsers(&userList, argv[1]);

    Matrix denahRumahSakit; // Denah rumah sakit
    LoadConfig(&denahRumahSakit, folder, &userList);

    PenyakitList penyakitList; // Daftar diagnosis penyakit
    LoadPenyakit(&penyakitList, folder);

    ObatList obatList; // Daftar obat
    LoadObat(&obatList, folder);

    ObatMap obatMap;
    LoadObatMap(&obatMap, folder);

    CommandList commandList; // Daftar command yang dapat digunakan

    const char *COMMAND_READY[COMMAND_CAPACITY] = {
        "HELP", "LOGIN", "LOGOUT", "REGISTER", "EXIT", "LUPA_PASSWORD", "LIHAT_USER", "LIHAT_PASIEN", "LIHAT_DOKTER", "CARI_USER", "CARI_PASIEN", "CARI_DOKTER", "TAMBAH_DOKTER", "LIHAT_DENAH", "LIHAT_RUANGAN", "ASSIGN_DOKTER", "DIAGNOSIS", "NGOBATIN", "LIHAT_SEMUA_ANTRIAN", "SAVE", "DAFTAR_CHECKUP", "ANTRIAN", "MINUM_OBAT", "PENAWAR", "PULANGDOK"};
    enum Command
    {
        HELP = 1,
        LOGIN,
        LOGOUT,
        REGISTER,
        EXIT,
        LUPA_PASSWORD,
        LIHAT_USER,
        LIHAT_PASIEN,
        LIHAT_DOKTER,
        CARI_USER,
        CARI_PASIEN,
        CARI_DOKTER,
        TAMBAH_DOKTER,
        LIHAT_DENAH,
        LIHAT_RUANGAN,
        ASSIGN_DOKTER,
        DIAGNOSIS,
        NGOBATIN,
        LIHAT_SEMUA_ANTRIAN,
        SAVE,
        DAFTAR_CHECKUP,
        ANTRIAN,
        MINUM_OBAT,
        PENAWAR,
        PULANGDOK
    };

    CreateCommandList(&commandList, COMMAND_READY); // Membuat List Statik yang berisikan command yang tersedia

    char arrayUrutanObat[OBAT_CAPACITY][500];
    for (int i = 0; i < 1000; i++)
    {
        strcpy(arrayUrutanObat[i], ""); // Inisialisasi arrayUrutanObat
    }

    Session session = {.loggedIn = 0}; // Ketika program mulai, session adalah logged out
    int command = 0;
    char input[50]; // Input command
    do
    {
        int valid = 0;
        do
        {
            printf("\n>>> Input Command: ");
            scanf(" %[^\n]", input);
            char commandAwal[50];
            int i = 0;
            while (input[i] != '\0' && input[i] != ' ' && i < sizeof(commandAwal) - 1)
            {
                commandAwal[i] = input[i];
                i++;
            }
            commandAwal[i] = '\0';
            ToUpperCase(commandAwal);
            for (int i = 0; i < COMMAND_CAPACITY; i++)
            {
                if (strcmp(commandAwal, ELMTNAME(commandList, i)) == 0)
                {
                    valid = 1;
                    command = ELMTKEY(commandList, i);
                    break;
                }
            }
            if (!valid)
            {
                printf("Perintah tidak ditemukan, silakan input ulang.\n");
            }
        } while (valid == 0);

        switch (command)
        {
        case HELP:
            Help(session);
            break;
        case LOGIN:
            Login(&userList, &session);
            break;
        case LOGOUT:
            Logout(&session);
            break;
        case REGISTER:
            RegisterUser(&userList, &session);
            break;
        case LUPA_PASSWORD:
            ResetPassword(&userList, &session);
            break;
        case EXIT:
            char simpan[10];
            do
            {
                printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
                scanf("%s", simpan);
                ToLowerCase(simpan); // Ubah ke huruf kecil
            } while (strcmp(simpan, "y") != 0 && strcmp(simpan, "n") != 0);
            if (strcmp(simpan, "y") == 0)
            {
                char command[256];
                char inputFolder[100];
                printf("\nMasukkan nama folder: ");
                scanf("%s", inputFolder);
                sprintf(command, "[ -d %s ] || mkdir %s", inputFolder, inputFolder);
                system(command);
                SaveUsers(&userList, inputFolder);
                SaveObat(folder, inputFolder);
                SavePenyakit(folder, inputFolder);
                SaveConfig(&denahRumahSakit, inputFolder, &userList);
            }
            break;
        case SAVE:
            char command[256];
            char inputFolder[100];
            printf("\nMasukkan nama folder: ");
            scanf("%s", inputFolder);
            sprintf(command, "[ -d %s ] || mkdir %s", inputFolder, inputFolder);
            system(command);
            SaveUsers(&userList, inputFolder);
            SaveObat(folder, inputFolder);
            SavePenyakit(folder, inputFolder);
            SaveConfig(&denahRumahSakit, inputFolder, &userList);
            break;
        case LIHAT_USER:
            LihatUser(&userList, &session);
            break;
        case LIHAT_PASIEN:
            LihatPasien(&userList, &session);
            break;
        case LIHAT_DOKTER:
            LihatDokter(&userList, &session);
            break;
        case CARI_USER:
            CariUser(&userList, &session);
            break;
        case CARI_PASIEN:
            CariPasien(&userList, &session);
            break;
        case CARI_DOKTER:
            CariDokter(&userList, &session);
            break;
        case TAMBAH_DOKTER:
            TambahDokter(&userList, &session);
            break;
        case LIHAT_DENAH:
            if (session.loggedIn != 1)
            {
                printf("Anda harus login terlebih dahulu!");
            }
            else
            {
                LihatDenah(&denahRumahSakit);
            }
            break;
        case LIHAT_RUANGAN:
            if (session.loggedIn == 1)
            {
                char ruangan[10];
                int i = 0, j = 0;
                while (input[i] != '\0' && input[i] != ' ')
                {
                    i++;
                }
                if (input[i] == ' ')
                {
                    i++;
                }
                while (input[i] != '\0' && j < sizeof(ruangan) - 1)
                {
                    ruangan[j] = input[i];
                    i++;
                    j++;
                }
                ruangan[j] = '\0';
                // if(ruangan[0] == '\0'){
                //     printf("Ruangan tidak ditemukan.\n");
                // } else {
                LihatRuangan(&denahRumahSakit, ruangan, &userList);
                // }
            }
            else
            {
                printf("Anda harus login terlebih dahulu!");
            }
            break;
        case ASSIGN_DOKTER:
            if (session.loggedIn == 1)
            {
                if (strcmp(GetRole(&session.currentUser), "manager") == 0)
                {
                    AssignDokter(&userList, &denahRumahSakit);
                }
                else
                {
                    printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
                }
            }
            else
            {
                printf("Anda harus login terlebih dahulu!");
            }
            break;
        case DIAGNOSIS:
            if (strcmp(session.currentUser.role, "dokter") == 0)
            {
                // Diagnosis(session.currentUser,penyakitList);
                int indeksRuangan[2];
                SearchRuangan(session.currentUser.id, &denahRumahSakit, indeksRuangan);

                if (indeksRuangan[0] == -1 && indeksRuangan[1] == -1)
                {
                    printf("Anda tidak ter-assign pada ruangan mana pun.\n");
                }
                else
                {
                    Ruangan *currentRuangan = GetRuangan(&denahRumahSakit, indeksRuangan[0], indeksRuangan[1]);
                    Node *current = currentRuangan->antrianPasien.head;
                    int found = 0;
                    int count = 0;
                    while (current != NULL && count < currentRuangan->kapasitasRuangan)
                    {
                        char namaPenyakit[256];
                        strcpy(namaPenyakit, "");
                        // Find the user in userList by ID and update diagnosa
                        for (int i = 0; i < userList.count; i++)
                        {
                            if (userList.users[i].id == current->data && strcmp(userList.users[i].role, "pasien") == 0)
                            {
                                if (userList.users[i].diagnosa == 0)
                                {
                                    Diagnosis(userList.users[i], penyakitList, namaPenyakit);
                                    if (strcmp(namaPenyakit, "") == 0)
                                    {
                                        printf("%s tidak terdiagnosa penyakit apapun!\n", userList.users[i].username);
                                    }
                                    else
                                    {
                                        printf("%s terdiagnosa penyakit %s!\n", userList.users[i].username, namaPenyakit);
                                    }
                                    userList.users[i].diagnosa = 1;
                                    found = 1;
                                    break;
                                }
                                else
                                {
                                    printf("Pasien %s sudah didiagnosis\n", userList.users[i].username);
                                    found = 1;
                                    break;
                                }
                            }
                        }
                        if (found)
                        {
                            break;
                        }
                        // count++;
                        // current = current->next;
                    }
                    if (!found)
                    {
                        printf("Tidak ada pasien dalam antrian yang belum didiagnosis.\n");
                    }
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh dokter.\n");
            }
            break;
        case NGOBATIN:
            if (strcmp(session.currentUser.role, "dokter") == 0)
            {
                // Diagnosis(session.currentUser,penyakitList);
                int indeksRuangan[2];
                SearchRuangan(session.currentUser.id, &denahRumahSakit, indeksRuangan);

                if (indeksRuangan[0] == -1 && indeksRuangan[1] == -1)
                {
                    printf("Anda tidak ter-assign pada ruangan mana pun.\n");
                }
                else
                {
                    Ruangan *currentRuangan = GetRuangan(&denahRumahSakit, indeksRuangan[0], indeksRuangan[1]);
                    Node *current = currentRuangan->antrianPasien.head;
                    int found = 0;
                    int count = 0;
                    while (current != NULL && count < currentRuangan->kapasitasRuangan)
                    {
                        char namaPenyakit[256];
                        strcpy(namaPenyakit, "");
                        // Find the user in userList by ID
                        for (int i = 0; i < userList.count; i++)
                        {
                            if (userList.users[i].id == current->data && strcmp(userList.users[i].role, "pasien") == 0)
                            {
                                if (userList.users[i].diagnosa == 1 && userList.users[i].ngobatin == 0)
                                {
                                    Diagnosis(userList.users[i], penyakitList, namaPenyakit);
                                    if (strcmp(namaPenyakit, "") == 0)
                                    {
                                        printf("%s tidak memiliki penyakit!\n", userList.users[i].username);
                                    }
                                    else
                                    {
                                        printf("%s memiliki penyakit %s!\n", userList.users[i].username, namaPenyakit);
                                        int penyakitId = GetPenyakitID(penyakitList, namaPenyakit);
                                        PrintObat(obatMap, penyakitId, obatList, namaPenyakit, arrayUrutanObat, &userList.users[i]);
                                    }
                                    userList.users[i].ngobatin = 1;
                                    found = 1;
                                    break;
                                }
                                else if (userList.users[i].diagnosa == 0)
                                {
                                    printf("Pasien belum didiagnosis!\n");
                                    found = 1;
                                    break;
                                }
                                else if (userList.users[i].ngobatin == 1)
                                {
                                    printf("Pasien %s sudah pernah diobati!\n", userList.users[i].username);
                                    found = 1;
                                    break;
                                }
                            }
                        }
                        if (found)
                        {
                            break;
                        }
                        // count++;
                        // current = current->next;
                    }
                    if (!found || count >= currentRuangan->kapasitasRuangan)
                    {
                        printf("Tidak ada pasien dalam antrian yang belum diobati.\n");
                    }
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh dokter.\n");
            }
            break;
        case LIHAT_SEMUA_ANTRIAN:
            if (strcmp(session.currentUser.role, "manager") == 0)
            {
                LihatDenah(&denahRumahSakit);
                for (int i = 0; i < denahRumahSakit.rows; i++)
                {
                    for (int j = 0; j < denahRumahSakit.cols; j++)
                    {
                        char ruangan[8];
                        ruangan[0] = 'A' + i;
                        if (j + 1 < 10)
                        {
                            ruangan[1] = '1' + j;
                            ruangan[1] = '0' + (j + 1);
                            ruangan[2] = '\0';
                        }
                        else
                        {
                            ruangan[1] = '0' + ((j + 1) / 10);
                            ruangan[2] = '0' + ((j + 1) % 10);
                            ruangan[3] = '\0';
                        }
                        int row, col;
                        UbahInput(ruangan, &row, &col);
                        // if (denahRumahSakit.data[row][col].dokter != -1)
                        // {
                        LihatRuangan(&denahRumahSakit, ruangan, &userList);
                        printAntrianRuangan(denahRumahSakit.data[row][col], &userList);
                        printf("\n");
                        // }
                    }
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
            }
            break;
        case ANTRIAN:
            if (strcmp(session.currentUser.role, "pasien") == 0)
            {
                LihatAntrianSaya(&userList, &session, &denahRumahSakit);
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh pasien.\n");
            }
            break;
        case DAFTAR_CHECKUP:
            DaftarCheckup(&userList, &session, &denahRumahSakit);
            break;
        case PULANGDOK:
            if (strcmp(session.currentUser.role, "pasien") == 0)
            {
                if (session.currentUser.ngobatin == 0 || session.currentUser.diagnosa == 0)
                {
                    printf("Kamu belum menerima diagnosis atau pengobatan dari dokter, jangan buru-buru pulang!\n");
                }
                else
                {
                    if (session.currentUser.jumlahObatMasukPerut >= session.currentUser.jumlahNgobat)
                    {
                        int benar = 1; // Nilai cek apakah urutan minum dengan resep sudah cocok atau belum
                        for (int i = 0; i < session.currentUser.jumlahNgobat; i++)
                        {
                            if (session.currentUser.perut.obat[i + 1].id != session.currentUser.urutanNgobat[i])
                            {
                                benar = 0;
                                break;
                            }
                        }
                        if (benar == 1)
                        {
                            printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
                            for (int i = 0; i < denahRumahSakit.rows; i++)
                            {
                                for (int j = 0; j < denahRumahSakit.cols; j++)
                                {
                                    Node *curr = denahRumahSakit.data[i][j].antrianPasien.head;
                                    while (curr != NULL)
                                    {
                                        if (curr->data == session.currentUser.id)
                                        {
                                            int idKeluar = dequeue(&denahRumahSakit.data[i][j].antrianPasien);
                                            if (denahRumahSakit.data[i][j].jumlahPasienDalamRuangan > 0)
                                            {
                                                denahRumahSakit.data[i][j].jumlahPasienDalamRuangan--;
                                            }
                                            if (denahRumahSakit.data[i][j].jumlahPasienDiAntrian > 0)
                                            {
                                                denahRumahSakit.data[i][j].jumlahPasienDiAntrian--;
                                            }
                                            printf("Pasien dengan ID %d telah keluar dari antrian.\n", idKeluar);
                                            session.currentUser.ngobatin = 0;
                                            session.currentUser.diagnosa = 0;
                                            session.currentUser.suhuTubuh = -1;
                                            session.currentUser.tekananDarahSistolik = -1;
                                            session.currentUser.tekananDarahDiastolik = -1;
                                            session.currentUser.detakJantung = -1;
                                            session.currentUser.saturasiOksigen = -1;
                                            session.currentUser.kadarGulaDarah = -1;
                                            session.currentUser.beratBadan = -1;
                                            session.currentUser.tinggiBadan = -1;
                                            session.currentUser.kadarKolesterol = -1;
                                            session.currentUser.trombosit = -1;
                                            break;
                                        }
                                        curr = curr->next;
                                    }
                                }
                            }
                        }
                        else if (benar == 0)
                        {
                            printf("Maaf, tapi kamu masih belum bisa pulang!\n");
                            printf("Urutan peminuman obat yang diharapkan:\n");
                            for (int i = 0; i < session.currentUser.jumlahNgobat; i++)
                            {
                                printf("%d", session.currentUser.urutanNgobat[i]);
                                if (i < session.currentUser.jumlahNgobat - 1)
                                {
                                    printf(" -> ");
                                }
                            }
                            printf("\n");
                            printf("Urutan peminum obat Anda:\n");
                            for (int i = 0; i < session.currentUser.jumlahObatMasukPerut; i++)
                            {
                                printf("%d", session.currentUser.perut.obat[i + 1].id);
                                if (i < session.currentUser.jumlahObatMasukPerut - 1)
                                {
                                    printf(" -> ");
                                }
                            }
                            printf("\n");
                            printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
                        }
                    }
                    else
                    {
                        printf("Jumlah obat yang kamu minum masih kurang dari yang diresepkan oleh dokter!\n");
                    }
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh pasien.\n");
            }
            break;
        case MINUM_OBAT:
            if (strcmp(session.currentUser.role, "pasien") == 0)
            {
                if (session.currentUser.ngobatin == 0)
                {
                    printf("Anda belum diobati oleh dokter!\n");
                }
                else
                {
                    char arrNamaObat[OBAT_CAPACITY][500];
                    printf("============ DAFTAR OBAT ============\n");
                    for (int i = 0; i < session.currentUser.jumlahObat; i++)
                    {
                        strcpy(arrNamaObat[i], GetObatById(obatList, session.currentUser.obat[i]).nama);
                        printf("%d. %s\n", i + 1, GetObatById(obatList, session.currentUser.obat[i]).nama);
                    }
                    MinumObat(obatList, &session.currentUser, arrNamaObat);
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh pasien.\n");
            }
            break;
        case PENAWAR:
            if (strcmp(session.currentUser.role, "pasien") == 0)
            {
                if (session.currentUser.jumlahObatMasukPerut > 0)
                {
                    Obat muntahin;
                    Pop(&session.currentUser.perut, &muntahin);
                    // Memasukkan obat kembali ke inventory
                    session.currentUser.obat[session.currentUser.jumlahObat++] = muntahin.id;
                    printf("Obat berhasil dimuntahkan dan dikembalikan ke inventory (ew), lain kali jangan makan obat sembarangan ya dek~\n");
                    session.currentUser.jumlahObatMasukPerut--;
                }
                else
                {
                    printf("Perut kosong!! Belum ada obat yang dimakan.\n");
                }
            }
            else
            {
                printf("Akses ditolak. Fitur ini hanya dapat diakses oleh pasien.\n");
            }
            break;
        default:
            printf("Command tidak ditemukan.\n");
        }
    } while (command != EXIT);

    return 0;
}