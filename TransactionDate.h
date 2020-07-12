//
// Created by gabri on 12/07/20.
//

#ifndef BANK_SYSTEM_TRANSACTIONDATE_H
#define BANK_SYSTEM_TRANSACTIONDATE_H

#include <ctime>

class TransactionDate {
private:
    int _day{}, _month{}, _year{};
public:
    int getDay() const   { return _day;   }
    int getMonth() const { return _month; }
    int getYear() const  { return _year;  }

    void setDay(int day)     { TransactionDate::_day = day;     }
    void setMonth(int month) { TransactionDate::_month = month; }
    void setYear(int year)   { TransactionDate::_year = year;   }

public:
    TransactionDate() {
        time_t t = time(nullptr);
        tm *timePtr = localtime(&t);

        setDay(timePtr->tm_mday);
        setMonth(timePtr->tm_mon + 1);
        setYear(1900 + timePtr->tm_year);
    }
};

#endif //BANK_SYSTEM_TRANSACTIONDATE_H
