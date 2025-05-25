#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <string.h>

#define COMMAND_CAPACITY 25

typedef struct
{
    char name[50];
    int key;
} Command;

typedef struct
{
    Command command[COMMAND_CAPACITY];
} CommandList;

#define ELMTKEY(l, i) (l).command[(i)].key
#define ELMTNAME(l, i) (l).command[(i)].name

/* Membuat List Statik yang berisikan command yang dapat digunakan */
void CreateCommandList(CommandList *commandList, const char *COMMAND_READY[]);

#endif