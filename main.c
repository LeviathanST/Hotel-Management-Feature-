//
// Created by hungt on 4/21/2024.
//

#include <stdio.h>
#include "src/core/User.database.h"

int main(){

    User user1 = {.username = "helloworld", .password = "saoembuon"};
    User user2 = {.username = "hihi", .password = "hungneemoi"};

    search_user_by_username("C:\\Users\\hungt\\CLionProjects\\FileUtilsV2\\users.txt", "helloworld");

    return 0;
}