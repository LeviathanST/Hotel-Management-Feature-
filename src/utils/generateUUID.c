//
// Created by hungt on 4/23/2024.
//

#include "generateUUID.h"




void generate_uuid(char *uuid) {
    const char *chars = "0123456789abcdef";

    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid[i] = '-';
        } else if (i == 14) {
            uuid[i] = '4'; // Version 4 UUID
        } else if (i == 19) {
            uuid[i] = chars[(rand() % 4) + 8]; // Variant 1 UUID
        } else {
            uuid[i] = chars[rand() % 16];
        }
    }
    uuid[36] = '\0';
}