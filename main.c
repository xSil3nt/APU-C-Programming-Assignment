#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mainMenu(), adminLogin(), adminMenu(), tutorLogin(), tutorMenu(), studentLogin(), studentMenu();

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
            printf("Thank you for using the APU Programming Cafe. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            mainMenu();
    }
}

//Login function for admin, only requires a password, no username needed. Password is hardcoded -xXEpicAdminXx-
//If correct password is entered, trigger admin menu, otherwise return to login screen
void adminLogin() {
    //Declare variable for password input, and prompt for it
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    
    //Check if input is = hardcoded password -xXEpicAdminXx-, strcmp returns 0 if strings match
    if (strcmp(password, "-xXEpicAdminXx-") == 0) {
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

    //Show prompt
    printf("Admin Menu\n");
    printf("___________\n");
    printf("1. Register tutor\n");
    printf("2. Register student\n");
    printf("3. Add session\n");
    printf("4. Enroll student to session\n");
    printf("5. Display sessions\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
    //Get input
    scanf("%d", &choice);
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

void main() {
    mainMenu();
}