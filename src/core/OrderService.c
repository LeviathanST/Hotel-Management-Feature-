//
// Created by hungt on 4/24/2024.
//

#include "OrderService.h"
#include "../utils/generateUUID.h"

void add_service(OrderService *service) {
    FILE *file = fopen("database/orderService.txt", "a");  // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file!");
        return;
    }

    // Write the order service data to the file
    fprintf(file, "Order ID: %s\n", service->orderID);
    fprintf(file, "Guest Name: %s\n", service->guestUsername);
    fprintf(file, "Service Name: %s\n", service->serviceName);
    fprintf(file, "Order Date: %s\n", service->orderDate);

    fclose(file);  // Close the file
    printf("Order successfully!\n");
}

void read_and_display_all_orders() {
    FILE *file = fopen("database/orderService.txt", "r");  // Open the file for reading
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    OrderService order;
    char line[256]; // Buffer to hold each line from the file

    printf("List of all orders:\n");
    printf("-------------------\n");

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line based on the expected data format
        if (sscanf(line, "Order ID: %39s", order.orderID) == 1) {
            // Read the next line for the guest name
            if (fgets(line, sizeof(line), file) && sscanf(line, "Guest Name: %49[^\n]", order.guestUsername) == 1) {
                // Continue with service name
                if (fgets(line, sizeof(line), file) && sscanf(line, "Service Name: %49[^\n]", order.serviceName) == 1) {
                    // Finally get the order date
                    if (fgets(line, sizeof(line), file) && sscanf(line, "Order Date: %10s", order.orderDate) == 1) {
                        // All data collected, print it out
                        printf("Order ID: %s\n", order.orderID);
                        printf("Guest Name: %s\n", order.guestUsername);
                        printf("Service Name: %s\n", order.serviceName);
                        printf("Order Date: %s\n", order.orderDate);
                        printf("-------------------\n");
                    }
                }
            }
        }
    }

    fclose(file);  // Close the file after reading
}