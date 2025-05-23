#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "person.h"
#include "bank.h"
#include "job.h"
#include "school.h"
#include "parameters.h"

void simulate(Person *people, int *totDays, int *curDayCount, int *totYears) {
    
    int days;
    printf("\nHow many days would you like to simulate? : ");
    scanf("%d", &days);

    *totDays += days;
    *curDayCount += days;
    int curYears;
    int addAge = 0;

    if (*curDayCount >= 365) {
        curYears = *curDayCount / 365;
        printf("Years: %d\n", curYears);
        addAge = curYears;
        *curDayCount = *curDayCount % 365;
        *totYears += curYears;
    }

    // Sets *p to the start of the array
    // Loops till name is set to null terminator
    Person *p = people;
    while (p->name[0] != '\0') {
        p->age = p->age + addAge;
        for (int i = 0; i < days; i++) {
            School *s = p->sch;
            if (strcmp(s->educationLevel, "High School") != 0) {
                Account *acc = p->acc;
                deposit(acc, work(p->job));
            }
        }
        p++;
    }

    /*
    for (int j = 0; j < totPeople; j++) {
        Person *p = &people[j];
        p->age = p->age + addAge;
        for (int i = 0; i < days; i++) {
            School *s = p->sch;
            if (strcmp(s->educationLevel, "High School") != 0) {
                Account *acc = p->acc;
                deposit(acc, work(p->job));
            }
        }
    }
    */
    addAge = 0;

    printf("Total Days: %d, Total Years: %d, Current Day Count: %d\n", *totDays, *totYears, *curDayCount);

}

int main() {
    int totDays = 0;
    int curDayCount = 0;
    int totYears = 0;
    int *pTotDays = &totDays;
    int *pCurDayCount = &curDayCount;
    int *pTotYears = &totYears;
    
    int personsToCreate;
    printf("How many people would you like to create? : ");
    scanf("%d", &personsToCreate);

    // Initialize the banks
    initBank();

    // Initialize the array for all persons, +1 for the null terminator
    Person *allPersons = (Person *)malloc((personsToCreate + 1) * sizeof(Person));

    // Seed the random number generator
    srand(time(NULL));
    // Create the persons
    for (int i = 0; i < personsToCreate; i++) {
        int randAge = rand() % 100;
        Person p = {"Test", randAge, assignBank(), createAccount(p.b), initSchool(&p), addStudent(p.sch, &p), initJob(&p)};
        allPersons[i] = p;
    }
    allPersons[personsToCreate].name[0] = '\0'; // Null terminate the last name to indicate the end of the array

    // Display the persons before the simulation
    for (int i = 0; i < personsToCreate; i++) {
        displayPerson(&allPersons[i]);
    }

    // Simulate the days
    printf("\n\nSIMULATING\n");
    simulate(allPersons, pTotDays, pCurDayCount, pTotYears);
    printf("\nSIMULATION COMPLETE\n\n");

    // Display the persons after the simulation
    for (int i = 0; i < personsToCreate; i++) {
        displayPerson(&allPersons[i]);
    }

    return 0;
}