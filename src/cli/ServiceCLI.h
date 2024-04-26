//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_SERVICECLI_H
#define FILEUTILSV2_SERVICECLI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../core/Service.database.h"
#include "../utils/CheckToken.h"

#define MAX_SERVICES 100
#define MAX_NAME_LENGTH 50

bool ServiceChoose(char option);

#endif //FILEUTILSV2_SERVICECLI_H
