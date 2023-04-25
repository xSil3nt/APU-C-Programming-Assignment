#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);
    
    if (strcmp(password, "-xXEpicAdminXx-") == 0) {
        adminMenu();
    } else {
        printf("Incorrect password. Please try again.\n");
        adminLogin();
    }
}

void adminMenu() {
    int choice;
    printf("Admin Menu\n");
    printf("___________\n");
    printf("1. Register tutor\n");
    printf("2. Register student\n");
    printf("3. Add session\n");
    printf("4. Enroll student to session\n");
    printf("5. Display sessions\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
}
void tutorLogin() {
    char username[50], password[50];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    FILE *tutorCreds = fopen("tutorCreds.apdata", "r");
    if (tutorCreds == NULL) {
        printf("Error: could not open tutor credentials file.\n");
        return;
    }

    char line[100];
    char *user, *pass;
    int found = 0;
    while (fgets(line, sizeof(line), tutorCreds)) {
        user = strtok(line, ",");
        pass = strtok(NULL, "#");
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(tutorCreds);

    if (found) {
        printf("\nLogin successful!\n");
        tutorMenu();
    } else {
        printf("\nInvalid username or password. Please try again.\n");
        tutorLogin();
    }
}