//
// Created by hungt on 4/24/2024.
//

#include "ShowUserOrder.h"

void show_user_orders(char type[12]) {
    FILE *file;

    char currentUsername[MAX_LINE_LENGTH];
    if (!fetch_username_from_token(currentUsername)) {
        printf("Please login and try again!\n");
        return;
    }

    if(strcmp(type, "room") == 0){
        file = fopen("database/orderRoom.txt", "r");
    } else {
        file = fopen("database/orderService.txt", "r");
    }

    if (file == NULL) {
        perror("Error opening file");
        return;
    }



    bool hasOrders = false;
    printf("Showing orders for %s:\n", currentUsername);

    if(strcmp(type, "room") == 0){
        OrderRoom order;
        // Adjust fscanf to expect the correct number of inputs
        while (fscanf(file, "Order ID: %36s\nRoom Number: %d\nGuest Name: %49s\nCheck-In Date: %10s\nCheck-Out Date: %10s\nNumber of Guests: %d\n",
                      order.orderID, &order.roomNumber, order.guestName, order.checkInDate, order.checkOutDate, &order.numberOfGuests) == 6) {
            if (strcmp(order.guestName, currentUsername) == 0) {
                printf("Order ID: %s\nRoom Number: %d\nGuest Name: %s\nCheck-In: %s\nCheck-Out: %s\nNumber of Guests: %d\n",
                       order.orderID, order.roomNumber, order.guestName, order.checkInDate, order.checkOutDate, order.numberOfGuests);
                printf("-----------\n");
                hasOrders = true;
            }
        }
    } else {
        OrderService order;
        while (fscanf(file, "Order ID: %36s\nGuest Name: %49s\nService Name: %49s\nOrder Date: %10s\n",
                      order.orderID, order.guestUsername, order.serviceName, order.orderDate) == 5) {
            if (strcmp(order.guestUsername, currentUsername) == 0) {
                printf("Order ID: %36s\nGuest Name: %s\nService Name: %s\nOrder Date: %s\n",
                       order.orderID, order.guestUsername, order.serviceName, order.orderDate);
                printf("-----------\n");
                hasOrders = true;
            }
        }
    }



    if (!hasOrders) {
        printf("No orders found for %s.\n", currentUsername);
    }
    fclose(file);
}