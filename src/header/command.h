#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <string.h>


#define COMMAND_CAPACITY 12

typedef struct {
    char name[50];
    int key;
} Command;


/* Definisi ADT List Statik untuk list command */
typedef struct {
    Command command[COMMAND_CAPACITY];
} CommandList;

/* SELEKTOR */
#define ELMTKEY(l,i) (l).command[(i)].key
#define ELMTNAME(l,i) (l).command[(i)].name

/* KONSTRUKTOR */
void CreateCommandList(CommandList *commandList, const char *COMMAND_READY[]);
/* Membuat List Statik yang berisikan command yang dapat digunakan */


#endif