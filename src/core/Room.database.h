//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_ROOM_DATABASE_H
#define FILEUTILSV2_ROOM_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Room {
    int roomNumber;
    char isOccupied[3];
} Room;

int read_room_status_from_file(const char *file_path, Room **rooms);

#endif //FILEUTILSV2_ROOM_DATABASE_H
