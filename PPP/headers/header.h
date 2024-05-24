#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef PPPDONE_HEADER_H
#define PPPDONE_HEADER_H

#endif //PPPDONE_HEADER_H

// defining a structure for storing detials of expense
struct Expense
{
    double value;
    char description[100];
    char date[15];
    // pointer to next expense for a student
    struct Expense *next;
};

// defining a structure for storing detials of Student
struct Student
{
    char name[50];
    char dob[15];
    int class;
    int year;
    int number;
    double balance;
    int expenseListSize;

    // pointer to next student
    struct Student *nextSudent;
    // head pointer of the expenselist of the student
    struct Expense *studentExpenseHead;
};

struct Student *swap(struct Student *s1, struct Student *s2);
void insertExpenses(struct Student *student, double val, char descrip[], char date[]);
void sortBalanceWise(struct Student **head, int numStudents);
void sortAlphabatically(struct Student **head, int numStudents);
int exist(struct Student *head, int number);
void insertStudent(struct Student **head, char name[], char dob[], int class, int year, int number, double balance, int *studentCount);
void deleteStudent(struct Student **head, int number, int *studentCount);
void printStudent(struct Student *s);
void printStudents(struct Student *head);
void readInputData(struct Student **StudentList, int *studentCount);
void writeToFile(struct Student *studentList);
//int validateDateOfExpense(char date[], char dob[]);
int validateDate(char date[]);


