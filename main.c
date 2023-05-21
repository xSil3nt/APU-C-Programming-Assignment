#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "hash.h"

//Set constants for variable lengths
#define PASSWORD_LENGTH 24
#define MAX_PASS_USER 25
#define MAX_LINE 200
#define MAX_ID 10
#define MAX_NAME_LEN 25

//Define colors to add some spice to outputs :D
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define UDL "\x1B[4m"

char securePass[25];

void main(), pause(), mainMenu(), adminLogin(), adminMenu(), tutorLogin(), tutorMenu(), studentLogin(), studentMenu(), regTutor(), delTutor(), regStudent(), delStudent(), createSession(), displaySessions(), delSession(), displaySessionStudents(), adminEnrollStudent(), enrollStudent(), displayStudents(), viewTutorSessions(), viewStudentSessions();
char* lookupStudentName();
char* lookupTutorName();
char* lookupTutorSubject();
char* secureInput();

char currentUser[MAX_PASS_USER];

    //Main Menu function
    void mainMenu() {
        //Declare var for selection
        int choice;

        //Show prompt
        //printf(BOLD UDL BLU "APU " CYN "Programming " GRN "Cafe\n\n" RESET);
        printf(BLU BOLD" ,.  ;-.  .  .   ;-.                                               ,-.             \n");
        printf("/  \\ |  ) |  |   |  )                                 o           /         ,-     \n");
        printf("|--| |-'  |  |   |-'  ;-. ,-. ,-: ;-. ,-: ;-.-. ;-.-. . ;-. ,-:   |    ,-:  |  ,-. \n");
        printf("|  | |    |  |   |    |   | | | | |   | | | | | | | | | | | | |   \\    | |  |- |-' \n");
        printf("'  ' '    `--`   '    '   `-' `-| '   `-` ' ' ' ' ' ' ' ' ' `-|    `-' `-`  |  `-' \n");
        printf("                              `-'                           `-'            -'      \n"RESET);
        printf("");
        
        printf(YEL "1. Login as Admin\n" );
        printf("2. Login as Tutor\n" );
        printf("3. Login as Student\n");
        printf(RED "4. Exit\n" RESET);
        printf("Enter your choice: ");
        //Ask for selection
        scanf("%d", &choice);

        //Call respective function depending on selection, and return to menu if invalid selection
        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                tutorLogin();
                break;
            case 3:
                studentLogin();
                break;
            case 4:
                printf("Thank you for using the APU Programming Cafe\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                mainMenu();
        }
    }

    char* secureInput() {
        //Declare variables
        int i = 0;
        char password[PASSWORD_LENGTH + 1];
        int input;
        printf("\nEnter Password (Upto 24 characters): ");
        while (i < PASSWORD_LENGTH) {
            input = getch();
            //Handle spaces and ESC character
            if (input == ' ' || input == 27) {
                continue;
            
            //Handle backspace char
            } else if (input == '\b') {
                //Trigger backspace if there are characters in the buffer, continue/ignore backspace otherwise
                if (i > 0) {
                    printf("\b \b");
                    --i;
                } else {
                    continue;
                }

                //If enter key or tab is used, the loop ends, since that marks the end of the password
            } else if (input == '\r' || input == '\t') {
                break; 

                //WEIRDEST bug I've ever seen, turns out CTRL+C = heart symbol, so it prevents exit. For some reason that = 3 ?????? wtf
            } else if (input == 3) {
                exit(0); 
                
                //Handle NULL char
            } else if (input == 0) {
                input= getch();
                continue;
            } else {
                //If the character entered is a valid character (not a space, Backspace, Enter, Tab, null character or extended ASCII code)
                //It is stored in the password buffer at position i, and i is incremented 
                password[i++] = input;
                printf("*");
            }
        }
        //Set the char after the last char of the password to \0 (null) to indicate end of password
        password[i] = '\0';
        strcpy(securePass, password);

        //Return password
        return securePass;
    }

    //Login function for admin, only requires a password, no username needed. Password is hardcoded abc
    //If correct password is entered, trigger admin menu, otherwise return to login screen
    void adminLogin() {
        //Declare variable for password input, and prompt for it
        char password[MAX_PASS_USER];
        printf("Logging in as "BOLD RED"ADMIN\n"RESET);
        strcpy(password, secureInput());
        
        //Check if input is = hardcoded password abc, strcmp returns 0 if strings match
        if (strcmp(password, "abc") == 0) {
            adminMenu();
        } else {
            //Call function again after throwing error if incorrect password is entered
            printf(RED "Incorrect password. Please try again.\n" RESET);
            adminLogin();
        }
    }

    void adminMenu() {
        //Declare var for selection
        int choice;
            //Show prompt
            printf(RED BOLD UDL"\nAdmin Menu\n" RESET);
            printf("\n");
            printf("1. Register tutor\n");
            printf("2. Register student\n");
            printf("3. Remove tutor\n");
            printf("4. Remove student\n");
            printf("5. Add session\n");
            printf("6. Enroll student to session\n");
            printf("7. Display sessions\n");
            printf("8. Remove sessions\n");
            printf("9. Display students assigned to a session\n");
            printf("10. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    //Call function to register tutor
                    regTutor();
                    pause();
                    adminMenu();
                case 2:
                    //Call function to register student
                    regStudent();
                    pause();
                    adminMenu();
                case 3:
                    //Call function to remove tutor
                    delTutor();
                    pause();
                    adminMenu();
                case 4:
                    //Call function to remove student
                    delStudent();
                    pause();
                    adminMenu();
                case 5:
                    //Call function to add session
                    createSession();
                    pause();
                    adminMenu();
                case 6:
                    //Call function to enroll student to session
                    adminEnrollStudent();
                    pause();
                    adminMenu();
                case 7:
                    //Call function to display sessions
                    displaySessions();
                    pause();
                    adminMenu();
                case 8:
                    //Call function to delete session
                    delSession();
                    pause();
                    adminMenu();
                case 9:
                    //Call function to show students assigned to a specific session
                    displaySessions();
                    displaySessionStudents();
                    pause();
                    adminMenu();
                case 10:
                    //Logout, return to main menu
                    mainMenu();
                    strcpy(currentUser, "");
                default:
                    printf(RED "\nInvalid choice. Please try again.\n" RESET);
            }
    }

    void regTutor() {
        //Declare variables for tutor details
        char tutorId[MAX_ID], tutorPass[MAX_PASS_USER], tutorName[MAX_NAME_LEN], tutorSubject[MAX_NAME_LEN], hashedPass[32];

        //Show list of current tutors
        printf("Currently registered tutors:\n");
        printf(MAG "\n%-10s %-20s %s\n", "Tutor ID", "Subject", "Tutor Name" RESET);
        FILE *tutorList = fopen("tutors.apdata", "r");
        char tutorline[MAX_LINE];
        while (fgets(tutorline, sizeof(tutorline), tutorList)) {
            char *id = strtok(tutorline, ",");
            char *name = strtok(NULL, ";");
            char *subject = strtok(NULL, "#");
            printf("%-10s %-20s %s\n", id, subject, name);
        }
        fclose(tutorList);

        //Prompt for tutor ID
        printf("\nEnter tutor ID (Case sensitive): ");
        scanf("%s", tutorId);

        //Check if tutor ID is already in use
        FILE *tutorCreds = fopen("tutorCreds.apdata", "r");
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), tutorCreds)) {
            char *id = strtok(line, ",");
            if (strcmp(id, tutorId) == 0) {
                printf("\nTutor ID already in use. Please try again.\n");
                fclose(tutorCreds);
                return;
            }
        }
        fclose(tutorCreds);

        //Prompt for tutor details
        printf("Enter tutor password (Case sensitive): ");
        scanf("%s", tutorPass);
        printf("Enter tutor name: ");
        getchar(); // consume the newline character left in the input buffer
        fgets(tutorName, sizeof(tutorName), stdin);
        tutorName[strcspn(tutorName, "\n")] = '\0'; // remove the newline character from the input
        printf("Enter tutor subject: ");
        fgets(tutorSubject, sizeof(tutorSubject), stdin);
        tutorSubject[strcspn(tutorSubject, "\n")] = '\0'; // remove the newline character from the input

        //Find hash of input password & String-ify
        sprintf(hashedPass, "%lu", hash(tutorPass));

        //Add tutor to system
        tutorCreds = fopen("tutorCreds.apdata", "a");
        fprintf(tutorCreds, "%s,%s#\n", tutorId, hashedPass);
        fclose(tutorCreds);

        FILE *tutors = fopen("tutors.apdata", "a");
        fprintf(tutors, "%s,%s;%s#\n", tutorId, tutorName, tutorSubject);
        fclose(tutors);

        printf(GRN BOLD"\nTutor added successfully.\n" RESET);
    }

    void delTutor() {
        //Declare variables for tutor ID
        char tutorId[MAX_ID];

        //Prompt for tutor ID
        printf("\nEnter tutor ID (Case sensitive): ");
        scanf("%s", tutorId);

        //Check if tutor ID exists
        FILE *tutors = fopen("tutors.apdata", "r");
        char line[MAX_LINE];
        int found = 0;
        while (fgets(line, sizeof(line), tutors)) {
            char *id = strtok(line, ",");
            if (strcmp(id, tutorId) == 0) {
                found = 1;
                break;
            }
        }
        fclose(tutors);

        if (!found) {
            printf("\nTutor ID not found. Please try again.\n");
            return;
        }

        //Delete tutor from system
        FILE *temp = fopen("temp.apdata", "w");
        tutors = fopen("tutors.apdata", "r");

        //This was the most annoying part of the assignment so far. This is so dumb, I hate this so much. This took sooooo long to figure out
        while (fgets(line, sizeof(line), tutors)) {
            //strstr looks for tutorId in line, returns NULL if not found
            char *p = strstr(line, tutorId);
            //If strstr can't find tutorId in line, it's a line we want to keep
            //*(p + strlen(tutorId)) != ',' checks if the character right after the tutorId is not a comma, we use a pointer here cus we wanna see the character itself
            //If the next character is a comma, it means the we don't want to keep the line.
            //We do this check in case a password has the tutorId in the password, eg: "abcT01cba"
            if (!p || *(p + strlen(tutorId)) != ',') {
                fprintf(temp, "%s", line);
            }
        }
        fclose(tutors);
        fclose(temp);

        //Delete the original file, and rename temp file to the original file name
        remove("tutors.apdata");
        rename("temp.apdata", "tutors.apdata");

        //Explaination for the code is above
        temp = fopen("temp.apdata", "w");
        FILE *tutorCreds = fopen("tutorCreds.apdata", "r");
        while (fgets(line, sizeof(line), tutorCreds)) {
            char *p = strstr(line, tutorId);
            if (!p || *(p + strlen(tutorId)) != ',') {
                fprintf(temp, "%s", line);
            }
        }
        fclose(tutorCreds);
        fclose(temp);

        //Delete the original file, and rename temp file to the original file name
        remove("tutorCreds.apdata");
        rename("temp.apdata", "tutorCreds.apdata");

        printf(GRN BOLD"\nTutor deleted successfully." UDL "Don't forget to delete sessions corresponding to this tutor if needed.\n" RESET);
    }

    void regStudent() {
        //Declare variables for student details
        char studentId[MAX_ID], studentPass[MAX_PASS_USER], studentName[MAX_PASS_USER], hashedPass[32];

        //Show list of current students
        printf("Currently registered students:\n");
        printf(MAG "\n%-12s %s\n", "Student ID", "Student Name" RESET);
        FILE *studentList = fopen("students.apdata", "r");
        char studentline[MAX_LINE];
        while (fgets(studentline, sizeof(studentline), studentList)) {
            char *id = strtok(studentline, ",");
            char *name = strtok(NULL, "#");
            printf("%-12s %s\n", id, name);
        }
        fclose(studentList);

        //Prompt for student ID
        printf("\nEnter student ID (Case sensitive, eg: TP001): ");
        scanf("%s", studentId);

        //Check if student ID is already in use
        FILE *studentCreds = fopen("studentCreds.apdata", "r");
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), studentCreds)) {
            char *id = strtok(line, ",");
            if (strcmp(id, studentId) == 0) {
                printf("\nStudent ID already in use. Please try again.\n");
                fclose(studentCreds);
                return;
            }
        }
        fclose(studentCreds);

        //Prompt for student details
        printf("Enter student password (Case sensitive): ");
        scanf("%s", studentPass);
        printf("Enter student name: ");
        getchar(); // consume the newline character left in the input buffer
        fgets(studentName, sizeof(studentName), stdin);
        studentName[strcspn(studentName, "\n")] = '\0'; // remove the newline character from the input

        //Find hash of input password & String-ify
        sprintf(hashedPass, "%lu", hash(studentPass));

        //Add student to system
        studentCreds = fopen("studentCreds.apdata", "a");
        fprintf(studentCreds, "%s,%s#\n", studentId, hashedPass);
        fclose(studentCreds);

        FILE *students = fopen("students.apdata", "a");
        fprintf(students, "%s,%s#\n", studentId, studentName);
        fclose(students);

        printf(GRN BOLD"\nStudent added successfully.\n"RESET);
    }


    void delStudent() {
        //Declare variables for student ID
        char studentId[MAX_ID];

        //Prompt for student ID
        printf("\nEnter student ID (Case sensitive): ");
        scanf("%s", studentId);

        //Check if student ID exists
        FILE *students = fopen("students.apdata", "r");
        char line[MAX_LINE];
        int found = 0;
        while (fgets(line, sizeof(line), students)) {
            char *id = strtok(line, ",");
            if (strcmp(id, studentId) == 0) {
                found = 1;
                break;
            }
        }
        fclose(students);

        if (!found) {
            printf("\nStudent ID not found. Please try again.\n");
            return;
        }

        //Delete student from system
        FILE *temp = fopen("temp.apdata", "w");
        students = fopen("students.apdata", "r");

        //This was the most annoying part of the assignment so far. This is so dumb, I hate this so much. This took sooooo long to figure out
        while (fgets(line, sizeof(line), students)) {
            //strstr looks for studentId in line, returns NULL if not found
            char *p = strstr(line, studentId);
            //If strstr can't find studentId in line, it's a line we want to keep
            //*(p + strlen(studentId)) != ',' checks if the character right after the studentId is not a comma, we use a pointer here cus we wanna see the character itself
            //If the next character is a comma, it means the we don't want to keep the line.
            //We do this check in case a password has the studentId in the password, eg: "abcT01cba"
            if (!p || *(p + strlen(studentId)) != ',') {
                fprintf(temp, "%s", line);
            }
        }
        fclose(students);
        fclose(temp);

        //Delete the original file, and rename temp file to the original file name
        remove("students.apdata");
        rename("temp.apdata", "students.apdata");

        //Explaination for the code is above
        temp = fopen("temp.apdata", "w");
        FILE *studentCreds = fopen("studentCreds.apdata", "r");
        while (fgets(line, sizeof(line), studentCreds)) {
            char *p = strstr(line, studentId);
            if (!p || *(p + strlen(studentId)) != ',') {
                fprintf(temp, "%s", line);
            }
        }
        fclose(studentCreds);
        fclose(temp);

        //Delete the original file, and rename temp file to the original file name
        remove("studentCreds.apdata");
        rename("temp.apdata", "studentCreds.apdata");

        printf(GRN BOLD"\nStudent deleted successfully.\n" RESET);
    }

    void tutorLogin() {
        //Function for logging in tutors
        //TODO: Maybe commonize tutor and student login? Dunno how much work that will be, decide later?? 
        //Declare variables for input, 20 characters should be enough
        //TODO: Maybe declare a const to store max input?
        char username[MAX_PASS_USER], password[MAX_PASS_USER], hashedpass[32];
        //Prompt for input
        printf("Logging in as "BOLD GRN "TUTOR\n" RESET);
        printf("Enter your username (Case sensitive): ");
        scanf("%s", username);
        strcpy(password, secureInput());

        //Find hash of input password & String-ify
        sprintf(hashedpass, "%lu", hash(password));


        //Open the file that stores tutor credentials, and throw an error if file not found
        FILE *tutorCreds = fopen("tutorCreds.apdata", "r");
        if (tutorCreds == NULL) {
            printf("Error: could not open tutor credentials file.\n");
            return;
        }

        //The file stores each set of credentials in a line, # marks the end of the line, commas seperate the credentials by type.
        //Char array to store lines of the file as we loop through the file to find the password and username
        char line[MAX_LINE];
        //Decare pointers to store user and pass found in the file
        char *user, *pass;
        
        //This feels like a confusing way to loop through the file, but I think it's the best
        //fgets takes 3 arguments, where to store the text, max size of text, and where to read from
        //The while loop continues until there is no more text, aka, fgets returns NULL when it reaches the end of the file
        while (fgets(line, sizeof(line), tutorCreds)) {
            //Get username from the line currently being read, by looking for a comma (called the delimiter)
            user = strtok(line, ",");
            //Get password from the line currently being read, looks for hashtag
            //We use NULL as the first argument because we want strtok to continue checking from the where the previous strtok left off, kinda confusing at first, but it works :p
            pass = strtok(NULL, "#");

            //Compare entered details with the ones from the file at the current line, if they match, trigger the tutorMenu
            if (strcmp(username, user) == 0 && strcmp(hashedpass, pass) == 0) {
                printf(GRN BOLD "\nLogin successful!\n" RESET);
                fclose(tutorCreds);
                //Set tutor as current user
                strcpy(currentUser,username);
                tutorMenu();
            }
        }
        //We will exit the loop naturally if we don't find matching credentials, so ask the user to try again.
        printf(RED "\nInvalid username or password. Please try again.\n" RESET);
        fclose(tutorCreds);
        tutorLogin();
    }

    void tutorMenu() {
        int choice;
        printf(BOLD UDL YEL "\nTutor Menu " RESET UDL"- Logged in as " BOLD BLU "%s (%s)\n" RESET, lookupTutorName(currentUser), currentUser);
        printf("\n");
        printf("1. View sessions assigned to me\n");
        printf("2. View students in session\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                //Function for viewing sessions assigned to tutor
                viewTutorSessions();
                pause();
                tutorMenu();
            case 2:
                //Function for viewing students in session
                viewTutorSessions();
                displaySessionStudents();
                pause();
                tutorMenu();
            case 3:
                //Logout, return to main menu
                strcpy(currentUser, "");
                mainMenu();
            default:
                tutorMenu();
                break;
        }
    
    }

    void studentMenu() {
        int choice;
        printf(BOLD UDL YEL "\nStudent Menu " RESET UDL"- Logged in as " BOLD BLU "%s (%s)\n" RESET, lookupStudentName(currentUser), currentUser);
        printf("1. View my sessions\n");
        printf("2. View all sessions\n");
        printf("3. Enroll in a session\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                //View my sessions
                viewStudentSessions();
                pause();
                studentMenu();
            case 2:
                //View all sessions
                displaySessions();
                pause();
                studentMenu();
            case 3:
                //Enroll student into a session of their choice
                enrollStudent(currentUser);
                pause();
                studentMenu();
            case 4:
                //Logout, return to main menu
                strcpy(currentUser, "");
                mainMenu();
            default:
                studentMenu();
                break;
        }
    }

    //Mostly a copy paste from tutorLogin function, should probably commonize but I'm currently a little lazy, perhaps a problem for future me
    void studentLogin() {
        //Function for logging in students 
        //Declare variables for input, 20 characters should be enough
        //TODO: Maybe declare a const to store max input?
        char username[MAX_PASS_USER], password[MAX_PASS_USER], hashedPass[32];
        //Prompt for input
        printf("Logging in as "BOLD GRN"STUDENT\n"RESET);
        printf("Enter your username (Case sensitive): ");
        scanf("%s", username);
        strcpy(password, secureInput());

        //Find hash of input password & String-ify
        sprintf(hashedPass, "%lu", hash(password));

        //Open the file that stores student credentials, and throw an error if file not found
        FILE *studentCreds = fopen("studentCreds.apdata", "r");
        if (studentCreds == NULL) {
            printf("Error: could not open student credentials file.\n");
            return;
        }

        //The file stores each set of credentials in a line, # marks the end of the line, commas seperate the credentials by type.
        //Char array to store lines of the file as we loop through the file to find the password and username
        char line[MAX_LINE];
        //Decare pointers to store user and pass found in the file
        char *user, *pass;
        
        //This feels like a confusing way to loop through the file, but I think it's the best
        //fgets takes 3 arguments, where to store the text, max size of text, and where to read from
        //The while loop continues until there is no more text, aka, fgets returns NULL when it reaches the end of the file
        while (fgets(line, sizeof(line), studentCreds)) {
            //Get username from the line currently being read, by looking for a comma (called the delimiter)
            user = strtok(line, ",");
            //Get password from the line currently being read, looks for hashtag
            //We use NULL as the first argument because we want strtok to continue checking from the where the previous strtok left off, kinda confusing at first, but it works :p
            pass = strtok(NULL, "#");

            //Compare entered details with the ones from the file at the current line, if they match, trigger the studentMenu
            if (strcmp(username, user) == 0 && strcmp(hashedPass, pass) == 0) {
                printf(GRN BOLD "\nLogin successful!\n" RESET);
                fclose(studentCreds);
                //Set current user to username
                strcpy(currentUser, username);
                studentMenu();
                return;
            }
        }
        //We will exit the loop naturally if we don't find matching credentials, so ask the user to try again.
        printf(RED "\nInvalid username or password. Please try again.\n" RESET);
        fclose(studentCreds);
        studentLogin();
    }

    void createSession() {
        //Declare variables for session information
        char tutorId[MAX_ID];
        char sessionId[MAX_ID];
        char day[MAX_NAME_LEN];
        char time[MAX_NAME_LEN];
        char location[MAX_NAME_LEN];

        //Display list of tutors and their subjects
        printf(MAG "\n%-10s %-20s %s\n", "Tutor ID", "Subject", "Tutor Name" RESET);
        FILE *tutors = fopen("tutors.apdata", "r");
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), tutors)) {
            char *id = strtok(line, ",");
            char *name = strtok(NULL, ";");
            char *subject = strtok(NULL, "#");
            printf("%-10s %-20s %s\n", id, subject, name);
        }
        fclose(tutors);

        //Prompt for tutor ID
        printf("\nEnter tutor ID (Case sensitive, Eg: T01): ");
        scanf("%s", tutorId);

        //Check if tutor ID exists and if tutor already has a session
        tutors = fopen("tutors.apdata", "r");
        char *findSubject = NULL;
        char *findName = NULL;
        char *existingSessionId = NULL;
        while (fgets(line, sizeof(line), tutors)) {
            char *id = strtok(line, ",");
            if (strcmp(id, tutorId) == 0) {
                findName = strtok(NULL, ";");
                findSubject = strtok(NULL, "#");
                break;
            }
        }
        fclose(tutors);

        if (!findName || !findSubject) {
            printf("\nTutor ID not found. Please try again.\n");
            return;
        }

        FILE *sessions = fopen("sessions.apdata", "r");
        while (fgets(line, sizeof(line), sessions)) {
            char *sessionTutorId = strtok(line, ",");
            char *sessionSessionId = strtok(NULL, ",");
            if (strcmp(sessionTutorId, tutorId) == 0) {
                existingSessionId = sessionSessionId;
                break;
            }
        }
        fclose(sessions);

        if (existingSessionId) {
            printf("\nTutor already has a session (Session ID: %s). Please try again.\n", existingSessionId);
            return;
        }

        //Prompt for session information
        printf("Enter session ID (Case sensitive): ");
        scanf("%s", &sessionId);

        //Check if session ID is unique
        sessions = fopen("sessions.apdata", "r");
        while (fgets(line, sizeof(line), sessions)) {
            char *sessionTutorId = strtok(line, ",");
            char *sessionSessionId = strtok(NULL, ",");
            if (strcmp(sessionSessionId, sessionId) == 0) {
                printf("\nSession ID already exists. Please try again.\n");
                fclose(sessions);
                return;
            }
        }
        fclose(sessions);

        printf("Enter day: ");
        scanf("%s", day);
        printf("Enter time: ");
        scanf("%s", time);
        printf("Enter location: ");
        scanf("%s", location);

        // Open students.apdata file
        FILE *tutorsFile = fopen("tutors.apdata", "r");
        char line2[MAX_LINE];
        char tutorSubject[MAX_NAME_LEN];
        // Find the line with the specified tutor ID
        while (fgets(line2, sizeof(line2), tutorsFile)) {
            char *searchId = strtok(line2, ",");
            char *searchName = strtok(NULL, ";");
            char *searchSubject = strtok(NULL, "#");
            if (strcmp(searchId, tutorId) == 0) {
                fclose(tutorsFile);
                strcpy(tutorSubject,searchSubject);
                break;
            }
        }
        fclose(tutorsFile);

        //Write session to file
        sessions = fopen("sessions.apdata", "a");
        fprintf(sessions, "%s,%s,%s,%s,%s,%s,%s#\n", tutorId, sessionId, tutorSubject, lookupTutorName(tutorId), day, time, location);
        fclose(sessions);

        FILE *sessionStudents = fopen("sessionStudents.apdata", "a");
        fprintf(sessionStudents, "%s;TP000\n", sessionId);
        fclose(sessionStudents);

        printf(GRN BOLD "\nSession created successfully.\n" RESET);
    }

    void displaySessions() {
        //Display list of sessions
        printf(MAG BOLD UDL "\n%-10s %-15s %-20s %-20s %-10s %-10s %s\n", "Tutor ID", "Session ID", "Subject", "Tutor Name", "Day", "Time", "Location" RESET);
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), sessions)) {
            char *tutorId = strtok(line, ",");
            char *sessionId = strtok(NULL, ",");
            char *subject = strtok(NULL, ",");
            char *name = strtok(NULL, ",");
            char *day = strtok(NULL, ",");
            char *time = strtok(NULL, ",");
            char *location = strtok(NULL, "#");

            //Only show actual sessions, new line in the file causes this func to show null everywhere in the final line
            if (tutorId != NULL)
            {
                printf("%-10s %-15s %-20s %-20s %-10s %-10s %s\n", tutorId, sessionId, subject, name, day, time, location);
            }
            
            
        }
        fclose(sessions);
    }
    
    void delSession() {
        //Display list of sessions
        printf("\nList of sessions:\n");
        displaySessions();

        //Prompt for session ID
        char sessionId[MAX_ID];
        printf("\nEnter session ID (Case sensitive): ");
        scanf("%s", sessionId);

        //Check if session ID exists
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[MAX_LINE];
        int sessionFound = 0;
        while (fgets(line, sizeof(line), sessions)) {
            char *sessionSessionId = strtok(line, ",");
            if (strcmp(sessionSessionId, sessionId) == 0) {
                sessionFound = 1;
                break;
            }
        }
        fclose(sessions);

        if (sessionFound = 0) {
            printf("\nSession ID not found. Please try again.\n");
            return;
        }

        //Delete session from sessionStudents.apdata
        FILE *sessionStudents = fopen("sessionStudents.apdata", "r");
        FILE *temp = fopen("temp.apdata", "w");
            while (fgets(line, sizeof(line), sessionStudents)) {
                //strstr looks for sessionId in line, returns NULL if not found
                char *p = strstr(line, sessionId);
                //If strstr can't find sessionId in line, it's a line we want to keep
                //*(p + strlen(sessionId)) != ',' checks if the character right after the tutorId is not a comma, we use a pointer here cus we wanna see the character itself
                //If the next character is a comma, it means the we don't want to keep the line.
                if (!p || *(p + strlen(sessionId)) != ';') {
                    fprintf(temp, "%s", line);
                }
            }
        fclose(sessionStudents);
        fclose(temp);

        remove("sessionStudents.apdata");
        rename("temp.apdata", "sessionStudents.apdata");

        //Delete session from sessions.apdata
        sessions = fopen("sessions.apdata", "r");
        FILE *temp2 = fopen("temp.apdata", "w");
            while (fgets(line, sizeof(line), sessions)) {
                //strstr looks for sessionId in line, returns NULL if not found
                char *p = strstr(line, sessionId);
                //If strstr can't find sessionId in line, it's a line we want to keep
                //*(p + strlen(sessionId)) != ',' checks if the character right after the tutorId is not a comma, we use a pointer here cus we wanna see the character itself
                //If the next character is a comma, it means the we don't want to keep the line.
                if (!p || *(p + strlen(sessionId)) != ',') {
                    fprintf(temp2, "%s", line);
                }
            }
        fclose(sessions);
        fclose(temp2);

        remove("sessions.apdata");
        rename("temp.apdata", "sessions.apdata");


        printf(GRN BOLD "\nSession deleted successfully.\n" RESET);
    }

    void pause() {
        printf("\nPress any key to continue\n");
        getchar();
        getchar();
    }

    char* lookupStudentName(char *studentId) {
        // Open students.apdata file
        FILE *studentsFile = fopen("students.apdata", "r");
        char line[MAX_LINE];
        // Find the line with the specified student ID
        while (fgets(line, sizeof(line), studentsFile)) {
            char *id = strtok(line, ",");
            char *name = strtok(NULL, "#");
            if (strcmp(id, studentId) == 0) {
                fclose(studentsFile);
                return name;
            }
        }
        fclose(studentsFile);
        return NULL;
    }

    char* lookupTutorName(char *tutorId) {
        // Open students.apdata file
        FILE *tutorsFile = fopen("tutors.apdata", "r");
        char line[MAX_LINE];
        // Find the line with the specified tutor ID
        while (fgets(line, sizeof(line), tutorsFile)) {
            char *id = strtok(line, ",");
            char *name = strtok(NULL, ";");
            if (strcmp(id, tutorId) == 0) {
                fclose(tutorsFile);
                return name;
            }
        }
        fclose(tutorsFile);
        return NULL;
    }

    char* lookupTutorSubject(char *tutorId) {
        // Open students.apdata file
        FILE *tutorsFile = fopen("tutors.apdata", "r");
        char line[MAX_LINE];
        // Find the line with the specified tutor ID
        while (fgets(line, sizeof(line), tutorsFile)) {
            char *id = strtok(line, ",");
            char *name = strtok(NULL, ";");
            char *subject = strtok(NULL, "#");
            if (strcmp(id, tutorId) == 0) {
                fclose(tutorsFile);
                return subject;
            }
        }
        fclose(tutorsFile);
        return NULL;
    }

    void displaySessionStudents() {
        char sessionId[MAX_ID];
        printf("Enter session ID (Case sensitive): ");
        scanf("%s", sessionId);

        // Open sessionStudents.apdata file
        FILE *sessionStudents = fopen("sessionStudents.apdata", "r");
        char line[MAX_LINE];

        // Find the line with the specified session ID
        while (fgets(line, sizeof(line), sessionStudents)) {
            char *session = strtok(line, ";");
            if (strcmp(session, sessionId) == 0) {
                char *students = strtok(NULL, "\n");
                printf("Students assigned to session " RED "%s" RESET ":\n", sessionId);
                char *student = strtok(students, ", ");
                int count = 0;
                char *studentIdList[MAX_LINE];
                while (student != NULL) {
                    studentIdList[count] = student;
                    count++;
                    student = strtok(NULL, ", ");
                }
                for (int i = 0; i < count; i++) {
                    if (lookupStudentName(studentIdList[i]) != NULL) {
                        printf(GRN "%s" RESET " - " CYN "%s\n" RESET, studentIdList[i], lookupStudentName(studentIdList[i]));
                    }
                }
                fclose(sessionStudents);
                return;
            }
        }
        printf("No students assigned to session " RED "%s\n" RESET, sessionId);
        fclose(sessionStudents);
        pause();
    }

    void adminEnrollStudent() {
        char selectedStudentId[MAX_ID];
        displayStudents();
        printf(YEL "Enter a student id to enroll (Case sensitive): " RESET);
        scanf("%s",selectedStudentId);
        
        //Check if student ID exists
        FILE *students = fopen("students.apdata", "r");
        char line[MAX_LINE];
        int found = 0;
        while (fgets(line, sizeof(line), students)) {
            char *id = strtok(line, ",");
            if (strcmp(id, selectedStudentId) == 0) {
                found = 1;
                enrollStudent(selectedStudentId);
                break;
            }
        }
        fclose(students);

        if (!found) {
            printf("\nStudent ID not found. Please try again.\n");
            return;
        }
    }

void enrollStudent(char *studentId) {
    char sessionId[MAX_ID];

    displaySessions();
    printf("Enter Session ID to enroll %s (%s) to (Case sensitive): ", lookupStudentName(studentId), studentId);
    scanf("%s", sessionId);

    //Check if session ID exists
    FILE *sessions = fopen("sessionStudents.apdata", "r");
    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), sessions)) {
        char *id = strtok(line, ";");
        if (strcmp(id, sessionId) == 0) {
            found = 1;
            break;
        }
    }
    fclose(sessions);

    if (!found) {
        printf("\nSession ID not found. Returning to menu.\n");
        return;
    }

    //Add studentId to sessionStudents.apdata file
    FILE *sessionStudents = fopen("sessionStudents.apdata", "r");
    FILE *tempFile = fopen("tempSessionStudents.apdata", "w");
    char sessionLine[MAX_LINE];
    int sessionFound, success;
    sessionFound = 0;
    while (fgets(sessionLine, sizeof(sessionLine), sessionStudents)) {
        success = 0;
        char *session = strtok(sessionLine, ";");
        char *studentList = strtok(NULL, "\n");
        if (strcmp(session, sessionId) == 0) { //If this is the session we want, set sessionfound to 1
            sessionFound = 1;
            if (!strstr(studentList,studentId)) { //If studentId is NOT in student list, add to list and throw in file
                fprintf(tempFile, "%s;%s,%s\n", session, studentList, studentId);
                printf(GRN BOLD "\n%s (%s) has been enrolled in session %s.\n" RESET, lookupStudentName(studentId), studentId, sessionId);
            } else if (strstr(studentList,studentId)) { //If studentId is already part of the session, keep the line as is
                printf(YEL BOLD "\n%s (%s) is already enrolled in %s\n" RESET, lookupStudentName(studentId), studentId, sessionId);
                fprintf(tempFile, "%s;%s\n", session, studentList);
            }
                
        } else {
            fprintf(tempFile, "%s;%s\n", session, studentList);
        }
    }
    fclose(sessionStudents);
    fclose(tempFile);
    _fcloseall();
    //Replace original file with temporary file
    int removeStatus = remove("sessionStudents.apdata");
    if (removeStatus == 0) {
        printf("");
    } else {
        printf("Error: unable to delete file, please delete tempSessionStudents.apdata manually and restart the program");
    } 
    rename("tempSessionStudents.apdata", "sessionStudents.apdata");

    if (!sessionFound) {
        printf("\nSession ID not found in sessionStudents.apdata. Returning to menu.\n");
        return;
    }
    
}

    void displayStudents() {
        // Open the students file for reading
        FILE *students = fopen("students.apdata", "r");

        // Check if the file exists
        if (!students) {
            printf("\nNo students found.\n");
            return;
        }

        // Declare a buffer to store each line read from the file
        char line[MAX_LINE];

        // Read each line and extract the studentId and studentName
        printf(MAG "\nStudent ID\tStudent Name\n" RESET);
        while (fgets(line, sizeof(line), students)) {
            // Extract the studentId and studentName using strtok
            char *id = strtok(line, ",");
            char *name = strtok(NULL, "#");

            // Print the studentId and studentName
            printf("%s\t\t%s\n", id, name);
        }

        // Close the file
        fclose(students);

    }

    void viewTutorSessions() {
        //Display list of sessions
        printf(MAG BOLD UDL "\n%-10s %-15s %-20s %-20s %-10s %-10s %s\n", "Tutor ID", "Session ID", "Subject", "Tutor Name", "Day", "Time", "Location" RESET);
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), sessions)) {
            char *tutorId = strtok(line, ",");
            char *sessionId = strtok(NULL, ",");
            char *subject = strtok(NULL, ",");
            char *name = strtok(NULL, ",");
            char *day = strtok(NULL, ",");
            char *time = strtok(NULL, ",");
            char *location = strtok(NULL, "#");

            //Only show actual sessions, new line in the file causes this func to show null everywhere in the final line
            if (strcmp(tutorId, currentUser) == 0)
            {
                printf("%-10s %-15s %-20s %-20s %-10s %-10s %s\n", tutorId, sessionId, subject, name, day, time, location);
            }
        }
        fclose(sessions);
        return;
    }

    void viewStudentSessions() {
        FILE *sessionStudents = fopen("sessionStudents.apdata", "r");
        char line[MAX_LINE];
        printf(MAG BOLD UDL "\n%-10s %-15s %-20s %-20s %-10s %-10s %s\n", "Tutor ID", "Session ID", "Subject", "Tutor Name", "Day", "Time", "Location" RESET);
        while(fgets(line, sizeof(line), sessionStudents)) {
            if (strstr(line, currentUser)) {
                char *selectSessionId = strtok(line, ";");
                //Display list of sessions that match selected session ID

                
                FILE *sessions = fopen("sessions.apdata", "r");
                char sessionLine[MAX_LINE];
                while (fgets(sessionLine, sizeof(sessionLine), sessions)) {
                        char *tutorId = strtok(sessionLine, ",");
                        char *sessionId = strtok(NULL, ",");
                        char *subject = strtok(NULL, ",");
                        char *name = strtok(NULL, ",");
                        char *day = strtok(NULL, ",");
                        char *time = strtok(NULL, ",");
                        char *location = strtok(NULL, "#");
                    

                    //Only show sessions that match the ones assigned to current student
                    if (!strcmp(sessionId, selectSessionId)) {
                        printf("%-10s %-15s %-20s %-20s %-10s %-10s %s\n", tutorId, sessionId, subject, name, day, time, location);
                    }
                }
                fclose(sessions);
            }
        }
        return;
    }

    void main() {
        //Program starts here
        mainMenu();
    }