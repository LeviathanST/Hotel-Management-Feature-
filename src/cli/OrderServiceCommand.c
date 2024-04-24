//
// Created by hungt on 4/24/2024.
//

#include "OrderServiceCommand.h"

bool OrderServiceChoose(char option){
    OrderService service;
    char uuid[37];
    generate_uuid(uuid);
    switch (option) {;
        case 'n':
            strcpy(service.orderID, uuid);

            if (!fetch_username_from_token(service.guestUsername)) {
                printf("Please login and try again!\n");
                return false;
            }

            printf("Username: %s\n", service.guestUsername);


            printf("Enter service's name:");
            scanf("%49s", service.serviceName);

            printf("Enter date:");
            scanf("%10s", service.orderDate);

            add_service(&service);
            printf("-----------\n");
            return false;
        case 's':
            show_user_orders("service");
            printf("-----------\n");
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}
