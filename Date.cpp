//
// Created by gabri on 7/20/20.
//

#include "Date.h"


Date::Date(TRANS_INFO* transInfo) : _transInfo(transInfo){
    time_t t = time(nullptr);
    if (t == -1) {
        _transInfo->isValidData = false;
        return;
    }

    tm *timePtr = localtime(&t);
    if (timePtr == nullptr) {
        _transInfo->isValidData = false;
        return;
    }

    SetDay(timePtr->tm_mday);
    SetMonth(timePtr->tm_mon + 1);
    SetYear(1900 + timePtr->tm_year);

    _transInfo->isValidData = true;
}

bool Date::IsBissextile(int year) {
    return year % 4 == 0 or year % 400 == 0;
}

// 30 : 4,6,9,11
//
bool Date::SetDay(int day) {
    int month = GetMonth();
    if ( day < 1  or
         day > 31 or
        (month == 2  and not IsBissextile(GetYear()) and day > 28) or
        (month == 2  and IsBissextile(GetYear()) and day > 29) or
        (month == 4  and day > 30) or
        (month == 6  and day > 30) or
        (month == 9  and day > 30) or
        (month == 11 and day > 30) )
        return false;
    _transInfo->Day = day;
    return true;
}
bool Date::SetMonth (int month) {
    if (month <= 1 or month >= 12)
        return false;
    _transInfo->Month = month;
    return true;
}

bool Date::SetYear(int year) {
    _transInfo->Year = year;
    return true;
}


int Date::GetDay() const {
    return _transInfo->Day;
}
int Date::GetMonth() const {
    return _transInfo->Month;
}
int Date::GetYear() const {
    return _transInfo->Year;
}

bool Date::IsValidDate() const {
    return _transInfo->isValidData;
}