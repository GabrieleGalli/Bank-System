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

    ACCOUNT_INFO &getAccountInfo();
    TRANS_INFO   &getTransInfo();
    std::list<TRANS_INFO *> &getTransactions();

};


#endif //BANK_SYSTEM_ACCOUNT_H
