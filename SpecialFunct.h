// #include <stdio.h>
// #include <string.h>
// #include <ctype.h> // For tolower()
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
// #include "SpecialFunct.h"
#include "Data_Base.h"
#include "StudentH.h"
#include "ModuleH.h"
#include "DepartmentH.h"
#include "CourseH.h"
#include "LectureH.h"

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

// Function to convert a string to lowercase
void strToLower(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

// int checkYesNO();

int getInput(char *words[], int numWords) {
    char input[MAX_WORD_LENGTH];
    if (scanf("%s", input) == 1) {
        // Check if the input is an integer
        int isInteger = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                isInteger = 0;
                break;
            }
        }
        if (isInteger) {
            // Output the integer
            int num;
            sscanf(input, "%d", &num);
            while(getchar() != '\n');
            return num;
        }
    }

    // Convert input string to lowercase
    strToLower(input);

    // Search for the substring in the array (case-insensitive)
    int foundIndex = -1; // Initialize to -1 (not found)
    for (int i = 0; i < numWords; i++) {
        char temp[MAX_WORD_LENGTH];
        strcpy(temp, words[i]);
        strToLower(temp);
        if (strstr(temp, input) != NULL) {
            foundIndex = i;
            break; // Stop searching once found
        }
    }

    // Output the result
    if (foundIndex == -1) {
        while(getchar() != '\n');
        return -1;
    } else {
        while(getchar() != '\n');
        return foundIndex+1;
    }
    
}

void addFunctions(int n, char *User_ID){
    switch (n)
    {
    case 1:
        // add_department();
        printf("\nDo you want to add courses for the department?\n(y - for yes/n - for no): ");
        int choice = checkYesNo();
        if(choice == 1){
            addFunctions(2, User_ID);
        } else{
            break;
        }
    case 2:
        createCourse(User_ID);
        printf("\nDo you want to create modules for the course?\n(y - for yes/n - for no): ");
        int choice1 = checkYesNo();
        if(choice1 == 1){
            addFunctions(3, User_ID);
        } else{
            break;
        }
    case 3:
        createModule(User_ID);
        break;

    default:
        break;
    }
}