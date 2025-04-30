#include <stdio.h>
#include "./header/user.h"
#include "./header/auth.h"
#include "./header/utils.h"
#include "./header/manager.h"

int main() {
    UserList userList; // Daftar pengguna
    LoadUsers(&userList);
    char arrCommand[20][50] = {"HELP", "LOGIN", "LOGOUT", "REGISTER", "EXIT", "LUPA_PASSWORD", "LIHAT_USER", "LIHAT_PASIEN", "LIHAT_DOKTER"};
    char input[50]; // Input command
    enum Command { HELP=1, LOGIN, LOGOUT, REGISTER, EXIT, LUPA_PASSWORD, LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER };
    Session session = {.loggedIn = 0};

    int command = 0;
    int commandCount = sizeof(arrCommand) / sizeof(arrCommand[0]);
    do {
        int valid = 0;
        do {
            printf("\n>>> Input Command: ");
            scanf("%s", input);
            ToUpperCase(input);
            for (int i = 0; i < commandCount; i++) {
                if (strcmp(input, arrCommand[i]) == 0) {
                    valid = 1;
                    break;
                }
            }
            if (!valid) {
                printf("Perintah tidak ditemukan, silakan input ulang.\n");
            }
        } while(valid == 0);

        for (int i = 0; i < commandCount; i++) {
            if (strcmp(input, arrCommand[i]) == 0) {
                command = i + 1;
                break;
            }
        }

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

            default:
                printf("Command tidak ditemukan.\n");
        }
    } while(command != EXIT);

    return 0;
}