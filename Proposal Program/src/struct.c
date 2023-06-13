#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

int i,j;

int main()
{
    FILE* student_file;
    student_file = fopen("..\\..\\Proposal Program\\src\\main files\\all_students_sheet.csv", "r");

    if (student_file == NULL) {
        printf("Error opening file..\n");
        return 1;
    }

    STUDENT student_info[BODY_SIZE];
    int records = 0;

    // Skip the header line
    char header[100];
    fgets(header, sizeof(header), student_file);

    while (fscanf(student_file, "%[^,],%[^,],%[^,],%c,%[^\n]\n",
        student_info[records].student_id,
        student_info[records].last_name,
        student_info[records].first_name,
        &student_info[records].sex,
        student_info[records].course) == 5) {

        records++;

        if (records == BODY_SIZE) {
            printf("Maximum number of records reached..\n");
            break;
        }
    }

    fclose(student_file);

    qsort(student_info, records, sizeof(STUDENT), compareByLastName);

    printf("\nNumber of Students: %d\n", records);
    printLine('=',87);
    printf("|    STUDENT ID     |             NAME             |  SEX  |    COURSE & SECTION      |\n");
    printLine('=',87);
    for (int i = 0; i < records; i++) {

        printf("|  %-15s  |   %-10s %-15s |   %c   |      %-20s|\n",
            student_info[i].student_id,
            strcat(student_info[i].last_name, ","),
            student_info[i].first_name,
            student_info[i].sex,
            student_info[i].course);
    }
    printLine('=',87);

    return 0;
}
