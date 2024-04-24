//
// Created by hungt on 4/22/2024.
//



//
// Created by hungt on 4/22/2024.
//
#include "System.h"

bool Choose(char option){
    bool back = false;
    switch (option) {
        case 'u':
            while(!back){
                printf("User:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = UserChoose(choice);
            }
            return false;
        case 'o':
            const char* authorized_roles1[] = {"admin", "member"};
            int num_roles1 = sizeof(authorized_roles1) / sizeof(authorized_roles1[0]);

            if(!check_role(authorized_roles1, num_roles1)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            while(!back){
                printf("Order:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = OrderChoose(choice);
            }
            return false;
        case 's':
            while(!back){
                printf("Service:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = ServiceChoose(choice);
            }
            return false;
        case 'q':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}