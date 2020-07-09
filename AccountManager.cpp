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
    auto &ai = acc->getAccountInfo();

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

int AccountManager::ClearAccounts(std::list<Account *> list) {
    // Clears the list of accounts
    int nAcc = 0;
    for (;;) {
        auto account = list.back();
        if (account == nullptr)
            break;
        list.remove(account);
        delete account;
        nAcc++;
    }
    return nAcc;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// CHECK *
//********
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CheckValidAccount(const Account_struct &aStruct) {
    // Ensures that two accounts with the same fiscal code cannot be created.
    bool isSuccess = true;

    for (auto account : _accounts) {
        auto ai = account->getAccountInfo();
        if (strcmp(aStruct.FiscalCode, ai.FiscalCode) == 0) {
            std::cout << "CheckValidAccount::Equal Fiscal Codes" << std::endl;
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
        auto &ai = const_cast<ACCOUNT_INFO &>(account->getAccountInfo());
        if (ai.ID == ID) {
            std::cout << "CheckValidID::Existing ID" << std::endl;
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
        auto &ai = account->getAccountInfo();
        if (ai.ID == ID and strcmp(ai.Password, pass) == 0) {
            std::cout << "CheckValidPassword::Correct ID and Password" << std::endl;
            isSuccess = true;
            break;
        } else if (ai.ID == ID and strcmp(ai.Password, pass) != 0)
            std::cout << "CheckValidPassword::Incorrect ID or Password" << std::endl;
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// GET *
//******
int AccountManager::GetNewID() {
    // Ensures that the new account receives an unique ID.
    int newID = GetNumAccounts() + 1;
    for (auto &account : _accounts) {
        auto &ai = account->getAccountInfo();
        if (newID <= ai.ID)
            newID = ai.ID + 1;
    }
    return newID;
}
//----------------------------------------------------------------------------------------------------------------------

const char* AccountManager::GetTransactionName(TRANS_CODE transCode) {
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

Account * AccountManager::GetAccount_FromID(int ID) {
    // Retrieve an account by given ID.
    for (auto account : _accounts) {
        auto &ai =account->getAccountInfo();
        if (ai.ID == ID)
            return account;
    }

    std::cout << "GetAccount_FromID::This ID doesn't exist" << std::endl;
    return nullptr;
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// LOAD FILE *
//************
bool AccountManager::LoadAccountsFromFile() {
    // Load accounts from Accounts.dat to accounts list. It must be done once.

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
    // Store account details with other accounts.
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
    // Creates the file on which the transactions are based.
    FILE *fp;
    fp = fopen(_transFileName, "wb");
    fclose(fp);
}
//----------------------------------------------------------------------------------------------------------------------



//**********************************************************************************************************************
// PRINT INFORMATION *
//********************
void AccountManager::PrintAccounts(bool printTrans) {
    // Prints account details (ID, name, surname).
    // If printTrans is set to true it also prints all account transactions.
    for (auto &account : _accounts) {
        auto &ai = account->getAccountInfo();
        std::cout << "ID:" << ai.ID << " Name:" << ai.Name << " Surname:" << ai.Surname << std::endl;
        if (printTrans)
            PrintTransactions(ai.ID);
    }
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::PrintTransactions(int ID) {
    // Prints all account (retrieved from ID) transactions.
    auto acc = GetAccount_FromID(ID);
    auto trs = acc->getTransactions();
    int count = 1;
    for (auto t : *trs) {
        std::cout << "Transaction: " << count << std::endl
                  << "Date: "   << t->Day << "/" << t->Month << "/" << t->Year << std::endl
                  << "Amount: " << t->Amount << std::endl
                  << "Code: "   << GetTransactionName(t->Code) << std::endl;
        count++;
    }
    count = 0;
}
//----------------------------------------------------------------------------------------------------------------------