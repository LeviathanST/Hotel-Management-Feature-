//
// Created by hungt on 4/23/2024.
//

#include "OrderRoom.h"

void add_room(OrderRoom room){

    FILE *file = fopen("database/orderRoom.txt", "a"); // Open the file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the orderRoom data to the file
    fprintf(file, "Order ID: %36s\n", room.orderID);
    fprintf(file, "Room Number: %d\n", room.roomNumber);
    fprintf(file, "Guest Name: %s\n", room.guestName);
    fprintf(file, "Check-In Date: %s\n", &room.checkInDate);
    fprintf(file, "Check-Out Date: %s\n", &room.checkOutDate);
    fprintf(file, "Number of Guests: %d\n", room.numberOfGuests);

    fclose(file); // Close the file
}
