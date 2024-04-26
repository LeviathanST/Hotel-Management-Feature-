//
// Created by hungt on 4/23/2024.
//

#include "OrderCommand.h"
#include "../utils/readFromFile.h"

bool OrderChoose(char option){
    bool back = false;

    switch (option) {;
        case 'r':
            readFileContents("guide/OrderRoom.txt");
            while(!back){
                printf("Order room:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = OrderRoomChoose(choice);
            }
            return false;
        case 's':
            while(!back){
                printf("Order service:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = OrderServiceChoose(choice);
            }
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
            printf("-----------\n");
            return false;
    }
}
