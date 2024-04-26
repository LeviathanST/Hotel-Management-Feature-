//
// Created by hungt on 4/22/2024.
//

#include "System.h"
#include "src/utils/readFromFile.h"

bool Choose(char option){
    bool back = false;
    switch (option) {
        case 'u':
            readFileContents("guide/USER.txt");
            while(!back){
                printf("User:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = UserChoose(choice);
            }
            return false;
        case 'o':
            readFileContents("guide/OrderCommand.txt");
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
            readFileContents("guide/SERVICE.txt");
            while(!back){
                printf("Service:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = ServiceChoose(choice);
            }
            return false;
        case 'r':
            readFileContents("guide/ROOM.txt");
            while(!back){
                printf("Room:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = RoomChoose(choice);
            }

            return false;
        case 'a':
            readFileContents("guide/Staff.txt");
            while(!back){
                printf("Staff:");
                char choice;
                scanf("%s", &choice);
                printf("-----------\n");

                back = StaffChoose(choice);
            }
            return false;
        case 'q':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}