//
// Created by hungt on 4/24/2024.
//

#include "Date.h"

int daysBetweenDates(Date startDate, Date endDate) {
    struct tm start = {0}, end = {0};
    start.tm_year = startDate.year - 1900; // tm_year is years since 1900
    start.tm_mon = startDate.month - 1;    // tm_mon is months since January (0-11)
    start.tm_mday = startDate.day;

    end.tm_year = endDate.year - 1900;
    end.tm_mon = endDate.month - 1;
    end.tm_mday = endDate.day;

    // Convert to time_t (seconds since epoch)
    time_t start_time = mktime(&start);
    time_t end_time = mktime(&end);

    // Calculate difference in seconds and then convert to days
    double difference = difftime(end_time, start_time);
    return (int)(difference / (60 * 60 * 24)); // Convert seconds to days
}

int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int getDaysInMonth(int year, int month) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    return daysInMonth[month - 1];
}

int validateDate(const char* date) {
    int y, m, d;
    // Adjust sscanf to parse non-padded month and day values
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) == 3) {
        if (y > 0 && m >= 1 && m <= 12 && d >= 1 && d <= getDaysInMonth(y, m)) {
            return 1; // Valid date
        }
    }
    return 0; // Invalid date
}
