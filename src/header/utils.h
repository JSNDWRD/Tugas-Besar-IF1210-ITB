#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "auth.h"
#include "user.h"
#include "command.h"

// Membuat copy dari suatu string yang di lowercase
void ToLower(char *str, char *target);

// Make lowercase string -> untuk cek username
void ToLowerCase(char *str);

// Make uppercase string
void ToUpperCase(char *str);

// Mengembalikan float dalam bentuk string
char* FloatToStr(float x);

// Mengembalikan integer dalam bentuk string
char* IntToStr(int x);

/* Memberikan tampilan Help berdasarkan session (sudah login atau belum) */
void Help(Session session); 

// Untuk fitur reset password
void RunLenEncode(char* str, char* encoded);


#endif