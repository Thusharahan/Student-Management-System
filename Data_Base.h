//Header files
#include<stdbool.h>

//Maximum Number of Entity Entries
#define MAX_DEPT 10
#define MAX_CORS 20
#define MAX_MOD 50
#define MAX_LEC 15
#define MAX_STD 100

//Max char array lenghts
#define MAX_ID_LEN 10
#define MAX_NAME_LEN 50
#define MAX_DES_LEN 100
#define MAX_PHN_LEN 15

//***************************************DEPARTMENT****************************************************
typedef struct{
    char Dept_ID[MAX_ID_LEN];
    char Dept_Name[MAX_NAME_LEN];
    char Dept_Head[MAX_ID_LEN];
    bool active;
}Department;

Department departments[MAX_DEPT] = {
    {"EN", "Engineering", "L_005", true},
    {"IT", "Information and Technology", "L_003", true}
};

//***************************************COURSE********************************************************
typedef struct {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char departmentId[MAX_ID_LEN];
    char inChargeLecturerId[MAX_ID_LEN];
    bool active;
} Course;

Course courses[MAX_CORS] = {
    {"EN_01", "HND", "EN", "L_001", true},
    {"IT_01", "HND", "IT", "L_002", true},
    {"EN_02", "Degree", "EN", "L_003", true},
    {"IT_02", "Degree", "IT", "L_004", true},
    {"EN_03", "Masters", "EN", "L_005", true},
    {"IT_03", "Masters", "IT", "L_006", true},
};

//***************************************MODULES********************************************************
typedef struct Module {
    char course_id[MAX_ID_LEN];
    char module_id[MAX_ID_LEN];
    char module_name[MAX_NAME_LEN];
    char module_description[MAX_DES_LEN];
    char lecturer_id[MAX_ID_LEN];
    bool active;
} Module;

Module modules[MAX_MOD] = {
    //Engineering Level 1
    {"EN_01", "EN_0101", "Electrical", "Fundamentals of electrical engineering", "L_001", true},
    {"EN_01", "EN_0102", "Mechanical", "Basics of mechanical engineering principles", "L_002", true},
    {"EN_01", "EN_0103", "Computer Science", "Introduction to computer science concepts", "L_002", true},
    
    //Engineering Level 2
    {"EN_02", "EN_0201", "Mathematics", "Foundations of mathematics", "L_004", true},
    {"EN_02", "EN_0202", "Physics", "Principles of physics", "L_005", true},
    {"EN_02", "EN_0203", "Chemistry", "Basics of chemistry", "L_006", true},
    
    //Masters Engineering
    {"EN_03", "EN_0301", "Advanced Mathematics", "Advanced topics in mathematics", "L_001", true},
    {"EN_03", "EN_0302", "Quantum Mechanics", "Study of quantum mechanics", "L_002", true},
    {"EN_03", "EN_0303", "Data Analysis", "Data analysis techniques", "L_003", true},

    //IT Level 1
    {"IT_01", "IT_0101", "Introduction to Information Technology", "Overview of IT concepts", "L_004", true},
    {"IT_01", "IT_0102", "Data Structures and Algorithms", "Fundamentals of data structures and algorithms", "L_005", true},
    {"IT_01", "IT_0103", "Database Management Systems", "Introduction to DBMS", "L_006", true},
    
    //IT Level 2
    {"IT_02", "IT_0201", "Computer Networks", "Introduction to computer networking", "L_001", true},
    {"IT_02", "IT_0202", "Operating Systems", "Principles of operating systems", "L_002"},
    {"IT_02", "IT_0203", "Software Engineering", "Basics of software engineering principles", "L_003", true},
    
    //Masters IT
    {"IT_03", "IT_0301", "Machine Learning", "Principles of machine learning", "L_004", true},
    {"IT_03", "IT_0302", "Cyber Security", "Introduction to cyber security concepts", "L_005", true},
    {"IT_03", "IT_0303", "Cloud Computing", "Overview of cloud computing technologies", "L_006", true}
};

//***************************************LECTURERS********************************************************
typedef struct {
    char name[MAX_NAME_LEN];
    char id[MAX_ID_LEN];
    char gender;
    char phone[MAX_PHN_LEN];
    char email[MAX_NAME_LEN];   
    char department_id[MAX_ID_LEN];
    bool active;
} Lecturer;

Lecturer lecturers[MAX_LEC] = {
    {"RAJAN", "L_001", 'M', "0762458907", "lecturer_001@gmail.com", "EN", true},
    {"SAMAROKON", "L_002", 'M', "0762458908", "lecturer_002@gmail.com", "IT", true},
    {"DAVID", "L_003", 'M', "0762458909", "lecturer_003@gmail.com", "IT", true},
    {"EMILY", "L_004", 'F', "0762458910", "lecturer_004@gmail.com", "EN", true},
    {"MICHAEL", "L_005", 'M', "0762458911", "lecturer_005@gmail.com", "IT", true},
    {"SOPHIA", "L_006", 'F', "0762458912", "lecturer_006@gmail.com", "EN", true}
};

//***************************************STUDENTS********************************************************
typedef struct
{
    //This variables are unique for the students.
    char Std_Name[MAX_NAME_LEN];
    char Std_ID[MAX_ID_LEN];
    char Std_ContactNo[MAX_NAME_LEN];
    char Std_Email[MAX_NAME_LEN];

    //This varibles will be implemented in other fields.
    char Std_Department[MAX_ID_LEN];
    char Std_Course[MAX_ID_LEN];

    //To check the visibility if the students.
    bool Std_Visible;
} Student;

Student students[MAX_STD] = {
        {"KAVITHA RAJENDRAN", "S_001", "0763456789", "kavitha@gmail.com", "EN", "EN_01", true},
        {"VIJAY KUMAR", "S_002", "0768765432", "vijay@yahoo.com", "IT", "IT_02", true},
        {"SARANYA MANOHARAN", "S_003", "0762233445", "saranya@gmail.com", "EN", "EN_03", true},
        {"PRIYA ARUMUGAM", "S_004", "0765566677", "priya@yahoo.com", "IT", "IT_01", true},
        {"RAJESHWARI KRISHNAN", "S_005", "0764433322", "rajeshwari@gmail.com", "EN", "EN_02", true},
        {"GOKUL ANAND", "S_006", "0769988877", "gokul@yahoo.com", "IT", "IT_03", true},
        {"HARINI SENTHIL", "S_007", "0767733344", "harini@gmail.com", "EN", "EN_01", true},
        {"MANOJ BALASUBRAMANIAN", "S_008", "0766622211", "manoj@yahoo.com", "IT", "IT_02", true},
        {"DIVYA NATARAJAN", "S_009", "0763311122", "divya@gmail.com", "EN", "EN_03", true},
        {"VIGNESH RAVI", "S_010", "0768899988", "vignesh@yahoo.com", "IT", "IT_01", true},
        {"ESHAN SAMARAKOON", "S_011", "0762211133", "eshan@gmail.com", "EN", "EN_02", true},
        {"NADEESHA WEERASINGHE", "S_012", "0769911122", "nadeesha@yahoo.com", "IT", "IT_03", true},
        {"CHATHURANGA SENANAYAKE", "S_013", "0767788899", "chathuranga@gmail.com", "EN", "EN_01", true},
        {"THILINI GUNARATNE", "S_014", "0765533344", "thilini@yahoo.com", "IT", "IT_02", true},
        {"CHAMINDA RATHNAYAKE", "S_015", "0764422211", "chaminda@gmail.com", "EN", "EN_03", true},
        {"RENUKA JAYASURIYA", "S_016", "0763344455", "renuka@yahoo.com", "IT", "IT_01", true},
        {"DINUSHA PERERA", "S_017", "0762233344", "dinusha@gmail.com", "EN", "EN_02", true},
        {"THARINDU FERNANDO", "S_018", "0768877766", "tharindu@yahoo.com", "IT", "IT_03", true},
        {"SANDUNI SILVA", "S_019", "0769988877", "sanduni@gmail.com", "EN", "EN_01", true},
        {"HASITHA PERERA", "S_020", "0765566677", "hasitha@yahoo.com", "IT", "IT_02", true}
    };
