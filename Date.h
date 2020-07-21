//
// Created by gabri on 7/20/20.
//

#ifndef BANK_SYSTEM_DATE_H
#define BANK_SYSTEM_DATE_H

#include <ctime>
#include "FileStructure.h"

class Date {
public:
    static bool GetDate(TRANS_INFO* transInfo) {
        time_t t = time(nullptr);
        if (t == -1) {
            transInfo->isValidData = false;
            return false;
        }

        tm *timePtr = localtime(&t);
        if (timePtr == nullptr) {
            transInfo->isValidData = false;
            return false;
        }

        transInfo->Day   = timePtr->tm_mday;
        transInfo->Month = timePtr->tm_mon + 1;
        transInfo->Year  = 1900 + timePtr->tm_year;

        transInfo->isValidData = true;
        return true;
    }
};


#endif //BANK_SYSTEM_DATE_H
