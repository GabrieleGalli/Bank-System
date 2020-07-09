//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNTMANAGER_H
#define BANK_SYSTEM_ACCOUNTMANAGER_H


#include "Account.h"

class AccountManager : public Account {
private:
    std::list<Account *> _accounts;
    char _transFileName[150];

public:

    // BASIC OPERATIONS
    bool CreateNewAccount(const char *name, const char *surname, const char* fiscalCode,
                          const char* city, const char* citizen, const char* pass);
    static int ClearAccounts( std::list<Account *> list);

    // CHECK
    bool CheckValidAccount(const Account_struct& aStruct);
    bool CheckValidID(int ID);
    bool CheckValidPassword(int ID, const char* pass);
    bool CheckValidID_Test(const int &ID);


    // GET
    int  GetNewID();
    int  GetNumAccounts() const { return _accounts.size(); }
    std::list<Account *> GetAccounts() { return _accounts; }
    static const char *GetTransactionName(TRANS_CODE transCode);
    Account *GetAccount_FromID(int ID);

    // LOAD
    bool LoadAccountsFromFile();

    bool WriteAccountsToFile();

    // TRANSACTIONS
    void GenerateTransactionsFile(Account* account);

    // PRINT INFORMATION
    void PrintAccounts(bool printTrans);
    void PrintTransactions(int ID);


};


#endif //BANK_SYSTEM_ACCOUNTMANAGER_H
