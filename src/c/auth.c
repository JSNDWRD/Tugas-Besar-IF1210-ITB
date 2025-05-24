#include "../header/auth.h"

// Implementasi untuk set
Set CreateNewSet()
{
    Set newSet;
    newSet.count = 0;
    return newSet;
}

void InsertSet(Set *set, char *value)
{
    strcpy(set->username[set->count], value);
    set->count++;
}

int IsInSet(Set *set, char *value)
{
    for (int i = 0; i < set->count; i++)
    {
        if (strcmp(set->username[i], value) == 0)
        {
            return 1; // sudah ada
        }
    }
    return 0; // belum ada
}

// Implementasi auth
// Login menggunakan username yang case sensitive
void Login(UserList *userList, Session *session)
{
    if (session->loggedIn)
    {
        printf("Anda sudah login sebagai %s.\n", session->currentUser.username);
        return;
    }

    char usernameInput[MAX_USERNAME_LENGTH], passwordInput[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    scanf("%s", usernameInput);
    printf("Password: ");
    scanf("%s", passwordInput);

    for (int i = 0; i < userList->count; i++)
    {
        // strcmp return 0 jika sama
        if (strcmp(usernameInput, userList->users[i].username) == 0)
        {
            if (strcmp(passwordInput, userList->users[i].password) == 0)
            {
                session->loggedIn = 1;
                session->currentUser = userList->users[i];
                if (strcmp(session->currentUser.role, "manager") == 0)
                {
                    printf("\nSelamat pagi Manager %s!\n", session->currentUser.username);
                }
                else if (strcmp(session->currentUser.role, "dokter") == 0)
                {
                    printf("\nSelamat pagi Dokter %s!\n", session->currentUser.username);
                }
                else
                { // Pasien
                    printf("\nSelamat pagi %s! Ada keluhan apa?\n", session->currentUser.username);
                }
                return;
            }
            else
            {
                printf("Password salah untuk pengguna yang bernama %s!\n", usernameInput);
                return;
            }
        }
    }
    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", usernameInput);
}

// Register dokter baru khusus manager
// Username case insensitive, jadi tidak bisa ada username yang sama, tapi case nya beda
void TambahDokter(UserList *userList, Session *session)
{
    if (strcmp(session->currentUser.role, "manager") != 0)
    {
        printf("Anda bukan manager!\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Username baru: ");
    scanf("%s", username);
    printf("Password baru: ");
    scanf("%s", password);

    // Buat set untuk cek username unik
    Set usernameSet = CreateNewSet();

    for (int i = 0; i < userList->count; i++)
    {
        char lowered[MAX_USERNAME_LENGTH];
        if (strcmp(userList->users[i].role, "dokter") == 0)
        {
            strcpy(lowered, userList->users[i].username);
            ToLowerCase(lowered);
            InsertSet(&usernameSet, lowered);
        }
    }

    char usernameLowered[MAX_USERNAME_LENGTH];
    strcpy(usernameLowered, username);
    ToLowerCase(usernameLowered);

    if (IsInSet(&usernameSet, usernameLowered))
    {
        printf("Sudah ada dokter dengan nama %s!\n", username);
        return;
    }

    // Jika username unik, buat user baru
    User newUser;
    int idTerbesar = 0;
    for (int i = 0; i < userList->count; i++)
    {
        if (userList->users[i].id > idTerbesar)
        {
            idTerbesar = userList->users[i].id;
        }
    }
    CreateUser(&newUser, idTerbesar + 1, username, password, "dokter", "-", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    AddUser(userList, newUser);
    printf("\nDokter %s berhasil ditambahkan!\n", newUser.username);
}

void RegisterUser(UserList *userList, Session *session)
{
    if (session->loggedIn)
    {
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

    for (int i = 0; i < userList->count; i++)
    {
        char lowered[MAX_USERNAME_LENGTH];
        strcpy(lowered, userList->users[i].username);
        ToLowerCase(lowered);
        InsertSet(&usernameSet, lowered);
    }

    char usernameLowered[MAX_USERNAME_LENGTH];
    strcpy(usernameLowered, username);
    ToLowerCase(usernameLowered);

    if (IsInSet(&usernameSet, usernameLowered))
    {
        printf("Registrasi gagal! User dengan nama %s sudah terdaftar.\n", username);
        return;
    }

    // Jika username unik, buat user baru
    User newUser;
    int idTerbesar = 0;
    for (int i = 0; i < userList->count; i++)
    {
        if (userList->users[i].id > idTerbesar)
        {
            idTerbesar = userList->users[i].id;
        }
    }
    CreateUser(&newUser, idTerbesar + 1, username, password, "pasien", "-", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    AddUser(userList, newUser);
    printf("\nPasien %s berhasil ditambahkan!\n", newUser.username);
}

void Logout(Session *session)
{
    if (session->loggedIn == 0)
    {
        printf("Logout gagal!\nAnda belum login, silahkan login terlebih dahulu sebelum melakukan logout.\n");
    }
    else
    {
        printf("Sampai jumpa, %s!\n", session->currentUser.username);
        session->loggedIn = 0;
        memset(&session->currentUser, 0, sizeof(session->currentUser)); // Mereset session->currentUser, set jadi 0.
        // future update (if ngebug) -> ubah integers jadi -1, string jadi "-"
    }
}

// Username dilihat case sensitive
void ResetPassword(UserList *userList, Session *session)
{
    if (session->loggedIn)
    {
        printf("Logout dulu sebelum reset password\n");
        return;
    }
    // future implementation: diapus kalau mau bisa reset di dalem session
    //-> berarti harus logout setelah reset password.

    char username[MAX_USERNAME_LENGTH], kode[MAX_UNIQUE_CODE];

    printf("Username: ");
    scanf("%s", username);
    printf("Kode Unik: ");
    scanf("%s", kode);

    char usn_encoded[MAX_UNIQUE_CODE];

    RunLenEncode(username, usn_encoded);

    int ada = 0;

    for (int i = 0; i < userList->count; i++)
    {
        if (strcmp(username, userList->users[i].username) == 0)
        {
            ada = 1;

            if (strcmp(kode, usn_encoded) != 0)
            {
                printf("Kode unik salah!\n");
                return;
            }
            if (strcmp(userList->users[i].role, "manager") == 0)
            {
                printf("\nSelamat pagi Manager ");
            }
            else if (strcmp(userList->users[i].role, "pasien") == 0)
            {
                printf("\nSelamat pagi ");
            }
            else if (strcmp(userList->users[i].role, "dokter") == 0)
            {
                printf("\nSelamat pagi Dokter ");
            }
            printf("%s, silakan update password Anda\n", userList->users[i].username);

            char newPass[MAX_PASSWORD_LENGTH];
            printf("Password baru: ");
            scanf("%s", newPass);

            strcpy(userList->users[i].password, newPass);
            printf("Password berhasil direset!\n");
            return;
        }
    }

    if (!ada)
    {
        printf("Username tidak terdaftar!\n");
    }
}