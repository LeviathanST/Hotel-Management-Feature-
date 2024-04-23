//
// Created by hungt on 4/21/2024.
//

#include <stdio.h>
#include "System.h"
#include <stdbool.h>


int main(){
    bool exit = false;

    while(!exit){
        char option;
        printf("Your option:");
        scanf("%s", &option);
        printf("-----------\n");


        exit = Choose(option);
    }


    return 0;
}