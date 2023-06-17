#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#ifdef _WIN32
const char* path_separator = "\\";
#else
const char* path_separator = "/";
#endif

void start_menu(){
	///
}

void return_menu(){
	system("cls");
	start_menu();
}

// creates new file
void create_new_file(const char* file_name) {
    const char* main_path = "D:%sFranz Docs%s", path_seperator,path_seperator;
    const char* personal_path = "Proposal Program";
    const char* subdirectory = "Your Files";

    char file_with_path[200];
    snprintf(file_with_path, sizeof(file_with_path), "%s%s%s%s%s.txt", personal_path, path_separator, subdirectory, path_separator, file_name);
    FILE* fptr = fopen(file_with_path, "w");

    if (fptr == NULL) {
        printf("Error Creating File!\n");
        exit(1);
    }
   
    fclose(fptr);

    printf("File '%s.txt' created successfully.\n", file_name);
}



void read_file (){
	const char* personal_path = "Proposal Program";
    const char* subdirectory = "Your Files";
    char file_with_path[200];
    snprintf(file_with_path, sizeof(file_with_path), "%s%s%s%s%s.txt", personal_path, path_separator, subdirectory, path_separator, file_name);
    
	FILE* fptr = fopen(file_with_path, "w");
}






// creates new file
void create_new_file(const char* file_name) {
    const char* main_path = "D:%sFranz Docs%s", path_seperator,path_seperator;
    const char* personal_path = "Proposal Program";
    const char* subdirectory = "Your Files";

    char file_with_path[200];
    snprintf(file_with_path, sizeof(file_with_path), "%s%s%s%s%s.txt", personal_path, path_separator, subdirectory, path_separator, file_name);
    FILE* fptr = fopen(file_with_path, "w");

    if (fptr == NULL) {
        printf("Error Creating File!\n");
        exit(1);
    }
   
    fclose(fptr);

    printf("File '%s.txt' created successfully.\n", file_name);
}

void navigation(){
    int user_input;
    scanf("", &input_user);
    switch (input_user){
        case 1: ; 
        break;
        case 2: ; 
        break;
        default: 
        printf("Please enter a valid navigation number..");
        break;
    }
}


void read_file (){
	const char* personal_path = "Proposal Program";
    const char* subdirectory = "Your Files";

    char file_with_path[200];
    snprintf(file_with_path, sizeof(file_with_path), "%s%s%s%s%s.txt", personal_path, path_separator, subdirectory, path_separator, file_name);
    
    FILE* fptr = fopen(file_with_path, "r");
    
    if (fptr == NULL) {
        printf("Error Reading File!\n");
        exit(1);
    }

}
 
