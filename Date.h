//
// Created by gabri on 7/20/20.
//

#ifndef BANK_SYSTEM_DATE_H
#define BANK_SYSTEM_DATE_H

#include <ctime>
#include "FileStructure.h"

class Date {
private:
    TRANS_INFO* _transInfo;

public:
    Date() = default;
    explicit Date(TRANS_INFO* _transInfo);

    static bool IsBissextile(int year) ;

    bool SetDay(int day);                                                                                         //test
    bool SetMonth (int month);                                                                                    //test
    bool SetYear(int year);                                                                                       //test

    int  GetDay()      const;                                                                                     //test
    int  GetMonth()    const;                                                                                     //test
    int  GetYear()     const;                                                                                     //test

    bool IsValidDate() const;
};


#endif //BANK_SYSTEM_DATE_H
