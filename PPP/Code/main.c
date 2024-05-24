#include "header.h"

int main()
{
    int studentCount = 0;
    struct Student *StudentsList = NULL;
    // reading data from the file on start of the program
    readInputData(&StudentsList, &studentCount);
    int choice;
    // using do while loop for menu driven format
    do {
        // printing the menu
        printf("\n1. Add a new student.\n2. Delete a student.\n3. List all students alphabetically.\n4. List students with balance below a certain amount (in descending order of balances).\n5. Present all the information of a particular student.\n6. Make an expense for a particular student.\n7. Upload a student's account with a value\n8. Exit\nYour Choice:");
        scanf("%d", &choice);
        // using switch on the user choice
        switch (choice) {
            // if user choose option 1 then asking user for details and adding that student to the list
            case 1: {
                char name[50];
                char dob[15];
                int class;
                int year;
                int number;
                double balance;
                printf("\nEnter the Details of student to add:\n");
                printf("Name:");
                scanf("%s", name);
                fflush(stdin);
                printf("Date of birth:");
                scanf("%s", dob);
                while (validateDate(dob) == 0) {
                    printf("Date is invalid!!\n");
                    printf("Date:");
                    scanf("%s", dob);
                }
                printf("Year student is in:");
                scanf("%d", &year);
//                while (isdigit(year) == 0) {
//                    printf("Year of the student must be an integer value.\n");
//                    printf("Year:");
//                    scanf("%d", &year);
//                }
                printf("Class:");
                scanf("%d", &class);
//                while (isdigit(class) == 0) {
//                    printf("Class of the student must be an integer value.\n");
//                    printf("Class:");
//                    scanf("%d", &class);
//                }
                printf("Number:");
                scanf("%d", &number);
//                while (isdigit(number) == 0) {
//                    printf("Number of the student must be an integer value.\n");
//                    printf("Number:");
//                    scanf("%d", &number);
//                }
                printf("Balance:");
                scanf("%lf", &balance);
                while (balance < 0) {
                    printf("Balance must be 0 or plus.\n");
                    printf("Balance:");
                    scanf("%lf", &balance);
                }

//                while(isdigit(balance)==0){
//                    printf("Balance of the student must be an integer value.\n");
//                    printf("Balance:");
//                    scanf("%d", &year);
//                }

                insertStudent(&StudentsList, name, dob, class, year, number, balance, &studentCount);
                break;
            }

                // if user choose option 2 then asking user for details and deleting that student from the list
            case 2: {
                int number;
                printf("\nEnter the number of the student to delete:\n");
                printf("Number:");
                scanf("%d", &number);
//                while(isdigit(number)==0){
//                    printf("Number of the student must be an integer value.\n");
//                    printf("Number:");
//                    scanf("%d", &number);
//                }
                deleteStudent(&StudentsList, number, &studentCount);

                break;
            }

                // if user choose option 3 then printing the list in alphabetical order
            case 3: {
                sortAlphabatically(&StudentsList, studentCount);
                printf("\nListing the Students in Alphabetical order:\n");
                printStudents(StudentsList);

                break;
            }

                // if user choose option 4 then asking user for limit and then printing those student with less balance than the limit in descending order
            case 4: {
                double limit;
                printf("\nEnter the balance limit:");
                scanf("%lf", &limit);
                //Verify if exist a function to validate float like isDigit()
                while (limit <= 0) {
                    printf("Please enter a valid balance limit:");
                    scanf("%lf", &limit);
                }
                printf("\nThe list of Students with below balance of $%.2f:\n", limit);
                sortBalanceWise(&StudentsList, studentCount);
                struct Student *temp = StudentsList;
                for (int i = 0; i < studentCount; i++) {
                    if (temp->balance < limit) {
                        printStudent(temp);
                    }
                    temp = temp->nextSudent;
                }
                sortAlphabatically(&StudentsList, studentCount);

                break;
            }

                // if user choose option 5 then asking user for details and printing the details of that student if it exist in the list
            case 5: {
                int number;
                printf("\nEnter the number of student to get complete information:\n");
                printf("Number:");
                scanf("%d", &number);
//                while(isdigit(number)==0){
//                    printf("Number of the student must be an integer value.\n");
//                    printf("Number:");
//                    scanf("%d", &number);
//                }
                struct Student *temp = StudentsList;
                for (int i = 0; i < studentCount; i++) {
                    if (temp->number == number) {
                        printStudent(temp);
                        break;
                    }
                    temp = temp->nextSudent;
                }

                break;
            }

                // if user choose option 6 then asking user for details of student and expense for that student and add the input expense to the student's expense list
            case 6: {
                int number;
                printf("\nEnter the number of the student to make an expense:\n");
                printf("Number:");
                scanf("%d", &number);
//                while(isdigit(number)==0){
//                    printf("Number of the student must be an integer value.\n");
//                    printf("Number:");
//                    scanf("%d", &number);
//                }
                struct Student *temp = StudentsList;
                for (int i = 0; i < studentCount; i++) {
                    if (temp->number == number) {
                        double value;
                        char description[100];
                        char date[15];
                        printf("\nEnter the details of the Expense:\n");
                        printf("Value:");
                        scanf("%lf", &value);
                        printf("Description:");
                        scanf("%s", description);
                        fflush(stdin);
                        printf("Date:");
                        scanf("%s", date);
                        while (validateDate(date) == 0) {
                            printf("Date is invalid!!\n");
                            printf("Date:");
                            scanf("%s", date);
                        }
                        insertExpenses(temp, value, description, date);
                        break;
                    }
                    temp = temp->nextSudent;
                }

                break;
            }

                // if user choose option 7 then asking user for details and updating the balance of the student by adding that value
            case 7: {
                int number;
                printf("\nEnter the number of the student to add value to balance:\n");
                printf("Number:");
                scanf("%d", &number);
//            while (isdigit(number) == 0) {
//                printf("Number of the student must be an integer value.\n");
//                printf("Number:");
//                scanf("%d", &number);
//            }
                struct Student *temp = StudentsList;
                for (int i = 0; i < studentCount; i++) {
                    if (temp->number == number) {
                        double val;
                        printf("\nEnter the value to add to the balance:");
                        scanf("%lf", &val);
                        while (val <= 0) {
                            printf("Please enter a valid value to add:");
                            scanf("%lf", &val);
                        }
                        temp->balance += val;
                        break;
                    }
                    temp = temp->nextSudent;
                }

                break;
            }

                // if user choose option 8 then printing the exiting message and break
            case 8: {
                printf("Exiting!!\n");

                break;
            }

                // if user chooses other than mentioned options printing the invalid choice message
            default: {
                printf("Invalid Choice!!\n");
            }
                printf("\n");

                // running the loop until user choose 8 (to exit)
        }
    }while (choice != 8);

    // on exiting write the details to the database
    writeToFile(StudentsList);

    // printing the updating success message
    printf("\nUpdated the Database successfully!!\n");
    return 0;
}