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
    void CloneTransInfo(const TRANS_INFO& info) { _transInfo = info; }

public:
    Transaction() {
        _transInfo.Clear();
        Date::GetDate(&_transInfo);
    }
    explicit Transaction(Transaction* src_trans) {
        auto ti = GetTransInfo_ptr();
        ti->Day = src_trans->GetDay();
        ti->Month = src_trans->GetMonth();
        ti->Year  = src_trans->GetYear();
        ti->isValidData = src_trans->IsValidDate();
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

    bool IsValidDate() const;

    int  GetDay()      const;                                                                                     //test
    int  GetMonth()    const;                                                                                     //test
    int  GetYear()     const;                                                                                     //test
    double GetAmount() const;                                                                                     //test
    int GetFromID()    const;                                                                                     //test
    int GetToID()      const;                                                                                     //test
};

#endif //BANK_SYSTEM_TRANSACTION_H
