////
//// Created by hungt on 4/22/2024.
////
//
//#include "Order.database.h"
//
//
////
//// Created by hungt on 4/21/2024.
////
//
//#include "Order.database.h"
//
//#define USERNAME_PREFIX "username: "
//#define MAX_LINE_LENGTH 256
//
//
//
///*
// * ADD USER
// * */
//void add_user(const char *filename, const User* user){
//    if(search_user_by_username(filename, user->username, false)){
//        printf("User already exists!\n");
//        return;
//    }
//
//    FILE *file = fopen(filename, "a"); // Open for appending
//    if (file == NULL) {
//        perror("Error opening file");
//        return;
//    }
//
//    fprintf(file, "username: %s\n", user->username);
//    fprintf(file, "password: %s\n", user->password);
//    fprintf(file, "email: %s\n", user->email);
//    fprintf(file, "phone: %s\n", user->phone);
//    fprintf(file, "orderingIds: [");
//    for (size_t i = 0; i < user->numOrderingIds; i++) {
//        // Print each individual ordering ID string and quote them if they are meant to be strings
//        fprintf(file, "\"%s\"", user->orderingIds[i]);
//        if (i < user->numOrderingIds - 1) {
//            fprintf(file, ", "); // Add a comma after all but the last element
//        }
//    }
//    fprintf(file, "]\n\n");
//
//    fclose(file);
//}
//
///*
// * SEARCH USER
// * */
//
//bool search_user_by_username(const char *filename, const char *usernameToSearch, bool printActive) {
//    FILE *file = fopen(filename, "r");
//    if (!file) {
//        perror("Error opening file");
//        return false;
//    }
//
//    User user;
//    char line[MAX_LINE_LENGTH];
//    bool foundUser = false;
//
//    while (fgets(line, sizeof(line), file)) {
//        // Remove trailing newline character
//        line[strcspn(line, "\n")] = 0;
//
//        // Check if the line starts with the 'username' field
//        if (strncmp(line, USERNAME_PREFIX, strlen(USERNAME_PREFIX)) == 0) {
//            // Extract the username from the current line
//            strcpy(user.username, line + strlen(USERNAME_PREFIX));
//
//            // If the username matches, proceed to populate the rest of the fields
//            if (strcmp(user.username, usernameToSearch) == 0) {
//                if(printActive){
//                    printf("%s\n", line); // Print username
//
//                    // Read and print the rest of the user details
//                    fgets(user.password, sizeof(user.password), file); printf("%s", user.password);
//                    fgets(user.email, sizeof(user.email), file); printf("%s", user.email);
//                    fgets(user.phone, sizeof(user.phone), file); printf("%s", user.phone);
//                    fgets(line, sizeof(line), file); line[strcspn(line, "\n")] = 0;
//                    // Assuming a simple format and not validating the input strictly
//                    // The IDs are expected to be in the form: orderingIds: ["id1","id2","id3"]
//                    char* token = strtok(line + 13, "[\", ]");
//                    user.numOrderingIds = 0;
//                    while (token && user.numOrderingIds < MAX_ORDERING_IDS) {
//                        strncpy(user.orderingIds[user.numOrderingIds], token, MAX_ORDERING_ID_LENGTH-1);
//                        user.orderingIds[user.numOrderingIds][MAX_ORDERING_ID_LENGTH-1] = '\0'; // Ensure null-termination
//                        printf("Ordering ID %zu: %s\n", user.numOrderingIds+1, user.orderingIds[user.numOrderingIds]);
//                        user.numOrderingIds++;
//                        token = strtok(NULL, "[\", ]");
//                    }
//                }
//                foundUser = true;
//                break;
//            }
//        }
//    }
//
//    fclose(file);
//
//    if(printActive){
//        if (!foundUser) {
//            printf("User '%s' not found.\n", usernameToSearch);
//        }
//    }
//
//    return foundUser;
//}
//
///*
// * UPDATE USER
// * */
//
//void update_user(const char *filename, const char *username, const User *updatedUserData) {
//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("Could not open file for reading.\n");
//        return;
//    }
//    FILE *tempFile = fopen("temp.txt", "w");
//    if (tempFile == NULL) {
//        printf("Could not open temporary file for writing.\n");
//        fclose(file);
//        return;
//    }
//
//    User currentUser;
//    int found = 0;
//
//    // Read current users and write to temporary file
//    while (fscanf(file, "username: %s\npassword: %s\n", currentUser.username, currentUser.password) == 3) {
//        if (currentUser.username == username) {
//            fprintf(tempFile, "username: %s\npassword: %s\n", currentUser.username,updatedUserData->password);
//            found = 1;
//        } else {
//            fprintf(tempFile, "username: %s\npassword: %s\n", currentUser.username, currentUser.password);
//        }
//    }
//
//    fclose(file);
//    fclose(tempFile);
//
//    // Check if the user was found
//    if (found) {
//        // Delete the old file and rename the new file
//        remove(filename);
//        rename("temp.txt", filename);
//    } else {
//        printf("User with username %s not found.\n", username);
//        remove("temp.txt");
//    }
//}
//
///*
// * REMOVE USER
// * */
//
//int remove_user(const char *filename, const char *usernameToRemove) {
//    FILE *file = fopen(filename, "r");
//    if (!file) {
//        perror("Error opening file for reading");
//        return -1;
//    }
//
//    FILE *tempFile = fopen("temp.txt", "w");
//    if (!tempFile) {
//        perror("Error opening temporary file for writing");
//        fclose(file);
//        return -1;
//    }
//
//    char line[256];
//    int found = 0;
//    int skipSection = 0;
//
//    while (fgets(line, sizeof(line), file) != NULL) {
//        if (strstr(line, USERNAME_PREFIX)) {
//            char *lineUsername = line + strlen(USERNAME_PREFIX);
//            lineUsername[strcspn(lineUsername, "\n")] = 0; // Remove newline
//
//            if (strcmp(lineUsername, usernameToRemove) == 0) {
//                found = 1;
//                skipSection = 1; // Begin skipping lines for this user
//                continue; // Skip adding this line
//            }
//        }
//
//        // If we encounter a blank line, it signifies the end of a user section
//        if (strcmp(line, "\n") == 0) {
//            skipSection = 0; // Stop skipping lines
//        }
//
//        // If not skipping, write the line to temp file
//        if (!skipSection) {
//            fprintf(tempFile, "%s", line);
//        }
//    }
//
//    fclose(file);
//    fclose(tempFile);
//
//    // Remove and rename files based on whether the user was found
//    if (found) {
//        remove(filename);
//        rename("temp.txt", filename);
//        printf("User %s removed.\n", usernameToRemove);
//    } else {
//        remove("temp.txt"); // No need to keep temp file if no user was removed
//        printf("User %s not found.\n", usernameToRemove);
//    }
//    return found ? 1 : 0;
//}
//
//int login(const char *filename, const char *username, const char *password) {
//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("File could not be opened for reading.\n");
//        return 0;
//    }
//
//    User user;
//    char line[256];
//    int found = 0;
//
//    while (fgets(line, sizeof(line), file) != NULL) {
//        // Trim newline character
//        line[strcspn(line, "\r\n")] = 0;
//
//        // Matching line with username
//        if (strncmp(line, "username: ", 10) == 0) {
//            // Copy the username from the line by offsetting by 10 characters
//            strcpy(user.username, line + 10);
//
//            // Next line should be the password of this user
//            if (fgets(line, sizeof(line), file) != NULL) {
//                line[strcspn(line, "\r\n")] = 0;
//                // Ensure it is formatted as a password line
//                if (strncmp(line, "password: ", 10) == 0) {
//                    strcpy(user.password, line + 10);
//                    if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
//                        printf("Login successful!\n");
//                        found = 1;
//                        break; // Exit if the user is found
//                    }
//                }
//            }
//        }
//    }
//
//    if (!found) {
//        printf("Login faiiled!\n");
//    }
//
//
//
//    fclose(file);
//    return found;
//}
//
//
//
//
//
