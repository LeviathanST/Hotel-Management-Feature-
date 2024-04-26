//
// Created by hungt on 4/24/2024.
//

#include "ServiceCLI.h"


bool ServiceChoose(char option){
    const char* authorized_roles2[] = {"admin"};
    const char* authorized_roles3[] = {"admin", "rcp","member"};
    int num_roles2 = sizeof(authorized_roles2) / sizeof(authorized_roles2[0]);
    int num_roles3 = sizeof(authorized_roles3) / sizeof(authorized_roles3[0]);

    switch (option) {
        case 'n':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                printf("-----------\n");
                return false;
            }

            addService();
            return false;
        case 's':
            if(!check_role(authorized_roles3, num_roles3)){
                printf("Not enough permission. Please login!\n");
                printf("-----------\n");
                return false;
            }

            displayServices();
            return false;
        case 'u':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                printf("-----------\n");
                return false;
            }

            editService();
            return false;
        case 'd':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                printf("-----------\n");
                return false;
            }

            deleteService();
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
            printf("-----------\n");
            return false;
    }
}