//
// Created by hungt on 4/23/2024.
//


#include "CheckToken.h"

#define MAX_LINE_LENGTH 255

// Helper function to extract a field value from a line
bool extract_field_value(const char* line, const char* field, char* value) {
    char* start = strstr(line, field);
    if (start != NULL) {
        sscanf(start + strlen(field), "%s", value); // Extract the value after the field name
        return true;
    }
    return false;
}

// Function to check if the user exists in users.txt
bool user_exists(const char *filename, const char *username) {
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return false;
    }

    bool found = false;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char user[MAX_LINE_LENGTH];
        if (extract_field_value(line, "username: ", user)) {
            if (strcmp(user, username) == 0) {
                found = true;
                break;
            }
        }
    }

    fclose(file);
    return found;
}

//// Function to check the role, verifying the username and role from token.txt
//bool check_role(const char *authorized_role) {
//    char line[MAX_LINE_LENGTH];
//    FILE *token_file = fopen("database/token.txt", "r");
//    if (token_file == NULL) {
//        perror("Failed to open token.txt");
//        return false;
//    }
//
//    char username[MAX_LINE_LENGTH] = {0};
//    bool found_username = false;
//    bool is_authorized = false;
//
//    while (fgets(line, MAX_LINE_LENGTH, token_file) != NULL) {
//        // Extract username if not already found
//        if (!found_username && extract_field_value(line, "username: ", username)) {
//            found_username = true;
//            // Check if user exists in users.txt
//            if (!user_exists("database/users.txt", username)) {
//                printf("User %s does not exist in users.txt\n", username);
//                fclose(token_file);
//                return false;
//            }
//        }
//
//        // Check for the role
//        char role[MAX_LINE_LENGTH];
//        if (extract_field_value(line, "role: ", role)) {
//            if (strcmp(role, authorized_role) == 0) {
//                is_authorized = true;
//                break;
//            }
//        }
//    }
//
//    fclose(token_file);
//    return is_authorized;
//}

bool check_role(const char **authorized_roles, int num_roles) {
    char line[MAX_LINE_LENGTH];
    FILE *token_file = fopen("database/token.txt", "r");
    if (token_file == NULL) {
        perror("Failed to open token.txt");
        return false;
    }

    char username[MAX_LINE_LENGTH] = {0};
    bool found_username = false;
    bool is_authorized = false;

    while (fgets(line, MAX_LINE_LENGTH, token_file) != NULL) {
        // Extract username if not already found
        if (!found_username && extract_field_value(line, "username: ", username)) {
            found_username = true;
            // Check if user exists in users.txt
            if (!user_exists("database/users.txt", username)) {
                printf("User %s does not exist in users.txt\n", username);
                fclose(token_file);
                return false;
            }
        }

        // Check for the role
        char role[MAX_LINE_LENGTH];
        if (extract_field_value(line, "role: ", role)) {
            for (int i = 0; i < num_roles; i++) {
                if (strcmp(role, authorized_roles[i]) == 0) {
                    is_authorized = true;
                    break;
                }
            }
            if (is_authorized) {
                break;
            }
        }
    }

    fclose(token_file);
    return is_authorized;
}
