//
// Created by hungt on 4/24/2024.
//

#ifndef FILEUTILSV2_DATE_H
#define FILEUTILSV2_DATE_H

#include <stdio.h>
#include <time.h>

typedef struct {
    int year;
    int month;
    int day;
} Date;

int daysBetweenDates(Date startDate, Date endDate);
int validateDate(const char* date) ;
#endif //FILEUTILSV2_DATE_H
