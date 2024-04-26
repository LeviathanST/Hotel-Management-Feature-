//
// Created by hungt on 4/26/2024.
//

#include "readFromFile.h"


void readFileContents(const char *filename) {
    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the file");
        return;
    }

    // Read and display the file content line by line
    char line[1024]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // Close the file
    fclose(file);
}