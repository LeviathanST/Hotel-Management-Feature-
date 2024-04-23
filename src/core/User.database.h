//
// Created by hungt on 4/21/2024.
//

#ifndef FILEUTILSV2_USER_DATABASE_H
#define FILEUTILSV2_USER_DATABASE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_ORDERING_IDS 10 // Change this to the max number of ordering IDs you expect
#define MAX_ORDERING_ID_LENGTH 10

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char role [10];
    char orderingIds[MAX_ORDERING_IDS][MAX_ORDERING_ID_LENGTH]; // Array to hold ordering IDs, which are integers
    size_t numOrderingIds; // A count of how many ordering IDs are being used
} User;


extern void add_user(const char *filename, const User* user);
extern bool search_user_by_username(const char *filename, const char *usernameToSearch, bool printActive);
extern void update_user(const char *filename, const char *username, const User *updatedUserData);
extern int remove_user(const char *filename, const char *usernameToRemove);
extern int login(const char *filename, const char *username, const char *password);

#endif //FILEUTILSV2_USER_DATABASE_H
