    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void main(), mainMenu(), adminLogin(), adminMenu(), tutorLogin(), tutorMenu(), studentLogin(), studentMenu(), regTutor(), delTutor(), regStudent(), delStudent(), createSession();

    //Main Menu function
    void mainMenu() {
        //Declare var for selection
        int choice;

        //Show prompt
        printf("Welcome to the APU Programming Cafe\n");
        printf("___________________________________\n");
        printf("1. Login as Admin\n");
        printf("2. Login as Tutor\n");
        printf("3. Login as Student\n");
        printf("4. Exit\n");
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
            printf("8. Logout\n");
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
                    break;
                case 7:
                    //Call function to display sessions
                    break;
                case 8:
                    printf("\nLogging out\n");
                    //Return to main menu
                    mainMenu();
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
            }
        } while (choice != 6);
    }

    void regTutor() {
        //Declare variables for tutor details
        char tutorId[5], tutorPass[20], tutorName[50], tutorSubject[50];

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

        //Add tutor to system
        tutorCreds = fopen("tutorCreds.apdata", "a");
        fprintf(tutorCreds, "%s,%s#\n", tutorId, tutorPass);
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

        printf("\nTutor deleted successfully.\n");
    }

    void regStudent() {
        //Declare variables for student details
        char studentId[10], studentPass[20], studentName[50];

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

        //Add student to system
        studentCreds = fopen("studentCreds.apdata", "a");
        fprintf(studentCreds, "%s,%s#\n", studentId, studentPass);
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
        char line[50];
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
        char username[20], password[20];
        //Prompt for input
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

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
            if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
                printf("\nLogin successful!\n");
                fclose(tutorCreds);
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
        printf("Tutor Menu\n");
        printf("___________\n");
        printf("1. View assigned sessions\n");
        printf("2. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    }

    void studentMenu() {
        int choice;
        printf("\nStudent Menu\n");
        printf("____________\n");
        printf("1. View sessions\n");
        printf("2. Enroll in a session\n");
        printf("3. Logout\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
    }

    //Mostly a copy paste from tutorLogin function, should probably commonize but I'm currently a little lazy, perhaps a problem for future me
    void studentLogin() {
        //Function for logging in students 
        //Declare variables for input, 20 characters should be enough
        //TODO: Maybe declare a const to store max input?
        char username[20], password[20];
        //Prompt for input
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);

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
            if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
                printf("\nLogin successful!\n");
                fclose(studentCreds);
                studentMenu();
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
        printf("\n%-10s %-20s %s\n", "Tutor ID", "Subject", "Tutor Name");
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

    void main() {
        //Program starts here
        mainMenu();
    }