//
// Created by gabri on 7/16/20.
//

#include "Transaction.h"

bool Transaction::SetTRANSCODE(TRANS_CODE transCode) {
    _transInfo.Code = transCode;
    return true;
}
bool Transaction::SetAmount(double amount) {
    _transInfo.Amount = amount;
    return true;
}
bool Transaction::SetFromID(int fromID) {
    _transInfo.fromID = fromID;
    return true;
}



bool Transaction::SetToID(int toID){
    _transInfo.toID = toID;
    return true;
}

TRANS_CODE Transaction::GetTRANSCODE() const {
    return _transInfo.Code;
}
int Transaction::GetDay() const {
    return _transInfo.Day;
}
int Transaction::GetMonth() const {
    return _transInfo.Month;
}
int Transaction::GetYear() const {
    return _transInfo.Year;
}
double Transaction::GetAmount() const {
    return _transInfo.Amount;
}
int Transaction::GetFromID() const {
    return _transInfo.fromID;
}
int Transaction::GetToID() const {
    return _transInfo.toID;
}

Date Transaction::GetDate() const {
    return _date;
}
