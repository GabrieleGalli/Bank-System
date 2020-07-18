//
// Created by gabri on 7/16/20.
//

#include "Transaction.h"

void Transaction::InitDate() {
    time_t t = time(nullptr);
    if (t == -1) {
        _transInfo.isValidData = false;
        return;
    }

    tm *timePtr = localtime(&t);
    if (timePtr == nullptr) {
        _transInfo.isValidData = false;
        return;
    }

    SetDay(timePtr->tm_mday);
    SetMonth(timePtr->tm_mon + 1);
    SetYear(1900 + timePtr->tm_year);

    _transInfo.isValidData = true;
}

bool Transaction::SetTRANSCODE(TRANS_CODE transCode) {
    _transInfo.Code = transCode;
    return true;
}
bool Transaction::SetDay(int day){
    _transInfo.Day = day;
    return true;
}
bool Transaction::SetMonth (int month){
    _transInfo.Month = month;
    return true;
}
bool Transaction::SetYear(int year){
    _transInfo.Year = year;
    return true;
}
bool Transaction::ValidateDate(bool isValid) {
    _transInfo.isValidData = isValid;
    return true;
}
bool Transaction::SetAmount(double amount){
    _transInfo.Amount = amount;
    return true;
}
bool Transaction::SetFromID(int fromID){
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
bool Transaction::IsValidDate() const {
    return _transInfo.isValidData;
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
