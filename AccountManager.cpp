//
// Created by gabri on 08/07/20.
//

#include <iostream>
#include "AccountManager.h"

//**********************************************************************************************************************
// BASIC OPERATIONS *
//*******************
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CreateNewAccount(const std::string& name, const std::string& surname, const std::string& fiscalCode,                          //test
                                      const std::string& city, const std::string& citizen, const std::string& pass) {
    auto *acc = new Account();

    if (not acc->SetName(name))
        return false;
    if (not acc->SetSurname(surname))
        return false;
    if (not acc->SetFiscalCode(fiscalCode))
        return false;
    if (not acc->SetCity(city))
        return false;
    if (not acc->SetCitizen(citizen))
        return false;
    if (not acc->SetPassword(pass))
        return false;
    if (not acc->SetID(GetNewID()))
        return false;

    if (not _accounts.empty()) {
        // If accounts already exist, check that what needs to be created does not already exist.
        if (not CheckValidAccount(acc)) {
            // The account already exists.
            std::cout << "Impossible to create this account. Retry." << std::endl;
            delete acc;
            return false;
        }
    }

    _accounts.push_back(acc);

    if (WriteAccountToFile(acc)) {
        GenerateTransactionsFile(acc);
        std::cout << "Your new ID is: " << acc->GetID() << std::endl;
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

bool AccountManager::CheckValidAccount(Account *account) {
    bool isSuccess = true;

    for (auto a : _accounts) {
        if (a->GetFiscalCode() == account->GetFiscalCode()) {
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
        if (account->GetID() == ID) {
            isSuccess = true;
            break;
        }
    }
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::CheckValidPassword(int ID, const std::string& pass) {
    // Returns true if the password given, associated with that ID, is correct.
    bool isSuccess = false;

    for (auto account : _accounts) {
        if ( (account->GetID() == ID) and (account->GetPassword() == pass) ) {
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
        if (newID <= account->GetID())
            newID = account->GetID() + 1;
    }
    return newID;
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::GetFileName(Account *account, std::string& fileName) {
    fileName = account->GetName() + account->GetSurname() + account->GetFiscalCode() + ".bin";
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
        if (account->GetID() == ID)
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
        auto *acc = new Account(accountInfo);
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
    std::string fileName;
    GetFileName(account, fileName);
    return LoadTransactionsFromFile(account, fileName);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::LoadTransactionsFromFile(Account *account, const std::string& fileName) {

    FILE *fp;
    double amount = 0;

    auto tr_list = account->GetTransactions();
    Account::ClearTransactionsList(tr_list);

    fp = fopen(fileName.c_str(), "rb");
    if (fp == nullptr)
        return true;

    TRANS_INFO transInfo;
    for (;;) {
        size_t len = fread(&transInfo, 1, sizeof(TRANS_INFO), fp);
        if (len != sizeof(TRANS_INFO))
            break;

        auto *pti = new Transaction(transInfo);
        amount += pti->GetAmount();
        tr_list->push_back(pti);
    }

    account->SetAmount(amount);

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

    if (fwrite(account->GetAccountInfo_ptr(), sizeof(ACCOUNT_INFO), 1, fp) != 1)
        isSuccess = false;

    fclose(fp);
    return isSuccess;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::WriteTransactionToFile(const std::string& fileName, Transaction *ptr) {
    FILE *fp;
    bool isSuccess = true;

    fp = fopen(fileName.c_str(), "ab");
    if (fp == nullptr)
        return false;
    if (fwrite(ptr->GetTransInfo_ptr(), sizeof(TRANS_INFO), 1, fp) == 1)
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
    std::string _transFileName = account->GetName() + account->GetSurname() + account->GetFiscalCode() + ".bin";
    fp = fopen(_transFileName.c_str(), "wb");
    fclose(fp);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::MakeInternalTransaction(int fromID, int toID, double amount) {

    if (fromID == toID)
        return false;
    if (amount <= 0)
        return false;

    auto src = GetAccount_FromID(fromID);
    auto dst = GetAccount_FromID(toID);
    if (src == nullptr or dst == nullptr)
        return false;

    if (src->GetAmount() < amount) {
        std::cout << "You don't have enough money in your account to make a transfer" << std::endl;
        return false;
    }

    bool isSuccess = true;

    auto *ptr_src = new Transaction;
    if (not ptr_src->IsValidDate())
        isSuccess = false;
    if (not ptr_src->SetTRANSCODE(Transfer_OUT))
        isSuccess = false;
    if (not ptr_src->SetAmount(-amount))
        isSuccess = false;
    if (not ptr_src->SetFromID(fromID))
        isSuccess = false;
    if (not ptr_src->SetToID(toID))
        isSuccess = false;

    if (not isSuccess) {
        delete ptr_src;
        return false;
    }


    auto *ptr_dst = new Transaction;
    // Set date from src
    if (not ptr_dst->SetDay(ptr_src->GetDay()))
        isSuccess = false;
    if (not ptr_dst->SetMonth(ptr_src->GetMonth()))
        isSuccess = false;
    if (not ptr_dst->SetYear(ptr_src->GetYear()))
        isSuccess = false;
    // fromID gives this date
    if (not ptr_dst->SetTRANSCODE(Transfer_IN))
        isSuccess = false;
    if (not ptr_dst->SetAmount(amount))
        isSuccess = false;
    if (not ptr_dst->SetFromID(fromID))
        isSuccess = false;
    if (not ptr_dst->SetToID(toID))
        isSuccess = false;

    if (not isSuccess) {
        delete ptr_src;
        delete ptr_dst;
        return false;
    }

    // Write transactions to src and dst files
    std::string srcFileName;
    std::string dstFileName;
    GetFileName(src, srcFileName);
    GetFileName(dst, dstFileName);

    if (WriteTransactionToFile(srcFileName, ptr_src))
        if (not WriteTransactionToFile(dstFileName, ptr_dst))
            isSuccess = false;

    if (not isSuccess) {
        delete ptr_src;
        delete ptr_dst;
        return false;
    }

    auto src_tlist = src->GetTransactions();
    src_tlist->push_back(ptr_src);
    src->UpdateAmount(-amount);

    auto dst_tlist = dst->GetTransactions();
    dst_tlist->push_back(ptr_dst);
    dst->UpdateAmount(amount);

    return true;
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Deposit(int ID, double amount) {

    if (amount <= 0)
        return false;

    auto account = GetAccount_FromID(ID);
    if (account == nullptr)
        return false;

    return Deposit(account, amount);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Deposit(Account *account, double amount) {

    if (amount <= 0)
        return false;

    if (account == nullptr)
        return false;

    bool isSuccess = true;
    std::string fileName;
    auto tlist = account->GetTransactions();
    auto *ptr = new Transaction;
    if (not ptr->IsValidDate())
        isSuccess = false;
    if (not ptr->SetTRANSCODE(Deposit_code))
        isSuccess = false;
    if (not ptr->SetAmount(amount))
        isSuccess = false;
    if (not ptr->SetFromID(0))
        isSuccess = false;
    if (not ptr->SetToID(account->GetID()))
        isSuccess = false;

    if (isSuccess) {
        GetFileName(account, fileName);
        if (not WriteTransactionToFile(fileName, ptr))
            isSuccess = false;
        else {
            std::cout << amount << " deposited in your account" << std::endl;
            tlist->push_back(ptr);
            account->UpdateAmount(amount);
            isSuccess = true;
        }
    }
    if (not isSuccess) {
        delete ptr;
        return false;
    }
    return true;

}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Withdrawal(int ID, double amount) {
    if (amount <= 0)
        return false;

    auto account = GetAccount_FromID(ID);
    if (account == nullptr)
        return false;

    return Withdrawal(account, amount);
}
//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::Withdrawal(Account *account, double amount) {

    if (account == nullptr)
        return false;
    if (amount <= 0)
        return false;

    if (account->GetAmount() >= amount) {
        bool isSuccess = true;
        std::string fileName;
        auto tlist = account->GetTransactions();
        auto *ptr = new Transaction;
        if (not ptr->IsValidDate())
            isSuccess = false;
        if (not ptr->SetTRANSCODE(Withdrawal_Code))
            isSuccess = false;
        if (not ptr->SetAmount(-amount))
            isSuccess = false;
        if (not ptr->SetFromID(account->GetID()))
            isSuccess = false;
        if (not ptr->SetToID(0))
            isSuccess = false;

        if (isSuccess) {
            GetFileName(account, fileName);
            if (not WriteTransactionToFile(fileName, ptr))
                isSuccess = false;
            else {
                std::cout << amount << " withdrawn from your account." << std::endl;
                tlist->push_back(ptr);
                account->UpdateAmount(-amount);
                isSuccess = true;
            }
        }
        if (not isSuccess) {
            delete ptr;
            return false;
        }
        return true;
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
        std::cout << "ID:" << account->GetID() << " Name:" << account->GetName() << " Surname:" << account->GetSurname() << std::endl;
        if (printTrans)
            PrintTransactions(account->GetID());
    }
}
//----------------------------------------------------------------------------------------------------------------------

void AccountManager::PrintTransactions(int ID) {
    // Prints all account (retrieved from ID) transactions.
    auto acc = GetAccount_FromID(ID);
    auto trs = acc->GetTransactions();
    int count = 1;
    for (auto t : *trs) {
        std::cout << "Transaction: " << count                                                      << std::endl
                  << "Date: "        << t->GetDay() << "/" << t->GetMonth() << "/" << t->GetYear() << std::endl
                  << "Amount: "      << t->GetAmount()                                             << std::endl
                  << "Code: "        << GetTransactionName(t->GetTRANSCODE())                      << std::endl
                  << "From: "        << t->GetFromID()                                             << std::endl
                  << "To: "          << t->GetToID()                                               << std::endl << std::endl;
        count++;
    }
    count = 0;
}
//----------------------------------------------------------------------------------------------------------------------
