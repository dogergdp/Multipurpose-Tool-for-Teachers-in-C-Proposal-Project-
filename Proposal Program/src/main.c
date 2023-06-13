#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "functions.h"

int main() {
    int choice;
    int sectionToOpen, fileToOpen;
    bool isValidChoice = false;
    const char* filePath;

    printf("\nSuccessful Log-in..\n");
    int numSections = displayMenu();

    while (!isValidChoice) {
        printf("\n\n[1] Add a Section\n");
        printf("[2] Delete a Section\n");
        printf("[3] Open a Section\n");
        printf("Enter your choice: ");

        int result = scanf("%d", &choice);

        if (result != 1) {
            printf("Invalid input. Please enter a number\n");
            // Clear the input buffer
            while (getchar() != '\n')
                continue;
        } else {
            switch (choice) {
                case 1:
                    system("cls");
                    addSection();
                    isValidChoice = true;
                    break;
                case 2:
                    system("cls");
                    int sectionToDelete;
                    printf("Enter the section number to delete: ");
                    scanf("%d", &sectionToDelete);
                    if (sectionToDelete >= 1 && sectionToDelete <= numSections) {
                        deleteSection(sectionToDelete);
                    } else {
                        printf("Invalid section number\n");
                        main();
                    }
                    isValidChoice = true;
                    break;
                case 3:
                    printf("Enter the section number to open: ");
                    scanf("%d", &sectionToOpen);
                    if (sectionToOpen >= 1 && sectionToOpen <= numSections) {
                        system("cls");
                        printf("Selected Section: %d\n", sectionToOpen);
                        printf("[1] Open Student Records\n");
                        printf("[2] Open Student Gradesheet\n");
                        printf("Enter your choice: ");
                        scanf("%d", &fileToOpen);

                        if (fileToOpen == 1) {
                            system("cls");
                            displayStudentRecord(sectionToOpen, fileToOpen);
                        } else if (fileToOpen == 2) {

                        } else {
                            printf("Invalid choice\n");
                            main();
                        }
                    } else {
                        printf("Invalid section number\n");
                        main();
                    }
                    isValidChoice = true;
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }
    }

    return 0;
}



