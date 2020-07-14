//
// Created by gabri on 08/07/20.
//

#include <iostream>
#include "AccountManager.h"

//**********************************************************************************************************************
// BASIC OPERATIONS *
//*******************
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CreateNewAccount(const char *name, const char *surname, const char *fiscalCode,
                                      const char *city, const char *citizen, const char *pass) {
    auto *acc = new Account();
    auto &ai = acc->GetAccountInfo();

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

    if (not _accounts.empty()) {
        // If accounts already exist, check that what needs to be created does not already exist.
        if (CheckValidAccount(ai)) {
            // If the account doesn't exist, create it.
            _accounts.push_back(acc);
            sprintf(_transFileName, "%s%s%s.bin", name, surname, fiscalCode);
        } else {
            // The account already exists.
            std::cout << "Impossible to create this account. Retry." << std::endl;
            delete acc;
            return false;
        }
    } else {
        _accounts.push_back(acc);
        sprintf(_transFileName, "%s%s%s.bin", name, surname, fiscalCode);
    }

    if (WriteAccountToFile(acc)) {
        GenerateTransactionsFile(acc);
        std::cout << "Your new ID is: " << ai.ID << std::endl;
        return true;
    } else {
        delete acc;
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::ClearAccounts(std::list<Account *> *list) {
    // Clears the list of accounts
    for (;;) {
        auto account = list->back();
        if (account == nullptr)
            break;
        list->remove(account);
        delete account;
    }
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// CHECK *
//********
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CheckValidAccount(const Account_struct &aStruct) {
    bool isSuccess = true;

    for (auto account : _accounts) {
        auto &ai = account->GetAccountInfo();
        if (strcmp(aStruct.FiscalCode, ai.FiscalCode) == 0) {
            isSuccess = false;
            break;
        }
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CheckValidID(int ID) {
    // Returns true if given ID already exists.
    bool isSuccess = false;

    for (auto account : _accounts) {
        auto &ai = account->GetAccountInfo();
        if (ai.ID == ID) {
            isSuccess = true;
            break;
        }
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CheckValidPassword(int ID, const char *pass) {
    // Returns true if the password given, associated with that ID, is correct.
    bool isSuccess = false;

    for (auto account : _accounts) {
        auto &ai = account->GetAccountInfo();
        if (ai.ID == ID and strcmp(ai.Password, pass) == 0) {
            isSuccess = true;
            break;
        }
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// GET *
//******
//----------------------------------------------------------------------------------------------------------------------

int AccountManager::GetNewID() {
    // Ensures that the new account receives an unique ID.
    int newID = GetNumAccounts() + 1;
    for (auto &account : _accounts) {
        auto &ai = account->GetAccountInfo();
        if (newID <= ai.ID)
            newID = ai.ID + 1;
    }
    return newID;
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::GetFileName(ACCOUNT_INFO &ai, char *fileName) {
    sprintf(fileName, "%s%s%s.bin", ai.Name, ai.Surname, ai.FiscalCode);
}
//----------------------------------------------------------------------------------------------------------------------

const char *AccountManager::GetTransactionName(TRANS_CODE transCode) {
    // Retrieve the transaction's code.
    switch (transCode) {
        case Deposit_code:
            return "Deposit";
        case Transfer_IN:
            return "Transfer IN";
        case Withdrawal_Code:
            return "Withdrawal";
        case Transfer_OUT:
            return "Transfer OUT";
        default:
            return "Unknown operation";
    }
}
//----------------------------------------------------------------------------------------------------------------------

Account *AccountManager::GetAccount_FromID(int ID) {
    // Retrieve an account by given ID.
    for (auto account : _accounts) {
        auto &ai = account->GetAccountInfo();
        if (ai.ID == ID)
            return account;
    }
    return nullptr;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// LOAD *
//*******
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::LoadAccountsFromFile() {
    // Load accounts from Accounts.dat to accounts list. It must be done once.

    FILE *fp;
    bool exist = true;

    ClearAccounts(&_accounts);

    fp = fopen("Accounts.dat", "rb");
    if (fp == nullptr)  // the file has yet to be created
        return exist = false;

    // the file has already been created -> push every file's account into _accounts list
    ACCOUNT_INFO accountInfo;
    while (fread(&accountInfo, sizeof(ACCOUNT_INFO), 1, fp) == 1) {
        auto *acc = new Account();
        auto &ai = acc->GetAccountInfo();
        ai = accountInfo;
        if (not LoadTransactionsFromFile(acc)) {
            delete acc;
            return false;
        }
        _accounts.push_back(acc);
    }

    fclose(fp);
    return exist;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::LoadTransactionsFromFile(Account *account) {
    char fileName[FILENAME_MAXLEN];
    auto info = account->GetAccountInfo();
    GetFileName(info, fileName);
    return LoadTransactionsFromFile(account, fileName);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::LoadTransactionsFromFile(Account *account, char *fileName) {

    FILE *fp;
    double amount = 0;

    auto tr_list = account->GetTransactions();
    Account::ClearTransactionsList(tr_list);

    fp = fopen(fileName, "rb");
    if (fp == nullptr)
        return true;

    TRANS_INFO transInfo;
    for (;;) {
        size_t len = fread(&transInfo, 1, sizeof(TRANS_INFO), fp);
        if (len != sizeof(TRANS_INFO))
            break;

        auto *pti = new(TRANS_INFO);
        *pti = transInfo;
        amount += transInfo.Amount;
        tr_list->push_back(pti);
    }

    auto &acc_Ainfo = account->GetAccountInfo();
    acc_Ainfo.Amount = amount;

    fclose(fp);
    return true;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// WRITE TO FILE *
//****************
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::WriteAccountToFile(Account *account) {
    FILE *fp;
    bool isSuccess = true;
    fp = fopen("Accounts.dat", "ab");
    if (fp == nullptr)
        return false;

    if (fwrite(&account->GetAccountInfo(), sizeof(ACCOUNT_INFO), 1, fp) != 1)
        isSuccess = false;

    fclose(fp);
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::WriteTransactionToFile(const char *fileName, TRANS_INFO *transInfo) {
    FILE *fp;
    bool isSuccess = true;

    fp = fopen(fileName, "ab");
    if (fp == nullptr)
        return false;
    if (fwrite(transInfo, sizeof(TRANS_INFO), 1, fp) == 1)
        isSuccess = true;

    fclose(fp);
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// TRANSACTIONS *
//***************
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::GenerateTransactionsFile(Account *account) {
    FILE *fp;
    fp = fopen(_transFileName, "wb");
    fclose(fp);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::MakeInternalTransaction(int fromID, int toID, int day, int month, int year, double amount) {
    if (fromID == toID)
        return false;
    if (amount <= 0)
        return false;

    auto src = GetAccount_FromID(fromID);
    auto dst = GetAccount_FromID(toID);
    if (src == nullptr or dst == nullptr)
        return false;

    char srcFileName[FILENAME_MAXLEN] = "";
    char dstFileName[FILENAME_MAXLEN] = "";

    Account_struct &src_Ainfo = src->GetAccountInfo();
    auto src_tlist = src->GetTransactions();

    TRANS_INFO transInfoSrc;
    double tmp;
    if (src_Ainfo.Amount >= amount) {
        transInfoSrc.Day = day;
        transInfoSrc.Month = month;
        transInfoSrc.Year = year;
        transInfoSrc.Code = Transfer_OUT;
        transInfoSrc.Amount = -amount;

        GetFileName(src_Ainfo, srcFileName);
        if (not WriteTransactionToFile(srcFileName, &transInfoSrc))
            return false;

        auto *ptri = new(TRANS_INFO);
        *ptri = transInfoSrc;
        src_tlist->push_back(ptri);
        src_Ainfo.Amount -= amount;
        tmp = src->GetAccountInfo().Amount;
    } else {
        std::cout << "You don't have enough money in your account to make a transfer" << std::endl;
        return false;
    }

    Account_struct &dst_Ainfo = dst->GetAccountInfo();
    auto dst_tlist = dst->GetTransactions();

    TRANS_INFO transInfoDst;
    transInfoDst.Day = day;
    transInfoDst.Month = month;
    transInfoDst.Year = year;
    transInfoDst.Code = Transfer_IN;
    transInfoDst.Amount = amount;

    GetFileName(dst_Ainfo, dstFileName);
    if (not WriteTransactionToFile(dstFileName, &transInfoDst))
        return false;

    auto *ptri = new(TRANS_INFO);
    *ptri = transInfoDst;
    dst_tlist->push_back(ptri);
    dst_Ainfo.Amount += amount;

    return true;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Deposit(int ID, double amount, int day, int month, int year) {

    if (amount <= 0)
        return false;

    auto account = GetAccount_FromID(ID);
    if (account == nullptr)
        return false;

    char fileName[FILENAME_MAXLEN] = "";

    auto tlist = account->GetTransactions();

    TRANS_INFO transInfo;
    transInfo.Day = day;
    transInfo.Month = month;
    transInfo.Year = year;
    transInfo.Code = Deposit_code;
    transInfo.Amount = amount;

    GetFileName(account->GetAccountInfo(), fileName);
    if (WriteTransactionToFile(fileName, &transInfo)) {
        auto *ptri = new(TRANS_INFO);
        *ptri = transInfo;
        std::cout << amount << " deposited in your account" << std::endl;
        tlist->push_back(ptri);
        auto &acc_Ainfo = account->GetAccountInfo();
        acc_Ainfo.Amount += amount;
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Deposit(Account *account, double amount, int day, int month, int year) {

    if (amount <= 0)
        return false;

    if (account == nullptr)
        return false;

    char fileName[FILENAME_MAXLEN] = "";

    auto tlist = account->GetTransactions();

    TRANS_INFO transInfo;
    transInfo.Day = day;
    transInfo.Month = month;
    transInfo.Year = year;
    transInfo.Code = Deposit_code;
    transInfo.Amount = amount;

    GetFileName(account->GetAccountInfo(), fileName);
    if (WriteTransactionToFile(fileName, &transInfo)) {
        auto *ptri = new(TRANS_INFO);
        *ptri = transInfo;
        std::cout << amount << " deposited in your account" << std::endl;
        tlist->push_back(ptri);
        auto &acc_Ainfo = account->GetAccountInfo();
        acc_Ainfo.Amount += amount;
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Withdrawal(int ID, double amount, int day, int month, int year) {
    if (amount <= 0)
        return false;

    auto account = GetAccount_FromID(ID);
    if (account == nullptr)
        return false;

    auto ai = account->GetAccountInfo();

    char fileName[FILENAME_MAXLEN] = "";

    auto tlist = account->GetTransactions();

    TRANS_INFO transInfo;
    if (ai.Amount >= amount) {
        transInfo.Day = day;
        transInfo.Month = month;
        transInfo.Year = year;
        transInfo.Code = Withdrawal_Code;
        transInfo.Amount = -amount;


        GetFileName(account->GetAccountInfo(), fileName);
        if (WriteTransactionToFile(fileName, &transInfo)) {
            auto *ptri = new(TRANS_INFO);
            *ptri = transInfo;
            std::cout << amount << " withdrawn from your account." << std::endl;
            tlist->push_back(ptri);
            auto &acc_Ainfo = account->GetAccountInfo();
            acc_Ainfo.Amount -= amount;
            return true;
        }
    } else
        return false;

    return false;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Withdrawal(Account *account, double amount, int day, int month, int year) {

    if (account == nullptr)
        return false;

    auto ai = account->GetAccountInfo();
    if (amount <= 0)
        return false;

    char fileName[FILENAME_MAXLEN];

    auto tlist = account->GetTransactions();

    TRANS_INFO transInfo;
    if (ai.Amount >= amount) {
        transInfo.Day = day;
        transInfo.Month = month;
        transInfo.Year = year;
        transInfo.Code = Withdrawal_Code;
        transInfo.Amount = -amount;

        GetFileName(account->GetAccountInfo(), fileName);
        if (WriteTransactionToFile(fileName, &transInfo)) {
            auto *ptri = new(TRANS_INFO);
            *ptri = transInfo;
            std::cout << amount << " withdrawn from your account." << std::endl;
            tlist->push_back(ptri);
            auto &acc_Ainfo = account->GetAccountInfo();
            acc_Ainfo.Amount -= amount;
            return true;
        } else
            return false;
    }
    return false;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// PRINT INFORMATION *
//********************
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::PrintAccounts(bool printTrans) {
    // Prints account details (ID, name, surname).
    // If printTrans is set to true it also prints all account transactions.
    for (auto &account : _accounts) {
        auto &ai = account->GetAccountInfo();
        std::cout << "ID:" << ai.ID << " Name:" << ai.Name << " Surname:" << ai.Surname << std::endl;
        if (printTrans)
            PrintTransactions(ai.ID);
    }
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::PrintTransactions(int ID) {
    // Prints all account (retrieved from ID) transactions.
    auto acc = GetAccount_FromID(ID);
    auto trs = acc->GetTransactions();
    int count = 1;
    for (auto t : *trs) {
        std::cout << "Transaction: " << count << std::endl
                  << "Date: "   << t->Day << "/" << t->Month << "/" << t->Year << std::endl
                  << "Amount: " << t->Amount << std::endl
                  << "Code: "   << GetTransactionName(t->Code) << std::endl << std::endl;
        count++;
    }
    count = 0;
}
//----------------------------------------------------------------------------------------------------------------------