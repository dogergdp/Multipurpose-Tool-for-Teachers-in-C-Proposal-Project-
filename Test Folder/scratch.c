#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
const char* path_separator = "\\";
#else
const char* path_separator = "/";
#endif

void replace_spaces(char str[]) {
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

void create_new_file(const char* file_name, int file_extension) {
	const char* main_path = "Franz Docs";
    const char* personal_path = "Proposal Program";
    const char* subdirectory = "Your Files";
    const char* format;
    
    if (file_extension == 0){
    	format = ".csv";
	}
	else if(file_extension == 1){
		format = ".txt";
	}
	else {
		
	}
	
	char text[300];
    char file_with_path[300];
    snprintf(file_with_path, sizeof(file_with_path), "D:%s%s%s%s%s%s%s%s%s", path_separator, main_path, path_separator, personal_path, path_separator, subdirectory, path_separator, file_name, format);
    FILE* fptr = fopen(file_with_path, "w");

    if (fptr == NULL) {
        printf("Error Creating File!\n");
        exit(1);
    }
    fclose(fptr);

    printf("File '%s%s' created successfully.\n", file_name, format);
}

int main() {
    char file_name[100];
    int file_type;
    
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &file_type) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            fflush(stdin);
            continue;
        }
        
        if (file_type == 0 || file_type == 1) {
            break;
        }
        
        printf("Please choose a valid file format.\n");
    }
    fflush(stdin);
    
	printf("Please enter the file name: ");
	fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\n")] = '\0';
    
	replace_spaces(file_name);
    create_new_file(file_name, file_type);

    return 0;
}
