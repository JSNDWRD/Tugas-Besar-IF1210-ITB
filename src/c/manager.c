#include "../header/manager.h"

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
        User user = userList->users[i];
        printf("%d | %-8s | %-6s | %s\n",
                user.id,
                user.username,
                user.role,
                user.riwayatPenyakit);
                // strcmp(user.role, "pasien") == 0 ? user.riwayatPenyakit : "-");
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

