#include "Room.database.h"

void displayRooms(struct Room rooms[], int size) {
    printf("List of all rooms:\n");
    for (int i = 0; i < size; i++) {
        printf("Room Number: %d, Occupied: %s\n",
               rooms[i].roomNumber,
               rooms[i].isOccupied ? "Yes" : "No");
    }
}

int read_room_status_from_file(const char *file_path, Room **rooms) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return 0;
    }

    int num_rooms = 0;
    Room *current_room = NULL;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'R' && line[1] == 'o' && line[2] == 'o' && line[3] == 'm') {
            if (num_rooms > 0) {
                current_room = realloc(current_room, sizeof(Room) * (num_rooms + 1));
            } else {
                current_room = malloc(sizeof(Room));
            }
            sscanf(line, "Room Number: %d", &(current_room[num_rooms].roomNumber));
            current_room[num_rooms].isOccupied[0] = 'N';
            current_room[num_rooms].isOccupied[1] = 'o';
            current_room[num_rooms].isOccupied[2] = '\0';
            num_rooms++;
        } else if (line[0] == 'O' && line[1] == 'c' && line[2] == 'c' && line[3] == 'u') {
            strcpy(current_room[num_rooms - 1].isOccupied, "Yes");
        }
    }

    fclose(file);

    *rooms = realloc(current_room, sizeof(Room) * num_rooms);
    return num_rooms;
}