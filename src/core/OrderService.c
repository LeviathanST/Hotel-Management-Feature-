//
// Created by hungt on 4/24/2024.
//

#include "OrderService.h"

void add_service(OrderService *service){
    char guestUsername[MAX_LINE_LENGTH];
    if (!fetch_username_from_token(guestUsername)) {
        printf("Failed to fetch username from token.txt\n");
        return;
    }

    FILE *file = fopen("database/orderService.txt", "a"); // Open the file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the orderRoom data to the file
    fprintf(file, "Order ID: %s\n", service->orderID);
    fprintf(file, "Guest Name: %s\n", service->guestUsername);
    fprintf(file, "Service Name: %s\n", service->serviceName);
    fprintf(file, "Order Date: %10s\n", service->orderDate);

    fclose(file); // Close the file
}