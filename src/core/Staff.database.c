//
////
//// Created by THIEN DUYEN on 4/23/2024.
////
//
//#include "Staff.database.h"
//#include <string.h>
//#include <stdio.h>
//
//bool ReadFromFile(char *filename, struct Staff *listStaff, int *numberStaff){
//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        return false;
//    }
//    while(!feof(file)) {
//        struct Staff staff;
//        fscanf(file, "%d",&staff.id);
//        fscanf( file, "%s", staff.username);
//        fscanf(file, "%s", staff.role);
//        fscanf(file, "%f", &staff.salary);
//        listStaff[*numberStaff] = staff;
//        *numberStaff += 1;
//    }
//    fclose(file);
//    return true;
//}
//bool saveToFile(char *filename, struct Staff *listStaff, int numberStaff){
//    FILE *file = fopen(filename, "w");
//    if (file == NULL) {
//        return false;
//    }
//    for (int i = 0; i < numberStaff; i++){
//        fprintf(file, "%d ",i);
//        fprintf(file, "%s ",listStaff[i].username);
//        fprintf(file, "%s ",listStaff[i].role);
//        fprintf(file, "%f ",listStaff[i].salary);
//        if (i < numberStaff -1) {
//            fprintf(file, "\n");
//        }
//    }
//    return true;
//}
//int loginStaff(char *username, char *password){
//    struct Staff listStaff[500];
//    int numberStaff = 0;
//    if (!ReadFromFile("database/staff.txt", listStaff, &numberStaff)){
//        return -1;
//    }
//    for (int i = 0; i < 4; i++) {
//        if (strcmp(listStaff[i].username, username) ==0 && strcmp(listStaff[i].password, password) == 0){
//            return listStaff[i].id;
//        }
//    }
//    return -1;
//}
//bool registerStaff(struct Staff newStaff){
//    struct Staff listStaff[500];
//    int numberStaff = 0;
//    if (!ReadFromFile("database/staff.txt", listStaff, &numberStaff)){
//        return -1;
//    }
//    listStaff[numberStaff] = newStaff;
//    numberStaff += 1;
//    if(!saveToFile("database/staff.txt", listStaff, numberStaff)){
//        return false;
//    }
//    return true;
//}