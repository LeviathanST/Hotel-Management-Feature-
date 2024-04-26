//
// Created by hungt on 4/26/2024.
//

#include "RoomCommand.h"


bool RoomChoose(char option){
    const char* authorized_roles2[] = {"admin"};
    const char* authorized_roles3[] = {"admin", "rcp","member"};
    int num_roles2 = sizeof(authorized_roles2) / sizeof(authorized_roles2[0]);
    int num_roles3 = sizeof(authorized_roles3) / sizeof(authorized_roles3[0]);

    switch (option) {
        case 's':
            const char *file_path = "database/room.txt";
            Room *rooms;
            int num_rooms = read_room_status_from_file(file_path, &rooms);

            for (int i = 0; i < num_rooms; i++) {
                printf("Room %d: \nOccupied: %3s\n", rooms[i].roomNumber, rooms[i].isOccupied);
                printf("-----------\n");
            }

            free(rooms);
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}