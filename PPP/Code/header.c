#include "header.h"

//function to verify if a given date is valid or not
int validateDate(char date[])
{

    char* token = strtok(date, "-");
    int day, month, year;
    day = atoi(token);

    while (token != NULL) {
        token = strtok(NULL, "-");
        month = atoi(token);
        token = strtok(NULL, "-");
        year = atoi(token);
        token = strtok(NULL, "");
    }

    int val = 0;

    //check month
    if(month>=1 && month<=12)
    {
        //check days
        if((day>=1 && day<=31) && (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)){
            printf("");
            val = 1;
        }
        else if((day>=1 && day<=30) && (month==4 || month==6 || month==9 || month==11)) {
            printf("");
            val = 1;

        }
        else if((day>=1 && day<=28) && (month==2)) {
            printf("");
            val = 1;

        }
        else if(day==29 && month==2 && (year%400==0 ||(year%4==0 && year%100!=0))) {
            printf("");
            val = 1;

        }
        else {
            printf("Day is invalid.\n");
            val = 0;
        }
    }
    else
    {
        printf("Month is invalid.\n");
        val = 0;
    }

    //check year
    if(year>2022){
        printf("Year is invalid.\n");
        val = 0;
    }

    return val;
}

//function to validate date of expense
//int validateDateOfExpense(char date[], char dob[])
//{
//    int val = 0;
//
//    //Get expense date
//    char* token = strtok(date, "-");
//    int day, month, year;
//    day = atoi(token);
//
//    while (token != NULL) {
//        token = strtok(NULL, "-");
//        month = atoi(token);
//        token = strtok(NULL, "-");
//        year = atoi(token);
//        token = strtok(NULL, "");
//    }
//
//    //////////////////////////////////////////////////////////////////////////////////////
//
//    //Get student date of birth
//    char* tokenDob = strtok(dob, "-");
//    int dayDob, monthDob, yearDob;
//    dayDob = atoi(tokenDob);
//
//    while (tokenDob != NULL) {
//        tokenDob = strtok(NULL, "-");
//        monthDob = atoi(tokenDob);
//        tokenDob = strtok(NULL, "-");
//        yearDob = atoi(tokenDob);
//        tokenDob = strtok(NULL, "");
//    }
//
//    //Compare dates
//    if(yearDob+18>year) {
//        printf("Error. Trying to do an expense to a underage person.\n");
//        val = 1;
//    }
//    if(yearDob+18==year){
//        if(monthDob>month){
//            printf("Error. Trying to do an expense to a underage person.\n");
//            val = 1;
//        }
//        else if(monthDob==month){
//            if(dayDob<day){
//                printf("Error. Trying to do an expense to a underage person.\n");
//                val = 1;
//            }
//        }
//    }
//    return val;
//}

// function to insert the expense or add expense to the student's expense list
void insertExpenses(struct Student *student, double val, char descrip[], char date[])
{

    // creating a new expense node
    struct Expense *newNode = (struct Expense *)malloc(sizeof(struct Expense));
    strcpy(newNode->date, date);
    strcat(newNode->date, "\0");
    strcpy(newNode->description, descrip);
    strcat(newNode->description, "\0");
    newNode->next = NULL;
    newNode->value = val;
    // traversing the expenselist and inserting the new node at the end of the listf or tail o the list
    struct Expense *temp = student->studentExpenseHead;


//    if(validateDateOfExpense(date, dob)==1){
//        printf("Can not insert expense on an underage student.\n");
//        return;
//    }

    //Checking if student has enough money
    if (student->balance<val)
    {
        printf("\nStudent has not enough money to buy that product.\n");
        return;
    }

    // if there is no expense for the student then making the new node as the head
    if (student->studentExpenseHead == NULL)
    {
        student->studentExpenseHead = newNode;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    student->balance -= newNode->value;
    // incrementing the expense count of the student after adding to the list
    student->expenseListSize += 1;
}

//function to swap the two student nodes
struct Student *swap(struct Student *s1, struct Student *s2)
{
    struct Student *tmp = s2->nextSudent;
    s2->nextSudent = s1;
    s1->nextSudent = tmp;
    return s2;
}

// function to sort the list according to the decreasing order of balance
void sortBalanceWise(struct Student **head, int numStudents)
{
    struct Student **h;
    struct Student *temp = *head;
    int swapInIteration;
    // traversing the list
    for (int i = 0; i <= numStudents; i++)
    {
        h = head;
        swapInIteration = 0;
        for (int j = 0; j < numStudents - i - 1; j++)
        {
            struct Student *temp = *h;
            struct Student *temp2 = temp->nextSudent;
            // if the balance of ith node is less than i+1 th node then swapping the nodes and keeping track of number of swaps
            if (temp->balance < temp2->balance)
            {
                *h = swap(temp, temp2);
                swapInIteration += 1;
            }
            h = &(*h)->nextSudent;
        }
        // if number of swaps in previous iteration are 0 then breaking the loop because the list is sorted at that iteration
        if (swapInIteration == 0)
        {
            break;
        }
    }
}

// function to sort the list in alphabaticall order
void sortAlphabatically(struct Student **head, int numStudents)
{
    struct Student **h;
    struct Student *temp = *head;
    int swapInIteration;
    for (int i = 0; i <= numStudents; i++)
    {
        h = head;
        swapInIteration = 0;
        for (int j = 0; j < numStudents - i - 1; j++)
        {
            struct Student *temp = *h;
            struct Student *temp2 = temp->nextSudent;

            // if the name of ith node is less than i+1 th node then swapping the nodes and keeping track of number of swaps
            if (strcmp(temp->name, temp2->name) > 0)
            {
                *h = swap(temp, temp2);
                swapInIteration += 1;
            }
            h = &(*h)->nextSudent;
        }
        // if number of swaps in previous iteration are 0 then breaking the loop because the list is sorted at that iteration
        if (swapInIteration == 0)
        {
            break;
        }
    }
}

// function to check whether a student with given details exist in the list or not if exist return 1 else return 0
int exist(struct Student *head, int number)
{
    // traversing the list
    struct Student *temp = head;
    while (temp != NULL)
    {
        // checking the exact match for the given details in the list
        if (temp->number == number)
        {
            return 1;
        }
        temp = temp->nextSudent;
    }

    return 0;
}

// function to insert the student to the passed list
void insertStudent(struct Student **head, char name[], char dob[], int class, int year, int number, double balance, int *studentCount)
{
    // if student is previously existing in the list then print already present message and return
    if (exist(*head, number) == 1)
    {
        printf("\n=>Student with given number already exist!!\n");
        return;
    }
    // creating a new student node with given details
    struct Student *newNode = (struct Student *)malloc(sizeof(struct Student));
    newNode->balance = balance;
    newNode->class = class;
    newNode->year = year;
    newNode->number = number;
    strcpy(newNode->name, name);
    strcat(newNode->name, "\0");
    strcpy(newNode->dob, dob);
    strcat(newNode->dob, "\0");
    newNode->nextSudent = NULL;
    newNode->studentExpenseHead = NULL;
    newNode->expenseListSize = 0;
    // if the student list is empty then new node the head node
    if ((*head) == NULL)
    {
        (*head) = newNode;
        // incrementing the student count
        *studentCount = *studentCount + 1;
        return;
    }
    // traversing te list
    struct Student *temp = *head;
    while (temp->nextSudent != NULL)
    {
        temp = temp->nextSudent;
    }
    temp->nextSudent = newNode;
    // incrementing the student count
    *studentCount = *studentCount + 1;
}

// function to delete the student from the list
void deleteStudent(struct Student **head, int number, int *studentCount)
{
    char answer;
    // if list is empty then return
    if (head == NULL)
    {
        return;
    }
    // comparing the first element with the  required details and if the detail matches then deleting it
    if ((*head)->number == number)
    {
        printf("Is this the person you want to delete: Yes/No\n");
        printStudent(*head);
        scanf("%s", &answer);
        if(strcmp(&answer, "No")==0)
        {
            return;
        }
        else if (strcmp(&answer, "Yes")==0)
        {
            printf("Student goign to be deleted.\n");
        }
        // traversing the expense list of the required student and deleting it
        struct Expense *temp = (*head)->studentExpenseHead;
        struct Expense *del = NULL;
        while (temp != NULL)
        {
            del = temp;
            temp = temp->next;
            free(del);
        }
        struct Student *tempS = (*head)->nextSudent;
        free((*head));
        (*head) = tempS;

        printf("Student Deleted Successfully!!\n");
        // decrementing the student count
        *studentCount = *studentCount - 1;
        return;
    }
    else
    {
        struct Student *delS = (*head);
        struct Student *tempS = NULL;

        while (delS->nextSudent != NULL)
        {
            tempS = delS;
            delS = delS->nextSudent;

            // comparing the ith element with the  required details and if the detail matches then deleting it
            if (delS->number == number)
            {
                printf("Is this the person you want to delete: Yes/No\n");
                printStudent(delS);
                scanf("%s", &answer);
                if(strcmp(&answer, "No")==0)
                {
                    return;
                }
                else if (strcmp(&answer, "Yes")==0)
                {
                    printf("Student goign to be deleted.\n");
                }
                struct Expense *temp = delS->studentExpenseHead;
                struct Expense *del = NULL;
                // traversing the expense list of the required student and deleting it
                while (temp != NULL)
                {
                    del = temp;
                    temp = temp->next;
                    free(del);
                }
                tempS->nextSudent = delS->nextSudent;
                free(delS);
                printf("Student Deleted Successfully!!\n");
                // decrementing the student count
                *studentCount = *studentCount - 1;
                return;
            }
        }
    }
    printf("\n=> Student with given details do not exist!!\n");
}

// function to print a single student passed in proper format
void printStudent(struct Student *s)
{
    // printing the student's details
    printf("\tName:%s\n", s->name);
    printf("\tDate of birth:%s\n", s->dob);
    printf("\tYear:%d\n", s->year);
    printf("\tClass:%d\n", s->class);
    printf("\tNumber:%d\n", s->number);
    printf("\tBalance:$%.2f\n", s->balance);

    // printing the students's expense details
    printf("\tExpenses: \n");
    // if no expense then print nil else print the complete the expense list
    if (s->expenseListSize == 0)
    {
        printf("\tNo expenses registered.\n\n");
        return;
    }
    struct Expense *temp = s->studentExpenseHead;
    for (int i = 0; i < s->expenseListSize; i++)
    {
        printf("\t%d.\tDate: /%s\n", i + 1, temp->date);
        printf("\t\tDescription: %s\n", temp->description);
        printf("\t\tValue: $%.2f\n\n", temp->value);
        temp = temp->next;
    }
}

// function to print the complete student list
void printStudents(struct Student *head)
{
    // if the list is empty then print required message else print the complete list
    if (head == NULL)
    {
        printf("\n=>There is no student in the list!\n\n");
    }
    else
    {
        struct Student *temp = head;
        int i = 1;
        while (temp != NULL)
        {
            printf("%d)", i);
            printStudent(temp);
            temp = temp->nextSudent;
            i += 1;
        }
    }
}

// function to read and load data from the database.txt file
void readInputData(struct Student **StudentList, int *studentCount)
{
    // creating file pointer and opening the file
    FILE *filePointer;
    filePointer = fopen("C:\\Users\\carli\\CLionProjects\\PPPdone\\database.txt", "r");
    if (!filePointer)
    {
        printf("Can't open file\n");
        return;
    }
    // reading data of the students form the file
    char buffer[1024];
    char name[50];
    char dob[15];
    int class;
    int year;
    int number;
    double balance;
    int expenseListSize;
    while (fgets(buffer, 1024, filePointer))
    {
        // using strtok to handle comma separated format
        char *value = strtok(buffer, ",");
        strcpy(name, value);
        value = strtok(NULL, ",");
        strcpy(dob, value);
        value = strtok(NULL, ",");
        year = atoi(value);
        value = strtok(NULL, ",");
        class = atoi(value);
        value = strtok(NULL, ",");
        number = atoi(value);
        value = strtok(NULL, ",");
        balance = atof(value);
        value = strtok(NULL, ",");
        expenseListSize = atoi(value);
        // inserting the student to the list
        insertStudent(StudentList, name, dob, class, year, number, balance, studentCount);
        // if the student also has expenses then adding the expenses to the list by reading from the file
        if (expenseListSize > 0)
        {
            double expenseVal;
            char des[100];
            char date[15];
            // searching the required student from the list
            struct Student *s = *StudentList;
            while ((strcmp(s->name, name) != 0) || (strcmp(s->dob, dob) != 0) || (s->class != class) || (s->number != number) || (s->year != year))
            {
                s = s->nextSudent;
            }
            // adding the read details to the list by using buffer and strtok and add expenses
            for (int i = 0; i < expenseListSize; i++)
            {
                fgets(buffer, 1024, filePointer);
                value = strtok(buffer, ",");
                expenseVal = atof(value);
                value = strtok(NULL, ",");
                strcpy(des, value);
                value = strtok(NULL, ",");
                strcpy(date, value);
                date[strlen(date) - 1] = '\0';
                insertExpenses(s, expenseVal, des, date);
            }
        }
    }
    // closing the file pointer
    fclose(filePointer);
    printf("\nSuccessfully loaded student database...\n\n");
}

// function to write the details to the data base file in required format
void writeToFile(struct Student *studentList)
{
    if (studentList != NULL)
    {
        // opening the file in write mode
        FILE *filePointer;
        filePointer = fopen("C:\\Users\\carli\\CLionProjects\\PPPdone\\database.txt", "w");
        struct Student *s = studentList;
        // traversing the student list
        while (s != NULL)
        {
            // writing the student details to the file
            fprintf(filePointer, "%s,%s,%d,%d,%d,%.2f,%d\n", s->name, s->dob, s->year, s->class, s->number, s->balance, s->expenseListSize);
            // writing the student's expense details to the file
            if (s->expenseListSize > 0)
            {
                struct Expense *temp = s->studentExpenseHead;
                for (int i = 0; i < s->expenseListSize; i++)
                {
                    fprintf(filePointer, "%.2f,%s,%s\n", temp->value, temp->description, temp->date);
                    temp = temp->next;
                }
            }
            s = s->nextSudent;
        }
        // closing the file after writing
        fclose(filePointer);
    }
}
