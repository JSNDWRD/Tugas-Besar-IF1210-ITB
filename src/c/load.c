#include "../header/kamus.h" 
#include "../header/load.h"

void LoadObatFromCSV(ListObat *l, Stack *S, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char line[100];
    fgets(line, 100, file);

    while (fgets(line, 100, file) != NULL && l->nEff < l->capacity) {
        DataObat o;
        char *token = strtok(line, ",");
        if (token != NULL) {
            o.id = atoi(token);
            token = strtok(NULL, ",\n");
            if (token != NULL) {
                strncpy(o.nama, token, sizeof(o.nama));
                o.nama[sizeof(o.nama) - 1] = '\0'; 
                strncpy(l->buffer[l->nEff++], o.nama, sizeof(o.nama));
                strncpy(S->obat[++S->top], o.nama, sizeof(o.nama));
            }
        }
    }

    fclose(file);
}
