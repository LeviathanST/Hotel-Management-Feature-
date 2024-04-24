//
// Created by hungt on 4/23/2024.
//

#ifndef FILEUTILSV2_ORDERROOM_H
#define FILEUTILSV2_ORDERROOM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Order.database.h"

#include "../utils/FetchUsernameFromTokenFile.h"
#include "../utils/ShowUserOrder.h"

#define MAX_LINE_LENGTH 255

extern void add_room(OrderRoom room);


#endif //FILEUTILSV2_ORDERROOM_H
