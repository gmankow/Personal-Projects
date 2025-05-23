#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "job.h"
#include "school.h"
#include "parameters.h"
#include "person.h"

void displayPerson(Person *p) {
    printf("\nPerson Info:\n\n");
    printf("Name: %s, Age: %d\n", p->name, p->age);
    displayAccount(p->acc);
    displayJob(p->job);
    displayStudent(p->stu);
}
