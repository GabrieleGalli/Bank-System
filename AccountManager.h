//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNTMANAGER_H
#define BANK_SYSTEM_ACCOUNTMANAGER_H


#include "Account.h"

class AccountManager : public Account {
private:
    std::list<Account *> _accounts;
    char _transFileName[FILENAME_MAXLEN];

public:

    // BASIC OPERATIONS
    bool CreateNewAccount(const char *name, const char *surname, const char* fiscalCode,
                          const char* city, const char* citizen, const char* pass);
    static void ClearAccounts(std::list<Account *> list);


    // CHECK
    bool CheckValidAccount(const Account_struct& aStruct);
    bool CheckValidID(int ID);
    bool CheckValidPassword(int ID, const char* pass);
    bool CheckValidID_Test(const int &ID);


    // GET
    int  GetNewID();
    int  GetNumAccounts() const { return _accounts.size(); }
    static void GetFileName(ACCOUNT_INFO &ai, char* fileName);
    std::list<Account *> GetAccounts() { return _accounts; }
    static const char *GetTransactionName(TRANS_CODE transCode);
    Account *GetAccount_FromID(int ID);


    // LOAD
    bool LoadAccountsFromFile();
    static bool LoadTransactionsFromFile(Account *account);
    static bool LoadTransactionsFromFile(Account *account, char *fileName);


    // WRITE
    static bool WriteAccountToFile(Account *account);
    static bool WriteTransactionToFile(const char *fileName, TRANS_INFO *transInfo);


    // TRANSACTIONS
    void GenerateTransactionsFile(Account *account);

    //crded
    bool MakeInternalTransaction(int fromID, int toID, int day, int month, int year, double amount);
    bool Deposit(int ID, double amount, int day, int month, int year);
    static bool Deposit(Account *account, double amount, int day, int month, int year);
    bool Withdrawal(int ID, double amount, int day, int month, int year);
    bool Withdrawal(Account *account, double amount, int day, int month, int year);

    // PRINT INFORMATION
    void PrintAccounts(bool printTrans);
    void PrintTransactions(int ID);


};


#endif //BANK_SYSTEM_ACCOUNTMANAGER_H
