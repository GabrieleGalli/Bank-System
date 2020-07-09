//
// Created by gabri on 08/07/20.
//

#include <iostream>
#include "Account.h"

//----------------------------------------------------------------------------------------------------------------------

double Account::GetAmount() {
    // Calculate the total amount of an account adding every transaction's amount
    double amount = 0;
    for (auto t : _transactions)
        amount += t->Amount;

    return amount;
}
//----------------------------------------------------------------------------------------------------------------------

void Account::ClearTransactionsList(std::list<TRANS_INFO* > *tlist) {
    // Takes a list of transaction info and clear it
    if (not tlist->empty()) {
        for (;;) {
            auto trans = tlist->back();
            if (trans == nullptr)
                break;
            tlist->remove(trans);
            delete trans;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
