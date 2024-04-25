#include "Service.database.h"

struct Service services[MAX_SERVICES];
int numServices = 0;

// Function to load services from a file
int loadServicesFromFile() {
    numServices = 0;
    FILE* file = fopen("database/service.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading: %s\n", "database/service.txt");
        return -1;
    }

    int initialNumServices = numServices;

    char line[100]; // Assuming no line will exceed 100 characters
    while (numServices < MAX_SERVICES && fgets(line, sizeof(line), file) != NULL) {
        char *nameStart = strstr(line, "Name Service:");
        char *priceStart = strstr(line, "Price($):");
        if (nameStart && priceStart) {
            // Extract name and price from the line
            sscanf(nameStart + strlen("Name Service:"), " %49[^-]", services[numServices].name);
            sscanf(priceStart + strlen("Price($):"), " %f", &services[numServices].price);

            numServices++;
        }
    }

    fclose(file);
    return numServices - initialNumServices;
}


// Function to save services to a file
int saveServicesToFile() {
    FILE* file = fopen("database/service.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", "database/service.txt");
        return -1;
    }

    for (int i = 0; i < numServices; i++) {
        fprintf(file, "Name Service: %s- Price($): %.2f\n", services[i].name, services[i].price);
        if (ferror(file)) {
            printf("Error writing data to file.\n");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

int service_exists(const char* name) {
    for (int i = 0; i < numServices; i++) {
        if (strcasecmp(services[i].name, name) == 0) {
            return 1; // Service exists
        }
    }
    return 0; // Service does not exist
}

// Function to capitalize the first letter of each word
void capitalize_first_letter(char* name) {
    for (int i = 0; name[i]; i++) {
        if (i == 0 || name[i - 1] == ' ') {
            name[i] = toupper(name[i]);
        } else {
            name[i] = tolower(name[i]);
        }
    }
}

// Function to display the list of services
void displayServices() {
    loadServicesFromFile();
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
    if (scanf(" %49[^\n]%*c", services[numServices].name) != 1) {
        printf("| Invalid service name. |\n");
        return;
    }

    printf("Enter price($): ");
    if (scanf("%f", &services[numServices].price) != 1) {
        printf("|   Invalid price   |\n");
        return;
    }

    if (service_exists(services[numServices].name)) {
        printf("|    Service already exists.    |\n");
        return;
    }

    capitalize_first_letter(services[numServices].name);
    numServices++;
    printf("|  Added new service successfully!  |\n");
    saveServicesToFile();
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
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    printf("Enter a new name for the service: ");
    if (scanf(" %49[^\n]%*c", services[choice].name) != 1) {
        printf("Invalid service name.\n");
        return;
    }

    printf("Enter new price for service: ");
    if (scanf("%f", &services[choice].price) != 1) {
        printf("Invalid price.\n");
        return;
    }

    printf("Edited service information successfully!\n");
    saveServicesToFile();

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
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    for (int i = choice; i < numServices - 1; i++) {
        strcpy(services[i].name, services[i + 1].name);
        services[i].price = services[i + 1].price;
    }

    numServices--;
    printf("Service deletion successful!\n");
    saveServicesToFile();
}