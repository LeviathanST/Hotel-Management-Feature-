//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_ORDERSERVICE_H
#define FILEUTILSV2_ORDERSERVICE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Order.database.h"

#include "../utils/FetchUsernameFromTokenFile.h"
#include "../utils/ShowUserOrder.h"

void add_service(OrderService *service);

#endif //FILEUTILSV2_ORDERSERVICE_H
