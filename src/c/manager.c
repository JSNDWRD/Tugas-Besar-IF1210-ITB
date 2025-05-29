#include "../header/manager.h"
// #include <stdio.h>

void SelectionSort(UserList *userList, int n, int basedOn, int order) {
    // n adalah jumlah elemen dalam array
    // basedOn = 1 -> sort by ID, basedOn = 2 -> sort by username
    // order = 1 -> ascending, order = 2 -> descending

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
            else if (basedOn == 2) {
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

void CariPilihan(int *pil) {
    *pil = 0;

    do { // validasi input
        printf("Cari berdasarkan:\n");
        printf("   1. ID\n");
        printf("   2. Nama\n> Pilihan: ");
        scanf("%d", pil);
        if (*pil < 1 || *pil > 2) {
            printf("Pilihan tidak valid. Silakan masukkan 1 atau 2.\n\n");
        }
    } while (*pil < 1 || *pil > 2);
}

void PrintPilihan(int *pil1, int *pil2) {
    *pil1 = 0;
    *pil2 = 0;

    do
    { // validasi input 1
        printf("Urutkan berdasarkan:\n");
        printf("   1. ID\n");
        printf("   2. Nama\n> Pilihan: ");
        scanf("%d", pil1);
        if (*pil1 < 1 || *pil1 > 2)
        {
            printf("Pilihan tidak valid. Silakan masukkan 1 atau 2.\n\n");
        }
    } while (*pil1 < 1 || *pil1 > 2);

    printf("\n");

    do { // validasi input 2
        printf("Urutkan secara:\n");
        printf("   1. Ascending\n");
        printf("   2. Descending\n> Pilihan: ");
        scanf("%d", pil2);
        if (*pil2 < 1 || *pil2 > 2)
        {
            printf("Pilihan tidak valid. Silakan masukkan 1 atau 2.\n\n");
        }
    } while (*pil2 < 1 || *pil2 > 2);
}

void PrintList(UserList *userList, int basedOn, int order) {
    if (userList->count == 0)
    {
        printf("Tidak ada pengguna yang terdaftar.\n");
        return;
    }
    printf("Menampilkan semua pengguna dengan ");

    if (basedOn == 1)
        printf("ID ");
    else if (basedOn == 2)
        printf("Nama ");

    if (order == 1)
        printf("terurut ascending:\n");
    else if (order == 2)
        printf("terurut descending:\n");

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
        int pil1, pil2; // pil1 = sort by, pil2 = asc/desc
        PrintPilihan(&pil1, &pil2);

        // copy userList to sortedList
        UserList *sortedList = malloc(sizeof(UserList));
        sortedList->count = 0;
        for (int i = 0; i < userList->count; i++) {
            User user = GetUserAt(userList, i);
            if (strcmp(GetRole(&user), "manager") != 0) {
                AppendUser(sortedList, user);
            }
        }

        SelectionSort(sortedList, sortedList->count, pil1, pil2);
        PrintList(sortedList, pil1, pil2);
        free(sortedList);
    }
}

void LihatPasien(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1, pil2;
    PrintPilihan(&pil1, &pil2);

    // filter hanya pasien
    UserList *sortedList = malloc(sizeof(UserList));
    sortedList->count = 0;
    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "pasien") == 0) {
            AppendUser(sortedList, user);
        }
    }

    SelectionSort(sortedList, sortedList->count, pil1, pil2);

    printf("Menampilkan daftar pasien dengan ");

    if (pil1 == 1)
        printf("ID ");
    else if (pil1 == 2)
        printf("Nama ");

    if (pil2 == 1)
        printf("terurut ascending:\n");
    else if (pil2 == 2)
        printf("terurut descending:\n");

    printf("ID | Nama     | Penyakit\n");
    printf("-----------------------------\n");
    for (int i = 0; i < sortedList->count; i++) {
        User user = GetUserAt(sortedList, i);
        printf("%d | %-8s | %s\n",
            GetID(&user),
            GetUsername(&user),
            GetRiwayatPenyakit(&user));
    }
    free(sortedList);
}

void LihatDokter(UserList *userList, Session *session)
{
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0)
    {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    int pil1, pil2;
    PrintPilihan(&pil1, &pil2);

    // filter hanya dokter
    UserList *sortedList = malloc(sizeof(UserList));
    sortedList->count = 0;
    for (int i = 0; i < userList->count; i++)
    {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "dokter") == 0)
        {
            AppendUser(sortedList, user);
        }
    }

    SelectionSort(sortedList, sortedList->count, pil1, pil2);

    printf("Menampilkan daftar dokter dengan ");

    if (pil1 == 1)
        printf("ID ");
    else if (pil1 == 2)
        printf("Nama ");

    if (pil2 == 1)
        printf("terurut ascending:\n");
    else if (pil2 == 2)
        printf("terurut descending:\n");

    printf("ID | Nama\n");
    printf("------------------\n");
    for (int i = 0; i < sortedList->count; i++)
    {
        User user = GetUserAt(sortedList, i);
        printf("%d | %s\n",
            GetID(&user),
            GetUsername(&user));
    }
    free(sortedList);
}

void CariUser(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    UserList *sortedList = malloc(sizeof(UserList));
    sortedList->count = 0;

    // copy userList to sortedList, untuk di sorting
    for (int i = 0; i < userList->count; i++) {
        AppendUser(sortedList, GetUserAt(userList, i));
    }

    int pilihan;
    CariPilihan(&pilihan); // validasi input

    if (pilihan == 1) {
        int idInput;
        printf("> Masukkan nomor ID user: ");
        scanf("%d", &idInput);

        SelectionSort(sortedList, sortedList->count, 1, 1);

        int index;
        if (BinarySearchUser(sortedList, idInput, &index)) {
            User user = GetUserAt(sortedList, index);
            if (strcmp(user.role, "manager") == 0) {
                printf("Tidak ditemukan user dengan ID %d.\n", idInput);
                return;
            }
            printf("Menampilkan user dengan nomor ID %d:\n", idInput);
            printf("ID | Nama     | Role   | Penyakit\n");
            printf("-------------------------------------\n");
            printf("%d | %-8s | %-6s | %s\n",
                GetID(&user),
                GetUsername(&user),
                GetRole(&user),
                GetRiwayatPenyakit(&user));
        }
        else {
            printf("Tidak ditemukan user dengan ID %d.\n", idInput);
        }
    }
    else if (pilihan == 2) {
        char nama[MAX_USERNAME_LENGTH];
        printf("> Masukkan nama user: ");
        scanf("%s", nama);

        // sorting: nama, ascending
        SelectionSort(sortedList, sortedList->count, 2, 1);

        int index;
        if (SequenceSearchUser(sortedList, nama, &index)) {
            User user = GetUserAt(sortedList, index);
            if (strcmp(user.role, "manager") == 0) {
                printf("Tidak ditemukan user dengan nama %s.\n", user.username);
                return;
            }
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
    free(sortedList);
}

void CariPasien(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    UserList *sortedList = malloc(sizeof(UserList));
    sortedList->count = 0;

    // copy userList to sortedList, khusus pasien
    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "pasien") == 0) {
            AppendUser(sortedList, user);
        }
    }

    int pilihan;
    do { // validasi input, tidak pakai fungsi karena input ada 3
        printf("Cari berdasarkan:\n");
        printf("   1. ID\n");
        printf("   2. Nama\n");
        printf("   3. Penyakit\n> Pilihan: ");
        scanf("%d", &pilihan);
        if (pilihan < 1 || pilihan > 3) {
            printf("Pilihan tidak valid. Silakan masukkan 1, 2, atau 3.\n\n");
        }
    } while (pilihan < 1 || pilihan > 3);

    if (pilihan == 1) {
        int idInput;
        printf("> Masukkan nomor ID pasien: ");
        scanf("%d", &idInput);

        SelectionSort(sortedList, sortedList->count, 1, 1); // sort by ID, ascending

        int index;
        if (BinarySearchUser(sortedList, idInput, &index)) {
            User user = GetUserAt(sortedList, index);
            printf("Menampilkan pasien dengan ID %d:\n", idInput);
            printf("ID | Nama     | Penyakit\n");
            printf("----------------------------\n");
            printf("%d | %-8s | %s\n",
                GetID(&user),
                GetUsername(&user),
                GetRiwayatPenyakit(&user));
            return;
        }
        else {
            printf("Tidak ditemukan pasien dengan ID %d.\n", idInput);
        }
    }
    else if (pilihan == 2) {
        char nama[MAX_USERNAME_LENGTH];
        printf("> Masukkan nama pasien: ");
        scanf(" %[^\n]", nama);

        int index;
        if (SequenceSearchUser(sortedList, nama, &index)) {
            User user = GetUserAt(sortedList, index);
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
    else if (pilihan == 3) {
        char penyakit[50];
        printf("> Masukkan nama penyakit: ");
        scanf(" %[^\n]", penyakit);

        // pasien dengan penyakit tsb
        UserList *pasienList = malloc(sizeof(UserList));
        pasienList->count = 0;

        for (int i = 0; i < sortedList->count; i++) {
            User user = GetUserAt(sortedList, i);
            char penyakitUser[50];
            strcpy(penyakitUser, GetRiwayatPenyakit(&user));
            ToLowerCase(penyakitUser);

            char penyakitInput[50];
            strcpy(penyakitInput, penyakit);
            ToLowerCase(penyakitInput);

            if (strcmp(penyakitUser, penyakitInput) == 0) {
                AppendUser(pasienList, user);
            }
        }

        if (pasienList->count == 0) {
            printf("Tidak ditemukan pasien dengan penyakit %s.\n", penyakit);
            return;
        }

        int pilihSort, urut;
        PrintPilihan(&pilihSort, &urut);
        // pilihSort = 1: ID, 2: Nama
        // urut = 1: ascending, 2: descending

        SelectionSort(pasienList, pasienList->count, pilihSort, urut);

        printf("Menampilkan pasien dengan penyakit %s dengan %s terurut %s:\n", penyakit, pilihSort == 1 ? "ID" : "Nama", urut == 1 ? "ascending" : "descending");

        printf("ID | Nama     | Penyakit\n");
        printf("----------------------------\n");
        for (int i = 0; i < pasienList->count; i++) {
            User user = GetUserAt(pasienList, i);
            printf("%d | %-8s | %s\n",
                GetID(&user),
                GetUsername(&user),
                GetRiwayatPenyakit(&user));
        }
        free(pasienList);
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
    free(sortedList);
}

void CariDokter(UserList *userList, Session *session) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "manager") != 0) {
        printf("Akses ditolak. Fitur ini hanya dapat diakses oleh manager.\n");
        return;
    }

    UserList *dokterList = malloc(sizeof(UserList));
    dokterList->count = 0;

    // copy userList to dokterList, khusus dokter
    for (int i = 0; i < userList->count; i++) {
        User user = GetUserAt(userList, i);
        if (strcmp(GetRole(&user), "dokter") == 0) {
            AppendUser(dokterList, user);
        }
    }
    
    int pilihan;
    CariPilihan(&pilihan);

    if (pilihan == 1) {
        int idInput;
        printf("> Masukkan nomor ID dokter: ");
        scanf("%d", &idInput);

        SelectionSort(dokterList, dokterList->count, 1, 1);

        int index;
        if (BinarySearchUser(dokterList, idInput, &index)) {
            User user = GetUserAt(dokterList, index);
            printf("Menampilkan dokter dengan ID %d:\n", idInput);
            printf("ID | Nama\n");
            printf("---------------\n");
            printf("%d | %s\n",
                GetID(&user),
                GetUsername(&user));
            return;
        }
        else {
            printf("Tidak ditemukan dokter dengan ID %d.\n", idInput);
        }
    }
    else if (pilihan == 2) {
        char nama[MAX_USERNAME_LENGTH];
        printf("> Masukkan nama dokter: ");
        scanf("%s", nama);

        SelectionSort(dokterList, dokterList->count, 2, 1);

        int index;
        if (SequenceSearchUser(dokterList, nama, &index)) {
            User user = GetUserAt(dokterList, index);
            printf("Menampilkan dokter dengan nama %s:\n", nama);
            printf("ID | Nama\n");
            printf("---------------\n");
            printf("%d | %s\n", GetID(&user), GetUsername(&user));
        }
        else {
            printf("Tidak ditemukan dokter dengan nama \"%s\".\n", nama);
        }
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
    free(dokterList);
}

int BinarySearchUser(UserList *userList, int id, int *index) {
    int left = 0;
    int right = userList->count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        User user = GetUserAt(userList, mid);
        int midUserId = GetID(&user);

        if (midUserId == id) {
            *index = mid;
            return 1;
        }
        else if (midUserId < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return 0; // tidak ditemukan
}

int SequenceSearchUser(UserList *userList, char *username, int *index) {
    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].username, username) == 0) {
            *index = i;
            return 1;
        }
    }
    return 0; // tidak ditemukan
}

User GetUserAt(UserList *userList, int idx) {
    return userList->users[idx];
}

User GetUserById(UserList *userList, int userId) {
    int left = 0;
    int right = userList->count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int midId = userList->users[mid].id;
        if (midId == userId) {
            return userList->users[mid];
        }
        else if (midId < userId) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    User userNull;
    userNull.id = -1;
    return userNull;
}

void SetUserAt(UserList *userList, int idx, User user) {
    userList->users[idx] = user;
}

int AppendUser(UserList *userList, User user) {
    if (userList->count < MAX_USERS)
    {
        userList->users[userList->count] = user;
        userList->count++;
        return 1; // berhasil
    }
    return 0; // gagal (penuh)
}

void AssignDokter(UserList *userList, Matrix *denahRumahSakit) {

    char username[MAX_USERNAME_LENGTH];
    printf("Username: ");
    scanf("%s", username);

    // Cari index dokter berdasarkan username
    int indexDokter;
    if (SequenceSearchUser(userList, username, &indexDokter) == 0){
        printf("User dengan nama %s tidak ditemukan.\n", username);
        return;
    }

    // Cek apakah user adalah dokter
    User dokter = GetUserAt(userList, indexDokter);
    if (strcmp(GetRole(&dokter), "dokter") != 0) {
        printf("User dengan nama %s bukan dokter.\n", username);
        return;
    }

    // Input ruangan
    char ruangan[12];
    printf("Ruangan: ");
    scanf("%s", ruangan);

    // Konversi input ruangan ke baris dan kolom
    int row, col;
    UbahInput(ruangan, &row, &col);

    // Cek apakah ruangan valid
    if (col < 0 || col >= denahRumahSakit->cols || row < 0 || row >= denahRumahSakit->rows) {
        printf("Ruangan %s tidak ditemukan.\n", ruangan);
        return;
    }

    Ruangan *r = GetRuangan(denahRumahSakit, row, col);

    // Cek apakah dokter sudah di-assign ke ruangan lain
    int dokterSudahDiAssign = 0;
    char ruanganDokter[12] = "";

    for (int i = 0; i < denahRumahSakit->rows; i++) {
        for (int j = 0; j < denahRumahSakit->cols; j++) {
            if (denahRumahSakit->data[i][j].dokter == GetID(&dokter)) {
                strcpy(ruanganDokter, denahRumahSakit->data[i][j].namaRuangan);
                dokterSudahDiAssign = 1;
                break;
            }
        }
        if (dokterSudahDiAssign)
            break;
    }

    // Cek apakah ruangan sudah ditempati dokter lain
    int ruanganSudahDitempati = (r->dokter != -1 && r->dokter != 0);
    char namaDokterDiRuangan[MAX_USERNAME_LENGTH] = "";

    if (ruanganSudahDitempati) {
        for (int i = 0; i < userList->count; i++) {
            User user = GetUserAt(userList, i);
            if (GetID(&user) == r->dokter) {
                strcpy(namaDokterDiRuangan, GetUsername(&user));
                break;
            }
        }
    }

    // Kasus 1: Ruangan Kosong dan dokter belum di assign di ruang manapun
    if (!ruanganSudahDitempati && !dokterSudahDiAssign) {
        r->dokter = GetID(&dokter);
        printf("\nDokter %s berhasil diassign ke ruangan %s!\n", GetUsername(&dokter), r->namaRuangan);
    }
    // Kasus 2: Ruangan Kosong dan dokter sudah di assign di ruang lain
    else if (!ruanganSudahDitempati && dokterSudahDiAssign) {
        printf("\nDokter %s sudah diassign ke ruangan %s!\n", GetUsername(&dokter), ruanganDokter);
    }
    // Kasus 3: Ruangan tidak kosong dan dokter belum di assign di ruang manapun
    else if (ruanganSudahDitempati && !dokterSudahDiAssign) {
        printf("\nDokter %s sudah menempati ruangan %s!\n", namaDokterDiRuangan, r->namaRuangan);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", GetUsername(&dokter));
    }
    // Kasus 4: Ruangan tidak kosong dan dokter sudah di assign di ruang lain
    else {
        printf("\nDokter %s sudah menempati ruangan %s!\n", GetUsername(&dokter), ruanganDokter);
        printf("Ruangan %s juga sudah ditempati dokter %s!\n", r->namaRuangan, namaDokterDiRuangan);
    }
}
