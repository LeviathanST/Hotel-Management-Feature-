
#include "Service.database.h"

// Function to load services from a file
int loadServicesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading: %s\n", filename);
        return -1;
    }

    int initialNumServices = numServices;

    while (numServices < MAX_SERVICES && fscanf(file, "%49s%f", services[numServices].name, &services[numServices].price) == 2) {
        numServices++;
    }

    fclose(file);
    return numServices - initialNumServices;
}

// Function to save services to a file
int saveServicesToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return -1;
    }

    for (int i = 0; i < numServices; i++) {
        fprintf(file, "%s %.2f\n", services[i].name, services[i].price);
        if (ferror(file)) {
            printf("Error writing data to file.\n");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}
// Function to display the list of services
void displayServices() {
    if (numServices == 0) {
        printf("\n|-NO SERVICES ADDED-|\n\n");
    } else {
        printf("\nLIST OF SERVICES:\n");
        for (int i = 0; i < numServices; i++) {
            printf("%d. Name: %s - Price($): %.2f\n", i + 1, services[i].name, services[i].price);
        }
    }
}

// Function to add a new service
void addService() {
    if (numServices >= MAX_SERVICES) {
        printf("Maximum number of services reached (MAX=100).\n");
        return;
    }

    printf("Enter Service: ");
    scanf(" %49[^\n]%*c", services[numServices].name);

    printf("Enter price($): ");
    scanf("%f", &services[numServices].price);

    numServices++;
    printf("| Add service successful! |\n");
}

// Function to edit service information
void editService() {
    if (numServices == 0) {
        printf("\nNo services have been added yet.\n");
        return;
    }

    displayServices();

    int choice;
    printf("Enter the service order number you want to edit: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    printf("Enter a new name for the service: ");
    scanf(" %49[^\n]%*c", services[choice].name);

    printf("Enter new price for service: ");
    scanf("%f", &services[choice].price);

    printf("Edited service information successfully!\n");
}

// Function to delete a service
void deleteService() {
    if (numServices == 0) {
        printf("No services to delete.\n");
        return;
    }

    displayServices();

    int choice;
    printf("Enter the service order number you want to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    for (int i = choice; i < numServices - 1; i++) {
        services[i] = services[i + 1];
    }

    numServices--;
    printf("Service deletion successful!\n");
}