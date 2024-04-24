//
// Created by hungt on 4/22/2024.
//

#ifndef FILEUTILSV2_ORDER_DATABASE_H
#define FILEUTILSV2_ORDER_DATABASE_H

#include "../utils/Date.h"

typedef struct {
    char orderID[36];        // Unique identifier for the order
    int roomNumber;     // Room number assigned to the order
    char guestName[50]; // Name of the guest
    char checkInDate; // Check-in date in YYYY-MM-DD format
    char checkOutDate; // Check-out date in YYYY-MM-DD format
    int numberOfGuests; // Number of guests staying
} OrderRoom;

typedef struct {
    char orderID[36];       // Unique identifier for the service order
    char guestUsername[50];
    char serviceName[50];
    char orderDate[10];
} OrderService;
#endif //FILEUTILSV2_ORDER_DATABASE_H
