// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<time.h>
// #include<ctype.h>
// #include "Data_Base.h"

//Git try - Commiiiiiiiiiiiiiiiiiiiiiiiiitttttttttttttttttttttttttttt--pushpandanP..... 
//hellloooooo

typedef struct{
    char Dept_ID[MAX_ID_LEN];
    char Del_By[MAX_NAME_LEN];
    char Del_T[MAX_NAME_LEN];
}Department_History;

Department_History department_history_array[MAX_DEPT];

void add_department();
void display_department();
void display_specific_department();
void update_department();
void delete_department(char *User_ID);
void view_delete();
int find_no_students(char department_id[MAX_ID_LEN]);
int find_no_lecturers(char department_id[MAX_ID_LEN]);
bool is_string_len_exceed(char text[], int text_len);
bool is_capitalized(const char *text);
bool is_only_letter(const char *input);
int dept_id_valid(char text[]);
int dept_name_valid(char text[]);
bool is_digit(const char *str);
void display_course();
void display_lecturers();
void available_department();
void view_std();

int add_dept_count = 2;
int del_dept_count = 0;

void Department_main(char *User_ID)
{      
    int choice;
    int department_del_count = 0;

    do
    {
        printf("\n--------------------------------------------\n");
        printf("   STUDENT MANAGEMENT SYSTEM - DEPARTMENT         ");
        printf("\n--------------------------------------------\n");
        printf("1. Add Department\n");
        printf("2. View Department\n");
        printf("3. Update Department\n");
        printf("4. Delete Department\n");
        printf("5. View History\n");
        printf("6. Exit\n\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        getchar();
        int display_choice;

        switch(choice)
        {
        case 1:
            add_department();
            break;
        case 2:
            printf("\nView Department:\n\n");
            do {
                printf("\n1. View all departments\n");
                printf("2. View specific department details\n");
                printf("3. View courses\n");
                printf("4. View Lecturers\n");
                printf("5. View students\n");
                printf("6. Exit to main menu\n");
                printf("\nEnter your choice: ");
                scanf("%d", &display_choice);
                getchar();

                switch (display_choice) {
                    case 1:
                        display_department();
                        break;
                    case 2:
                        display_specific_department();
                        break;
                    case 3:
                        display_course();
                        break;
                    case 4:
                        display_lecturers();
                        break;
                    case 5:
                        view_std();
                        break;
                    case 6:
                        printf("Exiting to main menu...\n");
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                }
            } while (display_choice != 6);
            break;
        case 3:
            update_department();
            break;
        case 4:
            delete_department(User_ID);
            break;
        case 5:
            view_delete();
            break;
        case 6:
            printf("Exiting to main menu. Thank You!\n");
            return;
        default:
            printf("\nInvalid choice! Please enter a number between 1 and 6\n");
            break;
        }

    } while (choice != 6);
}

//create department
void add_department()
{
    Department new_department;

    do
    {
        printf("Department ID example : Engineering - \"EN\". (Letters should be Capitalized)\n");
        printf("Enter Department ID : ");
        scanf("%s", new_department.Dept_ID);
    } while (dept_id_valid(new_department.Dept_ID) != 0);

    do
    {
        printf("\nDepartment Name example : Engieerning Department\n");
        printf("Enter Department Name : ");
        getchar();
        fgets(new_department.Dept_Name, sizeof(new_department.Dept_Name), stdin);
        new_department.Dept_Name[strcspn(new_department.Dept_Name, "\n")] = '\0';
    } while (dept_name_valid(new_department.Dept_Name) != 0);

    printf("\nLecturer ID format : L_0XX. (Range of xx : 00 to 15)\n");
    printf("Enter head of Department : ");
    fgets(new_department.Dept_Head, sizeof(new_department.Dept_Head), stdin);
    new_department.Dept_Head[strcspn(new_department.Dept_Head, "\n")] = '\0';

    int lec_av = 0;

    for(int i = 0; i < MAX_LEC; i++)
    {
        if(strcmp(new_department.Dept_Head, lecturers[i].id) == 0 && lecturers[i].active)
        {
            lec_av = 1;
            break;
        }
    }

    while(lec_av != 1)
    {
        printf("\nLecturer with \"%s\" ID not available\n", new_department.Dept_Head);
        printf("\nPlease enter a correct ID : ");
        fgets(new_department.Dept_Head, sizeof(new_department.Dept_Head), stdin);
        new_department.Dept_Head[strcspn(new_department.Dept_Head, "\n")] = '\0';

        for(int i = 0; i < MAX_LEC; i++)
        {
            if(strcmp(new_department.Dept_Head, lecturers[i].id) == 0 && lecturers[i].active)
            {
                lec_av = 1;
                break;
            }
        }
    }

    new_department.active = true;

    departments[add_dept_count++] = new_department;

    printf("\nDepartment added successfully.\n");

    char choice;
    printf("Do you want to add another department? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        add_department();
    }
}

//View all department details
void display_department()
{
    char Lecturer_Name[MAX_NAME_LEN];

    printf("\n---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-40s | %-30s | %-20s | %-20s |\n", "Department ID", "Department Name", "Head of Department", "No of Students", "No of Lecturers");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(departments[i].active)
        {
            for(int r = 0; r < MAX_LEC; r++)
            {
                if(strcmp(departments[i].Dept_Head, lecturers[r].id) == 0 && lecturers[r].active)
                {
                    strcpy(Lecturer_Name, lecturers[r].name);
                    break;
                }
                else
                {
                    strcpy(Lecturer_Name, "N/A");
                }
            }
            printf("| %-15s | %-40s | %-30s | %-20d | %-20d |\n", departments[i].Dept_ID, departments[i].Dept_Name, Lecturer_Name, find_no_students(departments[i].Dept_ID), find_no_lecturers(departments[i].Dept_ID));
        }
    }

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    char choice;
    printf("Do you want to view another department? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        display_department();
    }
}

//function to display courses and modules under courses
void display_course()
{
    char department_ID[MAX_ID_LEN];

    available_department();

    printf("Enter Department to view course details : ");
    scanf("%s", department_ID);

    int dept_av = 0;

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(strcmp(department_ID, departments[i].Dept_ID) == 0 && departments[i].active)
        {
            dept_av = 1;
            break;
        }
    }

    while(dept_av != 1)
    {
        printf("\nDepartment with \"%s\" ID not available\n", department_ID);
        printf("\nPlease enter a correct ID : ");
        fgets(department_ID, sizeof(department_ID), stdin);
        department_ID[strcspn(department_ID, "\n")] = '\0';

        for(int i = 0; i < MAX_DEPT; i++)
        {
            if(strcmp(department_ID, departments[i].Dept_ID) == 0 && departments[i].active)
            {
                dept_av = 1;
                break;
            }
        }
    }

    printf("\nCourses : \n");
    
    for(int r = 0; r < MAX_CORS; r++)
    {
        if(strcmp(department_ID, courses[r].departmentId) == 0 && courses[r].active)
        {
            printf("\n%-5s : %-20s\n\n", courses[r].id, courses[r].name);
            for(int x = 0; x < MAX_MOD; x++)
            {
                if(strcmp(courses[r].id, modules[x].course_id) == 0 && modules[x].active)
                {
                    printf("\t%-5s : %-30s\n", modules[x].module_id, modules[x].module_name);
                }
            }
        }
    }

    char choice;
    printf("Do you want to view another course? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        display_course();
    }
}

//function to view lecturers
void display_lecturers()
{
    char department_ID[MAX_ID_LEN];

    available_department();

    printf("Enter Department to view course details : ");
    scanf("%s", department_ID);

    int dept_av = 0;

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(strcmp(department_ID, departments[i].Dept_ID) == 0 && departments[i].active)
        {
            dept_av = 1;
            break;
        }
    }

    while(dept_av != 1)
    {
        printf("\nDepartment with \"%s\" ID not available\n", department_ID);
        printf("\nPlease enter a correct ID : ");
        fgets(department_ID, sizeof(department_ID), stdin);
        department_ID[strcspn(department_ID, "\n")] = '\0';

        for(int i = 0; i < MAX_DEPT; i++)
        {
            if(strcmp(department_ID, departments[i].Dept_ID) == 0 && departments[i].active)
            {
                dept_av = 1;
                break;
            }
        }
    }

    printf("\nLecturers :\n");
    
    for(int r = 0; r < MAX_LEC; r++)
    {
        if(strcmp(department_ID, lecturers[r].department_id) == 0 && lecturers[r].active)
        {
            printf("\t%-5s : %-20s\n", lecturers[r].id, lecturers[r].name);
        }
    }

    char choice;
    printf("Do you want to view another department's lecturers? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        display_lecturers();
    }
}

void display_specific_department()
{
    char department_ID[MAX_ID_LEN];
    char Lecturer_Name[MAX_NAME_LEN];

    available_department();

    do
    {
        printf("Enter Department ID to view details: ");
        scanf("%s", department_ID);
    } while (dept_id_valid(department_ID) != 0);
    
    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(strcmp(departments[i].Dept_ID, department_ID) == 0 && departments[i].active)
        {
            //loop for finding lecturer name using lecturer ID
            for(int r = 0; r < MAX_LEC; r++)
            {
                if((strcmp(departments[i].Dept_Head, lecturers[r].id) == 0) && lecturers[r].active == true)
                {
                    strcpy(Lecturer_Name, lecturers[r].name);
                    break;
                }
                else
                {
                    strcpy(Lecturer_Name, "N/A");
                }
            }            

            printf("\n---------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-15s | %-40s | %-30s | %-20s | %-20s |\n", "Department ID", "Department Name", "Head of Department", "No of Students", "No of Lecturers");
            printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-15s | %-40s | %-30s | %-20d | %-20d |\n", departments[i].Dept_ID, departments[i].Dept_Name, Lecturer_Name, find_no_students(departments[i].Dept_ID), find_no_lecturers(departments[i].Dept_ID));
            printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }

    char choice;
    printf("Do you want to view another department? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        display_specific_department();
    }
}

void update_department() {
    char department_ID[MAX_ID_LEN];
    int found = 0;
    Department up_dept;

    available_department();

    printf("\nEnter Department ID to update : ");
    getchar();
    fgets(department_ID, sizeof(department_ID), stdin);
    department_ID[strcspn(department_ID, "\n")] = '\0';

    for(int i = 0; i < MAX_DEPT; i++) {
        if(strcmp(departments[i].Dept_ID, department_ID) == 0 && departments[i].active) {
            printf("Department found.\n");

            char update_choice[20];
            do {
                printf("\nWhich field do you want to update?\n");
                printf("1. Department Name\n");
                printf("2. Head of Department\n");
                printf("3. Exit\n");
                printf("Enter your choice: ");
                fgets(update_choice, sizeof(update_choice), stdin);
                update_choice[strcspn(update_choice, "\n")] = '\0';

                if(strcmp(update_choice, "1") == 0) {
                    printf("Enter Department Name : ");
                    fgets(departments[i].Dept_Name, sizeof(departments[i].Dept_Name), stdin);
                    departments[i].Dept_Name[strcspn(departments[i].Dept_Name, "\n")] = '\0';
                    printf("Department Name updated successfully.\n");
                } else if(strcmp(update_choice, "2") == 0) {
                    printf("Enter new Head of Department : ");
                    fgets(departments[i].Dept_Head, sizeof(departments[i].Dept_Head), stdin);
                    departments[i].Dept_Head[strcspn(departments[i].Dept_Head, "\n")] = '\0';
                    printf("Head of Department updated successfully.\n");
                } else if(strcmp(update_choice, "3") == 0) {
                    printf("Exiting update menu...\n");
                    break;
                } else {
                    printf("Invalid choice!\n");
                }
            } while(1);

            found = 1;
            break;
        }
    }

    if(!found) {
        printf("\nDepartment with ID \"%s\" not found.\n", department_ID);
    }

    char choice;
    printf("Do you want to update another department? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        update_department();
    }
}

void delete_department(char *User_ID)
{
    char department_ID[MAX_ID_LEN];
    int found = 0;

    available_department();

    printf("Enter Department ID to delete : ");
    scanf("%s", department_ID);

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(strcmp(departments[i].Dept_ID, department_ID) == 0 && departments[i].active)
        {
            strcpy(department_history_array[del_dept_count].Dept_ID, departments[i].Dept_ID);
            fgets(department_history_array[del_dept_count].Del_By, sizeof(department_history_array[del_dept_count].Del_By), stdin);
            strcpy(department_history_array[del_dept_count].Del_By,User_ID);
            department_history_array[del_dept_count].Del_By[strcspn(department_history_array[del_dept_count].Del_By, "\n")] = '\0';

            time_t now;
            time(&now);
            strcpy(department_history_array[del_dept_count].Del_T, ctime(&now));

            (del_dept_count)++;
            departments[i].active = false;

            
            for(int r = 0; r < MAX_CORS; r++)
            {
                if(strcmp(department_ID, courses[r].departmentId) == 0)
                {
                    courses[r].active = false;
                    for(int x = 0; x < MAX_MOD; x++)
                    {
                        if(strcmp(courses[r].id, modules[x].course_id) == 0)
                        {
                            modules[x].active = false;
                        }
                    }
                }
            }

            printf("Department deleted successfully.\n");
            found = 1;
            break;   
        }
    }
    if(!found)
    {
        printf("Department with ID \"%s\" not found.\n", department_ID);
    }

    char choice;
    printf("Do you want to delete another department? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
    delete_department(User_ID);
        }
}

void view_delete()
{
    printf("\nDeletion History\n");

    if(del_dept_count == 0)
    {
        printf("No deletion records found.\n");
    }

    else
    {
        printf("\nDepartment ID\t\tDeleted By\t\t\tDeletion Time\n\n");
        for(int i = 0; i < del_dept_count; i++)
        {
            printf("%-24s%-32s%s", department_history_array[i].Dept_ID, department_history_array[i].Del_By, department_history_array[i].Del_T);
        }
    }
}

//Function to find number of students
int find_no_students(char department_id[MAX_ID_LEN])
{
    int total = 0;

    for(int i = 0; i < MAX_STD; i++)
    {
        if(strcmp(department_id, students[i].Std_Department) == 0 && students[i].Std_Visible)        
        {
            total++;
        }
    }

    return total;
}

//Function to find number of Lecturers
int find_no_lecturers(char department_id[MAX_ID_LEN])
{
    int total = 0;

    for(int i = 0; i < MAX_LEC; i++)
    {
        if(strcmp(department_id, lecturers[i].department_id) == 0 && lecturers[i].active)        
        {
            total++;
        }
    }

    return total;
}

bool is_string_len_exceed(char text[], int text_len)
{
    if(strlen(text) > text_len)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_capitalized(const char *text) {
    while (*text != '\0') {
        if (!isupper(*text)) {
            return true;
        }
        text++;
    }
    return false;
}

bool is_only_letter(const char *input) {
    while (*input != '\0') {
        if (!isalpha(*input)) {
            return true; // Not only letters
        }
        input++;
    }
    return false; // Contains only letters
}

bool is_digit(const char *str) {
    while (*str) {
        if (isdigit(*str)) {
            return true;
        }
        str++;
    }
    return false;
}

int dept_id_valid(char text[])
{
    int count = 0;

    if(is_string_len_exceed(text, 2))
    {
        count++;
    }

    if(is_capitalized(text))
    {
        count++;    
    }

    if(is_only_letter(text))
    {
        count++;
    }

    if(count != 0)
    {
        printf("\nDepartment ID not in correct format.\n\n");
    }

    return count;
}

int dept_name_valid(char text[])
{
    int count = 0;

    if(is_string_len_exceed(text, MAX_NAME_LEN))
    {
        count++;
    }

    if(is_digit(text))
    {
        count++;
    }

    if(count != 0)
    {
        printf("Department name should only contain letters. (Max length : 50)\n\n");
    }

    return count;
}

void available_department()
{
    printf("Available Departments : \n");

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(departments[i].active)
        {
            printf("\t%-5s\n", departments[i].Dept_ID);
        }
    }
}

//viewing students
void view_std()
{
    char dept_id[MAX_ID_LEN];
    available_department();

    printf("Enter Department ID : ");
    scanf("%s", dept_id);

    for(int i = 0; i < MAX_DEPT; i++)
    {
        if(strcmp(dept_id, departments[i].Dept_ID) == 0 && departments[i].active)
        {
            printf("Department : %s\n\n", dept_id);
            printf("\tStudent ID\tStudnet Name\t\t\t\tStudent Course\t\tStudent Phone No\n\n");
        
            for(int r = 0; r < MAX_STD; r++)
            {
                if(strcmp(dept_id, students[r].Std_Department) == 0 && students[r].Std_Visible)
                {
                    printf("\t%-5s      -    %-30s      -    %-15s      -    %-15s\n", students[r].Std_ID, students[r].Std_Name, students[r].Std_Course, students[r].Std_ContactNo);
                }
            }
        }
    }
}

