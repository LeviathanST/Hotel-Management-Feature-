//
// Created by hungt on 4/23/2024.
//

#include "OrderRoomCommand.h"
#include "../core/OrderRoom.h"

bool OrderRoomChoose(char option){
    OrderRoom room;
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
            if(!check_role(authorized_roles3, num_roles3)){
                printf("Not enough permission!");
                return false;
            }

            char guestUsername[MAX_LINE_LENGTH];
            if (!fetch_username_from_token(guestUsername)) {
                printf("Please login and try again!\n");
                return false;
            }
            strcpy(room.guestName, guestUsername);
            strcpy(room.orderID, uuid);

            printf("Enter room number:");
            scanf("%d", &room.roomNumber); // Read an integer
            if(room.roomNumber < 1 || room.roomNumber > 20){
                printf("Room number is invalid!");
                return false;
            }

            while (getchar() != '\n'); // Clear the input buffer

            printf("Enter check-in date: [YYYY-MM-DD]\n");
            scanf("%s", room.checkInDate); // Read a string, up to 10 characters, leaving space for null terminator
            while (getchar() != '\n'); // Clear the input buffer

            printf("Enter check-out date: [YYYY-MM-DD]\n");
            scanf("%s", room.checkOutDate); // Read a string, up to 10 characters, leaving space for null terminator
            while (getchar() != '\n'); // Clear the input buffer

            printf("Enter number of guests:");
            scanf("%d", &room.numberOfGuests); // Read an integer
            while (getchar() != '\n'); // Clear the input buffer

            add_room(room);
            printf("-----------\n");
            return false;
        case 's':
            char currentUsername[MAX_LINE_LENGTH];
            if(check_role(authorized_roles2, num_roles2)){
                if (!fetch_username_from_token(currentUsername)) {
                    printf("Please login and try again!\n");
                    return false;
                }

                show_user_orders("room", NULL);
            } else if (check_role(authorized_roles3, num_roles3)){
                char choice;
                printf("Choose type: [g: get all; u: get by username]");
                scanf("%s", &choice);
                printf("-----------\n");

                switch (choice) {
                    case 'g':
                        read_and_display_all_room_orders();
                        return false;
                    case 'u':
                        printf("Username:");
                        scanf("%s", currentUsername);
                        printf("-----------\n");

                        show_user_orders("room", currentUsername);
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
            printf("-----------\n");
            return false;
    }
}
