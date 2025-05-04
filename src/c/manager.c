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
                // jika negatif, berarti userList->users[j].id < userList->users[idMin].id
                beda = userList->users[j].id - userList->users[idMin].id;
            }
            else if(basedOn == 2){
                // strcmp mengembalikan nilai negatif jika str1 < str2,
                // nilai nol jika sama, dan nilai positif jika str1 > str2
                beda = strcmp(userList->users[j].username, userList->users[idMin].username);
            }

            if ((order == 1 && beda < 0) || (order == 2 && beda > 0)) {
                idMin = j;
            }
        }

        // swap di dalam loop
        if (idMin != i) {
            User temp = userList->users[idMin];
            userList->users[idMin] = userList->users[i];
            userList->users[i] = temp;
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
        printf("%d | %-8s | %-6s | %s\n",
            userList->users[i].id,
            userList->users[i].username,
            userList->users[i].role,
            userList->users[i].riwayatPenyakit);
            // strcmp(userList->users[i].role, "pasien") == 0 ? userList->users[i].riwayatPenyakit : "-");
    }
}

void LihatUser(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(session->currentUser.role, "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }
    else {
        int pil1 = 0, pil2 = 0;  // pil1 = sort by, pil2 = asc/desc
        PrintPilihan(&pil1, &pil2);

        // copy userList to sortedList
        UserList sortedList;
        sortedList.count = userList->count;
        for (int i = 0; i < userList->count; i++) {
            sortedList.users[i] = userList->users[i];
        }

        SelectionSort(&sortedList, sortedList.count, pil1, pil2);
        PrintList(&sortedList, pil1, pil2);
    }
}

void LihatPasien(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(session->currentUser.role, "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1 = 0, pil2 = 0;
    PrintPilihan(&pil1, &pil2);

    // filter hanya pasien
    UserList sortedList;
    sortedList.count = 0;
    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].role, "pasien") == 0) {
            sortedList.users[sortedList.count++] = userList->users[i];
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
        printf("%d | %-8s | %s\n",
            sortedList.users[i].id,
            sortedList.users[i].username,
            sortedList.users[i].riwayatPenyakit);
    }
}

void LihatDokter(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(session->currentUser.role, "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1 = 0, pil2 = 0;
    PrintPilihan(&pil1, &pil2);

    // filter hanya dokter
    UserList sortedList;
    sortedList.count = 0;
    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].role, "dokter") == 0) {
            sortedList.users[sortedList.count++] = userList->users[i];
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
        printf("%d | %s\n",
                sortedList.users[i].id,
                sortedList.users[i].username);
    }
}

void CariUser(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(session->currentUser.role, "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    // sorting, ascending berdasarkan nama
    UserList sortedList;
    sortedList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        sortedList.users[sortedList.count++] = userList->users[i];
    }

    int pilihan = 0;
    printf("Urutkan berdasarkan:\n");
    printf("   1. ID\n");
    printf("   2. Nama\n> Pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        int idInput;
        printf("> Masukkan nomor ID user: ");
        scanf("%d", &idInput);

        int ada = 0;
        for (int i = 0; i < sortedList.count; i++) {
            if (sortedList.users[i].id == idInput) {
                printf("Menampilkan user dengan nomor ID %d:\n", idInput);
                printf("ID | Nama     | Role   | Penyakit\n");
                printf("-------------------------------------\n");
                printf("%d | %-8s | %-6s | %s\n",
                    sortedList.users[i].id,
                    sortedList.users[i].username,
                    sortedList.users[i].role,
                    sortedList.users[i].riwayatPenyakit);
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
            printf("Menampilkan pengguna dengan nama %s:\n", nama);
            printf("ID | Nama     | Role   | Penyakit\n");
            printf("-------------------------------------\n");
            printf("%d | %-8s | %-6s | %s\n",
                sortedList.users[index].id,
                sortedList.users[index].username,
                sortedList.users[index].role,
                sortedList.users[index].riwayatPenyakit);
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
    if (!session->loggedIn || strcmp(session->currentUser.role, "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    UserList sortedList;
    sortedList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].role, "pasien") == 0) {
            sortedList.users[sortedList.count++] = userList->users[i];
        }
    }

    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf("> Pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1 || pilihan == 2) {
        // mirip cari user
        int sortBy = (pilihan == 1) ? 1 : 2;
        SelectionSort(&sortedList, sortedList.count, sortBy, 1);
        
        if (pilihan == 1) {
            int id;
            printf("> Masukkan nomor ID pasien: ");
            scanf("%d", &id);

            for (int i = 0; i < sortedList.count; i++) {
                if (sortedList.users[i].id == id) {
                    printf("Menampilkan pasien dengan ID %d:\n", id);
                    printf("ID | Nama     | Penyakit\n");
                    printf("----------------------------\n");
                    printf("%d | %-8s | %s\n", id, sortedList.users[i].username, sortedList.users[i].riwayatPenyakit);
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
                printf("Menampilkan pasien dengan nama %s:\n", nama);
                printf("ID | Nama     | Penyakit\n");
                printf("----------------------------\n");
                printf("%d | %-8s | %s\n",
                    sortedList.users[index].id,
                    sortedList.users[index].username,
                    sortedList.users[index].riwayatPenyakit);
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
            if (strcmp(sortedList.users[i].riwayatPenyakit, penyakit) == 0) {
                pasienList.users[pasienList.count++] = sortedList.users[i];
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
            printf("%d | %-8s | %s\n", 
                pasienList.users[i].id,
                pasienList.users[i].username,
                pasienList.users[i].riwayatPenyakit);
        }
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
}

void CariDokter(UserList *userList, Session *session) {
    UserList dokterList;
    dokterList.count = 0;

    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].role, "dokter") == 0) {
            dokterList.users[dokterList.count++] = userList->users[i];
        }
    }

    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n>>> Pilihan: ");
    scanf("%d", &pilihan);

    SelectionSort(&dokterList, dokterList.count, pilihan, 1);

    if (pilihan == 1) {
        int id;
        printf("> Masukkan nomor ID dokter: ");
        scanf("%d", &id);

        for (int i = 0; i < dokterList.count; i++) {
            if (dokterList.users[i].id == id) {
                printf("Menampilkan dokter dengan ID %d:\n", id);
                printf("ID | Nama\n");
                printf("---------------\n");
                printf("%d | %s\n", id, dokterList.users[i].username);
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
            printf("Menampilkan dokter dengan nama %s:\n", nama);
            printf("ID | Nama\n");
            printf("---------------\n");
            printf("%d | %s\n", dokterList.users[index].id, dokterList.users[index].username);
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
        ToLower(currUser, userList->users[mid].username);

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

