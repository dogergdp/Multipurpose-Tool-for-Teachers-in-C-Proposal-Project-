#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include "functions.h"

int main() {
    int choice;
    int sectionToOpen;
    bool isValidChoice = false;
    bool exitProgram = false;
    const char* filePath;

    printf("\nSuccessful Log-in..\n");
    int numSections = displayMenu();

    while (!exitProgram) {
        while (!isValidChoice) {
            printf("\n\n");
            printf("[1] Add a Section\n");
            printf("[2] Delete a Section\n");
            printf("[3] Open a Section\n");
            printf("[4] Exit\n");
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
                        isValidChoice = true; // Set isValidChoice to true to return to the menu
                        break;
                    case 2:
                        system("cls");
                        int sectionToDelete;
                        printf("Enter the section number to delete: ");
                        scanf("%d", &sectionToDelete);
                        if (sectionToDelete >= 1 && sectionToDelete <= numSections) {
                            deleteSection(sectionToDelete);
                            system("cls");
                            numSections = displayMenu(); // Update numSections after deletion
                        } else {
                            printf("Invalid section number\n");
                        }
                        isValidChoice = true; // Set isValidChoice to true to return to the menu
                        break;
                    case 3:
                        printf("Which section would you like to open?: ");
                        scanf("%d", &sectionToOpen);
                        if (sectionToOpen > numSections || sectionToOpen < 1) {
                            printf("Invalid Choice.\n");
                        } else {
                            system("cls");
                            displayStudentRecord(sectionToOpen);
                            int choice2;
                            printf("[1] Open Student Records\n");
                            printf("[2] Gradesheet\n");
                            printf("[3] Make a Group\n");
                            printf("[4] Return to Start\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice2);

                            switch (choice2) {
                                case 1:
                                    printf("Selected Section: %d\n", sectionToOpen);
                                    printf("[1] Add Student\n");
                                    printf("[2] Delete Student\n");
                                    printf("[3] BACK\n");
                                    printf("Enter your choice: ");
                                    int fileToOpen;
                                    scanf("%d", &fileToOpen);
                                    if (fileToOpen == 1) {
                                        system("cls");
                                        addStudentRecord(sectionToOpen);
                                    }
                                    break;
                                // Add more cases for other options if needed
                                case 4:
                                    // Set isValidChoice to true to return to the menu
                                    isValidChoice = true;
                                    break;
                                default:
                                    printf("Invalid choice.\n");
                                    break;
                            }
                        }
                        break;
                    case 4:
                        exitProgram = true;
                        isValidChoice = true; // Set isValidChoice to true to exit the program
                        break;
                    default:
                        system("cls");
                        printf("Invalid choice.\n");
                        main();
                        break;
                }
            }
        }

        isValidChoice = false; // Reset isValidChoice for the next iteration
    }

    return 0;
}




