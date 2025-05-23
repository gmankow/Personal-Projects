#ifndef SCHOOL_H
#define SCHOOL_H

#include "person.h"

typedef struct {
    char *studentName;
    int grades[8];
    char *schoolName[50];
    char *educationLevel[50];
    char *major[50];
} Student;

typedef struct {
    char *schoolName[50];
    Student students[100];
    int totalStudents;
    char *educationLevel[50];
} School;

School* initSchool(Person *p);
Student* addStudent(School *s, Person *p);
void displayStudent(Student *s);
void displayAllStudents(School *s);

#endif