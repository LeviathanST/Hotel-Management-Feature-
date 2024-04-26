//
// Created by hungt on 4/24/2024.
//

#include "ShowUserOrder.h"

void show_user_orders(char type[12], const char *guestUsername) {
    FILE *file;
    char currentUsername[MAX_LINE_LENGTH];

    // Fetch the current username if guestUsername is not provided
    if (guestUsername == NULL || strlen(guestUsername) == 0) {
        if (!fetch_username_from_token(currentUsername)) {
            printf("Please login and try again!\n");
            printf("-----------\n");
            return;
        }
        guestUsername = currentUsername;
    }

    if(!search_user_by_username("database/users.txt", guestUsername, false)){
        printf("User is not existed!\n");
        printf("-----------\n");
        return;
    }



    const char *filename = strcmp(type, "room") == 0 ? "database/orderRoom.txt" : "database/orderService.txt";
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file\n");
        printf("-----------\n");
        return;
    }

    bool hasOrders = false;
    printf("Showing orders for %s:\n", guestUsername);
    char buffer[MAX_LINE_LENGTH];

    if (strcmp(type, "room") == 0) {
        OrderRoom order;
        while (fscanf(file, "Order ID: %36s\nRoom Number: %d\nGuest Name: %49s\nCheck-In Date: %10s\nCheck-Out Date: %10s\nNumber of Guests: %d\n",
                      order.orderID, &order.roomNumber, order.guestName, order.checkInDate, order.checkOutDate, &order.numberOfGuests) == 6) {
            if (strcmp(order.guestName, guestUsername) == 0) {
                printf("Order ID: %s\nRoom Number: %d\nGuest Name: %s\nCheck-In: %s\nCheck-Out: %s\nNumber of Guests: %d\n-----------\n",
                       order.orderID, order.roomNumber, order.guestName, order.checkInDate, order.checkOutDate, order.numberOfGuests);
                hasOrders = true;
            }
        }
    } else {
        OrderService order;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (sscanf(buffer, "Order ID: %36s", order.orderID) == 1) {
                // No output here, wait until all fields are parsed
            } else if (sscanf(buffer, "Guest Name: %49[^\n]", order.guestUsername) == 1) {
                if (strcmp(order.guestUsername, guestUsername) != 0) {
                    continue;  // Skip this order as it does not match the specified username
                }
                hasOrders = true;  // Order for this username exists
                printf("Order ID: %s\nGuest Name: %s\n", order.orderID, order.guestUsername);
            } else if (hasOrders && sscanf(buffer, "Service Name: %49[^\n]", order.serviceName) == 1) {
                printf("Service Name: %s\n", order.serviceName);
            } else if (hasOrders && sscanf(buffer, "Order Date: %10s", order.orderDate) == 1) {
                printf("Order Date: %s\n-----------\n", order.orderDate);
                hasOrders = true;  // Reset after full order is displayed
            }
        }
    }

    if (!hasOrders) {
        printf("No orders found for %s.\n", guestUsername);
        printf("-----------\n");
    }
    fclose(file);
}