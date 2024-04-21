//
// Created by hungt on 4/21/2024.
//

#ifndef FILEUTILSV2_USER_DATABASE_H
#define FILEUTILSV2_USER_DATABASE_H
typedef struct {
    char username[100];
    char password[100];
} User;

extern void add_user(const char *filename, User user);
int search_user_by_username(const char *filename, const char *searchUsername);
extern void update_user(const char *filename, const char *username, const User *updatedUserData);
int remove_user(const char *filename, const char *usernameToRemove);

#endif //FILEUTILSV2_USER_DATABASE_H
