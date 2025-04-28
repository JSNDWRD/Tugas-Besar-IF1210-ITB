#include "../header/user.h"

void LoadUsers(UserList *userList){
    FILE *fUserList = fopen("./src/file/user.csv","r");
    
    // Inisialisasi index awal dan jumlah 
    int count = 0;

    if (fUserList == NULL) {
        perror("FILE user.csv kosong\n");
    }

    char baris[1024]; 
    // Skip baris header
    fgets(baris, sizeof(baris), fUserList);

    while(fgets(baris,sizeof(baris),fUserList)){
        // Algoritma untuk menyimpan data user
        // Work in progress...
        count++;
    }
    userList->count = count;
    fclose(fUserList);
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