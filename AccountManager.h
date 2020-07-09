//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNTMANAGER_H
#define BANK_SYSTEM_ACCOUNTMANAGER_H


#include "Account.h"

class AccountManager : public Account {
private:
    std::list<Account *> _accounts;
    std::list<TRANS_INFO* > _accTrans;
    //std::map<std::list<TRANS_INFO>, Account *> _accountTransMAP;
    char _transFileName[150];

public:
    // BASIC OPERATIONS
    bool CreateNewAccount(const char *name, const char *surname, const char* fiscalCode,
                          const char* city, const char* citizen, const char* pass);
    static int  ClearAccounts(  std::list<Account *> alist);


    // CHECK
    bool CheckValidAccount(const Account_struct& aStruct);

    // GET
    int  GetNewID();
    int  GetNumAccounts() const { return _accounts.size(); }

    // LOAD
    bool LoadAccountsFromFile();

    bool WriteAccountsToFile();

    // TRANSACTIONS
    void GenerateTransactionsFile(Account* account);

    void PrintAccounts();

};


#endif //BANK_SYSTEM_ACCOUNTMANAGER_H
