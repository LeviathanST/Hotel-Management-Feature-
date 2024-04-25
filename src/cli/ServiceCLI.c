//
// Created by hungt on 4/24/2024.
//

#include "ServiceCLI.h"

bool ServiceChoose(char option){
    switch (option) {
        case 'n':
            addService();
            return false;
        case 's':
            displayServices();
            return false;
        case 'u':
            editService();
            return false;
        case 'd':
            deleteService();
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}