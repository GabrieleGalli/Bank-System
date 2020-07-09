//
// Created by gabri on 08/07/20.
//

#include "Account.h"

ACCOUNT_INFO &Account::getAccountInfo() {
    return _accountInfo;
}

std::list<TRANS_INFO *> &Account::getTransactions() {
    return _transactions;
}

TRANS_INFO &Account::getTransInfo() {
    return _transInfo;
}