#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#endif // FUNCTIONS_H_INCLUDED

#define ID_SIZE 16
#define FIRST_NAME 64
#define LAST_NAME 64
#define BODY_SIZE 1024
#define COURSE_SIZE 32
#define PATH_SIZE 512

void printLine(char character, int length);
void replace_spaces(char str[]);
void textScan(char* buffer);
int compareByLastName(const void* a, const void* b);
int countStudentsInSection(const char* section_file_path);
int displayMenu();
void deleteSection(int sectionNumber);
void addSection();
void displayStudentRecord(int sectionIndex);
void displayGradesheet(int sectionIndex);
const char* openSection(int sectionIndex);
void addStudentRecord(int sectionIndex);



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

typedef struct {
    char student_id[ID_SIZE];
    char last_name[LAST_NAME];
    char first_name[FIRST_NAME];
    char sex;
    int written_tscore;
    int perform_tscore;
    int exam_score;
    int average;
    int total;
    char status[8];
} GRADESHEET;



void printLine(char character, int length){
    for(int i = 0; i < length; i++){
        printf("%c", character);
    }
    printf("\n");
}


void replace_spaces(char str[]) {
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}


int compareByLastName(const void* a, const void* b) {
    const STUDENT* studentA = (const STUDENT*)a;
    const STUDENT* studentB = (const STUDENT*)b;
    return strcmp(studentA->last_name, studentB->last_name);
}


int countStudentsInSection(const char* section_file_path) {
    FILE* section_file = fopen(section_file_path, "r");
        if (section_file == NULL) {
            printf("Error countStudentsInSection for: %s\n", section_file_path);
            return 0;
        }

    int student_count = 0;
    char line[PATH_SIZE];

    // Skip the header line
    fgets(line, sizeof(line), section_file);

    while (fgets(line, sizeof(line), section_file)) {
        // Each line represents a student record
        student_count++;
    }

    fclose(section_file);
    return student_count;
}



void deleteSection(int sectionNumber) {
    // Open the section_menu.csv file for reading
    FILE* menu_file = fopen("..\\..\\Proposal Program\\src\\main files\\section_menu.csv", "r");
        if (menu_file == NULL) {
            printf("Error deleteSection file..\n");
            return;
        }

    // Create a temporary file to store the updated contents of section_menu.csv
    FILE* temp_menu_file = fopen("..\\..\\Proposal Program\\src\\main files\\temp_menu.csv", "w");
        if (temp_menu_file == NULL) {
            printf("Error creating temporary menu file..\n");
            fclose(menu_file);
            return;
        }

    // Copy the header line from section_menu.csv to the temporary file
    char header[1024];
    if (fgets(header, sizeof(header), menu_file)) {
        fputs(header, temp_menu_file);
    }

    // Copy all lines except the one to be deleted to the temporary file
    char line[1024];
    int lineCount = 0;
    while (fgets(line, sizeof(line), menu_file)) {
        lineCount++;

        // Skip the line if it matches the section number to be deleted
        if (lineCount == sectionNumber)
            continue;

        fputs(line, temp_menu_file);
    }

    fclose(menu_file);
    fclose(temp_menu_file);

    // Remove the original section_menu.csv file
    if (remove("..\\..\\Proposal Program\\src\\main files\\section_menu.csv") != 0) {
        printf("Error deleting section_menu.csv file..\n");
        displayMenu();
        return;
    }

    // Rename the temporary file to section_menu.csv
    if (rename("..\\..\\Proposal Program\\src\\main files\\temp_menu.csv", "..\\..\\Proposal Program\\src\\main files\\section_menu.csv") != 0) {
        printf("Error renaming temporary menu file..\n");
        displayMenu();
        return;
    }

    // Open the filepath_records.txt file for reading
    FILE* records_file = fopen("..\\..\\Proposal Program\\src\\main files\\filepath_records.txt", "r");
    if (records_file == NULL) {
        printf("Error deleteSection records file..\n");
        return;
    }

    // Create a temporary file to store the updated contents of filepath_records.txt
    FILE* temp_records_file = fopen("..\\..\\Proposal Program\\src\\main files\\temp_records.txt", "w");
    if (temp_records_file == NULL) {
        printf("Error creating temporary records file..\n");
        fclose(records_file);
        return;
    }

    // Copy all lines except the one to be deleted to the temporary file
    lineCount = 0;
    while (fgets(line, sizeof(line), records_file)) {
        lineCount++;

        // Skip the line if it matches the section number to be deleted
        if (lineCount == sectionNumber)
            continue;

        fputs(line, temp_records_file);
    }

    fclose(records_file);
    fclose(temp_records_file);

    // Remove the original filepath_records.txt file
    if (remove("..\\..\\Proposal Program\\src\\main files\\filepath_records.txt") != 0) {
        printf("Error deleting filepath_records.txt file..\n");
        displayMenu();
        return;
    }

    // Rename the temporary file to filepath_records.txt
    if (rename("..\\..\\Proposal Program\\src\\main files\\temp_records.txt", "..\\..\\Proposal Program\\src\\main files\\filepath_records.txt") != 0) {
        printf("Error renaming temporary records file..\n");
        displayMenu();
        return;
    }

    system("cls");
    printf("Section %d deleted successfully.\n", sectionNumber);
    displayMenu();
}





int displayMenu() {

    FILE* menu_file = fopen("..\\..\\Proposal Program\\src\\main files\\section_menu.csv", "r");
        if (menu_file == NULL) {
            printf("Error opening the section_menu.csv file in displayMenu.\n");
            return 1;
        }

    MENU menu_info[BODY_SIZE];
    int num_section = 0;

    // Skip the header line
    char header[100];
    fgets(header, sizeof(header), menu_file);

    char line[1024];
    while (fgets(line, sizeof(line), menu_file)) {
        if (num_section == BODY_SIZE) {
            printf("Maximum number of records reached..\n");
            break;
        }

        sscanf(line, "%[^,],%[^,],%*d,%*d,%[^\n]\n",
               menu_info[num_section].course_menu,
               menu_info[num_section].year_section,
               menu_info[num_section].status);

        num_section++;
    }

    fclose(menu_file);

    printf("\nNumber of Sections: %d\n", num_section);
    printLine('=', 59);
    printf("| |       COURSE       | YEAR AND LEVEL | NO. OF STUDENTS |\n");
    printLine('=', 59);

    FILE* txtFile = fopen("..\\..\\Proposal Program\\src\\main files\\filepath_records.txt", "r");
        if (txtFile == NULL) {
            printf("Error opening the filepath_records.txt file in displayMenu.\n");
            exit (1);
        }

    char file_path[PATH_SIZE];
    int section_count = 0;
    while (fgets(file_path, sizeof(file_path), txtFile)) {
        // Remove the trailing newline character
        file_path[strcspn(file_path, "\n")] = '\0';

        // Call countStudentsInSection
        int student_count = countStudentsInSection(file_path);
        menu_info[section_count].student_number = student_count;

        printf("|%d| %-19s|  %-14s| %-15d |\n",
               section_count + 1,
               menu_info[section_count].course_menu,
               menu_info[section_count].year_section,
               menu_info[section_count].student_number);

        section_count++;
    }

    fclose(txtFile);

    printLine('=', 59);

    return section_count;
}





void addSection(){
    char section_course[16];
    char section_year[8];
    char new_section_name[256];
    char file_section_records[PATH_SIZE];

    printf("What is the course code?\n");
    scanf("%15s", section_course);

    printf("What is the year and section?\n");
    scanf("%10s", section_year);

    snprintf(file_section_records, PATH_SIZE, "..\\\\..\\\\Proposal Program\\\\src\\\\main files\\\\%s_%s_StudentRecords.csv", section_course, section_year);


    FILE* store_file = fopen("..\\..\\Proposal Program\\src\\main files\\section_menu.csv", "a");
    FILE* writePATHrecords = fopen("..\\..\\Proposal Program\\src\\main files\\filepath_records.txt", "a");

        if (store_file == NULL || writePATHrecords == NULL) {
            printf("Error opening section_menu.csv or filepath_records.txt in addSection..");
            exit(1);
        }

    fprintf(store_file, "%s,%s,,,,,\n", section_course,section_year);
    fprintf(writePATHrecords,"%s\n", file_section_records);

    fclose(store_file);
    fclose(writePATHrecords);

    FILE *studentRecordsFile = fopen(file_section_records, "w");
        if (studentRecordsFile == NULL) {
            printf("Error opening %s in addSection...\n", file_section_records);
            exit(1);
        }

    // WRITE HEADRES FOR STUDENT RECORDS
    fprintf(studentRecordsFile, "Student No.,Last Name,First Name,Sex\n");

    fclose(studentRecordsFile);

    //Return to main()
    system("cls");
    printf("Files created successfully.\n");
    main();
}





const char* openSection(int sectionIndex) {
    static char filePath[256];  // Static buffer to store the file path

    FILE* file = fopen("..\\..\\Proposal Program\\src\\main files\\filepath_records.txt", "r");
        if (file == NULL) {
            printf("Error opening filepath_records.txt in openSection..\n");
            exit(1);
        }

    // Skips to the selected section index
    char line[256];
    for (int i = 0; i < sectionIndex; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Invalid section index in openSection...\n");
            fclose(file);
            return NULL;
        }
    }

    // Remove the newline character if present
    char* newlinePos = strchr(line, '\n');
    if (newlinePos != NULL) {
        *newlinePos = '\0';
    }

    fclose(file);
    strncpy(filePath, line, sizeof(filePath) - 1);
    filePath[sizeof(filePath) - 1] = '\0';  // Ensure null-termination

    return filePath;
}




void displayStudentRecord(int sectionIndex) {
    const char* filePath = openSection(sectionIndex);
        if (filePath != NULL) {
            // Use the file path to display the contents or perform other operations
            printf("File path: %s\n", filePath);
        } else {
            // Handle the case when the file path is not available
            printf("Error retrieving file path in displayStudentRecord..\n");
        };

    FILE* student_file = fopen(filePath, "r");
        if (student_file == NULL) {
            printf("Error opening file in displayStudentRecord..\n");
            exit(1);
        }

    STUDENT student_info[BODY_SIZE];
    int num_students = 0;

    // Skips the header line
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
    printLine('=', 52);
    printf("| |   STUDENT ID    |          NAME          | SEX | \n");
    printLine('=', 52);
    for (int i = 0; i < num_students; i++) {
        printf("|%d| %-16s| %s, %-15s |  %c  |\n",
               i + 1,
               student_info[i].student_id,
               student_info[i].last_name,
               student_info[i].first_name,
               student_info[i].sex);
    }
    printLine('=', 52);

}



void addStudentRecord(int sectionIndex){
    char id_student[ID_SIZE];
    char name_last[LAST_NAME];
    char name_first[FIRST_NAME];
    char sex_student;

    printf("What is the STUDENT ID?\n");
    scanf("%15s", id_student);
    getchar();

    printf("What is the LAST NAME of the student?\n");
    scanf("%15s", name_last);
    getchar();

    printf("What is the FIRST NAME of the student?\n");
    scanf("%15s", name_first);
    getchar();

    printf("What is the SEX of this student? ex. (M or F)?\n");
    scanf("%c", &sex_student);
    getchar();

    const char* appendRecordpath = openSection(sectionIndex);

    FILE* appendPATHrecords = fopen(appendRecordpath, "a");
        if (appendPATHrecords == NULL) {
            printf("Error appending file in addStudentRecord..\n");
            exit(1);
        }

    fprintf(appendPATHrecords, "%s,%s,%s,%c\n", id_student, name_last, name_first,sex_student);

    fclose(appendPATHrecords);

    system("cls");
    printf("Files created successfully.\n");
}


void createGradesheet(int sectionIndex){

    const char* filePath = openSection(sectionIndex);
    char filename[PATH_SIZE];
    char buffer[PATH_SIZE];
    FILE* fptr;
    FILE* file = fopen(filePath, "r");
        if (file == NULL) {
            printf("Error reading file in sectionIndex.\n");
            exit(1);
        }

    GRADESHEET gradesheets[BODY_SIZE];

    char line[BODY_SIZE];
    char student_id[ID_SIZE];
    char last_name[LAST_NAME];
    char first_name[FIRST_NAME];
    char sex;
    int num_passers = 0;
    int num_gradesheets = 0;
    bool validChoice = false;

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        // Use sscanf to extract the columns
        if (sscanf(line, "%[^,],%[^,],%[^,],%c", student_id, last_name, first_name, &sex) == 4)
            {
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
        main();
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
    printf("[2] Return to Menu\n");
    printf("Enter your choice: ");

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
                    system("cls");
                    main();
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
            }
        }
    }
}










