// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <time.h>
// #include <ctype.h>
// #include"Data_Base.h"

// #define MAX_COURSES 100
// #define MAX_MODULES 3
// #define MAX_DEPARTMENTS 3

 #define MAX_HISTORY_ENTRIES 100


typedef struct {
    time_t timestamp;
    char userId[10];
    char entity[20];
    char action[10];
    char newValue[50];
    char oldValue[50];
    char editedCourseId[10]; 
} HistoryEntryCourse;


HistoryEntryCourse Course_history[MAX_HISTORY_ENTRIES];
int historyIndexCourse = 0;

// Global variables
int numCourses = 6;
// char currentUserId[10] = "1"; // Assume a default user ID for now

// Function prototypes

void createCourse(char *User_ID);
void readCourse();
void readSpecificCourse();
void readAllCourses();
void editCourse(char *User_ID);
void deleteCourse(char *User_ID);
void addHistoryEntry(const char *userId, const char *entity, const char *action, const char *newValue, const char *oldValue, const char *editedCourseId);
void reviewHistory();
bool isValidNameCourse(char *input) {
    // Iterate through each character in the input string
    for (int i = 0; input[i] != '\0'; i++) {
        // Check if the character is not a letter, number, or space
        if (!isalnum(input[i]) && !isspace(input[i])) {
            return false; // Return false if a special character is found
        }
    }
    return true; // Return true if the input contains only valid characters
}
bool isValidDeptID(const char *input) {
    // Check if the string length is 2
    if (strlen(input) != 2) {
        return false;
    }

    // Check if both characters are capital letters
    if (!isupper(input[0]) || !isupper(input[1])) {
        return false;
    }

    return true;
}
int isValidFormat(const char *input) {
    // Check if the string length is 5
    if (strlen(input) != 5) {
        return 0;
    }

    // Check if the first two characters are capital letters
    if (!isupper(input[0]) || !isupper(input[1])) {
        return 0;
    }

    // Check if the third character is '_'
    if (input[2] != '_') {
        return 0;
    }

    // Check if the last two characters are digits
    if (!isdigit(input[3]) || !isdigit(input[4])) {
        return 0;
    }

    // If all conditions are met, return 1 (true)
    return 1;
}


int isValidID_2( char* id, char prefix[]) {

    if(id[0] != prefix[0] || id[1] != '_'){
        return 0;
    }
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) {
            return 0; // Not a digit
        }
    }
    return 1;
}
void Course_main(char *User_ID) {

    int choice;
    do {
        printf("\n--------------------------------------------\n");
        printf("      STUDENT MANAGEMENT SYSTEM - COURSE        ");
        printf("\n--------------------------------------------\n");
        printf("1. Create Course\n");
        printf("2. view Course\n");
        printf("3. Edit Course\n");
        printf("4. Delete Course\n");
        printf("5. Review History\n");
        printf("6. Exit\n");
        printf("\n   Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                createCourse(User_ID);
                break;
            case 2:
                readCourse();
                break;
            case 3:
                editCourse(User_ID);
                break;
            case 4:
                deleteCourse(User_ID);
                break;
            case 5:
                reviewHistory();
                break;
            case 6:
                printf("Exiting to main menu. Thank You!\n");
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while(choice != 6);
}

void createCourse(char *User_ID) {
    
    // Check if maximum courses limit has been reached
    if (numCourses >= MAX_CORS) {
        printf("Cannot create more courses. Maximum limit reached.\n");
        return;
    }

    Course newCourse;

    char tempId[MAX_ID_LEN];
    bool validInput = false;
    input_departmentId:
    do {
        bool departmentExists = false;
        printf("\nAvailable departments are:\n ");
        int k = sizeof(departments->Dept_ID) / sizeof(departments[0].Dept_ID);
        
for (int i = 0; i < k+1; ++i) {
    // Check if the department name is not empty
     {
        printf("For %s type '%s'\n", departments[i].Dept_Name, departments[i].Dept_ID);
    }
}
       printf("\nEnter department ID: ");
        scanf("%s", newCourse.departmentId);
        
        if(isValidDeptID(newCourse.departmentId))
          {goto label_2;}
          else {printf("\nInput is invalid....!\n\n");
          printf("Do you want to contnue?\n(y - for yes/n - for no): :");
                 char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_departmentId;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
                 else {printf("\nInvalid input....!\n(y - for yes/n - for no): ");}
                 }
        
        // Check if department ID exists
        label_2:
        for (int i = 0; i < MAX_DEPT; ++i) {
            if (strcmp(newCourse.departmentId, departments[i].Dept_ID) == 0) {
                departmentExists = true;
                break;
            }
        }
        if (!departmentExists) {
            printf("\nDepartment ID does not exist...! Please enter a valid department ID.\n\n");
            printf("Do you want to continue?\n(y - for yes/n - for no): ");
                 char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_departmentId;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
        } else {
            validInput = true;
        }
        
    } while (!validInput);

         label_4:
        printf(" \nEnter course name: ");
        scanf("%s", newCourse.name);
        if(!isValidNameCourse(newCourse.name))
        {char choice_1;
          printf("\n");
          printf("Name should not have any special charecters...!\n");
          printf("\n");
          printf("Do you want to continue?\n(y - for yes/n - for no):  ");
           label_5:
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  label_4;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
                 else {printf("\nInvalid input....\n(y - for yes/n - for no):  ");
                 goto label_5;
                 }
        }
        

       
    input_courseid:// label creted for jump
    do {
        bool validInput = false;
        printf("\nEnter course ID: (ID Shouls be in this format:AB_XX): ");
        scanf("%s", newCourse.id);
        
        

    
        if(isValidFormat(newCourse.id))/// validation for course id
          {goto label_1;}
          else {printf("\nInput is invalid.....!\n");
          printf("\nDo you want to continue?\n(y - for yes/n - for no): ");
                 char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_courseid;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
                 }
     

        // Check if course ID already exists
        label_1:
        for (int i = 0; i < numCourses; ++i) {
            if (strcmp(newCourse.id, courses[i].id) == 0) {
                printf("\nCourse ID already exists...! Please enter a different ID.\n");
                printf("Do you want to continue?\n(y - for yes/n - for no): : ");
                 char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_courseid;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
            } else {
                validInput = true;
            }
        }
    } while (!validInput);


    input_inchargeLecturertId:/// label for get back lecture id
    do {
          bool lecturerExists = false;
        printf("\nEnter in-charge lecturer ID(L_XXX): ");
        scanf("%s", tempId);
        char pre[1]="L";

        if(isValidID_2(tempId,pre))/// validation for lecture id
          {goto label_3;}
          else {printf("\nInput is invalid....!\n");
          printf("Do you want to continue?\n(y - for yes/n - for no): ");
                 char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_inchargeLecturertId;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
                 }

        // Check if in-charge lecturer ID exists
        label_3:
        for (int i = 0; i < MAX_LEC; ++i) {
            if (strcmp(tempId, lecturers[i].id) == 0) {
                lecturerExists = true;
                break;
            }
        }
        if (!lecturerExists) {
            printf("In-charge lecturer ID does not exist. Please enter a valid ID.\n");
             printf("Do you want to continue?\n(y - for yes/n - for no): ");
                char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {goto  input_inchargeLecturertId;}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
        } else {
            validInput = true;
        }
    } while (!validInput);

    // Set course active
    newCourse.active = true;

    // Add the new course to the courses array
    courses[numCourses++] = newCourse;

    // Update history
    addHistoryEntry(User_ID, "course", "create", " ", newCourse.name, newCourse.id);

    printf("\nCourse created successfully....1\n");

    // Ask if user wants to continue or return to the previous menu
    char choice;
    printf("Do you want to continue editing?\n(y - for yes/n - for no): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        createCourse(User_ID); // Recursively call createCourse() to re-enter the input
    }
}



void readSpecificCourse(void (*previousMenu)()) {
    char courseId[10];
    printf("\nEnter the course ID (AB_XX) : ");
    scanf("%s", courseId);
     
    bool found = false;
    for (int i = 0; i < numCourses; ++i) {
        if (strcmp(courses[i].id, courseId) == 0 && courses[i].active) {
            found = true;
            printf("\nCourse Name: %s\n", courses[i].name);
            printf("Course ID: %s\n", courses[i].id);
           for (int j = 0; j < MAX_DEPT; ++j) {
                if (strcmp(departments[j].Dept_ID, courses[i].departmentId) == 0 && departments[j].active) {
                    printf("Department Name: %s\n", departments[j].Dept_Name);
                }
            }
           for (int j = 0; j < MAX_LEC; ++j) {
                if (strcmp(lecturers[j].id, courses[i].inChargeLecturerId) == 0 && lecturers[j].active) {
                    printf("In-Charge lecturer Name: %s\n", lecturers[j].name);
                }
            }
            printf("\nModules:\n");
            printf("----------------------------------------------------\n");
            printf("| %-15s | %-30s |\n", "Module ID", "Module Name");
            printf("----------------------------------------------------\n");
            for (int j = 0; j < MAX_MOD; ++j) {
                if (strcmp(modules[j].course_id, courses[i].id) == 0 && modules[j].active) {
                    printf("| %-15s | %-30s |\n", modules[j].module_id, modules[j].module_name);
                }
            }
            printf("-------------------------------------------------------------\n");
            printf("\n");
            break;
        }
    }

    if (!found) {
        printf("\nCourse not found or inactive....!\n");
       printf("\nDo you want to review history?\n(y - for yes/n - for no): ");
                char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') 
                  {reviewHistory();}
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
    }

    int option2;
    printf("Choose the NUMBER of required option:\n");
    printf("1. View another course\n");
    printf("2. Return to menu\n\n");
    printf("Enter your choice: ");
    scanf("%d", &option2);
    if (option2 == 2) {
        // Return to the previous menu
        previousMenu();
    } else if (option2 == 1) {
        readSpecificCourse(previousMenu); // Call the function recursively
    }
}
void readAllCourses(void (*previousMenu)()) {
    printf("\n\n");
    printf("\033[1m\033[4m"); // Bold and underline
    printf("All Courses:\n");
    printf("\033[0m"); // Reset formatting

    for (int i = 0; i < numCourses; ++i) {
        if (courses[i].active) {
            printf("\n\n");
            printf("Course Name: %s\n", courses[i].name);
            printf("Course ID: %s\n", courses[i].id);
            for(int j=0;j<MAX_DEPT;++j){
               if(strcmp(courses[i].departmentId,departments[j].Dept_ID)==0 && departments[i].active) {
                printf("Department name: %s\n", departments[j].Dept_Name);
                break;}
                else if(strcmp(courses[i].departmentId,departments[j].Dept_ID)==0 && !departments[i].active) {
                printf("Department name: Not Available/n ");
                break;}
            }
            
            for(int j=0;j<MAX_LEC;++j){
               if(strcmp(courses[i].inChargeLecturerId,lecturers[j].id==0 && lecturers[i].active)) {
                printf("In-Charge lecturer name: %s\n", lecturers[j].name);
                break;}
                if(strcmp(courses[i].inChargeLecturerId,lecturers[j].id==0 && !lecturers[i].active)) {
                printf("In-Charge lecturer name: Not available \n ");
                break;}
            }
            printf("\nModules:\n");
            printf("----------------------------------------------------\n");
            printf("| %-15s | %-30s |\n", "Module ID", "Module Name");
            printf("----------------------------------------------------\n");
            for (int j = 0; j < MAX_MOD; ++j) {
                if (strcmp(modules[j].course_id, courses[i].id) == 0 && modules[j].active) {
                    printf("| %-15s | %-30s |\n", modules[j].module_id, modules[j].module_name);
                }
            }
            printf("-------------------------------------------------------------\n");
        }
    }

    int option1;
    printf("\nChoose an option:\n");
    printf("1. Return to menu\n");
    printf("2. View specific course details\n");
    printf("Enter your choice: ");
    scanf("%d", &option1);
    if (option1 == 1) {
        // Return to the previous menu
        previousMenu();
    } else if (option1 == 2) {
        readSpecificCourse(previousMenu); // Call the function recursively
    }
}



void readCourse() {
    int viewOption;
    printf("Choose an option:\n\n");
    printf("1. View all courses\n");
    printf("2. View specific course\n");
    printf("3. Return to Main menu\n\n");
    printf("Enter the number of your choice: ");
    scanf("%d", &viewOption);

    if (viewOption == 1) {
        // Call readAllCourse() and pass readCourse() as the previous menu
        readAllCourses(readCourse);
    } else if (viewOption == 2) {
        // Call readSpecificCourse() and pass readCourse() as the previous menu
        readSpecificCourse(readCourse);
    } else if(viewOption == 3) {
        // Return if the user chooses option 3
        return;
    }
    else{
           printf("Invalid input.....!\n");
    }
}

void editCourse(char *User_ID) {
    char courseId[10];
    printf("\nEnter the course ID to edit: ");
    scanf("%s", courseId);
    if (!isValidFormat(courseId)) {
        printf("\nInput is invalid....!\n");
        printf("Do you want to continue?\n(y - for yes/n - for no): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
            editCourse(User_ID);
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return;
        }
    }

    bool found = false;
    for (int i = 0; i < numCourses; ++i) {
        if (strcmp(courses[i].id, courseId) == 0 && courses[i].active) {
            found = true;
            int choice;
            printf("\n\n");
            printf("Select field to edit:\n\n");
            printf("1. Course Name\n");
            printf("2. Department ID\n");
            printf("3. In-charge Lecturer ID\n");
            printf("\nEnter the number of  your choice: ");
            scanf("%d", &choice);
            getchar();

            // Variable to store old value before editing
            char oldValue[50];
            switch (choice) {
                case 1:
                    // Save old value
                    strcpy(oldValue, courses[i].name);
                    printf("\nCurrent name: %s\n", oldValue);
                    printf("Enter new course name: ");
                    scanf("%s", courses[i].name);
                    if (!isValidNameCourse(courses[i].name)) {
                        printf("\nName should not have any special characters....!\n");
                        label_10:
                        printf("Do you want to continue?\n(y - for yes/n - for no): ");
                        char choice_2;
                        scanf(" %c", &choice_2);
                        if (choice_2 == 'y' || choice_2 == 'Y') {
                            editCourse(User_ID);
                        } else if (choice_2 == 'n' || choice_2 == 'N') {
                            return;
                        }
                        else{printf("In Valid input.....!");
                            goto label_10;}
                    }
                    addHistoryEntry(User_ID, "cour_name", "edit", courses[i].name, oldValue, courseId);
                    break;

                case 2:
                    // Save old value
                    strcpy(oldValue, courses[i].departmentId);
                    char tempDeptId[10]; 
                    bool departmentExists = false;
                    do {
                        printf("Current department ID: %s\n\n", oldValue);
                        printf("Enter new department ID: ");
                        scanf("%s", tempDeptId);

                        // Check if department ID exists
                        for (int j = 0; j < MAX_DEPT; ++j) {
                            if (strcmp(tempDeptId, departments[j].Dept_ID) == 0) {
                                departmentExists = true;
                                strcpy(courses[i].departmentId, tempDeptId); // Copy temp value to courses array
                                addHistoryEntry(User_ID, "Dept_ID", "edit", courses[i].departmentId, oldValue, courseId);
                                break;
                            }
                        }
                        if (!departmentExists) {
                            printf("Department ID does not exist...! Please enter a valid department ID.\n\n");
                            printf("Do you want to continue editing?\n(y - for yes/n - for no): ");
                            char choice;
                            scanf(" %c", &choice);
                            if (choice == 'n' || choice == 'N') {
                                break; // Return to the previous menu
                            }
                        }
                    } while (!departmentExists);
                    break;

                case 3:
                    // Save old value
                    strcpy(oldValue, courses[i].inChargeLecturerId);
                    char tempinLecId[10]; 
                    bool LecturerExists = false;
                    do {
                        printf("\nCurrent in-charge Lecturer ID: %s\n\n", oldValue);
                        printf("Enter new in-charge Lecturer ID: ");
                        scanf("%s", tempinLecId);

                        // Check if lecturer ID exists
                        for (int j = 0; j < MAX_LEC; ++j) {
                            if (strcmp(tempinLecId, lecturers[j].id) == 0) {
                                LecturerExists = true;
                                strcpy(courses[i].inChargeLecturerId, tempinLecId); // Copy temp value to courses array
                                addHistoryEntry(User_ID, "Incharge_Lec_ID", "edit", courses[i].inChargeLecturerId, oldValue, courseId);
                                break;
                            }
                        }
                        if (!LecturerExists) {
                            printf("Lecturer ID does not exist....! Please enter a valid Lecturer ID.\n\n");
                            printf("Do you want to continue editing?\n(y - for yes/n - for no): ");
                            char choice;
                            scanf(" %c", &choice);
                            if (choice == 'n' || choice == 'N') {
                                break; // Return to the previous menu
                            }
                        }
                    } while (!LecturerExists);
                    break;
            }
        }
    }

    if (!found) {
        printf("\nCourse not found or inactive...!\n");
    }

    // Ask for further action
    int furtherAction;
    printf("\n1. Edit another course\n");
    printf("2. Main menu\n\n");
    printf("\nEnter your choice: ");
    scanf("%d", &furtherAction);

    if (furtherAction == 1) {
        editCourse(User_ID);
    }
}


void deleteCourse(char *User_ID) {
    char courseId[10];
    printf("\nEnter the course ID to delete: ");
    scanf("%s", courseId);

    bool found = false;
    for (int i = 0; i < numCourses; ++i) {
        if (strcmp(courses[i].id, courseId) == 0 && courses[i].active) {
            found = true;
            printf("\nDo you want to delete %s in %s?", courses[i].name, departments[i].Dept_Name );
            printf("\n(y - for yes/n - for no): ");
            char choice;
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                // Set course as inactive
                courses[i].active = false;
                
                // Disable modules associated with the deleted course
                for (int j = 0; j < MAX_MOD; ++j) {
                    if (strcmp(modules[j].course_id, courses[i].id) == 0 && modules[j].active) {
                        modules[j].active = false;
                    }
                }
                
                // Update history
                addHistoryEntry(User_ID, "course", "delete", "", courses[i].name, courseId);
                printf("\nCourse deleted successfully....!\n");
            } else if (choice == 'n' || choice == 'N') {
                printf("\nDeletion cancelled.....!\n");
            } else {
                printf("Invalid choice.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\nNot found or already inactive.\n\n");
    }

    // Ask for further action
    char furtherAction;
    printf("\nDo you want to delete another course?\n(y - for yes/n - for no): " );
    scanf(" %c", &furtherAction);
    if (furtherAction == 'y' || furtherAction == 'Y') {
        deleteCourse(User_ID);
    }
}


void addHistoryEntry(const char *userId, const char *entity, const char *action, const char *newValue, const char *oldValue, const char *editedCourseId) {
    if (historyIndexCourse < MAX_HISTORY_ENTRIES) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        strcpy(Course_history[historyIndexCourse].userId, userId);
        strcpy(Course_history[historyIndexCourse].entity, entity);
        strcpy(Course_history[historyIndexCourse].action, action);
        strcpy(Course_history[historyIndexCourse].newValue, newValue);
        strcpy(Course_history[historyIndexCourse].oldValue, oldValue);
        strcpy(Course_history[historyIndexCourse].editedCourseId, editedCourseId);
        Course_history[historyIndexCourse].timestamp = now; // Store the time_t value

        historyIndexCourse++;
    } else {
        printf("History entries limit reached. Cannot add more entries.\n");
    }
}

void reviewHistory() {
    printf("History Table:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| Time                 | User ID | Entity    | EditedCourseID | Action | New Value | Old Value |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    char timestamp[20]; // Buffer to store formatted timestamp

    for (int i = 0; i < historyIndexCourse; ++i) {
        struct tm *tm_info = localtime(&Course_history[i].timestamp);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("| %-20s | %-7s | %-9s | %-14s | %-6s | %-9s | %-9s |\n", timestamp, 
               Course_history[i].userId, Course_history[i].entity, Course_history[i].editedCourseId, Course_history[i].action, 
               Course_history[i].newValue, Course_history[i].oldValue);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
}