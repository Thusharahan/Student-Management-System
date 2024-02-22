#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "SpecialFunct.h"
#include "Data_Base.h"
#include "StudentH.h"
#include "ModuleH.h"
#include "DepartmentH.h"
#include "CourseH.h"
#include "LectureH.h"

#define MAX_LENGTH 50
#define MAX_USERS 5

// Structure to hold user credentials
typedef struct {
    char userId[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

// Array to store user credentials
User users[MAX_USERS] = {
    {"Admin_1", "password1"},
    {"Admin_2", "password2"},
    {"Admin_3", "password3"},
    {"Admin_4", "password4"},
    {"Admin_5", "password5"}
};

// Function to check if the entered user ID and password are valid
int validateCredentials(char *userId, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].userId, userId) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Credentials are valid
        }
    }
    return 0; // Credentials are invalid
}

int main(){
    int choice;

    char *MainMenu[] = {
        "Departments",
        "Courses",
        "Modules",
        "Lectures",
        "Students",
        "Exit"
    };

    char userID[] = "Admin";
    // char userID[MAX_LENGTH];
    char password[MAX_LENGTH];

    // while (1)
    // {
    //     printf("---------------------------------------------------------------\n");
    //     printf("           \033[1mWELCOME TO STUDENTS MANAGEMENT SYSTEM!\033[0m\n");
    //     printf("---------------------------------------------------------------\n\n");

    //     printf("Enter your user ID: ");
    //     scanf("%s", userID);

    //     printf("Enter your password: ");
    //     scanf("%s", password);

    //     // Check if the entered user ID and password are valid
    //     if (validateCredentials(userID, password)) {
    //         printf("Welcome, %s! You have successfully logged in.\n\n", userID);
    //         // const char USER_ID[] = userID;
    //         break;
    //         // Place your program logic here after successful login
    //     } else {
    //         printf("Invalid user ID or password. Access denied.\n");
    //     }   
        
    // }

    while(1){
        printf("---------------------------------------------------------------\n");
        printf("                 \033[1mSTUDENT MANAGEMENT SYSTEM\033[0m\n");
        printf("---------------------------------------------------------------\n\n");
        printf("Available fields of student management system.\n\n");
        printf("1. Department\n2. Courses\n3. Modules\n4. Lectures\n5. Students \n6. Exit\n");
        printf("Choose any fields you want to work with: ");
        choice = getInput(MainMenu ,5);

        switch(choice){
            case 1:
                Department_main(userID);
                break;
            case 2:
                Course_main(userID);
                break;
            case 3:
                Module_main(userID);
                break;
            case 4:
                Lecture_main(userID);
                break;
            case 5:
                Student_main(userID);
                break;
            case 6:
                printf("Exiting programme.\nThank you. \n");
                return 0;
            default:
                printf("Invalid choise. Please try again.\n\n\n");
                continue;

        }   
    }

    return 0;
}
