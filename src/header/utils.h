#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "auth.h"
#include "user.h"

// Make lowercase string -> untuk cek username
void ToLowerCase(char *str);

/* Memberikan tampilan Help berdasarkan session (sudah login atau belum) */
void Help(Session session);

/* F18 - Exit */
void Exit();

#endif