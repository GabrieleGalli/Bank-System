//
// Created by gabri on 09/07/20.
//

#include "gtest/gtest.h"
#include "../AccountManager.h"

AccountManager am;
int createdAccounts = 0;


TEST(AccountManager, Test_CreateNewAccount) {
    // Test if a new account has been added
    // This test also includes the following functions of the Account class:
    //      SetName, SetSurname, SetFiscalCode, SetCity, SetCitizen, SetPassword, SetID,
    //      GetName, GetSurname, GetFiscalCode, GetCity, GetCitizen, GetPassword, GetID.

    auto list = am.GetAccounts();
    int  size = list.size();
    am.CreateNewAccount("n1", "s1", "f1", "c1", "ct1", "p1");
    createdAccounts++;
    auto newList = am.GetAccounts();
    int  newSize = newList.size();
    ASSERT_EQ(newSize, size + 1);
    auto account = am.GetAccount_FromID(1);
    ASSERT_EQ("n1", account->GetName());
    ASSERT_EQ("s1", account->GetSurname());
    ASSERT_EQ("f1", account->GetFiscalCode());
    ASSERT_EQ("c1", account->GetCity());
    ASSERT_EQ("ct1",account->GetCitizen());
    ASSERT_EQ("p1", account->GetPassword());
}

TEST(AccountManager, Test_ClearAccounts) {
    // Test if ClearAccounts actually deletes the list of accounts
    am.CreateNewAccount("n2", "s2", "f2", "c2", "ct2", "p2");
    createdAccounts++;
    auto list = am.GetAccounts();
    int  size = list.size();
    AccountManager::ClearAccounts(&list);
    int newSize = list.size();
    ASSERT_EQ(0, newSize);
}

TEST(AccountManager, Test_CheckValidID) {
    // Test if find the right id for all existing accounts
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n3", "s3", "f3", "c3", "ct3", "p3");
    createdAccounts++;
    am.CreateNewAccount("n4", "s4", "f4", "c4", "ct4", "p4");
    createdAccounts++;
    auto list = am.GetAccounts();
    int size = list.size();
    for (int ii = 1; ii <= createdAccounts; ++ii)
        ASSERT_TRUE(am.CheckValidID(ii));
}

TEST(AccountManager, Test_GetNewID) {
    int  newID = am.GetNewID();
    auto list = am.GetAccounts();
    for (auto a : list) {
        bool isEqual = false;
        if (a->GetID() == newID)
            isEqual = true;
        ASSERT_FALSE(isEqual);
    }
}

TEST(AccountManager, Test_GetFileName) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n5", "s5", "f5", "c5", "ct5", "p5");
    std::string fileName;
    std::string equals = "n5s5f5.bin";
    auto account = am.GetAccount_FromID(1);
    AccountManager::GetFileName(account, fileName);
    ASSERT_EQ(equals, fileName);
}

TEST(AccountManager, Test_GetAccounts) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n11", "s11", "f11", "c11", "ct11", "p11");  // ID : 1
    am.CreateNewAccount("n12", "s12", "f12", "c12", "ct12", "p12");  // ID : 2
    int jj = 1;
    for (auto a : am.GetAccounts()) {
        ASSERT_EQ(a, am.GetAccount_FromID(jj));
        jj++;
    }
}

TEST(AccountManager, Test_GetAccount_FromID) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n10", "s10", "f10", "c10", "ct10", "p10");  // ID : 1
    for (auto a : am.GetAccounts()) {
        // There's only one account in list and it must be it
        ASSERT_EQ(a, am.GetAccount_FromID(1));
    }
}

TEST(AccountManager, Test_Deposit) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    // This test also includes the following functions of the Account class: SetAmount, GetAmount.
    // This test also includes the following functions of the Transaction class: SetAmount, SetFromID, SetToID
    am.CreateNewAccount("n6", "s6", "f6", "c6", "ct6", "p6");  // ID : 1
    auto a1 = am.GetAccount_FromID(1);
    double originalAmount = a1->GetAmount();
    am.Deposit(1, 100);
    double newAmount1 = a1->GetAmount();
    ASSERT_EQ(originalAmount + 100, newAmount1);
    AccountManager::Deposit(a1, 200);
    double newAmount2 = a1->GetAmount();
    ASSERT_EQ(newAmount1 + 200, newAmount2);
}

TEST(AccountManager, Test_Withdrawal) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    // This test also includes the following functions of the Account class: SetAmount, GetAmount.
    // This test also includes the following functions of the Transaction class: SetAmount, SetFromID, SetToID
    am.CreateNewAccount("n7", "s7", "f7", "c7", "ct7", "p7");  // ID : 1
    auto a1 = am.GetAccount_FromID(1);
    double originalAmount = a1->GetAmount();
    am.Deposit(1, 100);
    am.Withdrawal(1, 50);
    double newAmount1 = a1->GetAmount();
    ASSERT_EQ(originalAmount + 50, newAmount1);
    AccountManager::Deposit(a1, 200);
    AccountManager::Withdrawal(a1, 50);
    double newAmount2 = a1->GetAmount();
    ASSERT_EQ(newAmount1 + 150, newAmount2);
}

TEST(AccountManager, Test_MakeInternalTransaction) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    // This test also includes the following functions of the Account class: SetAmount, GetAmount.
    // This test also includes the following functions of the Transaction class:
    //      GetAmount, GetFromID, GetToID, SetAmount, SetFromID, SetToID
    am.CreateNewAccount("n8", "s8", "f8", "c8", "ct8", "p8");  // ID : 1
    am.CreateNewAccount("n9", "s9", "f9", "c9", "ct9", "p9");  // ID : 2
    auto a1 = am.GetAccount_FromID(1);
    auto a2 = am.GetAccount_FromID(2);
    AccountManager::Deposit(a1, 100);
    double originalAmount_a1 = a1->GetAmount();
    double originalAmount_a2 = a2->GetAmount();
    am.MakeInternalTransaction(1, 2, 50);
    double newAmount_a1 = a1->GetAmount();
    double newAmount_a2 = a2->GetAmount();
    ASSERT_EQ(originalAmount_a1 - 50, newAmount_a1);
    ASSERT_EQ(originalAmount_a2 + 50, newAmount_a2);
}

TEST(Transaction, Test_TransactionDate) {
    Transaction tr;
    // Test's Date
    ASSERT_EQ(18,   tr.GetDay());
    ASSERT_EQ(7,    tr.GetMonth());
    ASSERT_EQ(2020, tr.GetYear());
}