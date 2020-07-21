//
// Created by gabri on 7/17/20.
//

#ifndef BANK_SYSTEM_TRANSACTION_H
#define BANK_SYSTEM_TRANSACTION_H

#include "FileStructure.h"
#include "Date.h"
#include <ctime>

class Transaction {
private:
    TRANS_INFO _transInfo{};
    Date _date{};
    void CloneTransInfo(const TRANS_INFO& info) { _transInfo = info; }

public:
    Transaction() {
        _transInfo.Clear();
        _date = Date(&_transInfo);
    }

    explicit Transaction(const TRANS_INFO& info) {
        CloneTransInfo(info);
    }

    TRANS_INFO *GetTransInfo_ptr() { return &_transInfo; }

    bool SetTRANSCODE(TRANS_CODE transCode);
    bool SetAmount(double amount);                                                                                //test
    bool SetFromID(int fromID);                                                                                   //test
    bool SetToID(int toID);                                                                                       //test
    TRANS_CODE GetTRANSCODE() const;

    int  GetDay()      const;                                                                                     //test
    int  GetMonth()    const;                                                                                     //test
    int  GetYear()     const;                                                                                     //test
    double GetAmount() const;                                                                                     //test
    int GetFromID()    const;                                                                                     //test
    int GetToID()      const;                                                                                     //test

    Date GetDate() const;
};

#endif //BANK_SYSTEM_TRANSACTION_H
