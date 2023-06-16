#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

int i,j;


int main() {
    const char* filePath = openSection(1);
    char filename[PATH_SIZE];
    char buffer[PATH_SIZE];
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    GRADESHEET gradesheets[BODY_SIZE];
    int num_gradesheets = 0;

    char line[BODY_SIZE];
    char student_id[ID_SIZE];
    char last_name[LAST_NAME];
    char first_name[FIRST_NAME];
    char sex;
    int num_passers = 0;
    bool validChoice = false;

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        // Use sscanf to extract the columns
        if (sscanf(line, "%[^,],%[^,],%[^,],%c", student_id, last_name, first_name, &sex) == 4) {
            strcpy(gradesheets[num_gradesheets].student_id, student_id);
            strcpy(gradesheets[num_gradesheets].last_name, last_name);
            strcpy(gradesheets[num_gradesheets].first_name, first_name);
            gradesheets[num_gradesheets].sex = sex;

            num_gradesheets++;

            if (num_gradesheets == BODY_SIZE) {
                printf("Maximum number of gradesheets reached.\n");
                break;
            }
        }
    }

    fclose(file);

    if (num_gradesheets == 0) {
        system("cls");
        printf("No records found in the file.\n");
        displayMenu();
        return 0;
    }

    // Loop through gradesheets and ask for scores
    for (int i = 0; i < num_gradesheets; i++) {
        printf("Enter scores for %s %s (%s):\n", gradesheets[i].first_name, gradesheets[i].last_name, gradesheets[i].student_id);
        printf("Written Test Score: ");
        scanf("%d", &gradesheets[i].written_tscore);
        printf("Performance Test Score: ");
        scanf("%d", &gradesheets[i].perform_tscore);
        printf("Exam Score: ");
        scanf("%d", &gradesheets[i].exam_score);

        // Compute average
        gradesheets[i].total = gradesheets[i].written_tscore +
                                gradesheets[i].perform_tscore +
                                gradesheets[i].exam_score;
        gradesheets[i].average = gradesheets[i].total / 3;

        // Determine pass/fail status
        if (gradesheets[i].average >= 50) {
            strcpy(gradesheets[i].status, "PASSED");
            num_passers++;

        } else {
            strcpy(gradesheets[i].status, "FAILED");
        }
    }

    // Display gradesheet in table form
    printLine('=',87);
    printf("|%-20s|%-14s |%-15s|%-10s|%-10s|%-10s|\n", "Student ID", "Last Name", "First Name", "Total", "Average", "Status");
    printLine('=',87);
    for (int i = 0; i < num_gradesheets; i++) {
        printf("|%-20s|%-15s|%-15s|%-10d|%-9d |%-10s|\n",
               gradesheets[i].student_id,
               gradesheets[i].last_name,
               gradesheets[i].first_name,
               gradesheets[i].total,
               gradesheets[i].average,
               gradesheets[i].status);
    }
    printLine('=',87);

    int choice;
    printf("Would you like to download your gradesheet?\n");
    printf("[1] Yes\n");
    printf("[2] Return to Menu");

    while (!validChoice) {
        scanf("%d", &choice);
        if (choice != 1 && choice != 2) {
            printf("Invalid Choice\n");
        } else {
            switch (choice) {
                case 1:
                    printf("What would you like to name the file?\n");
                    scanf("%255s", buffer);  // Read input into buffer, limited to 255 characters
                    replace_spaces(buffer);
                    snprintf(filename, sizeof(filename), "..\\..\\Proposal Program\\Your Files\\%s.csv", buffer);
                    fptr = fopen(filename, "w");
                    if (fptr == NULL) {
                        printf("Error creating CSV File.\n");
                        exit(1);
                    }
                    fprintf(fptr, "STUDENT ID,LAST NAME,FIRST NAME,TOTAL SCORE,AVERAGE,STATUS\n");
                    for (int i = 0; i < num_gradesheets; i++) {
                        fprintf(fptr, "%s,%s,%s,%d,%d,%-10s\n",
                                gradesheets[i].student_id,
                                gradesheets[i].last_name,
                                gradesheets[i].first_name,
                                gradesheets[i].total,
                                gradesheets[i].average,
                                gradesheets[i].status);
                    }
                    fclose(fptr);
                    printf("File Successfully Downloaded\n");
                    printf("File is located at %s\n", filename);
                    break;
                case 2:
                    validChoice = true;
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
            }
        }
    }


    return 0;
}
