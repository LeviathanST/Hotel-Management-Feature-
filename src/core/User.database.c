//
// Created by hungt on 4/21/2024.
//

#include "User.database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ADD USER
 * */
void add_user(const char *filename, User user){
    if(search_user_by_username(filename, user.username)){
        printf("User already exists!\n");
        return;
    }

    FILE *file = fopen(filename, "a"); // Open for appending to avoid overwriting contents
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write user data to file
    fprintf(file, "username: %s\npassword: %s\n", user.username, user.password);

    // Close the file
    fclose(file);
}

/*
 * SEARCH USER
 * */

int search_user_by_username(const char *filename, const char *searchUsername) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File could not be opened for reading.\n");
        return 0;
    }

    User user;
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Trim newline character
        line[strcspn(line, "\r\n")] = 0;

        // Matching line with username
        if (strncmp(line, "username: ", 10) == 0) {
            // Copy the username from the line by offsetting by 10 characters
            strcpy(user.username, line + 10);

            // Next line should be the password of this user
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\r\n")] = 0;
                // Ensure it is formatted as a password line
                if (strncmp(line, "password: ", 10) == 0) {
                    strcpy(user.password, line + 10);
                    if (strcmp(user.username, searchUsername) == 0) {
                        printf("User Found:\nusername: %s\npassword: %s\n", user.username, user.password);
                        found = 1;
                        break; // Exit if the user is found
                    }
                }
            }
        }
    }

    if (!found) {
        printf("User '%s' not found in the file.\n", searchUsername);
    }

    fclose(file);
    return found;
}

/*
 * UPDATE USER
 * */

void update_user(const char *filename, const char *username, const User *updatedUserData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Could not open temporary file for writing.\n");
        fclose(file);
        return;
    }

    User currentUser;
    int found = 0;

    // Read current users and write to temporary file
    while (fscanf(file, "username: %s\npassword: %s\n", currentUser.username, currentUser.password) == 3) {
        if (currentUser.username == username) {
            fprintf(tempFile, "username: %s\npassword: %s\n", currentUser.username,updatedUserData->password);
            found = 1;
        } else {
            fprintf(tempFile, "username: %s\npassword: %s\n", currentUser.username, currentUser.password);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Check if the user was found
    if (found) {
        // Delete the old file and rename the new file
        remove(filename);
        rename("temp.txt", filename);
    } else {
        printf("User with username %s not found.\n", username);
        remove("temp.txt");
    }
}

/*
 * REMOVE USER
 * */
int remove_user(const char *filename, const char *usernameToRemove) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return -1;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return -1;
    }

    char line[256];
    int found = 0, isUsernameLine = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        // Identify username lines and check if it matches the user to remove
        if (strstr(line, "username") && strstr(line, usernameToRemove)) {
            found = 1;
            isUsernameLine = 1; // Mark the next line (password) for skipping
            continue;
        }

        if (isUsernameLine) {
            isUsernameLine = 0; // Skip this line since it's the password of the user to be removed
            continue;
        }

        // If it's not the user to remove, or not a password line just after the user, keep the line
        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    // Remove and rename files based on whether the user was found
    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("User %s removed.\n", usernameToRemove);
        return 1;
    } else {
        remove("temp.txt"); // No need to keep temp file if no user removed
        printf("User %s not found.\n", usernameToRemove);
        return 0;
    }
}


