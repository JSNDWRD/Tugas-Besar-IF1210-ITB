#include "../header/kamus.h"
#include "../header/obat.h"

//BELUM FIX
void MinumObat(ListObat *inventory, Stack *perut){
    Obat obatDiminum;
    int pilihan;

    printList(*inventory);
    
    printf("Pilih obat untuk diminum: ");
    scanf("%d", &pilihan);
    while(!isIdxEff(*inventory, pilihan-1)){
        printf("Pilihan nomor tidak tersedia!\n\n");
        printf("Pilih obat untuk diminum: ");
        scanf("%d", &pilihan);
    }

    deleteAt(inventory, &obatDiminum, pilihan-1);
    push(perut, obatDiminum);
    printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n\n", obatDiminum);
}

void MinumPenawar(ListObat *inventory, Stack *perut){
    Obat muntah;
    if(isStackEmpty(*perut)){
        printf("Perut kosong!! Belum ada obat yang diminum.\n\n");
    }
    else{
        pop(perut, &muntah);
        insertLast(inventory, muntah);
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n\n", muntah);
    }
}

void PulangDok(ListObat inventory, Stack urutan, Stack perut){
    printf("Dokter sedang memeriksa keadaanmu... \n\n");

    //case blm diagnosed 

    //case blm habisin obat
    if(!isListEmpty(inventory)){
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n\n");
    }

    else{
        //KASUS 3: Pasien sudah menghabiskan obat, namun terdapat urutan yang salah dalam konsumsinya
        if(!isStackEqual(urutan,perut)){
            printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
            printf("Urutan peminuman obat yang diharapkan:\n");
            printStackObat(urutan);
            printf("\n");
            printf("Urutan obat yang kamu minum:\n");
            printStackObat(perut);
            printf("\n");
            printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai !\n\n");
        }

        //KASUS 4: Pasien sudah menghabiskan obat, dan semuanya valid.
        else{
            printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");
        }
    }
}