#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school.h"
#include "parameters.h"
#include "person.h"

School* initSchool(Person *p) {
    School *sch = (School *)malloc(sizeof(School));
    if (p->age >= 18) {
        strcpy(sch->educationLevel, "College");
    } else {
        strcpy(sch->educationLevel, "High School");
    }
    strcpy(sch->schoolName, giveSchool(sch->educationLevel));
    sch->totalStudents = 0;
    return sch;
}

Student* addStudent(School *s, Person *p) {
    Student *newStudent = &s->students[s->totalStudents];
    newStudent->studentName = p->name;
    strcpy(newStudent->educationLevel, s->educationLevel);
    strcpy(newStudent->schoolName, s->schoolName);
    if (strcmp(s->educationLevel, "College") == 0) {
        strcpy(newStudent->major, giveMajor());
    } else {
        strcpy(newStudent->major, "None");
    }
    for (int i = 0; i < 8; i++) {
        int randGrade = rand() % 100;
        newStudent->grades[i] = randGrade;
    }
    s->totalStudents++;

    return newStudent;
}

void displayAllStudents(School *s) {
    printf("School Name: %s\n", s->schoolName);
    for (int i = 0; i < s->totalStudents; i++) {
        displayStudent(&s->students[i]);
    }
}

void displayStudent(Student *s) {
    printf("Student Name: %s, Education Level: %s, School: %s, Major: %s\n", s->studentName, s->educationLevel, s->schoolName,s->major);
    printf("Grades: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", s->grades[i]);
    }
    printf("\n");
}