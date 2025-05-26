// #include "../header/obat.h"

// void MinumObat(User *user)
// {
//     if (ObatListLength(user->inventory) != 0)
//     {
//         Obat obatDiminum;
//         int pilihan;

//         printf("============ DAFTAR OBAT ============\n");
//         PrintListObat(user->inventory);

//         printf("Pilih obat untuk diminum: ");
//         scanf("%d", &pilihan);
//         while (!IsIdxEff(user->inventory, pilihan - 1))
//         {
//             printf("Pilihan nomor tidak tersedia!\n\n");
//             printf("Pilih obat untuk diminum: ");
//             scanf("%d", &pilihan);
//         }

//         DeleteAt(&user->inventory, &obatDiminum, pilihan - 1);
//         Push(&user->perut, obatDiminum);
//         printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", obatDiminum.nama);
//     }
//     else
//     {
//         printf("Kamu belum menerima obat apapun dari dokter.\n");
//     }
// }

// void MinumPenawar(User *user)
// {
//     Obat muntah;
//     if (IsStackEmpty(user->perut))
//     {
//         printf("Perut kosong!! Belum ada obat yang diminum.\n");
//     }
//     else
//     {
//         Pop(&user->perut, &muntah);
//         InsertLast(&user->inventory, muntah);
//         printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", muntah.nama);
//     }
// }

// bool IsUrut(ObatList urutanObat, Stack perut)
// {
//     if (urutanObat.length != perut.top)
//         return false;
//     for (int i = 0; i < perut.top; i++)
//     {
//         if (urutanObat.obats[i].id != perut.obat[i].id)
//         {
//             return false;
//         }
//     }
//     return true;
// }

// void PulangDok(User *user, Session *session, ObatList urutanObat, ObatList obatList)
// {
//     printf("Dokter sedang memeriksa keadaanmu... \n");

//     // KASUS 1: Pasien belum diberikan diagnosa penyakit oleh dokter
//     if (user->diagnosa == 0)
//     {
//         printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
//     }

//     // KASUS 2: Pasien belum menghabiskan seluruh obat yang diberikan kepadanya
//     else if (!IsListEmpty(user->inventory))
//     {
//         printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
//     }

//     else
//     {
//         // KASUS 3: Pasien sudah menghabiskan obat, namun terdapat urutan yang salah dalam konsumsinya
//         if (!IsUrut(urutanObat, session->currentUser.perut))
//         {
//             printf("Maaf, tapi kamu masih belum bisa pulang!\n");
//             printf("Urutan peminuman obat yang diharapkan:\n");
//             for (int i = 0; i < urutanObat.length; i++)
//             {
//                 printf("%s", urutanObat.obats[i].nama);
//                 if (i < urutanObat.length - 1)
//                 {
//                     printf(" -> ");
//                 }
//             }
//             printf("\n");
//             printf("Urutan obat yang kamu minum:\n");
//             PrintStackObat(user->perut);
//             printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
//         }

//         // KASUS 4: Pasien sudah menghabiskan obat, dan semuanya valid.
//         else
//         {
//             printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
//         }
//     }
// }