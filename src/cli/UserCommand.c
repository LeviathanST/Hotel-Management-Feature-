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
            const char* authorized_roles1[] = {"admin", "member"};
            int num_roles1 = sizeof(authorized_roles1) / sizeof(authorized_roles1[0]);

            if(!check_role(authorized_roles1, num_roles1)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            printf("Username:");
            scanf("%99s", usernameInput);  // Using %99s to prevent buffer overflow

            remove_user(path, usernameInput);
            return false;
        case 'a':
            const char* authorized_roles2[] = {"admin", "member"};
            int num_roles2 = sizeof(authorized_roles2) / sizeof(authorized_roles2[0]);

            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            printf("Username:");
            scanf("%s", usernameInput);

            search_user_by_username(path, usernameInput, true);
            printf("-----------\n");
            return false;
        case 'u':
            char username[MAX_LINE_LENGTH];
            char choice;

            if(!fetch_username_from_token(username)){
                printf("Please login and try again!");
                return false;
            }
            printf("[n: number phone]\n");
            printf("[p: password]\n");
            printf("Choose type to change:");
            scanf("%s", &choice);
            printf("-----------\n");

            User updatedUserdata;
            switch (choice) {
                case 'p':
                    printf("Enter your new password:");
                    scanf("%10s", updatedUserdata.password);

                    if (update_user("database/users.txt", username, &updatedUserdata, "password")) {
                        printf("Password updated successfully!\n");
                    } else {
                        printf("Password update failed.\n");
                    }
                    return false;
                case 'n':
                    printf("Enter your new phone number:");
                    scanf("%10s", updatedUserdata.phone);

                    if (update_user("database/users.txt", username, &updatedUserdata, "phone")) {
                        printf("Phone number updated successfully!\n");
                    } else {
                        printf("Phone number update failed.\n");
                    }
                    return false;
                default:
                    printf("Your choice is invalid. Please try again!\n");
                    return false;
            }

        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}