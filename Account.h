//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNT_H
#define BANK_SYSTEM_ACCOUNT_H

#include "FileStructure.h"
#include "Transaction.h"
#include <list>
#include <map>

class Account {
private:
    ACCOUNT_INFO _accountInfo{};

    void CloneAccountInfo(const ACCOUNT_INFO& info) { _accountInfo = info; }

protected:
    std::list<Transaction *> _transactions;

public:
    Account() { _accountInfo.Clear(); }
    explicit Account(const ACCOUNT_INFO& info) { CloneAccountInfo(info); }
    virtual ~Account() { ClearTransactionsList(&_transactions); }

    std::list<Transaction *> *GetTransactions() { return &_transactions; }
    ACCOUNT_INFO * GetAccountInfo_ptr() { return &_accountInfo; }

    static void ClearTransactionsList(std::list<Transaction *> *tlist);

    bool SetID(int ID);                                                                                           //test
    bool SetName(const std::string& name);                                                                        //test
    bool SetSurname (const std::string& surname);                                                                 //test
    bool SetFiscalCode(const std::string& fiscalCode);                                                            //test
    bool SetCity(const std::string& city);                                                                        //test
    bool SetCitizen(const std::string& citizen);                                                                  //test
    bool SetPassword(const std::string& pass);                                                                    //test
    bool SetAmount(double amount);                                                                                //test
    bool UpdateAmount(double amount);                                                                             //test

    int GetID() const { return _accountInfo.ID; }                                                                 //test
    std::string GetName()       const;                                                                            //test
    std::string GetSurname()    const;                                                                            //test
    std::string GetFiscalCode() const;                                                                            //test
    std::string GetCity()       const;                                                                            //test
    std::string GetCitizen()    const;                                                                            //test
    std::string GetPassword()   const;                                                                            //test
    double GetAmount()          const;                                                                            //test
    double CalculateAmount()    const;
};

#endif //BANK_SYSTEM_ACCOUNT_H
