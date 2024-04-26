//
// Created by hungt on 4/24/2024.
//

#include "OrderServiceCommand.h"
#include "../utils/readFromFile.h"


bool OrderServiceChoose(char option){
    OrderService service;
    char uuid[37];
    generate_uuid(uuid);

    const char* authorized_roles2[] = {"member"};
    const char* authorized_roles3[] = {"admin", "rcp",};
    const char* authorized_roles4[] = {"admin", "rcp", "member"};
    int num_roles2 = sizeof(authorized_roles2) / sizeof(authorized_roles2[0]);
    int num_roles3 = sizeof(authorized_roles3) / sizeof(authorized_roles3[0]);
    int num_roles4 = sizeof(authorized_roles4) / sizeof(authorized_roles4[0]);


    switch (option) {;
        case 'n':
            if(!check_role(authorized_roles4, num_roles4) ){
                printf("Not enough permission!\n");
                return false;
            }

//            strcpy(service.orderID, uuid);

            strncpy(service.orderID, uuid, sizeof(service.orderID) - 1);
            service.orderID[sizeof(service.orderID) - 1] = '\0';

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
            char currentUsername[MAX_LINE_LENGTH];
            if(check_role(authorized_roles2, num_roles2)){
                if (!fetch_username_from_token(currentUsername)) {
                    printf("Please login and try again!\n");
                    return false;
                }

                show_user_orders("service", NULL);
            } else if (check_role(authorized_roles3, num_roles3)){
                char choice;
                readFileContents("guide/ShowService.txt");
                printf("Choose type:");
                scanf("%s", &choice);
                printf("-----------\n");

                switch (choice) {
                    case 'g':
                        read_and_display_all_orders();
                        return false;
                    case 'u':
                        printf("Username:");
                        scanf("%s", currentUsername);
                        printf("-----------\n");

                        show_user_orders("service", currentUsername);
                        return false;
                    default:
                        printf("Invalid. Please try again!");
                        return false;
                }
            }

            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}
