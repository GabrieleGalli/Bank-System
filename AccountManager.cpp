//
// Created by gabri on 08/07/20.
//

#include <iostream>
#include "AccountManager.h"

//**********************************************************************************************************************
// BASIC OPERATIONS *
//*******************
bool AccountManager::CreateNewAccount(const char *name, const char *surname, const char *fiscalCode,
                                      const char *city, const char *citizen, const char *pass) {
    auto *acc = new Account();
    auto &ai = const_cast<ACCOUNT_INFO &>(acc->getAccountInfo());

    size_t len = sizeof(ai.Name);
    strncpy(ai.Name, name, len);
    ai.Name[len - 1] = '\0';

    len = sizeof(ai.Surname);
    strncpy(ai.Surname, surname, len);
    ai.Surname[len - 1] = '\0';

    len = sizeof(ai.FiscalCode);
    strncpy(ai.FiscalCode, fiscalCode, len);
    ai.FiscalCode[len - 1] = '\0';

    len = sizeof(ai.City);
    strncpy(ai.City, city, len);
    ai.City[len - 1] = '\0';

    len = sizeof(ai.Citizen);
    strncpy(ai.Citizen, citizen, len);
    ai.Citizen[len - 1] = '\0';

    len = sizeof(ai.Password);
    strncpy(ai.Password, pass, len);
    ai.Password[len - 1] = '\0';

    ai.ID = GetNewID();
    //ai.IBAN = GetNewIBAN();

    if (not _accounts.empty()) {
        // If accounts already exist, check that what needs to be created does not already exist.
        if (CheckValidAccount(ai)) {
            // If the account doesn't exist, create it.
            _accounts.push_back(acc);
            std::cout << "CreateNewAccount::Pushed Account - Account Num: " << _accounts.size() << std::endl;
            sprintf(_transFileName, "%s%s%s.bin", name, surname, fiscalCode);
            GenerateTransactionsFile(acc);
            return true;
        } else {
            // The account already exists.
            std::cout << "CreateNewAccount::This account already exists. Retry." << std::endl;
            delete acc;
            return false;
        }
    } else {
        _accounts.push_back(acc);
        std::cout << "CreateNewAccount::Pushed Account - Account Num: " << _accounts.size() << std::endl;
        sprintf(_transFileName, "%s%s%s.bin", name, surname, fiscalCode);
        GenerateTransactionsFile(acc);
        return true;
    }
}
//----------------------------------------------------------------------------------------------------------------------

int AccountManager::ClearAccounts(std::list<Account *> alist) {
    int nAcc = 0;
    for (;;) {
        auto account = alist.back();
        if (account == nullptr)
            break;
        alist.remove(account);
        delete account;
        nAcc++;
    }
    return nAcc;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// CHECK *
//********
bool AccountManager::CheckValidAccount(const Account_struct &aStruct) {
    bool isSuccess = true;

    for (auto account : _accounts) {
        auto &ai = const_cast<ACCOUNT_INFO &>(account->getAccountInfo());
        if (strcmp(aStruct.FiscalCode, ai.FiscalCode) == 0) {
            std::cout << "CheckValidAccount::Equal Fiscal Codes" << std::endl;
            isSuccess = false;
            break;
        }
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// GET *
//******
int AccountManager::GetNewID() {
    // Ensures that the new account receives an unique ID
    int newID = GetNumAccounts() + 1;
    for (auto &account : _accounts) {
        auto &ai = const_cast<ACCOUNT_INFO &>(account->getAccountInfo());
        if (newID <= ai.ID)
            newID = ai.ID + 1;
    }
    return newID;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// LOAD FILE *
//************
bool AccountManager::LoadAccountsFromFile() {
    // Returns true if Accounts file exists and it's successfully loaded -> exist some accounts

    FILE *fp;
    bool exist = true;

    ClearAccounts(_accounts);

    fp = fopen("Accounts.bin", "rb");
    if (fp == nullptr) {
        // the file has yet to be created
        return exist = false;
    }
    for (;;) {
        // the file has already been created -> push every file's account into _accounts list
        ACCOUNT_INFO accountInfo;
        if (fread(&accountInfo, sizeof(ACCOUNT_INFO), 1, fp) == 1) {
            auto *acc = new Account();
            auto &ai = const_cast<ACCOUNT_INFO &>(acc->getAccountInfo());
            ai = accountInfo;
            _accounts.push_back(acc);
        } else break;
    }

    fclose(fp);
    return exist;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// WRITE TO FILE *
//****************
bool AccountManager::WriteAccountsToFile() {
    FILE *fp;
    bool isSuccess = true;
    fp = fopen("Accounts.dat", "wb");
    if (fp == nullptr)
        return false;
    for (auto &account : _accounts) {
        if (fwrite(&account->getAccountInfo(), sizeof(ACCOUNT_INFO), 1, fp) != 1) {
            isSuccess = false;
            break;
        }
    }
    fclose(fp);
    return isSuccess;
}
//-----------------------------------------------------------------------------------------



//**********************************************************************************************************************
// TRANSACTIONS *
//***************
void AccountManager::GenerateTransactionsFile(Account *account) {
    FILE *fp;
    fp = fopen(_transFileName, "wb");
    fclose(fp);
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// PRINT INFORMATION *
//********************
void AccountManager::PrintAccounts() {
    for (auto &account : _accounts) {
        auto &ai = const_cast<ACCOUNT_INFO &>(account->getAccountInfo());
        std::cout << "ID:" << ai.ID << " Name:" << ai.Name << " Surname:" << ai.Surname << std::endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------