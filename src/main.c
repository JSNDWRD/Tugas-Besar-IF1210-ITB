#include <stdio.h>
#include "./header/user.h"
#include "./header/auth.h"
#include "./header/utils.h"
#include "./header/manager.h"
#include "./header/hospital.h"
#include "./header/command.h"

int main(int argc, char* argv[]) {
    UserList userList; // Daftar pengguna
    char folder[50];
    strcpy(folder,argv[1]);
    LoadUsers(&userList,argv[1]);

    Matrix denahRumahSakit; // Denah rumah sakit
    LoadConfig(&denahRumahSakit,folder);

    CommandList commandList; // Daftar command yang dapat digunakan

    const char *COMMAND_READY[COMMAND_CAPACITY] = {
        "HELP", "LOGIN", "LOGOUT", "REGISTER", "EXIT", "LUPA_PASSWORD", "LIHAT_USER", "LIHAT_PASIEN", "LIHAT_DOKTER", "CARI_USER", "CARI_PASIEN", "CARI_DOKTER", "TAMBAH_DOKTER", "LIHAT_DENAH", "LIHAT_RUANGAN"
    };
    enum Command { HELP=1, LOGIN, LOGOUT, REGISTER, EXIT, LUPA_PASSWORD, LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER, CARI_USER, CARI_PASIEN, CARI_DOKTER, TAMBAH_DOKTER, LIHAT_DENAH, LIHAT_RUANGAN };

    CreateCommandList(&commandList,COMMAND_READY); // Membuat List Statik yang berisikan command yang tersedia
    
    Session session = {.loggedIn = 0}; // Ketika program mulai, session adalah logged out
    int command = 0;
    char input[50]; // Input command
    do {
        int valid = 0;
        do {
            printf("\n>>> Input Command: ");
            scanf(" %[^\n]", input);
            char commandAwal[50];
            int i = 0;
            while(input[i] != '\0' && input[i] != ' ' && i < sizeof(commandAwal)-1){
                commandAwal[i] = input[i];
                i++;
            }
            commandAwal[i] = '\0';
            ToUpperCase(commandAwal);
            for (int i = 0; i < COMMAND_CAPACITY; i++) {
                if (strcmp(commandAwal, ELMTNAME(commandList,i)) == 0) {
                    valid = 1;
                    command = ELMTKEY(commandList,i);
                    break;
                }
            }
            if (!valid) {
                printf("Perintah tidak ditemukan, silakan input ulang.\n");
            }
        } while(valid == 0);

        // for (int i = 0; i < COMMAND_CAPACITY; i++) {
        //     if (strcmp(input, commandList.command[i].name) == 0) {
        //         command = i + 1;
        //         break;
        //     }
        // }

        switch (command) {
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
                do {
                    printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
                    scanf("%s", simpan);
                    ToLowerCase(simpan); // Ubah ke huruf kecil
                } while(strcmp(simpan, "y") != 0 && strcmp(simpan, "n") != 0);
                if(strcmp(simpan,"y") == 0){
                    char command[256];
                    char inputFolder[100];
                    printf("\nMasukkan nama folder: ");
                    scanf("%s",inputFolder);
                    sprintf(command, "[ -d %s ] || mkdir %s", inputFolder, inputFolder);
                    system(command);
                    SaveUsers(userList, inputFolder);
                    // SaveConfig(denahRumahSakit);
                }
                break;
            case LIHAT_USER:
                LihatUser(&userList,&session);
                break;
            case LIHAT_PASIEN:
                LihatPasien(&userList,&session);
                break;
            case LIHAT_DOKTER:
                LihatDokter(&userList,&session);
                break;
            case CARI_USER:
                CariUser(&userList,&session);
                break;
            case CARI_PASIEN:
                CariPasien(&userList, &session);
                break;
            case CARI_DOKTER:
                CariDokter(&userList,&session);
                break;
            case TAMBAH_DOKTER:
                TambahDokter(&userList,&session);
                break;
            case LIHAT_DENAH:
                if(session.loggedIn != 1){
                    printf("Anda harus login terlebih dahulu!");
                } else {
                    LihatDenah(&denahRumahSakit);
                }
                break;
            case LIHAT_RUANGAN:
                if(session.loggedIn == 1){
                    char ruangan[10];
                    int i = 0, j = 0;
                    while(input[i] != '\0' && input[i] != ' '){
                        i++;
                    }
                    if(input[i] == ' '){
                        i++;
                    }
                    while(input[i] != '\0' && j < sizeof(ruangan)-1){
                        ruangan[j] = input[i];
                        i++;
                        j++;
                    }
                    ruangan[j] = '\0';
                    // if(ruangan[0] == '\0'){
                    //     printf("Ruangan tidak ditemukan.\n");
                    // } else {
                        LihatRuangan(&denahRumahSakit, ruangan, userList);
                    // }
                }  else {
                    printf("Anda harus login terlebih dahulu!");
                }
                break;
            default:
                printf("Command tidak ditemukan.\n");
        }
    } while(command != EXIT);

    return 0;
}