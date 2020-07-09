//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_ACCOUNT_H
#define BANK_SYSTEM_ACCOUNT_H


#include "FileStructure.h"
#include <list>
#include <map>

class Account {
private:
    ACCOUNT_INFO _accountInfo{};
    TRANS_INFO   _transInfo{};

protected:
    std::list<TRANS_INFO*> _transactions;

public:
    Account() { _accountInfo.Clear(); }
    virtual ~Account() { ClearTransactionsList(&_transactions); }

    ACCOUNT_INFO &getAccountInfo() { return _accountInfo; }
    TRANS_INFO   *getTransInfo()   { return &_transInfo;  }
    std::list<TRANS_INFO *> *getTransactions() { return &_transactions; }

    double GetAmount();
    static void ClearTransactionsList(std::list<TRANS_INFO* > *tlist);

};


#endif //BANK_SYSTEM_ACCOUNT_H
