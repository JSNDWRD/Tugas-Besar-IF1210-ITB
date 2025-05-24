#include "../header/user.h"
#include "../header/utils.h"

void CreateUser(User *user, int id, char *username, char *password, char *role, char *riwayatPenyakit,
                float suhuTubuh, int tekananDarahSistolik, int tekananDarahDiastolik, int detakJantung,
                float saturasiOksigen, int kadarGulaDarah, float beratBadan, int tinggiBadan,
                int kadarKolesterol, int kadarKolesterolLDL, int trombosit)
{

    user->id = id;
    strcpy(user->username, username);
    strcpy(user->password, password);
    strcpy(user->role, role);
    strcpy(user->riwayatPenyakit, riwayatPenyakit);
    user->suhuTubuh = suhuTubuh;
    user->tekananDarahSistolik = tekananDarahSistolik;
    user->tekananDarahDiastolik = tekananDarahDiastolik;
    user->detakJantung = detakJantung;
    user->saturasiOksigen = saturasiOksigen;
    user->kadarGulaDarah = kadarGulaDarah;
    user->beratBadan = beratBadan;
    user->tinggiBadan = tinggiBadan;
    user->kadarKolesterol = kadarKolesterol;
    user->kadarKolesterolLDL = kadarKolesterolLDL;
    user->trombosit = trombosit;
    user->diagnosa = 0;
    user->ngobatin = 0;
}

int GetID(User *user)
{
    return user->id;
}

char *GetUsername(User *user)
{
    return user->username;
}

char *GetPassword(User *user)
{
    return user->password;
}

char *GetRole(User *user)
{
    return user->role;
}

char *GetRiwayatPenyakit(User *user)
{
    return user->riwayatPenyakit;
}

float GetSuhuTubuh(User *user)
{
    return user->suhuTubuh;
}

int GetTekananDarahSistolik(User *user)
{
    return user->tekananDarahSistolik;
}

int GetTekananDarahDiastolik(User *user)
{
    return user->tekananDarahDiastolik;
}

int GetDetakJantung(User *user)
{
    return user->detakJantung;
}

float GetSaturasiOksigen(User *user)
{
    return user->saturasiOksigen;
}

float GetKadarGulaDarah(User *user)
{
    return user->kadarGulaDarah;
}

float GetBeratBadan(User *user)
{
    return user->beratBadan;
}

int GetTinggiBadan(User *user)
{
    return user->tinggiBadan;
}

int GetKadarKolesterol(User *user)
{
    return user->kadarKolesterol;
}

int GetKadarKolesterolLDL(User *user)
{
    return user->kadarKolesterolLDL;
}

int GetTrombosit(User *user)
{
    return user->trombosit;
}

void SetID(User *user, int val)
{
    user->id = val;
}

void SetUsername(User *user, char *val)
{
    strcpy(user->username, val);
}

void SetPassword(User *user, char *val)
{
    strcpy(user->password, val);
}

void SetRole(User *user, char *val)
{
    strcpy(user->role, val);
}

void SetRiwayatPenyakit(User *user, char *val)
{
    strcpy(user->riwayatPenyakit, val);
}

void SetSuhuTubuh(User *user, float val)
{
    user->suhuTubuh = val;
}

void SetTekananDarahSistolik(User *user, int val)
{
    user->tekananDarahSistolik = val;
}

void SetTekananDarahDiastolik(User *user, int val)
{
    user->tekananDarahDiastolik = val;
}

void SetDetakJantung(User *user, int val)
{
    user->detakJantung = val;
}

void SetSaturasiOksigen(User *user, float val)
{
    user->saturasiOksigen = val;
}

void SetKadarGulaDarah(User *user, int val)
{
    user->kadarGulaDarah = val;
}

void SetBeratBadan(User *user, float val)
{
    user->beratBadan = val;
}

void SetTinggiBadan(User *user, int val)
{
    user->tinggiBadan = val;
}

void SetKadarKolesterol(User *user, int val)
{
    user->kadarKolesterol = val;
}

void SetKadarKolesterolLDL(User *user, int val)
{
    user->kadarKolesterolLDL = val;
}

void SetTrombosit(User *user, int val)
{
    user->trombosit = val;
}

void AddUser(UserList *userList, User newUser)
{
    userList->users[userList->count] = newUser;
    userList->count++;
}

void LoadUsers(UserList *userList, char *inputFolder)
{
    char folderName[100];
    strcpy(folderName, inputFolder);
    strcat(inputFolder, "/user.csv");
    FILE *fUserList = fopen(inputFolder, "r");

    // Inisialisasi jumlah user
    int count = 0;

    if (fUserList == NULL)
    {
        printf("Folder \"%s\" tidak ditemukan.\n", folderName);
    }

    char baris[1024];

    // Skip baris header
    fgets(baris, sizeof(baris), fUserList);

    while (fgets(baris, sizeof(baris), fUserList))
    {
        User user;

        // i sebagai iterator while-loop, current sebagai indeks sementara, dan kolomData sebagai indeks akses data per kolom (0: id, 1: username, dst...)
        int i = 0, current = 0, kolomData = 0;
        char currentData[100];

        while (baris[i] != '\0' && baris[i] != '\n')
        {
            if (baris[i] == ';' || baris[i] == ',')
            { // Cek Separator
                currentData[current] = '\0';
                switch (kolomData)
                {
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
                user.diagnosa = 0;
                user.ngobatin = 0;
                current = 0;
                kolomData++;
            }
            else
            {
                if ((size_t)current < sizeof(currentData) - 1)
                {
                    currentData[current] = baris[i];
                }
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

void SaveUsers(UserList userList, char *inputFolder)
{
    char outputPath[256];
    strcpy(outputPath, inputFolder);
    strcat(outputPath, "/user.csv");
    FILE *fUserList = fopen(outputPath, "w");
    fprintf(fUserList, "id,username,password,role,riwayatPenyakit,suhuTubuh,tekananDarahSistolik,tekananDarahDiastolik,detakJantung,saturasiOksigen,kadarGulaDarah,beratBadan,tinggiBadan,kadarKolesterol,kadarKolesterolLDL,trombosit\n");
    for (int i = 0; i < userList.count; i++)
    {
        User user = userList.users[i];
        fprintf(fUserList, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                user.id,
                user.username,
                user.password,
                user.role,
                strcmp(user.riwayatPenyakit, "-") == 0 ? "" : user.riwayatPenyakit,
                user.suhuTubuh == -1 ? "" : FloatToStr(user.suhuTubuh),
                user.tekananDarahSistolik == -1 ? "" : IntToStr(user.tekananDarahSistolik),
                user.tekananDarahDiastolik == -1 ? "" : IntToStr(user.tekananDarahDiastolik),
                user.detakJantung == -1 ? "" : IntToStr(user.detakJantung),
                user.saturasiOksigen == -1 ? "" : FloatToStr(user.saturasiOksigen),
                user.kadarGulaDarah == -1 ? "" : IntToStr(user.kadarGulaDarah),
                user.beratBadan == -1 ? "" : FloatToStr(user.beratBadan),
                user.tinggiBadan == -1 ? "" : IntToStr(user.tinggiBadan),
                user.kadarKolesterol == -1 ? "" : IntToStr(user.kadarKolesterol),
                user.kadarKolesterolLDL == -1 ? "" : IntToStr(user.kadarKolesterolLDL),
                user.trombosit == -1 || user.trombosit == 0 ? "" : IntToStr(user.trombosit));
    }
    fclose(fUserList);
}