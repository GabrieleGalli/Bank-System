//
// Created by gabri on 09/07/20.
//

#include "gtest/gtest.h"
#include "../AccountManager.h"

AccountManager am;
int createdAccounts = 0;


TEST(AccountManager, Test_CreateNewAccount) {
    // Test if a new account has been added
    auto list = am.GetAccounts();
    int size = list.size();
    am.CreateNewAccount("n1", "s1", "f1", "c1", "ct1", "p1");
    createdAccounts++;
    auto newList = am.GetAccounts();
    int newSize = newList.size();
    ASSERT_EQ(newSize, size + 1);
}

TEST(AccountManager, Test_ClearAccounts) {
    // Test if ClearAccounts actually deletes the list of accounts
    am.CreateNewAccount("n2", "s2", "f2", "c2", "ct2", "p2");
    createdAccounts++;
    auto list = am.GetAccounts();
    int size = list.size();
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
    int newID = am.GetNewID();
    auto list = am.GetAccounts();
    for (auto a : list) {
        auto aInfo = a->GetAccountInfo();
        bool isEqual = false;
        if (aInfo.ID == newID)
            isEqual = true;
        ASSERT_FALSE(isEqual);
    }
}

TEST(AccountManager, Test_GetFileName) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n5", "s5", "f5", "c5", "ct5", "p5");
    char fileName[150];
    char equals[150] = "n5s5f5.bin";
    auto account = am.GetAccount_FromID(1);
    AccountManager::GetFileName(account->GetAccountInfo(), fileName);
    ASSERT_EQ(*equals, *fileName);
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
    am.CreateNewAccount("n6", "s6", "f6", "c6", "ct6", "p6");  // ID : 1
    auto a1 = am.GetAccount_FromID(1);
    auto aInfo1 = a1->GetAccountInfo();
    double originalAmount = aInfo1.Amount;
    am.Deposit(1, 100, 13, 7, 2020);
    aInfo1 = a1->GetAccountInfo();
    double newAmount1 = aInfo1.Amount;
    ASSERT_EQ(originalAmount + 100, newAmount1);
    AccountManager::Deposit(a1, 200, 13, 7, 2020);
    aInfo1 = a1->GetAccountInfo();
    double newAmount2 = aInfo1.Amount;
    ASSERT_EQ(newAmount1 + 200, newAmount2);
}

TEST(AccountManager, Test_Withdrawal) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n7", "s7", "f7", "c7", "ct7", "p7");  // ID : 1
    auto a1 = am.GetAccount_FromID(1);
    auto aInfo1 = a1->GetAccountInfo();
    double originalAmount = aInfo1.Amount;
    am.Deposit(1, 100, 13, 7, 2020);
    am.Withdrawal(1, 50, 13, 7, 2020);
    aInfo1 = a1->GetAccountInfo();
    double newAmount1 = aInfo1.Amount;
    ASSERT_EQ(originalAmount + 50, newAmount1);
    AccountManager::Deposit(a1, 200, 13, 7, 2020);
    AccountManager::Withdrawal(a1, 50, 13, 7, 2020);
    aInfo1 = a1->GetAccountInfo();
    double newAmount2 = aInfo1.Amount;
    ASSERT_EQ(newAmount1 + 150, newAmount2);
}

TEST(AccountManager, Test_MakeInternalTransaction) {
    // TODO delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run
    am.CreateNewAccount("n8", "s8", "f8", "c8", "ct8", "p8");  // ID : 1
    am.CreateNewAccount("n9", "s9", "f9", "c9", "ct9", "p9");  // ID : 2
    auto a1 = am.GetAccount_FromID(1);
    auto a2 = am.GetAccount_FromID(2);
    AccountManager::Deposit(a1, 100, 13, 7, 2020);
    auto aInfo1 = a1->GetAccountInfo();
    auto aInfo2 = a2->GetAccountInfo();
    double originalAmount_a1 = aInfo1.Amount;
    double originalAmount_a2 = aInfo2.Amount;
    am.MakeInternalTransaction(1, 2, 13, 7, 2020, 50);
    aInfo1 = a1->GetAccountInfo();
    aInfo2 = a2->GetAccountInfo();
    double newAmount_a1 = aInfo1.Amount;
    double newAmount_a2 = aInfo2.Amount;
    ASSERT_EQ(originalAmount_a1 - 50, newAmount_a1);
    ASSERT_EQ(originalAmount_a2 + 50, newAmount_a2);
}