#ifndef CTD_H
#define CTD_H
#define MAX_SIZE 100
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

struct User {
    char *name;
    char *phoneNum;
    struct User* next;
};
typedef struct User PhoneUser;
typedef struct User* UserPtr;
typedef struct User* ListUser;

int readData_fromFile(ListUser *List, const char fileName[]);
int writeChange(ListUser List, const char fileName[]);

#endif