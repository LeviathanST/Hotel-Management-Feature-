//
// Created by hungt on 4/24/2024.
//

#include "FetchUsernameFromTokenFile.h"


bool fetch_username_from_token(char *username) {
    FILE *file = fopen("database/token.txt", "r");
    if (file == NULL) {
        perror("Failed to open token file");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    bool found = false;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *prefix = "username: ";
        char *found_str = strstr(line, prefix);
        if (found_str) {
            // Assuming username follows immediately after "username: "
            sscanf(found_str + strlen(prefix), "%s", username);
            found = true;
            break;
        }
    }

    fclose(file);
    return found;
}