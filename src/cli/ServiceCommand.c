//
// Created by hungt on 4/24/2024.
//

#include "ServiceCommand.h"

bool ServiceChoose(char option){
    switch (option) {
        case 'n':
            addService();
            return false;
        case 's':
            displayServices();
            return false;
        case 'b':
            return true;
        default:
            printf("Option is invalid. Please try again!\n");
    }
}
