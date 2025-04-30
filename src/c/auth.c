#include "../header/auth.h"

// Implementasi untuk set.
Set CreateNewSet() {
    Set newSet;
    newSet.count = 0;
    return newSet;
}

void InsertSet(Set *set, char *value) {
    strcpy(set->username[set->count], value);
    set->count++;
}

int IsInSet(Set *set, char *value) {
    for (int i = 0; i < set->count; i++) {
        if (strcmp(set->username[i], value) == 0) {
            return 1;  // sudah ada
        }
    }
    return 0;  // belum ada
}

// Implementasi auth.
void ToLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void Login(UserList *userList, Session *session) {
    if (session->loggedIn) {
        printf("Anda sudah login sebagai %s.\n", session->currentUser.username);
        return;
    }

    char usernameInput[MAX_USERNAME_LENGTH], passwordInput[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    scanf("%s", usernameInput);
    printf("Password: ");
    scanf("%s", passwordInput);

    for (int i = 0; i < userList->count; i++) {
        // strcmp return 0 jika sama
        if (strcmp(usernameInput, userList->users[i].username) == 0) {
            if (strcmp(passwordInput, userList->users[i].password) == 0) {
                session->loggedIn = 1;
                session->currentUser = userList->users[i];
                printf("Selamat datang, %s!\n", session->currentUser.username);
                return;
            } else {
                printf("Password salah untuk username %s.\n", usernameInput);
                return;
            }
        }
    }
    printf("Username %s tidak ditemukan!\n", usernameInput);
}

void RegisterUser(UserList *userList, Session *session) {
    if (session->loggedIn) {
        printf("Logout dulu sebelum register!\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Username baru: ");
    scanf("%s", username);
    printf("Password baru: ");
    scanf("%s", password);

    // Buat set untuk cek username unik
    Set usernameSet = CreateNewSet();

    for (int i = 0; i < userList->count; i++) {
        char lowered[MAX_USERNAME_LENGTH];
        strcpy(lowered, userList->users[i].username);
        ToLowerCase(lowered);
        InsertSet(&usernameSet, lowered);
    }

    char usernameLowered[MAX_USERNAME_LENGTH];
    strcpy(usernameLowered, username);
    ToLowerCase(usernameLowered);

    if (IsInSet(&usernameSet, usernameLowered)) {
        printf("Registrasi gagal! Username %s sudah terdaftar.\n", username);
        return;
    }

    // Jika username unik, buat user baru
    User newUser = CreateNewUser(userList->count + 1, username, password, "pasien", "-", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

    AddUser(userList, newUser);
    printf("Registrasi sukses! Silahkan login dengan akun baru.\n");
}
