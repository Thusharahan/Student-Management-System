// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>
// #include <time.h>
// #include <ctype.h>
// #include "input.h"
// #include "Data_Base.h"

#define MAX_STUDENTS 25
#define LIST_STUDENTS 20

// extern const char USER_ID[]; 

// char USER_ID[] = "ID_002";

int storenum = 0;

int num_students = 20;

typedef struct 
{
    char User_ID[20];
    char Timestamp[30];
    char Action[20];
    char St_ID[10];
    char Field[30];
    char Old_val[50];
    char New_val[50];
} History;

int num_history = 0;
History histories[50];


void add_student(char *USER_ID);
void display_students();
void search_student();
void delete_student(char *USER_ID);
void store_history(char *user, char *action, char *id, char *field, char *old_value, char *new_value);
void display_history();
int getCourse(int n);
int getDep(int n);

int isValidName(const char *name){
    while (*name) {
        if ((*name < 'A' || *name > 'Z') && *name != ' ') {
            return false;
        }
        name++;
    }
    return true;
}
int isValidPhoneNumber(const char* phone) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0; // Not a digit
        }
        count++;
    }
    // Check if there are exactly 10 digits
    if (count != 10 || phone[10] != '\0') {
        return 0;
    }
    return 1;
}

int isValidEmail(const char* email) {
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

int isValidID(const char* id) {
    if(id[0] != 'S' || id[1] != '_'){
        return 0;
    }
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) {
            return 0; // Not a digit
        }
    }
    return 1;

}

int checkYesNo() {
    while(1){
        char userInput[10];
        scanf("%9s", userInput); 

        for (int i = 0; userInput[i]; i++) {
            userInput[i] = tolower(userInput[i]);
        }

        // Compare the input string with "yes", "no", "y", and "n"
        if (strcmp(userInput, "yes") == 0 || strcmp(userInput, "y") == 0) {
            return 1; // Return 1 if input is "yes" or "y"
        } else if (strcmp(userInput, "no") == 0 || strcmp(userInput, "n") == 0) {
            return 2; // Return 2 if input is "no" or "n"
        } else {
            printf("Invalid input!\nPlease enter (y- for yes/n - for no):");
            continue;
        }
    }
}

//This function is used to create the list of students in the initial.
void add_student(char *USER_ID) {
    char St_Name[35], St_ID[6], St_ContactNo[14], St_Email[35], St_EnrolledYear[5], St_Department[3], St_Course[6];
    if (num_students < MAX_STUDENTS) {
        printf("\nEnter Student Details:\n");
        printf("\nStudents full name: \n");
        printf("Student's full name should be in block letters (E.g., FIRSTNAME SURNAME)\n");
        printf("Enter the students full name: ");
        while(1){
            scanf(" %[^\n]", St_Name); //Reads the string until it encounters a newline character (\n)
            if(isValidName(St_Name)){
                break;
            }else{
                printf("Invalid Name! Please enter again with correct format: ");
            }
        }

        sprintf(St_ID, "S_%03d", num_students + 1);

        printf("\nPhone number:\nPhone number should be in 10 digits (E.g: 0XXXXXXXXX)\n");
        printf("Enter the phone number: ");
        while(1){
            scanf("%s", &St_ContactNo);
            if(isValidPhoneNumber(St_ContactNo)){
                break;
            }else{
                printf("Invalid Phone Number! Try again with correct format. Phone number should be in 10 digits (E.g: 0XXXXXXXXX): ");
                continue;
            }
        }
        printf("\nEnter email address (example@email.com): ");
        while(1){
            scanf("%s", &St_Email);
            if(isValidEmail(St_Email)){
                break;
            }else{
                printf("Invalid Email Address! Try again with correct format (example@email.com): ");
            }
        }

        while(1){
            int count = 1;
            for (int i = 0; i < MAX_DEPT; i++){
                if (departments[i].active){
                    count++;
                }
            }
            if (count == 1) {
                printf("\nThere is no departments avilable or they have been deleted.\n");
                printf("Do you want to view history for more details? \n(y - for yes/n - for no): ");
                int depchoise = checkYesNo();
                if (depchoise == 1) {
                    // view_department();
                    printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                } 
                printf("Do you want to add any department?\n(y - for yes/n - for no): ");
                depchoise = checkYesNo();
                if (depchoise == 1) {
                    // addFunctions(1, USER_ID);
                    printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                }else{
                    printf("\nAdding students was incomplete!!\n");
                    return;
                }
            } else{
                break;
            }
        }

        printf("\nSelect one department from following:\n");
        printf("Available departments: \n");
        // char department[MAX_DEPT][MAX_NAME_LEN];
        int num = 0;
        for (int i = 0; i < MAX_DEPT; i++){
            if (departments[i].active) {
                num++;
                printf("%d. %s | ID - [%s]\n", num, departments[i].Dept_Name, departments[i].Dept_ID);
            }
        }
        
        label2:
        printf("\nEnter the department ID: ");
        scanf("%s", &St_Department);
        bool flag1 = true;
        for (int i = 0; i < MAX_DEPT; i++){
            if(strcmp(departments[i].Dept_ID,St_Department) == 0) {
                flag1 = false;
                break;
            }
        }
        if (flag1) {
            printf("Entered wrong Course ID! Please try again.\n");
            while(getchar() != '\n');
            goto label2;
        } 
        

        while (1){
            int count1 = 1;
            for (int i = 0; i < MAX_CORS; i++){
                if (strcmp(courses[i].departmentId, St_Department) == 0){
                    count1++;
                }
            }
            if (count1 == 1) {
                printf("\nThere is no courses avilable under the selected department or they have been deleted.\n");
                printf("Do you want to view history for more details? \n(y - for yes/n - for no): ");
                int depchoise1 = checkYesNo();
                if (depchoise1 == 1) {
                    // view_department();
                    printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                } 
                printf("Do you want to add any courses?\n(y - for yes/n - for no): ");
                depchoise1 = checkYesNo();
                if (depchoise1 == 1) {
                    addFunctions(2, USER_ID);
                    // printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                }else{
                    printf("\nAdding students was incomplete!!\n");
                    return;
                }
            } else {
                break;
            }
        }

        printf("\nAvailable courses under selected department:\n");
        num = 0;
        for (int i = 0; i < MAX_DEPT; i++) {
            if (strcmp(courses[i].departmentId, St_Department) == 0) {
                num++;
                printf("%d. %s | ID - [%s]\n", num, courses[i].name, courses[i].id);
            }
        }

        label3:
        printf("\nEnter the course ID: ");
        scanf("%s", St_Course);
        int flag = 0;
        for (int i = 0; i < MAX_CORS; i++){
            if(strcmp(courses[i].id,St_Course) == 0) {
                flag = 1;
                break;
            }            
        }
        if (flag == 0){
            printf("Entered wrong Course ID! Please try again.\n");
            while(getchar() != '\n');
            goto label3;
        }
           
        

        strcpy(students[num_students].Std_Name, St_Name);
        strcpy(students[num_students].Std_ID, St_ID);
        strcpy(students[num_students].Std_ContactNo, St_ContactNo);
        strcpy(students[num_students].Std_Email, St_Email);
        strcpy(students[num_students].Std_Department, St_Department);
        strcpy(students[num_students].Std_Course, St_Course);
        students[num_students].Std_Visible = true;
        num_students++;
        printf("Student details added succesfully.\n\n");
    } else {
        printf("\nMaximum number of students reached. Cannot add more students.\n");
    }
}

void display_students() {
    if (num_students == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                             STUDENT DETAILS                                                 \n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-25s | %-10s | %-15s | %-25s | %-30s | %-15s |\n", "Name", "Student ID", "Contact No", "Email", "Department", "Course");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    char ST_depname[MAX_NAME_LEN] , ST_couname[MAX_NAME_LEN];
    for (int i = 0; i < num_students; i++) {
        
        if (students[i].Std_Visible){
            int dep = getDep(i);
            int course = getCourse(i);
            if (departments[dep].active){
                strcpy(ST_depname ,departments[dep].Dept_Name);
            } else {
                strcpy(ST_depname , "N/A");
            }
            if (courses[course].active && departments[dep].active){
                strcpy(ST_couname ,courses[course].name);
            } else {
                strcpy(ST_couname , "N/A");
            }
            printf("| %-25s | %-10s | %-15s | %-25s | %-30s | %-15s |\n", 
                    students[i].Std_Name, students[i].Std_ID, students[i].Std_ContactNo, 
                    students[i].Std_Email, ST_depname, ST_couname);
        }
    }
}

int getDep(int n){
    for (int j = 0; j < MAX_DEPT; j++) {
        if (strcmp(departments[j].Dept_ID, students[n].Std_Department) == 0) {
            return j;
        }
    }
}

int getCourse(int n){
    for (int j = 0; j < MAX_DEPT; j++) {
        if (strcmp(courses[j].id, students[n].Std_Course) == 0) {
            return j;
        }
    }
}

void search_student() {
    bool found = false;
    error:
    printf("\nDo you want to search student by name or student ID?");
    printf("\n1. Name\n2. Student ID\n3. Exit to previous menu.\nEnter the number for your choise: ");
    char *choiseMenu[] = {
        "Name",
        "Student ID",
        "Exit to previous menu"
    };
    int choise = getInput(choiseMenu, 2);

    if (choise == 2) {
        printf("\nEnter the student ID you want to search for: ");
        char St_ID[6];
        while(1){
            scanf("%5s", St_ID);
            if (!isValidID(St_ID)) {
                printf("\nInvalid ID format! Please enter a valid student ID: ");
                continue;
            } else break;
        }
        for (int i = 0; i < num_students; i++) {
            char ST_depname[MAX_NAME_LEN] , ST_couname[MAX_NAME_LEN];
            if (strcmp(students[i].Std_ID, St_ID) == 0) {
                found = true;
                if (students[i].Std_Visible) {
                    int dep = getDep(i);
                    int course = getCourse(i);
                    if (departments[dep].active){
                        strcpy(ST_depname ,departments[dep].Dept_Name);
                    } else {
                        strcpy(ST_depname , "N/A");
                    }
                    if (courses[course].active && departments[dep].active){
                        strcpy(ST_couname ,courses[course].name);
                    } else {
                        strcpy(ST_couname , "N/A");
                    }
                    printf("Student found:\nName: %s\nStudent ID: %s\nContact: %s\nEmail: %s\nDepartment: %s\nCourse: %s\n",
                            students[i].Std_Name, students[i].Std_ID, students[i].Std_ContactNo,
                            students[i].Std_Email, ST_depname, ST_couname);
                } else {
                    printf("Requested student details have been deleted.\n");
                    printf("\nDo you want to review the history for more information?\n(y - for yes/n - for no): ");
                    int yesno = checkYesNo();
                    if (yesno == 1){
                        display_history();
                        return;
                    }
                }
                break;
            } 
        }
        if (!found) {
            printf("Student with ID %s not found.\n", St_ID);
        }
    } else if (choise == 1) {
        int count = 0;
        int indices[MAX_STUDENTS];
        printf("Enter the student's name: ");
        char name[50];
        scanf(" %[^\n]%*c", name);

        char searchUpper[35];
        strcpy(searchUpper, name);
        for (int i = 0; searchUpper[i]; i++) {
            searchUpper[i] = toupper(searchUpper[i]);
        }

        for (int i = 0; i < num_students; i++) {
            if (strstr(students[i].Std_Name, searchUpper) != NULL) {
                indices[count++] = i;
                found = true;
            }
        }

        if (!found) {
            printf("No students were found with the given name.\n");
            return;
        }

        if (count == 1) {
            int index = indices[0];
            char ST_depname[MAX_NAME_LEN] , ST_couname[MAX_NAME_LEN];
            if (students[index].Std_Visible) {
                int dep = getDep(index);
                int course = getCourse(index);
                if (departments[dep].active){
                    strcpy(ST_depname ,departments[dep].Dept_Name);
                } else {
                    strcpy(ST_depname , "N/A");
                }
                if (courses[course].active && departments[dep].active){
                    strcpy(ST_couname ,courses[course].name);
                } else {
                    strcpy(ST_couname , "N/A");
                }
                printf("Student found:\nName: %s\nStudent ID: %s\nContact: %s\nEmail: %s\nDepartment: %s\nCourse: %s\n",
                        students[index].Std_Name, students[index].Std_ID, students[index].Std_ContactNo,
                        students[index].Std_Email, ST_depname, ST_couname);
            } else {
                printf("Requested student details have been deleted.\n");
                printf("\nDo you want to review the history for more information?\n(y - for yes/n - for no): ");
                int yesno = checkYesNo();
                if (yesno == 1){
                    display_history();
                    return;
                }
            }
            return;
        }

        printf("Similar names found: \n");
        printf("-------------------- \n");

        for (int i = 0; i < count; i++) {
            int index = indices[i];
            printf("%d. %s\n", i + 1, students[index].Std_Name);
        }

        int choice;
        printf("\nEnter the index of the student you want to select: ");
        scanf("%d", &choice);
        char ST_depname[MAX_NAME_LEN] , ST_couname[MAX_NAME_LEN];

        if (choice >= 1 && choice <= count) {
            int index = indices[choice - 1];
            if (students[index].Std_Visible) {
                int dep = getDep(index);
                int course = getCourse(index);
                if (departments[dep].active){
                    strcpy(ST_depname ,departments[dep].Dept_Name);
                } else {
                    strcpy(ST_depname , "N/A");
                }
                if (courses[course].active && departments[dep].active){
                    strcpy(ST_couname ,courses[course].name);
                } else {
                    strcpy(ST_couname , "N/A");
                }
                printf("Student found:\nName: %s\nStudent ID: %s\nContact: %s\nEmail: %s\nDepartment: %s\nCourse: %s\n",
                        students[index].Std_Name, students[index].Std_ID, students[index].Std_ContactNo,
                        students[index].Std_Email, ST_depname, ST_couname);
            } else {
                printf("Requested student details have been deleted.\n");
                printf("\nDo you want to review the history for more information?\n(y - for yes/n - for no): ");
                int yesno = checkYesNo();
                if (yesno == 1){
                    display_history();
                    return;
                }
            }
        } else {
            printf("Invalid choice.\n");
        }
    } else if(choise == 3){

    } else {
        printf("Invalid Choise!\n");
        goto error;
    }
}

void delete_student(char *USER_ID) {
    char St_ID[6];
    printf("\nEnter the student ID you want to delete: ");
    while(1){
        scanf("%5s", St_ID);
        if (!isValidID(St_ID)) {
            printf("\nInvalid ID format! Please enter a valid student ID: ");
            continue;
        } else break;
    }
    bool found = false;
    char notapp[] = "NOT APPLICABLE";
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].Std_ID, St_ID) == 0) {
            found = true;
            if (students[i].Std_Visible) {
                printf("\nDo you want to confirm deleting the student with ID %s? \n(y - for yes/n - for no)",students[i].Std_ID);
                int yesno = checkYesNo();
                if (yesno == 1){
                    students[i].Std_Visible = false;
                    store_history(USER_ID, "Delete", students[i].Std_ID, notapp, notapp, notapp);
                    printf("Student with ID %s has been deleted.\n", St_ID); // Inform user of deletion
                } else if (yesno == 2){
                    printf("\nYour delete request has been cancelled.\n");
                    return;
                }
            } else {
                printf("Requested student details have already been deleted.\n");
                printf("\nDo you want to review the history for more information?\n(y - for yes/n - for no): ");
                int yesno = checkYesNo();
                if (yesno == 1){
                    display_history();
                    return;
                }
            }
            break; // Exit loop once student is found and processed
        }
    }
    if (!found) {
        printf("Student with ID %s not found.\n", St_ID);
    }
}

void store_history(char *user, char *action, char *id, char *field, char *old_value, char *new_value) {
    strcpy(histories[num_history].User_ID, user);
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(histories[num_history].Timestamp, sizeof(histories[num_history].Timestamp), "%d/%m/%Y %H:%M:%S", local);
    strcpy(histories[num_history].Action, action);
    strcpy(histories[num_history].St_ID, id);
    strcpy(histories[num_history].Field, field);
    strcpy(histories[num_history].Old_val, old_value);
    strcpy(histories[num_history].New_val, new_value);
    num_history++;
}

void display_history() {
    if (num_history == 0) {
        printf("\nNo history to display.\n");
        return;
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                             HISTORY DETAILS                                                 \n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-8s | %-20s | %-10s | %-8s | %-15s | %-30s | %-30s |\n", "User ID", "Time", "Student ID", "Action", "Field", "Old Value", "New value");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_history; i++) {
        
        if (strcmp(histories[i].Action,"Delete") == 0){
            printf("| %-8s | %-20s | %-10s | %-8s | %-15s | %-30s | %-30s |\n", 
                    histories[i].User_ID, histories[i].Timestamp, histories[i].St_ID,
                    histories[i].Action, "      ---      ", "             ---             ", "             ---             ");
        } else{
            printf("| %-8s | %-20s | %-10s | %-8s | %-15s | %-30s | %-30s |\n", 
                    histories[i].User_ID, histories[i].Timestamp, histories[i].St_ID,
                    histories[i].Action, histories[i].Field, histories[i].Old_val, histories[i].New_val);
        }
    }
}


void edit_student(char *USER_ID) {
    char id[10];
    char field[30];
    int filed;
    char contchoice;
    char old_value[50];
    char new_value[50];
    int idval = -1; // Initialize idval to an invalid index
    
    while (true) {
        printf("\nEnter student ID to update: ");
        scanf("%s", id);

        // Find the student's index by comparing the IDs
        for (int i = 0; i < num_students; i++) {
            if (strcmp(students[i].Std_ID, id) == 0) {
                idval = i;
                break;
            }
        }

        // Check if the student ID exists
        if (idval == -1) {
            printf("Student ID not found. Please try again.\n");
            continue;
        }
        break;
    }
    while (true) {
        char *fieldMenu[] = {
            "Name",
            "contact No",
            "Email",
            "Department",
            "Course"
        };
        
        printf("\nFields for editing student details\n1. Name\n2. Contact No \n3. Email \n4. Department \n5. Course");
        printf("\n\nChoose specific number of the field to edit: ");
        filed = getInput(fieldMenu, 5);

        switch (filed) {
            case 1:
                strcpy(field, "Name");
                printf("Current Name: %s\n", students[idval].Std_Name);
                printf("\nStudent's full name should be in block letters (E.g., FIRSTNAME SURNAME)\n");
                printf("Enter the new students full name: ");
                while(1){
                    scanf(" %[^\n]", new_value); //Reads the string until it encounters a newline character (\n)
                    if(isValidName(new_value)){
                        break;
                    }else{
                        printf("\nInvalid Name! Please enter again with correct format: ");
                    }
                }
                break;
            case 2:
                strcpy(field, "Contact_number");
                printf("Current Contact number: %s\n", students[idval].Std_ContactNo);
                printf("Enter new contact number (E.g. 0XXXXXXXXX): ");
                while(1){
                    scanf("%s", new_value);
                    if(isValidPhoneNumber(new_value)){
                        break;
                    }else{
                        printf("Invalid Phone Number! Try again with correct format. Contact number should be in 10 digits (E.g: 0XXXXXXXXX): ");
                        continue;
                    }
                }
                break;
            case 3:
                strcpy(field, "Email");
                printf("Current Email address: %s\n", students[idval].Std_Email);
                printf("Enter new email (example@email.com): ");
                while(1){
                    scanf("%s", new_value);
                    if(isValidEmail(new_value)){
                        break;
                    }else{
                        printf("Invalid Email Address! Try again with correct format (example@email.com): ");
                    }
                }
                break;
            case 4:
                strcpy(field, "Department");
                int dep = getDep(idval);
                printf("Current Department: %s\n", departments[dep].Dept_Name);
                while(1){
                    int count = 1;
                    for (int i = 0; i < MAX_DEPT; i++){
                        if (departments[i].active){
                            count++;
                        }
                    }
                    if (count == 1) {
                        printf("\nThere is no departments avilable or they have been deleted.\n");
                        printf("Do you want to view history for more details? \n(y - for yes/n - for no): ");
                        int depchoise = checkYesNo();
                        if (depchoise == 1) {
                            // view_department();
                            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                        } 
                        printf("Do you want to add any department?\n(y - for yes/n - for no): ");
                        depchoise = checkYesNo();
                        if (depchoise == 1) {
                            // addFunctions(1, USER_ID);
                            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                        }else{
                            printf("\nUpdating students was incomplete!!\n");
                            return;
                        }
                    } else{
                        break;
                    }
                }

                printf("\nSelect one department from following:\n");
                printf("Available departments: \n");
                // char department[MAX_DEPT][MAX_NAME_LEN];
                int num = 0;
                for (int i = 0; i < MAX_DEPT; i++){
                    if (departments[i].active) {
                        num++;
                        printf("%d. %s | ID - [%s]\n", num, departments[i].Dept_Name, departments[i].Dept_ID);
                    }
                }
                
                label4:
                printf("\nEnter the department ID: ");
                scanf("%s", &new_value);
                bool flag4 = true;
                for (int i = 0; i < MAX_DEPT; i++){
                    if(strcmp(departments[i].Dept_ID,new_value) == 0) {
                        flag4 = false;
                        break;
                    }
                }
                if (flag4){
                    printf("Entered wrong Course ID! Please try again.\n");
                    while(getchar() != '\n');
                    goto label4;
                }
                break;

                // printf("\nAvailable departments for selection: \n");
                // int num = 0;
                // for (int i = 0; i < MAX_DEPT; i++){
                //     if (strlen(departments[i].Dept_ID) > 0 && strlen(departments[i].Dept_Name) > 0) {
                //         printf("%d. %s | ID - [%s]\n", num + 1, departments[i].Dept_Name, departments[i].Dept_ID);
                //     }
                // }
                // printf("Enter new department ID: ");
                // scanf("%s", new_value);
                // break;
            case 5:
                strcpy(field, "Course");
                int course = getCourse(idval);
                dep = getDep(idval);
                printf("Current Course: %s\n", courses[course].name);
                while (1){
                    int count1 = 1;
                    for (int i = 0; i < MAX_CORS; i++){
                        if (strcmp(courses[i].departmentId, departments[dep].Dept_ID) == 0){
                            count1++;
                        }
                    }
                    if (count1 == 1) {
                        printf("\nThere is no courses avilable under the department or they have been deleted.\n");
                        printf("Do you want to view history for more details? \n(y - for yes/n - for no): ");
                        int depchoise1 = checkYesNo();
                        if (depchoise1 == 1) {
                            // view_department();
                            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                        } 
                        printf("Do you want to add any courses?\n(y - for yes/n - for no): ");
                        depchoise1 = checkYesNo();
                        if (depchoise1 == 1) {
                            // addFunctions(2, USER_ID);
                            printf("\nThis functionality is not implemented yet!\nPlease try another option.\n");
                        }else{
                            printf("\nAdding students was incomplete!!\n");
                            return;
                        }
                    } else {
                        break;
                    }
                }

                printf("\nAvailable courses under department:\n");
                num = 0;
                for (int i = 0; i < MAX_DEPT; i++) {
                    if (strcmp(courses[i].departmentId, departments[dep].Dept_ID) == 0) {
                        num++;
                        printf("%d. %s | ID - [%s]\n", num, courses[i].name, courses[i].id);
                    }
                }

                label5:
                printf("\nEnter the course ID: ");
                scanf("%s", new_value);
                bool flag5 = true;
                for (int i = 0; i < MAX_CORS; i++){
                    if(strcmp(courses[i].id,new_value) == 0) {
                        flag5 = false;
                        break;
                    }           
                }
                if (flag5){
                    printf("Entered wrong Course ID! Please try again.\n");
                    while(getchar() != '\n');
                    goto label5;
                }
                break;

                // printf("\nAvailable courses for selection: \n");
                // num = 0;
                // for (int i = 0; i < MAX_DEPT; i++) {
                //     if (strcmp(courses[i].departmentId, students[idval].Std_Department) == 0) {
                //         printf("%d. %s | ID - [%s]\n", num + 1, courses[i].name, courses[i].id);
                //     }
                // }
                // printf("Enter new course ID: ");
                // scanf("%s", new_value);
                // break;
            default:
                printf("Invalid field selected. Please try again.\n");
                continue;
        }
        
        // Save the old value before editing
        if (strcmp(field, "Name") == 0) {
            strcpy(old_value, students[idval].Std_Name);
            strcpy(students[idval].Std_Name, new_value);
            printf("\nStudent name was updated.\n");
        } else if (strcmp(field, "Contact_number") == 0) {
            strcpy(old_value, students[idval].Std_ContactNo);
            strcpy(students[idval].Std_ContactNo, new_value);
            printf("\nStudent contact number was updated.\n");
        } else if (strcmp(field, "Email") == 0) {
            strcpy(old_value, students[idval].Std_Email);
            strcpy(students[idval].Std_Email, new_value);
            printf("\nStudent email was updated.\n");
        } else if (strcmp(field, "Department") == 0) {
            strcpy(old_value, students[idval].Std_Department);
            strcpy(students[idval].Std_Department, new_value);
            printf("\nStudent department was updated.\n");
        } else if (strcmp(field, "Course") == 0) {
            strcpy(old_value, students[idval].Std_Course);
            strcpy(students[idval].Std_Course, new_value);
            printf("\nStudent course was updated.\n");
        } 
        
        // Call the store_history function with the correct arguments
        store_history(USER_ID, "Edited", id, field, old_value, new_value);
        
        while(getchar() != '\n');
        printf("\nDo you want to update more details of the student? \n(y - for yes/n - for no): ");
        scanf("%c", &contchoice);
        if (tolower(contchoice) == 'y') {
            continue;
        } else if (tolower(contchoice) == 'n'){
            break;
        }
        break;
    }
}

char *startingMenu[] = {
        "Add Student",
        "View Student Details",
        "Update Student Details",
        "Delete Student",
        "History",
        "Exit"
    };

char *viewMenu[] = {
    "View all the students details",
    "Search for a student by ID",
    "Exit to main menu"
};


void Student_main (char *USER_ID){
    char *choice[20];
    int choicenum,viewchoise;
    char id[10];
    while (true) {
        printf("\n--------------------------------------------\n");
        printf("    STUDENT MANAGEMENT SYSTEM - STUDENTS               ");
        printf("\n--------------------------------------------\n");
        printf("1. Add Student\n");
        printf("2. View Student Details\n");
        printf("3. Update Student Details\n");
        printf("4. Delete Student\n");
        printf("5. History\n");
        printf("6. Exit\n");
        printf("Enter number for your choice: ");
        
        choicenum = getInput(startingMenu, sizeof(startingMenu)/sizeof(startingMenu[0]));

        switch (choicenum) {
            case 1:
                add_student(USER_ID);
                while (true)
                {
                    printf("\nDo you want to continue adding students? \n(y - for yes/n - for no): ");
                    int yesno = checkYesNo();
                    if (yesno == 1){
                        add_student(USER_ID);
                        continue;
                    } else if(yesno == 2){
                        break;
                    }
                }
                break;
            case 2:
                rerunviewMenu:
                printf("\n1. View all the students details.\n2. Search for a specific student.\n3. Exit to main menu.\nEnter the number for your choice : ");
                // scanf("%d", &viewchoise);
                viewchoise = getInput(viewMenu, sizeof(viewMenu)/sizeof(viewMenu[0]));
                if(viewchoise == 1){
                    display_students();
                    printf("\nDo you want to search for a specific student?\n(y - for yes/n - for no): ");
                    int yesno = checkYesNo();
                    if (yesno == 1){
                        search_student();
                        continue;
                    } else if(yesno == 2){
                        break;
                    }
                    while (true)
                    {
                        printf("\nDo you want to continue search for another student's records? \n(y - for yes/n - for no): ");
                        int yesnorecur = checkYesNo();
                        if (yesnorecur == 1){
                            search_student();
                            continue;
                        } else if(yesnorecur == 2){
                            break;
                        }
                    }
                    break;
                } else if (viewchoise == 2) {
                    search_student();
                    while (true)
                    {
                        printf("\nDo you want to continue search for another student's records? \n(y - for yes/n - for no): ");
                        int yesno = checkYesNo();
                        if (yesno == 1){
                            search_student();
                            continue;
                        } else if(yesno == 2){
                            break;
                        }
                    }
                } else if(viewchoise == 3) {
                    break;
                } else {
                    printf("Invalid Choice!\n");
                    goto rerunviewMenu;
                }
                break;
            case 3:
                edit_student(USER_ID);
                while (true)
                {
                    printf("\nDo you want to edit another student's records? \n(y - for yes/n - for no): ");
                    int yesno = checkYesNo();
                    if (yesno == 1){
                    edit_student(USER_ID);
                        continue;
                    } else if(yesno == 2){
                        break;
                    }
                }
                break;
            case 4:
                delete_student(USER_ID);
                while (true)
                {
                    printf("\nDo you want to continue deleting records? \n(y - for yes/n - for no): ");
                    int yesno = checkYesNo();
                    if (yesno == 1){
                        delete_student(USER_ID);
                        continue;
                    } else if(yesno == 2){
                        break;
                    }
                }
                break;
            
            case 5:
                display_history();
                break;
            case 6:
                printf("Exiting to main menu. Thank You!\n");
                return;
            default:
                if(choicenum == -1){
                    printf( "Invalid choice. Please try again with number or the specific word.\n");
                }else{
                    printf("Invalid choice. Please enter a number between 1 and 6.\n");
                }    
        }
    }
}