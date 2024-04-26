////
//// Created by THIEN DUYEN on 4/23/2024.
////

#ifndef FILEUTILSV2_STAFF_DATABASE_H
#define FILEUTILSV2_STAFF_DATABASE_H

#include <stdbool.h>
#include "User.database.h"
#include "../utils/Date.h"

typedef struct {
    char uuid[85];
    char username[85];
    Date date;
    int time;
    bool status;
    float paid;
} DateWork;


bool assignRole(const char *filename, const char *username, User *newUser);
bool getAllUser(const char *filename, User *listUsers, int *size);

bool addDateWork(DateWork *dateWork);
bool updateDateWork(const char  *filename, const char *uuid, DateWork *dateWork, const char *fieldToUpdate);

bool calculateSalary(const char *username, float *salary, int month, int year);

bool getAllDateWorks(DateWork *listDateWorks, int size);
bool searchDateWorkByUsername(const char *username, DateWork *listDateWorks, int size);

#endif //FILEUTILSV2_STAFF_DATABASE_H