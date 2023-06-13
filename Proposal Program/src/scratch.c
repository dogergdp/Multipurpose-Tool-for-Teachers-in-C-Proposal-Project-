#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


#ifdef _WIN32
#include <Windows.h>
const char* path_separator = "\\";
#else
const char* path_separator = "/";
#endif


#define ID_SIZE 16
#define FIRST_NAME 64
#define LAST_NAME 64
#define BODY_SIZE 1024
#define COURSE_SIZE 32
#define PATH_SIZE 512

typedef struct {
    char student_id[ID_SIZE];
    char first_name[FIRST_NAME];
    char last_name[LAST_NAME];
    char sex;
} STUDENT;

typedef struct {
    char course_menu[COURSE_SIZE];
    char year_section[2];
    int student_number;
    int passer_number;
    char status[8];
} MENU;

typedef struct{
    char student_id[ID_SIZE];
    int written_tscore;
    int perform_tscore;
    int exam_score;
    int total;
    char status[8];
} GRADESHEET;


void printLine(char character, int length){
    for(int i = 0; i < length; i++){
        printf("%c", character);
    }
    printf("\n");
}

void displayStudentRecord() {

// Call openSection function and assign the return value to filename
    FILE* student_file;
    student_file = fopen("..\\..\\Proposal Program\\src\\main files\\BSCS_1A_StudentRecords.csv", "r");

    if (student_file == NULL) {
        printf("Error opening STUDENT records..\n");
        exit(1);
    }

    STUDENT student_info[BODY_SIZE];
    int num_students = 0;

    // Skip the header line
    char header[100];
    char line[1024];
    fgets(header, sizeof(header), student_file);

    while (fgets(line, sizeof(line), student_file)) {
        sscanf(line, "%[^,], %[^,], %[^,],  %c\n",
               student_info[num_students].student_id,
               student_info[num_students].first_name,
               student_info[num_students].last_name,
               &student_info[num_students].sex);

        num_students++;

        if (num_students == BODY_SIZE) {
            printf("Maximum number of records reached..\n");
            break;
        }
    }

    fclose(student_file);

    printf("\nNumber of Students: %d\n", num_students);
    printLine('=', 87);
    printf("| |   STUDENT ID   |  NAME    | SEX | \n");
    printLine('=', 87);
    for (int i = 0; i < num_students; i++) {
        printf("|%d| %-16s| %s, %-6s | %c |\n",
               i + 1,
               student_info[i].student_id,
               student_info[i].last_name,
               student_info[i].first_name,
               student_info[i].sex);
    }
    printLine('=', 87);
}


int main() {
    char fp[512];
    displayStudentRecord();
    printf("%s\n", fp);

    return 0;
}
