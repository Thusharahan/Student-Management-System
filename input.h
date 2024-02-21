#include <stdio.h>
#include <string.h>
#include <ctype.h> // For tolower()

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

// Function to convert a string to lowercase
void strToLower(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

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
            // printf("Input is an integer: %d\n", num);
            while(getchar() != '\n');
            return num;
        }
        // if (isdigit(input[0]) && input[1] == '.') {
        //     int num;
        //     sscanf(input, "%d", &num);
        //     return num;
        // }
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
        // printf("No matches found for the substring '%s'\n", input);
    } else {
        while(getchar() != '\n');
        return foundIndex+1;
        // printf("Substring '%s' found at index %d: %s\n", input, foundIndex, words[foundIndex]);
    }
    

    // return 0;
}