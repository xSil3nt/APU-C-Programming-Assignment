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
