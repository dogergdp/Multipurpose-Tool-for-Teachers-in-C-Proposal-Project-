#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include "functions.h"

void lockScreen();
void handleAddSection();
void handleDeleteSection();
void handleOpenSection();
void handleOpenSectionChoices();

void lockScreen() {
    char letterChoice;
    struct User user;
    char username[] = "tupadmin";
    char password[] = "Group2TUP";
    bool loginSuccessful = false;

    printf("\n\t\t\tProfessor's Student Access Module\n\n");

    do {
        printf("\t\t\tUsername: ");
        scanf("%s", user.username);
        printf("\t\t\tPassword: ");
        takePassword(user.password);

        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            loginSuccessful = true;
        } else {
            printf("LOGIN UNSUCCESSFUL\n");
            printf("Would you like to try again? (Y/N): ");
            scanf(" %c", &letterChoice);
        }
    } while (!loginSuccessful && (letterChoice == 'Y' || letterChoice == 'y'));

    if (loginSuccessful) {
        printf("\nSuccessful Log-in..\n");
        return;
    }
}


void handleAddSection() {
    system("cls");
    addSection();
    displayMenu();
}

void handleDeleteSection(int numSections) {
    printf("Enter the section number to delete: ");
    int sectionToDelete;
    scanf("%d", &sectionToDelete);
    if (sectionToDelete >= 1 && sectionToDelete <= numSections) {
        deleteSection(sectionToDelete);
    } else {
        printf("Invalid section number\n");
    }
}


void handleOpenSection(int numSections) {
    printf("Which section would you like to open?: ");
    int sectionToOpen;
    scanf("%d", &sectionToOpen);
    if (sectionToOpen > numSections || sectionToOpen < 1) {
        printf("Invalid Choice.\n");
        return;
    }

    system("cls");
    displayStudentRecord(sectionToOpen);

    // Handle additional choices within the selected section
    handleOpenSectionChoices(sectionToOpen, numSections);
}

void handleOpenSectionChoices(int sectionToOpen, int numSections) {
    int choice2;

    do {
        printf("[1] Add Student\n");
        printf("[2] Delete Student\n");
        printf("[3] Download Student Record\n");
        printf("[4] Create Gradesheet\n");
        printf("[5] Make a Group\n");
        printf("[6] BACK\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);

        switch (choice2) {
            case 1:
                system("cls");
                addStudentRecord(sectionToOpen);
                system("cls");
                displayStudentRecord(sectionToOpen);
                break;
            case 2:
                printf("Which student would you like to delete?\n");
                printf("Enter your choice: ");
                int studentToDelete;
                scanf("%d", &studentToDelete);
                system("cls");
                deleteStudentRecord(sectionToOpen, studentToDelete);
                displayStudentRecord(sectionToOpen);
                break;
            case 3:
                system("cls");
                displayStudentRecord(sectionToOpen);
                downloadStudentRecord(sectionToOpen);
                system("cls");
                displayStudentRecord(sectionToOpen);
                break;
            case 4:
                system("cls");
                createGradesheet(sectionToOpen);
                system("cls");
                displayStudentRecord(sectionToOpen);
                break;
            case 5:
                system("cls");
                groupFormation(sectionToOpen);
                system("cls");
                displayStudentRecord(sectionToOpen);
                break;
            case 6:
                system("cls");
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice2 != 3);
}

int main() {
    //lockScreen();
    system("cls");


    while (true) {
        system("cls");
        int numSections = displayMenu();
        printf("\n\n");
        printf("[1] Add a Section\n");
        printf("[2] Delete a Section\n");
        printf("[3] Open a Section\n");
        printf("[4] Exit\n");
        printf("Enter your choice: ");

        int choice;
        int result = scanf("%d", &choice);

        if (result != 1) {
            printf("Invalid input. Please enter a number\n");
            while (getchar() != '\n')
                continue;
        } else {
            switch (choice) {
                case 1:
                    system("cls");
                    handleAddSection();
                    system("cls");
                    numSections = displayMenu();
                    break;
                case 2:
                    system("cls");
                    numSections = displayMenu();
                    handleDeleteSection(numSections);
                    system("cls");
                    numSections = displayMenu();
                    break;
                case 3:
                    system("cls");
                    numSections = displayMenu();
                    handleOpenSection(numSections);
                    printf("\n\n");
                    printf("[1] Add a Section\n");
                    printf("[2] Delete a Section\n");
                    printf("[3] Open a Section\n");
                    printf("[4] Exit\n");
                    break;
                case 4:
                    return 0;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        }
    }

    return 0;
}



