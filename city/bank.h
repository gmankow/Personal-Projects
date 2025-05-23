#ifndef BANK_H
#define BANK_H

typedef struct {
    int accountNumber;
    int balance;
    char *bankName;
} Account;

typedef struct {
    Account accounts[100];
    int totalAccounts;
    char name[50];
} Bank;

void initBank();
Bank* assignBank();
Account* createAccount(Bank *b);
void displayAccount(Account *b);
void deposit(Account *b, int amount);
void withdraw(Account *b, int amount);
void transfer(Account *b1, Account *b2, int amount);
void allAccountsInfo(Bank *b);

#endif