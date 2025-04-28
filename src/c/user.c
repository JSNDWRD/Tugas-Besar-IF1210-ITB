#include "../header/user.h"

void LoadUsers(UserList *userList){
    FILE *fUserList = fopen("./src/file/user.csv","r");

    // Inisialisasi jumlah user
    int count = 0;

    if (fUserList == NULL) {
        perror("FILE user.csv kosong\n");
    }

    char baris[1024]; 

    // Skip baris header
    fgets(baris, sizeof(baris), fUserList);

    while (fgets(baris, sizeof(baris), fUserList)) {
        User user;

        // i sebagai iterator while-loop, current sebagai indeks sementara, dan kolomData sebagai indeks akses data per kolom (0: id, 1: username, dst...)
        int i = 0, current = 0, kolomData = 0;
        char currentData[100];

        while (baris[i] != '\0' && baris[i] != '\n') {
            if (baris[i] == ';' || baris[i] == ',') { // Cek Separator
                currentData[current] = '\0'; 
                switch (kolomData) {
                    case 0: 
                        user.id = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 1: 
                        if (strlen(currentData) > 0) 
                            strcpy(user.username, currentData); 
                        else 
                            strcpy(user.username, "-");
                        break;
                    case 2: 
                        if (strlen(currentData) > 0) 
                            strcpy(user.password, currentData); 
                        else 
                            strcpy(user.password, "-");
                        break;
                    case 3: 
                        if (strlen(currentData) > 0) 
                            strcpy(user.role, currentData); 
                        else 
                            strcpy(user.role, "-");
                        break;
                    case 4: 
                        if (strlen(currentData) > 0) 
                            strcpy(user.riwayatPenyakit, currentData); 
                        else 
                            strcpy(user.riwayatPenyakit, "-");
                        break;
                    case 5: 
                        user.suhuTubuh = (strlen(currentData) > 0) ? atof(currentData) : -1; 
                        break;
                    case 6: 
                        user.tekananDarahSistolik = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 7: 
                        user.tekananDarahDiastolik = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 8: 
                        user.detakJantung = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 9: 
                        user.saturasiOksigen = (strlen(currentData) > 0) ? atof(currentData) : -1; 
                        break;
                    case 10: 
                        user.kadarGulaDarah = (strlen(currentData) > 0) ? atof(currentData) : -1; 
                        break;
                    case 11: 
                        user.beratBadan = (strlen(currentData) > 0) ? atof(currentData) : -1; 
                        break;
                    case 12: 
                        user.tinggiBadan = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 13: 
                        user.kadarKolesterol = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                    case 14: 
                        user.kadarKolesterolLDL = (strlen(currentData) > 0) ? atoi(currentData) : -1; 
                        break;
                }
                current = 0;
                kolomData++;
            } else {
                if (current < sizeof(currentData) - 1)
                    currentData[current] = baris[i];
                    current++;
            }
            i++;
        }

        // Kolom Data trombosit
        currentData[current] = '\0';
        user.trombosit = strlen(currentData) > 0 ? atoi(currentData) : -1;

        userList->users[count] = user;
        count++;
    }
    userList->count = count;
    fclose(fUserList);

    // Test print hasil algoritma
    // for(int i = 0; i < count; i++) {
    //     printf("Id: %d\n", userList->users[i].id);
    //     printf("Username: %s\n", userList->users[i].username);
    //     printf("Password: %s\n", userList->users[i].password);
    //     printf("Role: %s\n", userList->users[i].role);
    //     printf("Riwayat Penyakit: %s\n", userList->users[i].riwayatPenyakit);
    //     printf("Suhu Tubuh: %.2f\n", userList->users[i].suhuTubuh);
    //     printf("Tekanan Darah Sistolik: %d\n", userList->users[i].tekananDarahSistolik);
    //     printf("Tekanan Darah Diastolik: %d\n", userList->users[i].tekananDarahDiastolik);
    //     printf("Detak Jantung: %d\n", userList->users[i].detakJantung);
    //     printf("Saturasi Oksigen: %.2f\n", userList->users[i].saturasiOksigen);
    //     printf("Kadar Gula Darah: %.2f\n", userList->users[i].kadarGulaDarah);
    //     printf("Berat Badan: %.2f\n", userList->users[i].beratBadan);
    //     printf("Tinggi Badan: %d\n", userList->users[i].tinggiBadan);
    //     printf("Kadar Kolesterol: %d\n", userList->users[i].kadarKolesterol);
    //     printf("Kadar Kolesterol LDL: %d\n", userList->users[i].kadarKolesterolLDL);
    //     printf("Trombosit: %d\n", userList->users[i].trombosit);
    //     printf("\n");
    // }
}

User CreateNewUser(int id, char *username, char *password, char *role, char *riwayatPenyakit,
                float suhuTubuh, int tekananDarahSistolik, int tekananDarahDiastolik, int detakJantung,
                float saturasiOksigen, float kadarGulaDarah, float beratBadan, int tinggiBadan,
                int kadarKolesterol, int kadarKolesterolLDL, int trombosit) {
    
    User newUser;
    newUser.id = id;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    strcpy(newUser.role, role);
    strcpy(newUser.riwayatPenyakit, riwayatPenyakit);
    newUser.suhuTubuh = suhuTubuh;
    newUser.tekananDarahSistolik = tekananDarahSistolik;
    newUser.tekananDarahDiastolik = tekananDarahDiastolik;
    newUser.detakJantung = detakJantung;
    newUser.saturasiOksigen = saturasiOksigen;
    newUser.kadarGulaDarah = kadarGulaDarah;
    newUser.beratBadan = beratBadan;
    newUser.tinggiBadan = tinggiBadan;
    newUser.kadarKolesterol = kadarKolesterol;
    newUser.kadarKolesterolLDL = kadarKolesterolLDL;
    newUser.trombosit = trombosit;

    return newUser;
}