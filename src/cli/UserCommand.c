//
// Created by hungt on 4/22/2024.
//

#include "UserCommand.h"
#include "../core/User.database.h"


bool UserChoose(char option){
    char path[100] = "database/users.txt";
    char usernameInput[100];
    char passwordInput[100];
    char emailInput[100];
    char phoneInput[100];

    User user;
    switch (option) {
        case 's':
            printf("Username:");
            scanf("%99s", usernameInput);  // Using %99s to prevent buffer overflow
            printf("Password:");
            scanf("%99s", passwordInput);  // Using %99s to prevent buffer overflow
            printf("Email:");
            scanf("%99s", emailInput);  // Using %99s to prevent buffer overflow
            printf("Number phone:");
            scanf("%99s", phoneInput);  // Using %99s to prevent buffer overflow


            strcpy(user.username, usernameInput);
            strcpy(user.password, passwordInput);
            strcpy(user.email, emailInput);
            strcpy(user.phone, phoneInput);

            add_user(path, &user);
            printf("-----------\n");
            return false;
        case 'l':
            printf("Username:");
            scanf("%99s", usernameInput);  // Using %99s to prevent buffer overflow
            printf("Password:");
            scanf("%99s", passwordInput);  // Using %99s to prevent buffer overflow


            login(path, usernameInput, passwordInput);
            printf("-----------\n");
            return false;
        case 'r':
            printf("Username:");
            scanf("%99s", usernameInput);  // Using %99s to prevent buffer overflow

            remove_user(path, usernameInput);
            return false;
        case 'a':
            printf("Username:");
            scanf("%s", usernameInput);

            search_user_by_username(path, usernameInput, true);
            printf("-----------\n");
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}