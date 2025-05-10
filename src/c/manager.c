#include "../header/manager.h"
#include <stdio.h>

void SelectionSort(UserList *userList, int n, int basedOn, int order) {
    int i, j, idMin;

    for (i = 0; i < n - 1; i++) {
        idMin = i;
        for (j = i + 1; j < n; j++) {
            // 'beda' adalah hasil perbandingan
            int beda;

            if (basedOn == 1) {
                // jika negatif, berarti user j (user1) memiliki ID lebih kecil dari user idMin (user2)
                User user1 = GetUserAt(userList, j);
                User user2 = GetUserAt(userList, idMin);
                beda = GetID(&user1) - GetID(&user2);
            }
            else if(basedOn == 2){
                // strcmp mengembalikan nilai negatif jika str1 < str2,
                // nilai nol jika sama, dan nilai positif jika str1 > str2
                User user1 = GetUserAt(userList, j);
                User user2 = GetUserAt(userList, idMin);
                beda = strcmp(GetUsername(&user1), GetUsername(&user2));
            }

            if ((order == 1 && beda < 0) || (order == 2 && beda > 0)) {
                idMin = j;
            }
        }

        // swap di dalam loop
        if (idMin != i) {
            User temp = GetUserAt(userList, idMin);
            SetUserAt(userList, idMin, GetUserAt(userList, i));
            SetUserAt(userList, i, temp);
        }
    }
}

void PrintPilihan(int *pil1, int *pil2) {
    printf("Urutkan berdasarkan:\n");
    printf("   1. ID\n");
    printf("   2. Nama\n> Pilihan: ");
    scanf("%d", pil1);

    printf("Urutkan secara:\n");
    printf("   1. Ascending\n");
    printf("   2. Descending\n> Pilihan: ");
    scanf("%d", pil2);
}

void PrintList(UserList *userList, int basedOn, int order) {
    if(userList->count == 0) {
        printf("Tidak ada pengguna yang terdaftar.\n");
        return;
    }
    printf("Menampilkan semua pengguna dengan ");

    if (basedOn == 1) printf("ID ");
    else if (basedOn == 2) printf("Nama ");

    if (order == 1) printf("terurut ascending:\n");
    else if (order == 2) printf("terurut descending:\n");

    printf("ID | Nama     | Role   | Penyakit\n");
    printf("-------------------------------------\n");

    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        printf("%d | %-8s | %-6s | %s\n",
            GetID(&user),
            GetUsername(&user),
            GetRole(&user),
            GetRiwayatPenyakit(&user));
            // strcmp(GetRole(&user), "pasien") == 0 ? GetRiwayatPenyakit(&user) : "-");
    }
}

void LihatUser(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }
    else {
        int pil1 = 0, pil2 = 0;  // pil1 = sort by, pil2 = asc/desc
        PrintPilihan(&pil1, &pil2);

        // copy userList to sortedList
        UserList sortedList;
        sortedList.count = 0;
        for (int i = 0; i < userList->count; i++) {
            User user = GetUserAt(userList, i);
            if (strcmp(GetRole(&user), "manager") != 0) {
                AppendUser(&sortedList, user);
            }
        }

        SelectionSort(&sortedList, sortedList.count, pil1, pil2);
        PrintList(&sortedList, pil1, pil2);
    }
}

void LihatPasien(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1 = 0, pil2 = 0;
    PrintPilihan(&pil1, &pil2);

    // filter hanya pasien
    UserList sortedList;
    sortedList.count = 0;
    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "pasien") == 0) {
            AppendUser(&sortedList, user);
        }
    }

    SelectionSort(&sortedList, sortedList.count, pil1, pil2);
    
    printf("Menampilkan daftar pasien dengan ");
    if (pil1 == 1) printf("ID ");
    else if (pil1 == 2) printf("Nama ");
    if (pil2 == 1) printf("terurut ascending:\n");
    else if (pil2 == 2) printf("terurut descending:\n");

    printf("ID | Nama     | Penyakit\n");
    printf("-----------------------------\n");
    for (int i = 0; i < sortedList.count; i++) {
        User user = GetUserAt(&sortedList, i);
        printf("%d | %-8s | %s\n",
            GetID(&user),
            GetUsername(&user),
            GetRiwayatPenyakit(&user));
    }
}

void LihatDokter(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1 = 0, pil2 = 0;
    PrintPilihan(&pil1, &pil2);

    // filter hanya dokter
    UserList sortedList;
    sortedList.count = 0;
    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "dokter") == 0) {
            AppendUser(&sortedList, user);
        }
    }

    SelectionSort(&sortedList, sortedList.count, pil1, pil2);

    printf("Menampilkan daftar dokter dengan ");
    if (pil1 == 1) printf("ID ");
    else if (pil1 == 2) printf("Nama ");
    if (pil2 == 1) printf("terurut ascending:\n");
    else if (pil2 == 2) printf("terurut descending:\n");
    printf("ID | Nama\n");
    printf("------------------\n");
    for (int i = 0; i < sortedList.count; i++) {
        User user = GetUserAt(&sortedList, i);
        printf("%d | %s\n",
                GetID(&user),
                GetUsername(&user));
    }
}

void CariUser(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    // sorting, ascending berdasarkan nama
    UserList sortedList;
    sortedList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        AppendUser(&sortedList, GetUserAt(userList, i));
    }

    int pilihan = 0;
    printf("Urutkan berdasarkan:\n");
    printf("   1. ID\n");
    printf("   2. Nama\n> Pilihan: ");
    do {
        scanf("%d", &pilihan);
        printf("> Pilihan: ");
    } while(pilihan != 1 && pilihan != 2);

    if (pilihan == 1) {
        int idInput;
        printf("> Masukkan nomor ID user: ");
        scanf("%d", &idInput);

        int ada = 0;
        for (int i = 0; i < sortedList.count; i++) {
            User user = GetUserAt(&sortedList, i);
            if (GetID(&user) == idInput) {
                printf("Menampilkan user dengan nomor ID %d:\n", idInput);
                printf("ID | Nama     | Role   | Penyakit\n");
                printf("-------------------------------------\n");
                printf("%d | %-8s | %-6s | %s\n",
                    GetID(&user),
                    GetUsername(&user),
                    GetRole(&user),
                    GetRiwayatPenyakit(&user));
                ada = 1;
                break;
            }
        }

        if (!ada) {
            printf("Tidak ditemukan user dengan ID %d.\n", idInput);
        }

    }
    else if (pilihan == 2) {
        char nama[MAX_USERNAME_LENGTH];
        printf("> Masukkan nama user: ");
        scanf("%s", nama);

        // sorting: nama, ascending
        SelectionSort(&sortedList, sortedList.count, 2, 1);

        int index;
        if (BinarySearchUser(&sortedList, nama, &index)) {
            User user = GetUserAt(&sortedList, index);
            printf("Menampilkan pengguna dengan nama %s:\n", nama);
            printf("ID | Nama     | Role   | Penyakit\n");
            printf("-------------------------------------\n");
            printf("%d | %-8s | %-6s | %s\n",
                GetID(&user),
                GetUsername(&user),
                GetRole(&user),
                GetRiwayatPenyakit(&user));
        }
        else {
            printf("Tidak ditemukan user dengan nama \"%s\".\n", nama);
        }

    } 
    else {
        printf("Pilihan tidak valid.\n");
    }

}

void CariPasien(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    UserList sortedList;
    sortedList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "pasien") == 0) {
            AppendUser(&sortedList, user);
        }
    }

    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf("> Pilihan: ");
   do {
        scanf("%d", &pilihan);
         printf("> Pilihan: ");
    } while(pilihan != 1 && pilihan != 2 && pilihan != 3);

    if (pilihan == 1 || pilihan == 2) {
        // mirip cari user
        int sortBy = (pilihan == 1) ? 1 : 2;
        SelectionSort(&sortedList, sortedList.count, sortBy, 1);
        
        if (pilihan == 1) {
            int id;
            printf("> Masukkan nomor ID pasien: ");
            scanf("%d", &id);

            for (int i = 0; i < sortedList.count; i++) {
                User user = GetUserAt(&sortedList, i);
                if (GetID(&user) == id) {
                    printf("Menampilkan pasien dengan ID %d:\n", id);
                    printf("ID | Nama     | Penyakit\n");
                    printf("----------------------------\n");
                    printf("%d | %-8s | %s\n", id, GetUsername(&user), GetRiwayatPenyakit(&user));
                    return;
                }
            }
            printf("Tidak ditemukan pasien dengan ID %d.n", id);
        }
        else {
            char nama[MAX_USERNAME_LENGTH];
            printf("> Masukkan nama pasien: ");
            scanf(" %[^\n]", nama);

            int index;
            if (BinarySearchUser(&sortedList, nama, &index)) {
                User user = GetUserAt(&sortedList, index);
                printf("Menampilkan pasien dengan nama %s:\n", nama);
                printf("ID | Nama     | Penyakit\n");
                printf("----------------------------\n");
                printf("%d | %-8s | %s\n",
                    GetID(&user),
                    GetUsername(&user),
                    GetRiwayatPenyakit(&user));
            }
            else {
                printf("Tidak ditemukan pasien dengan nama \"%s\".\n", nama);
            }
        }
    }
    else if (pilihan == 3) {
        char penyakit[50];
        printf("> Masukkan nama penyakit: ");
        scanf(" %[^\n]", penyakit);

        // pasien dengan penyakit tsb
        UserList pasienList;
        pasienList.count = 0;

        for (int i = 0; i < sortedList.count; i++) {
            User user = GetUserAt(&sortedList, i);
            if (strcmp(GetRiwayatPenyakit(&user), penyakit) == 0) {
                AppendUser(&pasienList, user);
            }
        }

        if (pasienList.count == 0) {
            printf("Tidak ditemukan pasien dengan penyakit %s.\n", penyakit);
            return;
        }

        int pilihSort;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf("> Pilihan: ");
        scanf("%d", &pilihSort);

        int urut;
        printf("Urutan sort %s?\n", pilihSort == 1 ? "ID" : "Nama");
        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("> Pilihan: ");
        scanf("%d", &urut);

        SelectionSort(&pasienList, pasienList.count, pilihSort, urut == 1 ? 1 : 0);

        printf("Menampilkan pasien dengan penyakit %s dengan %s terurut %s:\n", penyakit, pilihSort == 1 ? "ID" : "Nama", urut == 1 ? "ascending" : "descending");

        printf("ID | Nama     | Penyakit\n");
        printf("----------------------------\n");
        for (int i = 0; i < pasienList.count; i++) {
            User user = GetUserAt(&pasienList, i);
            printf("%d | %-8s | %s\n", 
                GetID(&user),
                GetUsername(&user),
                GetRiwayatPenyakit(&user));
        }
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
}

void CariDokter(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }
    UserList dokterList;
    dokterList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "dokter") == 0) {
            AppendUser(&dokterList, user);
        }
    }

    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n>>> Pilihan: ");
    do {
        scanf("%d", &pilihan);
        printf("> Pilihan: ");
    } while(pilihan != 1 && pilihan != 2);

    SelectionSort(&dokterList, dokterList.count, pilihan, 1);

    if (pilihan == 1) {
        int id;
        printf("> Masukkan nomor ID dokter: ");
        scanf("%d", &id);

        for (int i = 0; i < dokterList.count; i++) {
            User user = GetUserAt(&dokterList, i);
            if (GetID(&user) == id) {
                printf("Menampilkan dokter dengan ID %d:\n", id);
                printf("ID | Nama\n");
                printf("---------------\n");
                printf("%d | %s\n", id, GetUsername(&user));
                return;
            }
        }
        printf("Tidak ditemukan dokter dengan ID %d.\n", id);
    }
    else if (pilihan == 2) {
        char nama[MAX_USERNAME_LENGTH];
        printf("> Masukkan nama dokter: ");
        scanf("%s", nama);

        int index;
        if (BinarySearchUser(&dokterList, nama, &index)) {
            User user = GetUserAt(&dokterList, index);
            printf("Menampilkan dokter dengan nama %s:\n", nama);
            printf("ID | Nama\n");
            printf("---------------\n");
            printf("%d | %s\n", GetID(&user), GetUsername(&user));
        } else {
            printf("Tidak ditemukan dokter dengan nama \"%s\".\n", nama);
        }
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

int BinarySearchUser(UserList *userList, char *username, int *index) {
    char target[MAX_USERNAME_LENGTH], currUser[MAX_USERNAME_LENGTH];

    ToLower(target, username);

    int left = 0;
    int right = userList->count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        User user = GetUserAt(userList, mid);
        ToLower(currUser, GetUsername(&user));

        int cmp = strcmp(currUser, target);
        if (cmp == 0) {
            *index = mid;
            return 1;
        }
        else if (cmp < 0) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }

    return 0;  // tidak ditemukan
}

User GetUserAt(UserList *userList, int idx) {
    return userList->users[idx];
}

void SetUserAt(UserList *userList, int idx, User user) {
    userList->users[idx] = user;
}

int AppendUser(UserList *userList, User user) {
    if (userList->count >= 100) return 0;
    userList->users[userList->count++] = user;
    return 1;
}

