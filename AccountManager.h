//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNTMANAGER_H
#define BANK_SYSTEM_ACCOUNTMANAGER_H

#include "Account.h"

class AccountManager : public Account {
private:
    std::list<Account *> _accounts;

public:
    // BASIC OPERATIONS
    bool CreateNewAccount(const std::string& name, const std::string& surname, const std::string& fiscalCode,     //test
                          const std::string& city, const std::string& citizen, const std::string& pass);
    static void ClearAccounts(std::list<Account *> *list);                                                        //test


    // CHECK
    bool CheckValidAccount(Account *account);
    bool CheckValidID(int ID);                                                                                    //test
    bool CheckValidPassword(int ID, const std::string& pass);


    // GET
    int GetNewID();                                                                                               //test
    int GetNumAccounts() const { return _accounts.size(); }
    static void GetFileName(Account *account, std::string& fileName);                                             //test
    std::list<Account *> GetAccounts() { return _accounts; }                                                      //test
    static const char *GetTransactionName(TRANS_CODE transCode);
    Account *GetAccount_FromID(int ID);                                                                           //test


    // LOAD
    bool LoadAccountsFromFile();
    static bool LoadTransactionsFromFile(Account *account);
    static bool LoadTransactionsFromFile(Account *account, const std::string& fileName);


    // WRITE
    static bool WriteAccountToFile(Account *account);
    static bool WriteTransactionToFile(const std::string& fileName, Transaction *ptr);


    // TRANSACTIONS
    static void GenerateTransactionsFile(Account *account);
    bool MakeInternalTransaction (int fromID, int toID, double amount);                                           //test
    bool Deposit   (int ID, double amount);                                                                       //test
    bool Withdrawal(int ID, double amount);                                                                       //test
    static bool Deposit   (Account *account, double amount);                                                      //test
    static bool Withdrawal(Account *account, double amount);                                                      //test


    // PRINT INFORMATION
    void PrintAccounts(bool printTrans);
    void PrintTransactions(int ID);

};

#endif //BANK_SYSTEM_ACCOUNTMANAGER_H
