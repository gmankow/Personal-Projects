#ifndef PERSON_H
#define PERSON_H

typedef struct {
    char name[50];
    int age;
    struct Bank *b;
    struct Account *acc;
    struct School *sch;
    struct Student *stu;
    struct Job *job;
} Person;

void displayPerson(Person *p);

#endif