#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *EducationLevel[] = {"High School", "College"};
char *HighSchools[] = {"BSM", "Edina High School"};
char *Colleges[] = {"Iowa State University", "University of Iowa", "University of Northern Iowa"};
char *Majors[] = {"Engineering", "Medicine", "Business"};

char *Banks[] = {"Wells Fargo", "US Bank", "Bank of America"};
int EngineeringHrSalary = 100;
int MedicineHrSalary = 130;
int BusinessHrSalary = 70;

char *giveSchool(char *level) {
    if (strcmp(level, "High School") == 0) {
        return HighSchools[rand() % sizeof(HighSchools) / sizeof(HighSchools[0])];
    } else {
        return Colleges[rand() % sizeof(Colleges) / sizeof(Colleges[0])];
    }

}

char *giveEducationLevel() {
    return EducationLevel[rand() % sizeof(EducationLevel) / sizeof(EducationLevel[0])];
}

char *giveMajor() {
    return Majors[rand() % sizeof(Majors) / sizeof(Majors[0])];
}

char *giveBank() {
    return Banks[rand() % sizeof(Banks) / sizeof(Banks[0])];
}

char* giveBanks(int i) {
    return Banks[i];
}

int giveSalary(char *major) {
    if (strcmp(major, "Engineering") == 0) {
        return EngineeringHrSalary;
    } else if (strcmp(major, "Medicine") == 0) {
        return MedicineHrSalary;
    } else {
        return BusinessHrSalary;
    }
}