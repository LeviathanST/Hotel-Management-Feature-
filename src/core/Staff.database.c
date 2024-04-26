//
// Created by THIEN DUYEN on 4/25/2024.
//
#include "Staff.database.h"
#include"../utils/generateUUID.h"

#define USERNAME_PREFIX "username: "
#define MAX_LINE_LENGTH 256


bool assignRole(const char *filename, const char *username, User *newUser) {
    if (!update_user(filename, username, newUser, "role")) {
        printf("Update failed!\n");
        return false;
    }
    return true;

}

bool getAllUser(const char *filename, User *listUsers, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    User user;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Check if the line starts with the 'username' field
        if (strncmp(line, USERNAME_PREFIX, strlen(USERNAME_PREFIX)) == 0) {
            // Extract the username from the current line
            strcpy(user.username, line + strlen(USERNAME_PREFIX));

            // If the username matches, proceed to populate the rest of the fields


            // Read and print the rest of the user details
            fgets(user.password, sizeof(user.password), file);

            fgets(user.email, sizeof(user.email), file);

            fgets(user.phone, sizeof(user.phone), file);

            fgets(user.role, sizeof(user.role), file);

            listUsers[*size] = user;
            *size += 1;
        }
    }

    fclose(file);

    return true;
}

bool addDateWork(DateWork *dateWork){
    if(!search_user_by_username("database/users.txt", dateWork->username, false)){
        printf("User is not existed!\n");
        printf("-----------\n");
        return false;
    };

    FILE *file = fopen("database/dateWork.txt", "a");
    if (file == NULL){
        printf("Can't open file\n ");
        printf("-----------\n");
        return false;
    }

    generate_uuid(dateWork->uuid);

    fprintf(file, "%s, ", dateWork -> uuid);
    fprintf(file, "%s, ", dateWork ->username);
    fprintf(file, "%d-%d-%d,", dateWork->date.year, dateWork->date.month, dateWork->date.day);
    fprintf(file,"%d, ", dateWork->time);
    fprintf(file,"%d, ", false);
    fprintf(file,"%.2f\n", dateWork->paid);

    fclose(file);
    return true;
}

bool updateDateWork(const char *filename, const char *uuid, DateWork *dateWork, const char *fieldToUpdate) {
    if (strcmp(fieldToUpdate, "time") == 0) {
        if (dateWork->time < 0) {
            printf("Invalid time\n");
            return false;
        }
    } else if (strcmp(fieldToUpdate, "status") == 0) {
        if (dateWork->status != 0 && dateWork->status != 1) {
            printf("Invalid status\n");
            return false;
        }
    } else if (strcmp(fieldToUpdate, "paid") == 0) {
        if (dateWork->paid < 0) {
            printf("Invalid field to update\n");
            return false;
        }
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(" Can't open file\n ");
        return false;
    }

    FILE *tempFile = fopen("database/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Can't open file\n");
        fclose(file);  // Close the previously opened file before returning
        return false;
    }

    char line[265];
    bool updateSuccess = false; // Indicates if the update was successful

    while (fgets(line, sizeof(line), file)) {
        DateWork dateWorkTemp;
        sscanf(line, "%[^,], %[^,], %d-%d-%d, %d, %d, %f",
               dateWorkTemp.uuid, dateWorkTemp.username,
               &dateWorkTemp.date.year, &dateWorkTemp.date.month, &dateWorkTemp.date.day,
               &dateWorkTemp.time, &dateWorkTemp.status, &dateWorkTemp.paid);

        if (strcmp(dateWorkTemp.uuid, uuid) == 0) {
            updateSuccess = true; // Successful update, so we change the data
            if (strcmp(fieldToUpdate, "time") == 0) {
                dateWorkTemp.time = dateWork->time;
            } else if (strcmp(fieldToUpdate, "status") == 0) {
                dateWorkTemp.status = dateWork->status;
            } else if (strcmp(fieldToUpdate, "paid") == 0) {
                dateWorkTemp.paid = dateWork->paid;
            }
        }
        fprintf(tempFile, "%s, %s, %d-%d-%d, %d, %d, %.2f\n",
                dateWorkTemp.uuid, dateWorkTemp.username,
                dateWorkTemp.date.year, dateWorkTemp.date.month, dateWorkTemp.date.day,
                dateWorkTemp.time, dateWorkTemp.status, dateWorkTemp.paid);
    }

    fclose(file);
    fclose(tempFile);

    if (!updateSuccess) {
        printf("No record found for UUID %s\n", uuid);
        remove("database/temp.txt");  // Cleanup: No need to replace original if no update was made
        return false;
    }

    // Replace original file with updated data
    remove(filename);
    rename("database/temp.txt", filename);
    return true;
}

bool calculateSalary(const char *username, float *salary, int month, int year) {
    FILE *file = fopen("database/dateWork.txt", "r");
    if (file == NULL) {
        printf(" Can't open file\n ");
        printf("-----------\n");
        return false;
    }
    DateWork dateWork;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %d-%d-%d, %d, %d, %f",
               dateWork.uuid, dateWork.username,
               &dateWork.date.year, &dateWork.date.month, &dateWork.date.day,
               &dateWork.time, &dateWork.status, &dateWork.paid);

        if (strcmp(dateWork.username, username) == 0
            && dateWork.date.month == month && dateWork.date.year ==    year && dateWork.status == 1){
            *salary += dateWork.paid *(float)dateWork.time;
        }
    }

    printf("%f\n", *salary);
    fclose(file);
    return true;
}


bool getAllDateWorks(DateWork *listDateWorks, int size){
    FILE *file = fopen("database/dateWork.txt", "r");
    if (file == NULL) {
        printf(" Can't open file\n ");
        printf("-----------\n");
        return false;
    }
    DateWork dateWork;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %d-%d-%d, %d, %d, %f",
               dateWork.uuid, dateWork.username,
               &dateWork.date.year, &dateWork.date.month, &dateWork.date.day,
               &dateWork.time, &dateWork.status, &dateWork.paid);
        listDateWorks[size] = dateWork;

        printf("UUID: %s\n", dateWork.uuid);
        printf("Username: %s\n", dateWork.username);
        printf("Date: %d-%d-%d\n", dateWork.date.year, dateWork.date.month, dateWork.date.day);
        printf("Working time: %d\n", dateWork.time);
        printf("Paid: %f\n", dateWork.paid);
        printf("Status: %s\n", dateWork.status == 0 ? "Not completed!" : "Completed!");
        printf("-----------\n");

        size += 1;
    }
    fclose(file);
    return true;
}

bool searchDateWorkByUsername(const char *username, DateWork *listDateWorks, int size){
    if(!search_user_by_username("database/users.txt", username, false)){
        printf("User is not existed!\n");
        printf("-----------\n");
        return false;
    };


    FILE *file = fopen("database/dateWork.txt", "r");
    if (file == NULL) {
        printf(" Can't open file\n ");
        printf("-----------\n");
        return false;
    }
    DateWork dateWork;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %d-%d-%d, %d, %d, %f",
               dateWork.uuid, dateWork.username,
               &dateWork.date.year, &dateWork.date.month, &dateWork.date.day,
               &dateWork.time, &dateWork.status, &dateWork.paid);
        if (strcmp(dateWork.username, username) == 0){
            listDateWorks[size] = dateWork;

            printf("UUID: %s\n", dateWork.uuid);
            printf("Username: %s\n", dateWork.username);
            printf("Date: %d-%d-%d\n", dateWork.date.year, dateWork.date.month, dateWork.date.day);
            printf("Working time: %d\n", dateWork.time);
            printf("Paid: %f\n", dateWork.paid);
            printf("Status: %s\n", dateWork.status == 0 ? "Not completed!" : "Completed!");
            printf("-----------\n");

            size +=1;
        }
    }
    fclose(file);
    return true;
}