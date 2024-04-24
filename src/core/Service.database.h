//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_SERVICE_DATABASE_H
#define FILEUTILSV2_SERVICE_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERVICES 100
#define MAX_NAME_LENGTH 50

typedef struct Service {
    char name[MAX_NAME_LENGTH];
    float price;
};

struct Service services[MAX_SERVICES];
int numServices = 0; // Number of services currently stored

#endif //FILEUTILSV2_SERVICE_DATABASE_H
