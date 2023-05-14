#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

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


void main(), pause(), mainMenu(), adminLogin(), adminMenu(), tutorLogin(), tutorMenu(), studentLogin(), studentMenu(), regTutor(), delTutor(), regStudent(), delStudent(), createSession(), displaySessions(), delSession(), displaySessionStudents(), adminEnrollStudent(), enrollStudent(), displayStudents(), viewTutorSessions();
char* lookupStudentName();
char* lookupTutorName();

char currentUser[20];

    //Main Menu function
    void mainMenu() {
        //Declare var for selection
        int choice;

        //Show prompt
        printf(BOLD UDL BLU "APU " CYN "Programming " GRN "Cafe\n\n" RESET);
        
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

    //Login function for admin, only requires a password, no username needed. Password is hardcoded abc
    //If correct password is entered, trigger admin menu, otherwise return to login screen
    void adminLogin() {
        //Declare variable for password input, and prompt for it
        char password[20];
        printf("Enter admin password: ");
        scanf("%s", password);
        
        //Check if input is = hardcoded password abc, strcmp returns 0 if strings match
        if (strcmp(password, "abc") == 0) {
            adminMenu();
        } else {
            //Call function again after throwing error if incorrect password is entered
            printf("Incorrect password. Please try again.\n");
            adminLogin();
        }
    }

    void adminMenu() {
        //Declare var for selection
        int choice;
        do {
            //Show prompt
            printf("\nAdmin Menu\n");
            printf("___________\n");
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
                    break;
                case 2:
                    //Call function to register student
                    regStudent();
                    break;
                case 3:
                    //Call function to remove tutor
                    delTutor();
                    break;
                case 4:
                    //Call function to remove student
                    delStudent();
                    break;
                case 5:
                    //Call function to add session
                    createSession();
                    break;
                case 6:
                    //Call function to enroll student to session
                    adminEnrollStudent();
                    break;
                case 7:
                    //Call function to display sessions
                    displaySessions();
                    break;
                case 8:
                    //Call function to delete session
                    delSession();
                    break;
                case 9:
                    //Call function to show students assigned to a specific session
                    displaySessionStudents();
                    break;
                case 10:
                    printf("\nLogging out\n");
                    //Return to main menu
                    mainMenu();
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
            }
        } while (choice != 10);
    }

    void regTutor() {
        //Declare variables for tutor details
        char tutorId[5], tutorPass[20], tutorName[50], tutorSubject[50], hashedPass[32];

        //Prompt for tutor ID
        printf("\nEnter tutor ID: ");
        scanf("%s", tutorId);

        //Check if tutor ID is already in use
        FILE *tutorCreds = fopen("tutorCreds.apdata", "r");
        char line[50];
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
        printf("Enter tutor password: ");
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

        printf("\nTutor added successfully.\n");
    }

    void delTutor() {
        //Declare variables for tutor ID
        char tutorId[5];

        //Prompt for tutor ID
        printf("\nEnter tutor ID: ");
        scanf("%s", tutorId);

        //Check if tutor ID exists
        FILE *tutors = fopen("tutors.apdata", "r");
        char line[50];
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

        printf("\nTutor deleted successfully. Don't forget to delete sessions corresponding to this tutor if needed.\n");
    }

    void regStudent() {
        //Declare variables for student details
        char studentId[10], studentPass[20], studentName[50], hashedPass[32];

        //Prompt for student ID
        printf("\nEnter student ID: ");
        scanf("%s", studentId);

        //Check if student ID is already in use
        FILE *studentCreds = fopen("studentCreds.apdata", "r");
        char line[50];
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
        printf("Enter student password: ");
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

        printf("\nStudent added successfully.\n");
    }


    void delStudent() {
        //Declare variables for student ID
        char studentId[10];

        //Prompt for student ID
        printf("\nEnter student ID: ");
        scanf("%s", studentId);

        //Check if student ID exists
        FILE *students = fopen("students.apdata", "r");
        char line[100];
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

        printf("\nStudent deleted successfully.\n");
    }

    void tutorLogin() {
        //Function for logging in tutors
        //TODO: Maybe commonize tutor and student login? Dunno how much work that will be, decide later?? 
        //Declare variables for input, 20 characters should be enough
        //TODO: Maybe declare a const to store max input?
        char username[20], password[20], hashedpass[32];
        //Prompt for input
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

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
        char line[100];
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
                printf("\nLogin successful!\n");
                fclose(tutorCreds);
                //Set tutor as current user
                strcpy(currentUser,username);
                tutorMenu();
            }
        }
        //We will exit the loop naturally if we don't find matching credentials, so ask the user to try again.
        printf("\nInvalid username or password. Please try again.\n");
        fclose(tutorCreds);
        tutorLogin();
    }

    void tutorMenu() {
        int choice;
        printf(BOLD UDL YEL "\nTutor Menu " RESET UDL"- Logged in as " BOLD BLU "%s (%s)\n" RESET, lookupTutorName(currentUser), currentUser);
        printf("___________\n");
        printf("1. View sessions assigned to me\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                //Function for viewing sessions assigned to tutor
                viewTutorSessions();
                tutorMenu;
            case 2:
                //Logout, return to main menu
                mainMenu();
                strcpy(currentUser, NULL);
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

                studentMenu();
            case 2:
                //View all sessions
                displaySessions();
                studentMenu();
            case 3:
                //Enroll student into a session of their choice
                enrollStudent(currentUser);
                studentMenu();
            case 4:
                //Logout, return to main menu
                mainMenu();
                strcpy(currentUser, NULL);
                break;
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
        char username[20], password[20], hashedPass[32];
        //Prompt for input
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

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
        char line[100];
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
                printf("\nLogin successful!\n");
                fclose(studentCreds);
                //Set current user to username
                strcpy(currentUser, username);
                studentMenu();
                return;
            }
        }
        //We will exit the loop naturally if we don't find matching credentials, so ask the user to try again.
        printf("\nInvalid username or password. Please try again.\n");
        fclose(studentCreds);
        studentLogin();
    }

    void createSession() {
        //Declare variables for session information
        char tutorId[5];
        char sessionId[10];
        char day[10];
        char time[10];
        char location[20];

        //Display list of tutors and their subjects
        printf(MAG "\n%-10s %-20s %s\n", "Tutor ID", "Subject", "Tutor Name" RESET);
        FILE *tutors = fopen("tutors.apdata", "r");
        char line[50];
        while (fgets(line, sizeof(line), tutors)) {
            char *id = strtok(line, ",");
            char *nameAndSubject = strtok(NULL, "\n");
            char *subject = strtok(nameAndSubject, ";");
            char *name = strtok(NULL, ";");
            printf("%-10s %-20s %s\n", id, subject, name);
        }
        fclose(tutors);

        //Prompt for tutor ID
        printf("\nEnter tutor ID: ");
        scanf("%s", tutorId);

        //Check if tutor ID exists and if tutor already has a session
        tutors = fopen("tutors.apdata", "r");
        char *subject = NULL;
        char *name = NULL;
        char *existingSessionId = NULL;
        while (fgets(line, sizeof(line), tutors)) {
            char *id = strtok(line, ",");
            if (strcmp(id, tutorId) == 0) {
                name = strtok(NULL, ";");
                subject = strtok(NULL, "#");
                break;
            }
        }
        fclose(tutors);

        if (!name || !subject) {
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
        printf("Enter session ID: ");
        scanf("%s", sessionId);

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

        //Write session to file
        sessions = fopen("sessions.apdata", "a");
        fprintf(sessions, "%s,%s,%s,%s,%s,%s,%s#\n", tutorId, sessionId, subject, name, day, time, location);
        fclose(sessions);

        printf("\nSession created successfully.\n");
    }

    void displaySessions() {
        //Display list of sessions
        printf(MAG "\n%-10s %-15s %-20s %-20s %-10s %-10s %s\n", "Tutor ID", "Session ID", "Subject", "Tutor Name", "Day", "Time", "Location" RESET);
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[100];
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
        char sessionId[10];
        printf("\nEnter session ID: ");
        scanf("%s", sessionId);

        //Check if session ID exists
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[100];
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


        printf("\nSession deleted successfully.\n");
    }

    void pause() {
        printf("\nPress any key to continue\n");
        getchar();
        getchar();
    }

    char* lookupStudentName(char *studentId) {
        // Open students.apdata file
        FILE *studentsFile = fopen("students.apdata", "r");
        char line[100];
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
        char line[100];
        // Find the line with the specified student ID
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

    void displaySessionStudents() {
        char sessionId[10];
        printf("Enter session ID: ");
        scanf("%s", sessionId);

        // Open sessionStudents.apdata file
        FILE *sessionStudents = fopen("sessionStudents.apdata", "r");
        char line[100];

        // Find the line with the specified session ID
        while (fgets(line, sizeof(line), sessionStudents)) {
            char *session = strtok(line, ";");
            if (strcmp(session, sessionId) == 0) {
                char *students = strtok(NULL, "\n");
                printf("Students assigned to session " RED "%s" RESET ":\n", sessionId);
                char *student = strtok(students, ", ");
                int count = 0;
                char *studentIdList[100];
                while (student != NULL) {
                    studentIdList[count] = student;
                    count++;
                    student = strtok(NULL, ", ");
                }
                for (int i = 0; i < count; i++) {
                    if (lookupStudentName(studentIdList[i]) != NULL) {
                        printf(GRN "%s" RESET " - " BLU "%s\n" RESET, studentIdList[i], lookupStudentName(studentIdList[i]));
                    }
                }
                fclose(sessionStudents);
                pause();
                return;
            }
        }
        printf("No students assigned to session " RED "%s\n" RESET, sessionId);
        fclose(sessionStudents);
        pause();
    }

    void adminEnrollStudent() {
        char selectedStudentId[10];
        displayStudents();
        printf(YEL "Enter a student id to enroll: " RESET);
        scanf("%s",selectedStudentId);
        
        //Check if student ID exists
        FILE *students = fopen("students.apdata", "r");
        char line[100];
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
    char sessionId[10];

    displaySessions();
    printf("Enter Session ID to enroll %s (%s) to: ", lookupStudentName(studentId), studentId);
    scanf("%s", sessionId);

    //Check if session ID exists
    FILE *sessions = fopen("sessionStudents.apdata", "r");
    char line[100];
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
    char sessionLine[100];
    int sessionFound, alreadyExists = 0;
    while (fgets(sessionLine, sizeof(sessionLine), sessionStudents)) {
        char *session = strtok(sessionLine, ";");
        char *studentList = strtok(NULL, "\n");
        if (strcmp(session, sessionId) == 0) {
            sessionFound = 1;
            if (strstr(studentList,studentId) == NULL) {
                fprintf(tempFile, "%s;%s,%s\n", session, studentList, studentId);
            } else {
                alreadyExists = 1;
                fprintf(tempFile, "%s;%s\n", session, studentList);
            }
                
        } else {
            fprintf(tempFile, "%s;%s\n", session, studentList);
        }
    }
    fclose(sessionStudents);
    fclose(tempFile);

    //Replace original file with temporary file
    remove("sessionStudents.apdata");
    rename("tempSessionStudents.apdata", "sessionStudents.apdata");

    if (!sessionFound) {
        printf("\nSession ID not found in sessionStudents.apdata. Returning to menu.\n");
        return;
    }
    if (alreadyExists = 1) {
        printf("\n%s (%s) is already enrolled in %s\n", lookupStudentName(studentId), studentId, sessionId);
        return;
    } else {
        printf("\n%s (%s) has been enrolled in session %s.\n", lookupStudentName(studentId), studentId, sessionId);
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
        char line[100];

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
        printf(MAG "\n%-10s %-15s %-20s %-20s %-10s %-10s %s\n", "Tutor ID", "Session ID", "Subject", "Tutor Name", "Day", "Time", "Location" RESET);
        FILE *sessions = fopen("sessions.apdata", "r");
        char line[100];
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
    }

    void main() {
        //Program starts here
        mainMenu();
    }