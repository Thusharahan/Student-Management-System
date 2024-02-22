// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <ctype.h>
// #include <time.h>
// #include "Data_Base.h"


#define MAX_HISTORY_ENTRIES 100

// Define structures

typedef struct {
    time_t timestamp;
    char userId[10];
    char entity[20];
    char action[10];
    char newValue[50];
    char oldValue[50];
    char editedModuleId[10]; 
} HistoryEntryModule;

// Global arrays to hold data

HistoryEntryModule history[MAX_HISTORY_ENTRIES];
int historyIndexModule = 0;
int numModules = 20;

// Global variables
int numCourses1 = 6;
// char currentUserId[10] = "1"; // Assume a default user ID for now

// Function prototypes

void createModule(char *User_ID);
void readModule();
void editModule(char *User_ID);
void deleteModule(char *User_ID);
void addModuleHistoryEntry(const char *userId, const char *entity, const char *action, const char *newValue, const char *oldValue, const char *editedCourseId);
void reviewHistoryModule();
void search_modules();
int get_lecture(int n);
int get_course(int n);

//main module
void Module_main(char *User_ID) {
    int choice;
    do {
        printf("\n--------------------------------------------\n");
        printf("      STUDENT MANAGEMENT SYSTEM - MODULE        ");
        printf("\n--------------------------------------------\n");
        printf("1. Create Module\n");
        printf("2. View Module\n");
        printf("3. Edit Module\n");
        printf("4. Delete Module\n");
        printf("5. View History\n");
        printf("6. Exit\n");
        printf("Enter your choice number: ");
        
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                createModule(User_ID);
                break;
            case 2:
                readModule();
                break;
            case 3:
                editModule(User_ID);
                break;
            case 4:
                deleteModule(User_ID);
                break;
            case 5:
                reviewHistoryModule();
                break;
            case 6:
                printf("Exiting to main menu. Thank You!\n");
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6:\n");
                break;
        }
    } while(1);
}

// Function to check if the ID has the correct format
int isValidModuleID(const char* id, const char* course_id) {
    // Check if the ID has the correct length
    if (strlen(id) != 7) {
        return 0;
    }

    // Check if the first 5 characters match the course ID
    if (strncmp(id, course_id, 5) != 0) {
        return 0;
    }

    // Check if the last two characters are digits between 01 and 99
    if (!isdigit(id[5]) || !isdigit(id[6])) {
        return 0; // Not a digit
    }

    int lastTwoDigits = (id[5] - '0') * 10 + (id[6] - '0');
    if (lastTwoDigits < 1 || lastTwoDigits > 99) {
        return 0; // Not between 01 and 99
    }

    return 1; // ID is valid
}

void createModule(char *User_ID) {
    if (numModules >= MAX_MOD) {
        printf("Cannot create more modules. Maximum limit reached.\n");
        return;
    }

    Module newModule;
    bool validInput = false;

    input_courseid:
    printf("Enter course ID (eg: EN_01): ");
    scanf("%9s", newModule.course_id);

    // Check if the course ID exists
    validInput = false; // Reset validInput flag before checking
    // Assume numCourses1 is defined and contains the number of available courses
    for (int i = 0; i < numCourses1; ++i) {
        if (strcmp(newModule.course_id, courses[i].id) == 0) {
            validInput = true;
            break;
        }
    }
    if (!validInput) {
        printf("Error: Course ID does not exist. Please enter a valid ID.\n");
        printf("Do you want to create a new course?\n(y - for yes/n - for no/ c - for try again): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
            // createCourse(User_ID);
            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
            getchar();
            goto input_courseid;
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return;
        } else if (choice_1 == 'c' || choice_1 == 'C'){
            getchar();
            goto input_courseid; // Prompt user to input module ID again
        }else {
            printf("Invalid input. Try again...\n");
            getchar();
            goto input_courseid;
        }
    }

    input_moduleid:
    printf("Enter module ID (eg: EN_0101): ");
    scanf("%9s", newModule.module_id);

    // Check if the module ID has the correct format
    if (!isValidModuleID(newModule.module_id, newModule.course_id)) {
        printf("Error: Module ID should have the format %sXX where XX are two digits.\n", newModule.course_id);
        printf("Do you want to continue?\n(y - for yes/n - for no): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
            getchar();
            goto input_moduleid;
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return;
        } else {
            printf("Invalid input. Try again...\n");
            getchar();
            goto input_moduleid;
        }
    }

    // Check if the module ID already exists
    validInput = false; // Reset validInput flag before checking
    for (int i = 0; i < numModules; ++i) {
        if (strcmp(newModule.module_id, modules[i].module_id) == 0 && courses[i].active) {
            validInput = true;
            break;
        }
    }
    if (validInput) {
        printf("Error: Module ID already exists. Please enter a different ID.\n");
        printf("Do you want to continue?\n(y - for yes/n - for no): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
            getchar();
            goto input_moduleid;
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return;
        } else {
            printf("Invalid input. Try again...\n");
            getchar();
            goto input_moduleid;
        }
    }

    printf("Enter module name: ");
    scanf("%49s", newModule.module_name);
    printf("Enter module description: ");
    scanf("%99s", newModule.module_description);

    input_lecturerid:
    printf("Enter lecturer ID (eg: L_001): ");
    scanf("%9s", newModule.lecturer_id);

    // Check if the lecturer ID exists
    validInput = false; // Reset validInput flag before checking
    for (int i = 0; i < numModules; ++i) {
        if (strcmp(newModule.lecturer_id, modules[i].lecturer_id) == 0 && lecturers[i].active) {
            validInput = true;
            break;
        }
    }
    if (!validInput) {
        printf("Error: Lecturer ID does not exist. Please enter a valid ID.\n");
        printf("Do you want to add a new lecturer id?\n(y - for yes/n - for no/ c - for try again): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
            getchar();
            // createLecturer(User_ID);
            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
            goto input_lecturerid;
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return;
        }else if (choice_1 == 'c' || choice_1 == 'C'){
            getchar();
            goto input_lecturerid; // Prompt user to input module ID again
        }else {
            printf("Invalid input. Try again...\n");
            getchar();
            goto input_lecturerid;
        }
    }

    newModule.active = true;
    modules[numModules++] = newModule;
    addModuleHistoryEntry(User_ID, "module", "create", newModule.module_name, "", newModule.module_id);
    printf("Module created successfully...\n\n");

    int furtherAction;
    printf("1. Add another module\n");
    printf("2. Main menu\n");
    printf("Enter your choice number: ");
    scanf("%d", &furtherAction);
    getchar();
    if (furtherAction == 1) {
        createModule(User_ID);
    }
}

// Define the search_modules function outside of readModule
    void search_modules() {
    char moduleid[10];
    printf("Enter the module ID (eg: EN_0101) : ");
    scanf("%s", moduleid);
     
    bool found = false;
    for (int i = 0; i < numModules; ++i) {
        if (strcmp(modules[i].module_id, moduleid) == 0 && modules[i].active && courses[i].active) {
            found = true;
            printf("Module ID: %s\n", modules[i].module_id);
            printf("Module Name: %s\n", modules[i].module_name);
            printf("Module Description: %s\n", modules[i].module_description);
           for (int j = 0; j < MAX_LEC; ++j) {
                if (strcmp(lecturers[j].id, modules[i].lecturer_id) == 0 && lecturers[j].active) {
                    printf("Assigned lecturer Name: %s\n", lecturers[j].name);
                }
            }
            printf("\n");
            break;
        }
    }

    if (!found) {
        printf("Module not found or inactive.\n");
       printf("Do you want to review history?\n(y - for yes/n - for no): ");
                char choice_1;
                 scanf(" %c", &choice_1);
                 if (choice_1 == 'y' || choice_1 == 'Y') {
                  reviewHistoryModule();
                  }
                 else if(choice_1 == 'n' || choice_1 == 'N') 
                 {return;}
    }

    int option2;
    printf("Choose an option:\n");
    printf("1. View another Module\n");
    printf("2. Return to menu\n\n");
    printf("Enter your choice number: ");
    scanf("%d", &option2);
    if (option2 == 2) {
        // Return to the previous menu
        return;
    } else if (option2 == 1) {
        search_modules(); // Call the function recursively
    }
}

// Modify readModule function to call search_modules if option 2 is chosen
void readModule() {
    int option;
    printf("Choose an option\n");
    printf("1. View specific module details\n");
    printf("2. View all modules details\n");
    printf("3. Return to menu\n");
    printf("Enter your choice number: ");

    scanf("%d", &option);
    getchar();

    if (option == 3) {
        return;
    } else if (option == 1) {
        search_modules(readModule);; // Call search_modules function
    } else if (option == 2){
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-12s | %-12s | %-40s | %-50s | %-15s |\n", "Module ID", "Course ID", "Module Name", "Description", "Lecturer Name");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < numModules; ++i) {
            if (modules[i].active) {
                int lec = get_lecture(i) - 1;
                int cou = get_course(i) - 1;

                // If both lecture and course are deleted
                if (get_lecture(i) == 0 && get_course(i) == 0) {
                    printf("| %-12s | %-12s | %-40s | %-50s | %-15s |\n", modules[i].module_id, "N/A" , modules[i].module_name, modules[i].module_description,"N/A") ;
                }
                // If lecture is deleted
                else if (get_lecture(i) == 0) {
                    printf("| %-12s | %-12s | %-40s | %-50s | %-15s |\n", modules[i].module_id, modules[i].course_id, modules[i].module_name, modules[i].module_description,"N/A");
                }
                // If course is deleted
                else if (get_course(i) == 0) {
                    printf("| %-12s | %-12s | %-40s | %-50s | %-15s |\n", modules[i].module_id,"N/A", modules[i].module_name, modules[i].module_description, lecturers[lec].name);
                }
                // If both lecture and course are available
                else {
                    printf("| %-12s | %-12s | %-40s | %-50s | %-15s |\n", modules[i].module_id, modules[i].course_id, modules[i].module_name, modules[i].module_description, lecturers[lec].name);
                }
            }
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    } else {
        printf("Invalid input!\n");
        readModule();
    }
}

int get_lecture(int n) {
    for (int i = 0; i < MAX_LEC; i++) {
        if (strcmp(modules[n].lecturer_id, lecturers[i].id) == 0 && lecturers[i].active) {
            return i + 1;
        }
    }
    return 0;  // If no active lecturer is found for the module
}

int get_course(int n) {
    for (int i = 0; i < MAX_CORS; i++) {
        if (strcmp(modules[n].course_id, courses[i].id) == 0 && courses[i].active) {
            return i + 1;
        }
    }
    return 0;  // If no active lecturer is found for the module
}

void editModule(char *User_ID) {
    char moduleId[10];
    bool validInput = false; // Declare and initialize validInput flag
    Module newModule;

    // Input module ID
    input_moduleid:
    printf("Enter the module ID to edit (eg: EN_0101): ");
    scanf("%s", newModule.module_id);
    strcpy(moduleId,newModule.module_id);

    // Check if module ID exists
    for (int i = 0; i < numModules; ++i) {
        if (strcmp(newModule.module_id, modules[i].module_id) == 0) {
            validInput = true; // Set validInput to true if module ID exists
            break; // Exit loop once a match is found
        }
    }
    
    // If module ID doesn't exist, prompt user to continue or not
    if (!validInput) {
        printf("Error: Module ID does not exist. Please enter a valid ID.\n");
        printf("Do you want to create a new module?\n(y - for yes/n - for no/ c - for try again): ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y') {
             createModule(User_ID);
             getchar();
        } else if (choice_1 == 'n' || choice_1 == 'N') {
            return; // Return to main menu
        } else if (choice_1 == 'c' || choice_1 == 'C'){
            getchar();
            goto input_moduleid; // Prompt user to input module ID again
        }
        else{
            printf("Invalid input. Try again...\n");
            getchar();
            goto input_moduleid;
        }
    }

    // Flag to indicate if the module is found
    bool found = false;

    // Find and edit the module
    for (int i = 0; i < numModules; ++i) {
        if (strcmp(modules[i].module_id, newModule.module_id) == 0 && modules[i].active) {
            found = true;

            int choice;
            char oldValue[50];

            // Edit menu
            while (1) {
                printf("Select field to edit\n");
                printf("1. Module Name\n");
                printf("2. Description\n");
                printf("3. Lecturer ID\n");
                printf("4. Go Back\n");
                printf("5. Main Menu\n");
                printf("Enter your choice number: ");
                scanf("%d", &choice);
                getchar();

                switch (choice) {
                    case 1:
                        strcpy(oldValue, modules[i].module_name);
                        printf("Enter new module name: ");
                        scanf("%s", modules[i].module_name);
                        addModuleHistoryEntry(User_ID, "module", "edit", modules[i].module_name, oldValue, moduleId);
                        printf("Module edited successfully...\n\n");
                        break;
                    case 2:
                        strcpy(oldValue, modules[i].module_description);
                        printf("Enter new description: ");
                        scanf("%s", modules[i].module_description);
                        addModuleHistoryEntry(User_ID, "module", "edit", modules[i].module_description, oldValue, moduleId);
                        printf("Module edited successfully...\n\n");
                        break;
                    case 3:
                        strcpy(oldValue, modules[i].lecturer_id);
                    
                        input_lecturerid:
                        printf("Enter the lecturer ID (eg: L_001): ");
                        scanf("%s", newModule.lecturer_id);
                        validInput = false; // Reset validInput flag before checking
                        for (int i = 0; i < numModules; ++i) {
                            if (strcmp(newModule.lecturer_id, modules[i].lecturer_id) == 0 && lecturers[i].active) {
                                validInput = true; // Set validInput to true if a match is found
                                break; // Exit loop once a match is found
                            }
                        }
                        if (!validInput) {
                            printf("Error: Lecturer ID does not exist. Please enter a valid ID.\n");
                            printf("Do you want to add new lecturer?\n(y - for yes/n - for no/c - for try again): ");
                            char choice_1;
                            scanf(" %c", &choice_1);
                            if (choice_1 == 'y' || choice_1 == 'Y') {
                                getchar();
                                // createLecturer(User_ID);
                                printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                                goto input_lecturerid;
                            } else if (choice_1 == 'n' || choice_1 == 'N') {
                                return;
                            } else if (choice_1 == 'c' || choice_1 == 'C'){
                                getchar();
                                goto input_lecturerid; // Prompt user to input module ID again
                            }else {
                                printf("Invalid input. Try again...\n");
                                getchar();
                                goto input_lecturerid;
                            }
                        }
                        strcpy(modules[i].lecturer_id,newModule.lecturer_id);
                        addModuleHistoryEntry(User_ID, "module", "edit", modules[i].lecturer_id, oldValue, moduleId);
                        printf("Module edited successfully...\n\n");
                        break;
                    case 4:
                        return; // Go back
                    case 5:
                        Module_main(User_ID); // Return to main menu
                    default:
                        printf("Invalid choice. Try again...\n");
                }
            }
        }
    }

    if (!found) {
        printf("Module not found or inactive.\n");
    }
}

void deleteModule(char *User_ID) {
    char moduleId[10];
    printf("Enter the module ID to delete (eg: EN_0101): ");
    scanf("%s", moduleId);

    bool found = false;{
    printf("Press 'y' to confirm: ");
        char choice_1;
        scanf(" %c", &choice_1);
        if (choice_1 == 'y' || choice_1 == 'Y')
        {
        for (int i = 0; i < numModules; ++i) {
        if (strcmp(modules[i].module_id, moduleId) == 0 && modules[i].active) {
            found = true;
            modules[i].active = false;
            addModuleHistoryEntry(User_ID, "module", "delete", "", modules[i].module_name, moduleId);
            printf("Module deleted successfully...\n");
            break;
            }
        }
        } else{
           printf("Actions revoked...\n");
           deleteModule(User_ID);
        }
    }

    if (!found) {
        printf("Module not found or already inactive.\n");
    }

    int furtherAction;
    printf("1. Delete another module\n");
    printf("2. Main menu\n");
    printf("Enter your choice number: ");
    scanf("%d", &furtherAction);
    getchar();
    if (furtherAction == 1) {
        deleteModule(User_ID);
    }
}
void addModuleHistoryEntry(const char *userId, const char *entity, const char *action, const char *newValue, const char *oldValue, const char *editedModuleId) {
    if (historyIndexModule < MAX_HISTORY_ENTRIES) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        strcpy(history[historyIndexModule].userId, userId);
        strcpy(history[historyIndexModule].entity, entity);
        strcpy(history[historyIndexModule].action, action);
        strcpy(history[historyIndexModule].newValue, newValue);
        strcpy(history[historyIndexModule].oldValue, oldValue);
        strcpy(history[historyIndexModule].editedModuleId, editedModuleId);
        history[historyIndexModule].timestamp = now;

        historyIndexModule++;
    } else {
        printf("History entries limit reached. Cannot add more entries.\n");
    }
}

void reviewHistoryModule() {
    printf("\n------------------History Table------------------\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| Timestamp            | User ID | Entity    | EditedModuleID | Action | New Value | Old Value |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    char timestamp[20];

    for (int i = 0; i < historyIndexModule; ++i) {
        struct tm *tm_info = localtime(&history[i].timestamp);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("| %-20s | %-7s | %-9s | %-14s | %-6s | %-9s | %-9s |\n", timestamp,history[i].userId, history[i].entity, history[i].editedModuleId, history[i].action, history[i].newValue, history[i].oldValue);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
}