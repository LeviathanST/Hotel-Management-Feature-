//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_SHOWUSERORDER_H
#define FILEUTILSV2_SHOWUSERORDER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "FetchUsernameFromTokenFile.h"
#include "../core/Order.database.h"
#include "../core/User.database.h"

void show_user_orders(char type[12], const char *guestUsername);


#endif //FILEUTILSV2_SHOWUSERORDER_H
