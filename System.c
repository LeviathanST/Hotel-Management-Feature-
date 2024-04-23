//
// Created by hungt on 4/22/2024.
//



//
// Created by hungt on 4/22/2024.
//
#include "System.h"

bool Choose(char option){
    switch (option) {
        case 'u':
            bool back = false;
            while(!back){
                printf("User:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = UserChoose(choice);
            }
            return false;
        case 'q':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}