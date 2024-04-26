//
// Created by hungt on 4/25/2024.
//

#include "StaffCommand.h"
#include "../utils/readFromFile.h"

#define LINE_MAX_LENGTH 256

bool StaffChoose(char option){
    char usernameInput[LINE_MAX_LENGTH];
    char UUID[LINE_MAX_LENGTH];
    User user;
    DateWork listDateWork;

    const char* authorized_roles2[] = {"admin"};
    int num_roles2 = sizeof(authorized_roles2) / sizeof(authorized_roles2[0]);

    switch (option) {
        case 'n':

            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            DateWork dateWork;  // Declare a DateWork variable

            printf("Enter Staff's username: ");
            scanf("%84s", dateWork.username);  // Read a string with a maximum of 84 characters

            printf("Enter Date (dd-mm-yyyy): ");
            scanf("%d-%d-%d", &dateWork.date.day, &dateWork.date.month, &dateWork.date.year);

            printf("Enter time spent (in hours): ");
            scanf("%d", &dateWork.time);

            printf("Enter paid amount: ");
            scanf("%f", &dateWork.paid);

            // Attempt to add the DateWork record
            if (addDateWork(&dateWork)) {
                printf("DateWork added successfully.\n");
            } else {
                printf("Failed to add DateWork.\n");
            }
            return false;
        case 'r':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            printf("Username is changed role:");
            scanf("%255s", usernameInput);

            printf("Changing role:");
            scanf("%6s", user.role);

            assignRole("database/users.txt", usernameInput, &user);
            return false;
        case 'g':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            getAllDateWorks(&listDateWork, 1);
            return false;
        case 'c':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            int month;
            int year;
            float salary;

            printf("Username: ");
            scanf("%s", usernameInput);

            printf("Salary: ");
            scanf("%f", &salary);

            printf("Month: ");
            scanf("%d", &month);

            printf("Year: ");
            scanf("%d", &year);

            calculateSalary(usernameInput, &salary, month, year);
            return false;
        case 's':
            if(!check_role(authorized_roles2, num_roles2)){
                printf("Not enough permission. Please login!\n");
                return false;
            }

            printf("Username:");
            scanf("%s", usernameInput);
            printf("-----------\n");

            searchDateWorkByUsername(usernameInput, &listDateWork, 1);

            return false;
        case 'u':
            readFileContents("guide/UpdateDateWork.txt");
            printf("UUID:");
            char UUID[37]; // UUIDs are typically 36 characters + 1 for the null terminator
            scanf("%36s", UUID);

            printf("Choose field to update (s for status, t for time):");
            char field;
            scanf(" %c", &field); // Notice space before %c to skip any leftover newline characters
            switch (field) {
                case 's':
                    printf("Set status (0 or 1):");
                    int status;
                    if (scanf("%d", &status) == 1 && (status == 0 || status == 1)) {
                        DateWork dateWork; // Assume dateWork is appropriately initialized or fetched before this
                        dateWork.status = status;
                        if (updateDateWork("database/dateWork.txt", UUID, &dateWork, "status")) {
                            printf("Status updated successfully.\n");
                        } else {
                            printf("Failed to update status.\n");
                        }
                    } else {
                        printf("Invalid status. Please enter 0 or 1.\n");
                    }
                    printf("-----------\n");
                    return false;
                case 't':
                    printf("Changing time:");
                    scanf("%d", &dateWork.time);

                    updateDateWork("database/dateWork.txt", UUID, &dateWork, "time");
                    // Handle time updates similarly
                    printf("-----------\n");
                    return false;
                default:
                    printf("Invalid field. Please try again!\n");
                    return false;
            }
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}
