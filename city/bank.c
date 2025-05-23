#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"
#include "parameters.h"

Bank **createdBanks;

void initBank() {
    createdBanks = (Bank *)malloc(sizeof(Bank *) * 3);
    for (int i = 0; i < 3; i++) {
        createdBanks[i] = (Bank *)malloc(sizeof(Bank));
        Bank *b = (Bank *)malloc(sizeof(Bank));
        strcpy(b->name, giveBanks(i));
        //printf("Bank created: %s\n", b->name);
        b->totalAccounts = 0;
        createdBanks[i] = b;
    }
}

Bank* assignBank() {
    int randBank = rand() % 3;
    //printf("Bank assigned: %s\n", createdBanks[randBank]->name);
    return createdBanks[randBank];
}

Account* createAccount(Bank *b) {
    Account *newAccount = &b->accounts[b->totalAccounts];
    newAccount->accountNumber = b->totalAccounts++;
    newAccount->balance = 0;
    newAccount->bankName = b->name;
    //printf("Account created at: %s\n", b->name);

    return newAccount;
}

void displayAccount(Account *b) {
   printf("Bank: %s, Account Number: %d, Balance: %d\n", b->bankName, b->accountNumber, b->balance);
}

void deposit(Account *b, int amount) {
    b->balance += amount;
}

void withdraw(Account *b, int amount) {
    if (b->balance < amount) {
        printf("Insufficient balance\n");
    } else {
        b->balance -= amount;
    }
}

void transfer(Account *b1, Account *b2, int amount) {
    if (b1->balance < amount) {
        printf("Insufficient balance\n");
    } else {
        b1->balance -= amount;
        b2->balance += amount;
    }
}

void allAccountsInfo(Bank *b) {
    printf("Bank Name: %s\n", b->name);
    for (int i = 0; i < b->totalAccounts; i++) {
        printf("Account Number: %d, Balance: %d\n", i, b->accounts[i].balance);
    }
}