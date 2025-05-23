#ifndef JOB_H
#define JOB_H

#include "person.h"

typedef struct {
    int salary;
    int hoursPerDay;
} Job;

Job* initJob(Person *p);
void displayJob(Job *j);
void changeSalary(Job *j, int newSalary);
void changeHours(Job *j, int newHours);
void changeJob(Job *j, int newSalary, int newHours);
int work(Job *j);

#endif