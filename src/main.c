#include <stdio.h>
#include "./header/user.h"
#include "./header/auth.h"
#include "./header/utils.h"
#include "./header/manager.h"
// #include "./header/hospital.h"
#include "./header/command.h"

int main(int argc, char* argv[]) {
    UserList userList; // Daftar pengguna
    LoadUsers(&userList,argv[1]);

    // Matrix denahRumahSakit; // Denah rumah sakit
    // LoadConfig(&denahRumahSakit,argv[1]);

    CommandList commandList; // Daftar command yang dapat digunakan

    const char *COMMAND_READY[COMMAND_CAPACITY] = {
        "HELP", "LOGIN", "LOGOUT", "REGISTER", "EXIT", "LUPA_PASSWORD", "LIHAT_USER", "LIHAT_PASIEN", "LIHAT_DOKTER", "CARI_USER", "CARI_PASIEN", "CARI_DOKTER", "TAMBAH_DOKTER", "LIHAT_DENAH"
    };
    enum Command { HELP=1, LOGIN, LOGOUT, REGISTER, EXIT, LUPA_PASSWORD, LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER, CARI_USER, CARI_PASIEN, CARI_DOKTER, TAMBAH_DOKTER, LIHAT_DENAH };

    CreateCommandList(&commandList,COMMAND_READY); // Membuat List Statik yang berisikan command yang tersedia
    
    Session session = {.loggedIn = 0}; // Ketika program mulai, session adalah logged out
    int command = 0;
    char input[50]; // Input command
    do {
        int valid = 0;
        do {
            printf("\n>>> Input Command: ");
            scanf("%s", input);
            ToUpperCase(input);
            for (int i = 0; i < COMMAND_CAPACITY; i++) {
                if (strcmp(input, ELMTNAME(commandList,i)) == 0) {
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
                Exit(userList);
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
                // LihatDenah(&denahRumahSakit);
                break;
            default:
                printf("Command tidak ditemukan.\n");
        }
    } while(command != EXIT);

    return 0;
}