//
// Created by hungt on 4/23/2024.
//

#ifndef FILEUTILSV2_CHECKTOKEN_H
#define FILEUTILSV2_CHECKTOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//extern bool check_role(const char *authorized_role);

extern bool check_role(const char **authorized_roles, int num_roles);

#endif //FILEUTILSV2_CHECKTOKEN_H
