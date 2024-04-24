////
//// Created by hungt on 4/21/2024.
////

#include <stdio.h>
#include <stdbool.h>
#include "System.h"
#include "stdlib.h"


int main(){
    srand(time(NULL));
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
