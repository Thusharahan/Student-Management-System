// #include <stdio.h>
// #include <string.h>
// #include <time.h>
// #include <ctype.h>
// #include "Data_Base.h"
// #include 

#define MAX_HISTORY_ENTRIES 100

// Define struct for history log
typedef struct {
    char operation[20];
    char lecturerId[MAX_ID_LEN];
    char userName[MAX_NAME_LEN]; // Name of the user who made the modification
    char dateTime[30]; // Date and time of the modification
} LecturerHistory;

// Global arrays to store lecturers and history log
Lecturer lecturers[MAX_LEC];
LecturerHistory historyLecture[MAX_HISTORY_ENTRIES];
int numLecturers = 6;
int numHistoryEntries = 0;

// Function prototypes
void createLecturer(char *User_ID);
int isValidPhoneNumberLecture(const char* phone);
int isValidEmailLecture(const char* email);
int isValidNameLecture(const char *name);
void readLecturer();
void updateLecturer(char *User_ID);
void deleteLecturer(char *User_ID);
void addToHistory(const char* operation, const char* lecturerId, const char* userName);
void displayHistory();
int checkYesNoLecture();
int isValidIDLecture(const char* id);
void view_student(char lec_id[MAX_NAME_LEN]);


void Lecture_main(char *User_ID) {
    int choice;
    do {
        printf("\nWelcome to the Student Management System - Section of Lecturer\n");
        printf("Choices of Operations\n");
        printf("1. Add Lecturer\n");
        printf("2. View Lecturer\n");
        printf("3. Update Lecturer Details\n");
        printf("4. Delete Lecturer\n");
        printf("5. View History\n");
        printf("6. Exit\n");
        printf("\nEnter your choice for the operation by entering the operation number: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                createLecturer(User_ID);
                break;
            case 2:
                readLecturer();
                break;
            case 3:
                updateLecturer(User_ID);
                break;
            case 4:
                deleteLecturer(User_ID);
                break;
            case 5:
                displayHistory();
                break;
            case 6:
                printf("Exiting to main menu. Thank You!\n");
                return;
            default:
                printf("\nInvalid choice. Please enter a number from 1 to 6.\n");
        }
    } while (choice != 6);
}

// Function to create a new lecturer
void createLecturer(char *User_ID) {
    while (1) {
        if (numLecturers < MAX_LEC) {
            Lecturer newLecturer;
            // Generate the next lecturer ID
            sprintf(newLecturer.id, "L_%03d", numLecturers + 1);
            printf("\nAssigned Lecturer ID: %s\n", newLecturer.id); // Display the assigned ID
            printf("Enter lecturer information:\n");
            printf("Name should be in blocks letters\n");
            printf("Name: ");
            while (1) {
                fgets(newLecturer.name, sizeof(newLecturer.name), stdin);
                strtok(newLecturer.name, "\n");
                if (isValidNameLecture(newLecturer.name)) {
                    if (strlen(newLecturer.name) <= MAX_NAME_LEN) {
                        break; // Break out of the loop if both conditions are satisfied
                    } else {
                        printf("Name exceeds maximum length of %d characters. Please enter a shorter name.\n", MAX_NAME_LEN);
                        printf("Name: ");
                    }
                } else {
                    printf("Invalid Name! Please enter again with correct format: ");
                }
            }

            printf("Gender (M/F): ");
            while (true) {
                scanf(" %c", &newLecturer.gender);
                getchar();
                newLecturer.gender = toupper(newLecturer.gender);
                if (newLecturer.gender == 'M' || newLecturer.gender == 'F') {
                    break;
                } else {
                    printf("Invalid gender! Please enter 'M' for male or 'F' for female.\n");
                    printf("Gender (M/F): ");
                }
            }

            // Add email validation
            int validEmail = 0;
            do {
                printf("Email (Ex: lecturer_xxx@gmail.com, xxx defines ID no): ");
                fgets(newLecturer.email, sizeof(newLecturer.email), stdin);
                strtok(newLecturer.email, "\n");

                // Convert any uppercase characters in email to lowercase
                for (int i = 0; newLecturer.email[i]; i++) {
                newLecturer.email[i] = tolower(newLecturer.email[i]);
                }

                if (!isValidEmailLecture(newLecturer.email)) {
                    printf("Invalid email format! Please enter a valid email address.\n");
                } else {
                    // Check if the email already exists
                    int emailExists = 0;
                    for (int i = 0; i < numLecturers; i++) {
                        if (strcmp(newLecturer.email, lecturers[i].email) == 0) {
                            emailExists = 1;
                            break;
                        }
                    }
                    if (emailExists) {
                        printf("Email already exists! Please enter a unique email.\n");
                    } else {
                        validEmail = 1;
                    }
                }
            } while (!validEmail);
            
            int validPhone = 0;
            do {
                printf("Phone (Must be 10 digits number): ");
                fgets(newLecturer.phone, sizeof(newLecturer.phone), stdin);
                strtok(newLecturer.phone, "\n");
                if (strlen(newLecturer.phone) != 10 || !isValidPhoneNumberLecture(newLecturer.phone)) {
                    printf("Invalid phone number! Please enter a 10-digit number.\n");
                } else {
                    validPhone = 1;
                }
            } while (!validPhone);
            
            // Print available departments
            printf("Available Departments:\n");
            for (int i = 0; i < MAX_DEPT; i++) {
                if (strlen(departments[i].Dept_ID) > 0 && strlen(departments[i].Dept_Name) > 0) {
                    printf("%d. ID '%s' is for choosing the %s department\n", i + 1, departments[i].Dept_ID, departments[i].Dept_Name);
                }
            }

            // Get department choice from user
                int deptChoice;
                int departmentExists = 0;
            do {
                printf("Choose department (Enter the corresponding number): ");
                if (scanf("%d", &deptChoice) != 1) { // Check if input is a number
                    printf("Invalid input! Please enter a number.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue; 
                }
                getchar(); 

                if (deptChoice < 1 || deptChoice > MAX_DEPT) {
                    printf("Invalid input! Please enter a number within the range.\n");
                    continue; 
                }

                // Copy chosen department ID
                strcpy(newLecturer.department_id, departments[deptChoice - 1].Dept_ID);

                // Check if the department ID exists
                for (int i = 0; i < MAX_DEPT; i++) {
                    if (strcmp(newLecturer.department_id, departments[i].Dept_ID) == 0) {
                        departmentExists = 1;
                        break;
                    }
                }

                if (!departmentExists) {
                    printf("Invalid department ID! Please choose a valid department.\n");
                }

            } while (!departmentExists);


            // Remove newline characters from input
            strtok(newLecturer.name, "\n");
            strtok(newLecturer.email, "\n");

            // Set active flag to true
            newLecturer.active = true;

            lecturers[numLecturers++] = newLecturer;
            printf("\nLecturer added successfully!\n");

            addToHistory("Add", newLecturer.id, User_ID); 
            printf("Do you want to add another lecturer? (Press y to continue | n to Exit): ");
            int option = checkYesNoLecture();
            if (option == 1) {
                createLecturer(User_ID); // Exit the loop if user chooses not to add another lecturer
            }
         else if(option == 2)
        {
            return; 
        }
    }
}
}

void readLecturer() {
    while (1) {
        int choice;
        printf("\n1. View All Lecturers\n");
        printf("2. View Details for a Specific Lecturer\n");
        printf("3. View Students under the Lecturer\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1: {
                // Display all active lecturers
                if (numLecturers > 0) {
                    printf("\nList of All Lecturers:\n");
                    for (int i = 0; i < numLecturers; i++) {
                        if (lecturers[i].active) { // Check if lecturer is active
                            char departmentName[MAX_NAME_LEN];
                            int departmentFound = 0;
                            for (int j = 0; j < MAX_DEPT; j++) {
                                if (strcmp(departments[j].Dept_ID, lecturers[i].department_id) == 0) {
                                    strcpy(departmentName, departments[j].Dept_Name);
                                    departmentFound = 1;
                                    break;
                                }
                            }
                            if (!departmentFound) {
                                strcpy(departmentName, "N/A");
                            }

                            char courseName[MAX_NAME_LEN];
                            int courseFound = 0;
                            for (int k = 0; k < MAX_CORS; k++) {
                                if (strcmp(courses[k].inChargeLecturerId, lecturers[i].id) == 0) {
                                    strcpy(courseName, courses[k].name);
                                    courseFound = 1;
                                    break;
                                }
                            }
                            if (!courseFound) {
                                strcpy(courseName, "N/A");
                            }

                            // Find and print module names
                            char moduleNames[MAX_NAME_LEN] = ""; // Concatenated string to hold all module names
                            for (int m = 0; m < MAX_MOD; m++) {
                                if (strcmp(modules[m].lecturer_id, lecturers[i].id) == 0) {
                                    strcat(moduleNames, modules[m].module_name);
                                    strcat(moduleNames, ", ");
                                }
                            }
                            if (strlen(moduleNames) > 0) {
                                // Remove the trailing comma and space
                                moduleNames[strlen(moduleNames) - 2] = '\0';
                            } else {
                                strcpy(moduleNames, "N/A");
                            }

                            printf("ID: %s\n", lecturers[i].id);
                            printf("Name: %s\n", lecturers[i].name);
                            printf("Gender: %c\n", lecturers[i].gender);
                            printf("Phone: %s\n", lecturers[i].phone);
                            printf("Email: %s\n", lecturers[i].email);
                            printf("Department Name: %s\n", departmentName);
                            printf("Course Name: %s\n", courseName);
                            printf("Module Names: %s\n", moduleNames);
                            printf("\n");
                        }
                    }
                } else {
                    printf("No lecturers to display!\n");
                }
                break;
            }
            case 2: {
                // Search for a specific lecturer by name or ID
                if (numLecturers > 0) {
                    int validID = 0;
                    char search[MAX_NAME_LEN];
                    while (!validID) {
                        printf("\nEnter the ID of the lecturer (Ex: L_00x): ");
                        scanf("%s", search);
                        validID = isValidIDLecture(search);
                        if (!validID) {
                            printf("Invalid ID input. Please enter a correct ID.\n");
                        }
                    }

                    int found = 0;
                    for (int i = 0; i < numLecturers; i++) {
                        // Check if the entered string matches lecturer's name or ID
                        if ((strcmp(lecturers[i].name, search) == 0 || strcmp(lecturers[i].id, search) == 0) && lecturers[i].active) { 
                            printf("\nDetails for Lecturer with ID '%s':\n", search);
                            printf("Name: %s\n", lecturers[i].name);
                            printf("ID: %s\n", lecturers[i].id);
                            printf("Gender: %c\n", lecturers[i].gender);
                            printf("Phone: %s\n", lecturers[i].phone);
                            printf("Email: %s\n", lecturers[i].email);

                            // Find and print the department name
                            char departmentName[MAX_NAME_LEN];
                            int departmentFound = 0;
                            for (int j = 0; j < MAX_DEPT; j++) {
                                if (strcmp(departments[j].Dept_ID, lecturers[i].department_id) == 0) {
                                    strcpy(departmentName, departments[j].Dept_Name);
                                    departmentFound = 1;
                                    break;
                                }
                            }
                            if (!departmentFound) {
                                strcpy(departmentName, "N/A");
                            }

                            printf("Department: %s\n", departmentName);

                            // Find and print the course name
                            char courseName[MAX_NAME_LEN];
                            int courseFound = 0;
                            for (int k = 0; k < MAX_CORS; k++) {
                                if (strcmp(courses[k].inChargeLecturerId, lecturers[i].id) == 0) {
                                    strcpy(courseName, courses[k].name);
                                    courseFound = 1;
                                    break;
                                }
                            }
                            if (courseFound) {
                                printf("Courses: %s\n", courseName);
                            } else {
                                printf("Course: N/A\n");
                            }

                            // Find and print module names
                            printf("Module Names: ");
                            int moduleFound = 0;
                            for (int m = 0; m < MAX_MOD; m++) {
                                if (strcmp(modules[m].lecturer_id, lecturers[i].id) == 0) {
                                    printf("%s, ", modules[m].module_name);
                                    moduleFound = 1;
                                }
                            }
                            if (!moduleFound) {
                                printf("N/A");
                            }
                            printf("\n");

                            printf("\n");
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("No active lecturer found with the ID '%s'!\n", search);
                    }
                } else {
                    printf("No lecturers to display!\n");
                }
                break;
            }
            case 3:
                if (numLecturers > 0) {
                    int validID = 0;
                    char search[MAX_NAME_LEN];
                    while (!validID) {
                        printf("\nEnter the ID of the lecturer (Ex: L_00x): ");
                        scanf("%s", search);
                        validID = isValidIDLecture(search);
                        if (!validID) {
                            printf("Invalid ID input. Please enter a correct ID.\n");
                        }
                        else
                        {
                            view_student(search);
                        }
                    }

                }


                break;
            case 4:
                return; 
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
}
// Function to update a lecturer's information
void updateLecturer(char *User_ID) {
    while (1) {
        if (numLecturers > 0) {
            int validID = 0;
            char searchId[MAX_ID_LEN];
            while (!validID) {
                printf("\nEnter the ID of the lecturer to update (Ex: L_00x): ");
                scanf("%s", searchId);
                validID = isValidIDLecture(searchId);
                if (!validID) {
                    printf("Invalid ID input. Please enter a correct ID.\n");
                }
            }

            // Check if the user wants to exit
            if (strcmp(searchId, "exit") == 0) {
                break; // Exit the loop
            }

            int found = 0;
            for (int i = 0; i < numLecturers; i++) {
                if (strcmp(lecturers[i].id, searchId) == 0) {
                    printf("Lecturer found. Select the field to update:\n");
                    printf("1. Name\n");
                    printf("2. Gender\n");
                    printf("3. Phone Number\n");
                    printf("4. Email ID\n");
                    printf("5. Department\n");
                    printf("6. Exit\n");
                    printf("Enter your choice: ");

                    int choice;
                    scanf("%d", &choice);
                    getchar(); // Consume newline character

                    switch (choice) {
                        case 1:
                            printf("Enter new name: ");
                            while (1) {
                                fgets(lecturers[i].name, sizeof(lecturers[i].name), stdin);
                                strtok(lecturers[i].name, "\n");
                                if (isValidNameLecture(lecturers[i].name)) {
                                    if (strlen(lecturers[i].name) <= MAX_NAME_LEN) {
                                        break;
                                    } else {
                                        printf("Error: Name exceeds maximum length of %d characters. Please enter a shorter name.\n", MAX_NAME_LEN);
                                        printf("Name: ");
                                    }
                                } else {
                                    printf("Invalid Name! Please enter again with correct format: ");
                                }
                            }
                            break;

                        case 2:
                            printf("Enter new gender (M/F): ");
                            while(true){
                                scanf(" %c", &lecturers[i].gender);
                                getchar();
                                lecturers[i].gender = toupper(lecturers[i].gender);
                                if (lecturers[i].gender == 'M' || lecturers[i].gender == 'F') {
                                    break;
                                } else {
                                    printf("Error: Invalid gender! Please enter 'M' for male or 'F' for female.\n");
                                    printf("Gender (M/F): ");
                                }    
                            }
                            break;

                        case 3:
                            {
                                char newPhone[MAX_PHN_LEN];
                                int validPhone = 0;
                                do {
                                    printf("Enter new phone number: ");
                                    fgets(newPhone, sizeof(newPhone), stdin);
                                    strtok(newPhone, "\n"); // Remove newline characters
                                    if (strlen(newPhone) != 10 || !isValidPhoneNumberLecture(newPhone)) {
                                        printf("Invalid phone number! Please enter a 10-digit number.\n");
                                    } else {
                                        validPhone = 1;
                                    }
                                } while (!validPhone);
                                strcpy(lecturers[i].phone, newPhone);
                                break;
                            }

                        case 4:
                            {
                                char newEmail[MAX_NAME_LEN];
                                int validEmail = 0;
                                do {
                                    printf("Enter new email ID: ");
                                    fgets(newEmail, sizeof(newEmail), stdin);
                                    strtok(newEmail, "\n");

                                    // Convert any uppercase characters in email to lowercase
                                    for (int i = 0; newEmail[i]; i++) {
                                        newEmail[i] = tolower(newEmail[i]);
                                    }
                                    if (!isValidEmailLecture(newEmail)) {
                                        printf("Invalid email format! Please enter a valid email address.\n");
                                    } else {
                                        // Check if the email already exists
                                        int emailExists = 0;
                                        for (int j = 0; j < numLecturers; j++) {
                                            if (strcmp(newEmail, lecturers[j].email) == 0) {
                                                emailExists = 1;
                                                break;
                                            }
                                        }
                                        if (emailExists) {
                                            printf("Email already exists! Please enter a unique email.\n");
                                        } else {
                                            strcpy(lecturers[i].email, newEmail);
                                            validEmail = 1;
                                        }
                                    }
                                } while (!validEmail);
                                break;
                            }

                        case 5:
                            // Print available departments
                            printf("Available Departments:\n");
                            for (int i = 0; i < MAX_DEPT; i++) {
                                if (strlen(departments[i].Dept_ID) > 0 && strlen(departments[i].Dept_Name) > 0) {
                                    printf("%d. ID '%s' is for choosing the %s department\n", i + 1, departments[i].Dept_ID, departments[i].Dept_Name);
                                }
                            }

                            // Get department choice from user
                            int deptChoice;
                            char departmentID[MAX_ID_LEN];
                            int departmentExists = 0;
                            do {
                                printf("Choose department (Enter the corresponding number): ");
                                if (scanf("%d", &deptChoice) != 1) { // Check if input is a number
                                    printf("Invalid input! Please enter a number.\n");
                                    while (getchar() != '\n'); // Clear input buffer
                                    continue; 
                                }
                                getchar(); // Consume newline character

                                if (deptChoice < 1 || deptChoice > MAX_DEPT) {
                                    printf("Invalid input! Please enter a number within the range.\n");
                                    continue; 
                                }

                                // Copy chosen department ID
                                strcpy(departmentID, departments[deptChoice - 1].Dept_ID);

                                // Check if the department ID exists
                                for (int j = 0; j < MAX_DEPT; j++) {
                                    if (strcmp(departmentID, departments[j].Dept_ID) == 0) {
                                        departmentExists = 1;
                                        break;
                                    }
                                }

                                if (!departmentExists) {
                                    printf("Invalid department ID! Please choose a valid department.\n");
                                }

                            } while (!departmentExists);

                            // Copy chosen department ID to lecturer
                            strcpy(lecturers[i].department_id, departmentID);
                            break;
                        case 6:
                            return; // Exit the function
                        default:
                            printf("Invalid choice. Please enter a number from 1 to 6.\n");
                    }
                    addToHistory("Update", lecturers[i].id, User_ID);
                    printf("Lecturer information updated successfully!\n");
                    found = 1;
                    printf("\nDo you want to update another lecturer's information? (Press y to continue | Press n to exit): ");
                    int option = checkYesNoLecture();
                    if(option == 1){
                        updateLecturer(User_ID);
                    } else if(option == 2) {
                        return;
                    }
                    
                }
            }
            if (!found) {
                printf("No lecturer found with the ID '%s'!\n", searchId);
            }
        } else {
            printf("No lecturers to update!\n");
            break; // Exit the loop if there are no lecturers to update
        }
    }
}


// Function to delete a lecturer
void deleteLecturer(char *User_ID) {
    while (1) {
        if (numLecturers > 0) {
            char searchId[MAX_ID_LEN];
            printf("\nEnter the ID of the lecturer to delete (Enter 'exit' to quit): ");
            scanf("%s", searchId);

            // Check if the user wants to exit
            if (strcmp(searchId, "exit") == 0) {
                break; // Exit the loop
            }

            int found = 0;
            for (int i = 0; i < numLecturers; i++) {
                if (strcmp(lecturers[i].id, searchId) == 0) {
                    printf("Lecturer found. Are you sure you want to delete this lecturer? (Press Y to confirm | Press N to exit): ");
                    int confirm = checkYesNoLecture();

                    if (confirm == 1) {
                        // Set active flag to false
                        lecturers[i].active = false;
                        
                        addToHistory("Delete", searchId, User_ID);
                        printf("Lecturer deleted successfully!\n");
                    } else if (confirm == 2){
                        printf("Deletion cancelled.\n");
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No lecturer found with the ID '%s'!\n", searchId);
            }
        } else {
            printf("No lecturers to delete!\n");
            break; // Exit the loop if there are no lecturers to delete
        }
    }
}


// Function to add an entry to the history log
void addToHistory(const char* operation, const char* lecturerId, const char* userName) {
    if (numHistoryEntries < MAX_HISTORY_ENTRIES) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(historyLecture[numHistoryEntries].dateTime, sizeof(historyLecture[numHistoryEntries].dateTime), "%Y-%m-%d %H:%M:%S", t);
        strcpy(historyLecture[numHistoryEntries].operation, operation);
        strcpy(historyLecture[numHistoryEntries].lecturerId, lecturerId);
        strcpy(historyLecture[numHistoryEntries].userName, userName);
        numHistoryEntries++;
    } else {
        printf("History log is full. Cannot add more entries.\n");
    }
}

// Function to display the history log
void displayHistory() {
    if (numHistoryEntries > 0) {
        printf("\nHistory Log:\n");
        printf("--------------------------------------------------------------------------\n");
        printf("| %-20s | %-15s | %-10s | %-15s |\n", "Date/Time", "Operation", "Lecturer ID", "User");
        printf("--------------------------------------------------------------------------\n");
        for (int i = 0; i < numHistoryEntries; i++) {
            printf("| %-20s | %-15s | %-10s  | %-15s |\n", historyLecture[i].dateTime, historyLecture[i].operation, historyLecture[i].lecturerId, historyLecture[i].userName);
        }
        printf("--------------------------------------------------------------------------\n");
    } else {
        printf("History log is empty.\n");
    }
}

// Function to validate phone number format
int isValidPhoneNumberLecture(const char* phone) {
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0; // Not a digit
        }
    }
    return 1;
}

// Function to validate email format
int isValidEmailLecture(const char* email) {
    int atCount = 0;
    int dotCount = 0;
    for (int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            atCount++;
        } else if (email[i] == '.') {
            dotCount++;
        }
    }
    return (atCount == 1 && dotCount >= 1);
}

//Function to validate the Name
int isValidNameLecture(const char *name) {
    while (*name) {
        if ((*name < 'A' || *name > 'Z') && *name != ' ') {
            return false;
        }
        name++;
    }
    return true;
}

int checkYesNoLecture() {
    while(1){
        char userInput[10];
        scanf("%s", userInput); 

        for (int i = 0; userInput[i]; i++) {
            userInput[i] = tolower(userInput[i]);
        }

        // Compare the input string with "yes", "no", "y", and "n"
        if (strcmp(userInput, "Y") == 0 || strcmp(userInput, "y") == 0) {
            getchar();
            return 1; // Return 1 if input is "yes" or "y"
        } else if (strcmp(userInput, "N") == 0 || strcmp(userInput, "n") == 0) {
            getchar();
            return 2; // Return 2 if input is "no" or "n"
        } else {
            printf("Invalid input!\nPlease enter (y- for yes/n - for no):");
            continue;
        }
    }
}

int isValidIDLecture(const char* id) {
    if(id[0] != 'L' || id[1] != '_'){
        return 0;
    }
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) {
            return 0; // Not a digit
        }
    }
    return 1;
}


void view_student(char lec_id[])
{
    printf("\nStudents under Lecturers : \n\n");
    for(int i = 0; i < MAX_LEC; i++)
    {
        if(strcmp(lec_id, lecturers[i].id) == 0 && lecturers[i].active)
        {
            printf("%-5s - %-30s\n\n", lec_id, lecturers[i].name);
            for(int r = 0; r < MAX_CORS; r++)
            {
                if(strcmp(lec_id, courses[r].inChargeLecturerId) == 0 && courses[r].active)
                {
                    for(int x = 0; x < MAX_STD; x++)
                    {
                        if(strcmp(courses[r].id, students[x].Std_Course) == 0 && students[x].Std_Visible)
                        {
                            printf("\t%-5s  -  %-30s\n", students[x].Std_ID, students[x].Std_Name);
                        }
                    }
                }
            }
        }
    }
}



