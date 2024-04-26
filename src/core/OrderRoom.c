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

void read_and_display_all_room_orders() {
    FILE *file = fopen("database/orderRoom.txt", "r");  // Open the file for reading
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    OrderRoom order;
    char line[256]; // Buffer to hold each line from the file

    printf("List of all room orders:\n");
    printf("----------------------------\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line based on the expected data format
        if (sscanf(line, "Order ID: %36s", order.orderID) == 1) {
            fgets(line, sizeof(line), file);  // Assuming each data follows in sequence
            sscanf(line, "Room Number: %d", &order.roomNumber);
            fgets(line, sizeof(line), file);
            sscanf(line, "Guest Name: %49[^\n]", order.guestName);
            fgets(line, sizeof(line), file);
            sscanf(line, "Check-In Date: %10s", order.checkInDate);
            fgets(line, sizeof(line), file);
            sscanf(line, "Check-Out Date: %10s", order.checkOutDate);
            fgets(line, sizeof(line), file);
            sscanf(line, "Number of Guests: %d", &order.numberOfGuests);

            // All data collected, print it out
            printf("Order ID: %s\n", order.orderID);
            printf("Room Number: %d\n", order.roomNumber);
            printf("Guest Name: %s\n", order.guestName);
            printf("Check-In Date: %s\n", order.checkInDate);
            printf("Check-Out Date: %s\n", order.checkOutDate);
            printf("Number of Guests: %d\n", order.numberOfGuests);
            printf("----------------------------\n");
        }
    }

    fclose(file);  // Close the file after reading
}

