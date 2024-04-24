//
// Created by hungt on 4/23/2024.
//

#include "OrderRoomCommand.h"

//
// Created by hungt on 4/23/2024.
//

#include "OrderCommand.h"

//
// Created by hungt on 4/22/2024.
//


#include "./OrderRoomCommand.h"
#include "../core/OrderRoom.h"

bool OrderRoomChoose(char option){
    OrderRoom room;
    char uuid[37];
    generate_uuid(uuid);

    switch (option) {;
        case 'n':
            char guestUsername[MAX_LINE_LENGTH];
            if (!fetch_username_from_token(guestUsername)) {
                printf("Please login and try again!\n");
                return false;
            }
            strcpy(room.guestName, guestUsername);
            strcpy(room.orderID, uuid);

            printf("Enter room number:");
            scanf("%d", &room.roomNumber); // Read an integer
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
            show_user_orders("room");
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
            printf("-----------\n");
            return false;
    }
}
