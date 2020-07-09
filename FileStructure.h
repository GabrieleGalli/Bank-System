//
// Created by gabri on 08/07/20.
//

#ifndef BANK_SYSTEM_FILESTRUCTURE_H
#define BANK_SYSTEM_FILESTRUCTURE_H

#include <cstring>

enum TRANS_CODE {
    // In Codes
    Deposit_code,
    Transfer_IN,

    // Out Codes
    Withdrawal,
    Transfer_OUT
};

typedef struct Account_struct {
    size_t size;
    int ID;
    char Name[50];
    char Surname[50];
    char FiscalCode[18];
    char City[50];
    char Citizen[20];
    char Password[50];
    double Amount;

    void Clear() {
        size = sizeof(Account_struct);
        ID = 0;
        strcpy(Name, "");
        strcpy(Surname, "");
        strcpy(FiscalCode, "");
        strcpy(City, "");
        strcpy(Citizen, "");
        strcpy(Password, "");
    }
} ACCOUNT_INFO;

typedef struct Transactions_struct {
    size_t size;
    TRANS_CODE Code;
    int Day;
    int Month;
    int Year;
    double Amount;
} TRANS_INFO;

#endif //BANK_SYSTEM_FILESTRUCTURE_H
