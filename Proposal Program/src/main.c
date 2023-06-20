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


    do {
        printf("\n\n");
        tabText(6); printf("Professor's Student Access Module\n\n");
        tabText(5); printf("Username: ");
        scanf("%99s", user.username);  // Limit input to avoid buffer overflow
        tabText(5); printf("Password: ");
        takePassword(user.password);

        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            loginSuccessful = true;
        } else {
            newLine(2);
            tabText(5); printf("Invalid Credentials,");
            printf("would you like to try again? (Y/N): ");
            clearInputBuffer();  // Clear input buffer before reading character
            scanf(" %c", &letterChoice);

            if (letterChoice == 'Y' || letterChoice == 'y') {
                system("cls");
            } else if (letterChoice == 'N' || letterChoice == 'n') {
                exit (0);
            } else {
                system("cls");
                printf("Invalid input. Try again.\n");
                clearInputBuffer();
                letterChoice = ' ';
            }
        }
    } while (!loginSuccessful || (letterChoice == 'Y' || letterChoice == 'y'));
    if (loginSuccessful) {
        system("cls");
        printf("\nSuccessful Log-in..\n");
    }
}


void handleAddSection() {
    system("cls");
    addSection();
    system("cls");
}

void handleDeleteSection(int numSections)
{
    numSections = displayMenu();
    printf("Enter the section number to delete: ");
    int sectionToDelete;
    scanf("%d", &sectionToDelete);
    if (sectionToDelete >= 1 && sectionToDelete <= numSections) {
        deleteSection(sectionToDelete);
    } else {
        system("cls");
        printf("Invalid section number\n");
    }
    system("cls");
}


void handleOpenSection(int numSections) {

    newLine(1);
    tabText(3); printf("Which section would you like to open? Type an index: ");
    int sectionToOpen;
    if (scanf("%d", &sectionToOpen) != 1) {
        clearInputBuffer();
        system("cls");
        printf("Invalid Choice.\n");
        return;
    }

    clearInputBuffer();
    if (sectionToOpen > numSections || sectionToOpen < 1) {
        system("cls");
        printf("Invalid Choice.\n");
        return;
    } else {
        system("cls");
        displayStudentRecord(sectionToOpen);
        handleOpenSectionChoices(sectionToOpen);
    }
}

void handleOpenSectionChoices(int sectionToOpen) {
    int choice2;

    do {
        newLine(2);
        tabText(3); printf("[1] Add Student\n");
        tabText(3); printf("[2] Delete Student\n");
        tabText(3); printf("[3] Download Student Record\n");
        tabText(3); printf("[4] Create Gradesheet\n");
        tabText(3); printf("[5] Sort and Make a Group\n");
        tabText(3); printf("[6] BACK\n\n");
        tabText(3); printf("Enter your choice: ");
        scanf("%d", &choice2);
        if (choice2 != 1){

        }

        switch (choice2) {
            case 1:
                system("cls");
                addStudentRecord(sectionToOpen);
                system("cls");
                displayStudentRecord(sectionToOpen);
                break;
            case 2:
                system("cls");
                displayStudentRecord(sectionToOpen);
                newLine(2);
                tabText(3); printf("Which student would you like to delete?\n\n");
                tabText(3); printf("Enter your choice: ");
                int studentToDelete;
                if (scanf("%d", &studentToDelete) != 1) {
                    system("cls");
                    printf("Invalid input. Please enter a number.\n");
                    displayStudentRecord(sectionToOpen);
                    break;
                }
                if (studentToDelete != 1 || studentToDelete < 1) {
                    system("cls");
                    printf("Invalid student index.\n");
                    displayStudentRecord(sectionToOpen);
                    break;
                } else {
                    system("cls");
                    deleteStudentRecord(sectionToOpen, studentToDelete);
                    displayStudentRecord(sectionToOpen);
                    break;
                }

            case 3:
                system("cls");
                displayStudentRecord(sectionToOpen);
                downloadStudentRecord(sectionToOpen);
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
                displayStudentRecord(sectionToOpen);
                break;
            case 6:
                system("cls");
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice2 != 7);
}

int main() {

    //lockScreen();

    while (true) {
        int numSections = displayMenu();
        newLine(2);
        tabText(3); printf("[1] Add a Section\n");
        tabText(3); printf("[2] Delete a Section\n");
        tabText(3); printf("[3] Open a Section\n");
        tabText(3); printf("[4] Exit\n\n");
        tabText(3); printf("Enter your choice: ");

        int choice;
        int result = scanf("%d", &choice);

        if (result != 1) {
            system("cls");
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                continue;
        } else {
            switch (choice) {
                case 1:
                    system("cls");
                    handleAddSection();
                    break;
                case 2:
                    system("cls");
                    handleDeleteSection(numSections);
                    break;
                case 3:
                    system("cls");
                    numSections = displayMenu();
                    handleOpenSection(numSections);
                    break;
                case 4:
                    system("cls");
                    newLine(8);
                    tabText(5); printf("Thank you for using the program. Goodbye!\n");
                    newLine(8);
                    exit(0);
                default:
                    system("cls");
                    printf("Invalid choice.\n");
                    break;
            }
        }
    }

    return 0;
}



