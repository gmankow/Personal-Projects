#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "job.h"
#include "parameters.h"
#include "person.h"
#include "school.h"

Job* initJob(Person *p) {
    Job *j = (Job *)malloc(sizeof(Job));
    School *s = p->sch;
    if (strcmp(s->educationLevel, "College") == 0) {
        Student *stu = p->stu;
        j->salary = giveSalary(stu->major);
        int randHours = rand() % 4 + 6;
        j->hoursPerDay = randHours;
    }
    else {
        j->salary = 0;
        j->hoursPerDay = 0;
    }
    return j;
}

void displayJob(Job *j) {
    printf("Salary: %d, Hours: %d\n", j->salary, j->hoursPerDay);
}

void changeSalary(Job *j, int newSalary) {
    j->salary = newSalary;
}

void changeHours(Job *j, int newHours) {
    j->hoursPerDay = newHours;
}

void changeJob(Job *j, int newSalary, int newHours) {
    j->salary = newSalary;
    j->hoursPerDay = newHours;
}

int work(Job *j) {
    // randomize the hours worked
    // creates a random number between -1 and 1 and adds it to the hours worked
    int randHours = (rand() % 3) - 1;
    //printf("Working %d hours\n", j->hoursPerDay + randHours);
    //printf("You made: %d\n", j->salary * (j->hoursPerDay + randHours));
    return j->salary * (j->hoursPerDay + randHours);
}