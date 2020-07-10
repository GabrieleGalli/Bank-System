//
// Created by gabri on 09/07/20.
//

#include "gtest/gtest.h"
#include "../AccountManager.h"

AccountManager am;
int createdAccounts = 0;

bool AccountManager::CheckValidID_Test(const int &ID) {
    // Returns true if given ID already exists.
    bool isSuccess = false;

    for (auto account : _accounts) {
        auto &ai = account->getAccountInfo();
        if (ai.ID == ID) {
            std::cout << "CheckValidID::Existing ID" << std::endl;
            isSuccess = true;
            break;
        }
    }
    return isSuccess;
}


TEST(AccountManager, Test_AccountCreation) {
    // Test if a new account has been added
    auto list = am.GetAccounts();
    int size = list.size();
    am.CreateNewAccount("n1", "s1", "f1", "c1", "ct1", "p1");
    createdAccounts++;
    auto newList = am.GetAccounts();
    int  newSize = newList.size();
    ASSERT_EQ(newSize, size + 1);
}

TEST(AccountManager, Test_ClearAccounts) {
    // Test if ClearAccounts actually deletes the list of accounts
    am.CreateNewAccount("n2", "s2", "f2", "c2", "ct2", "p2");
    createdAccounts++;
    auto list = am.GetAccounts();
    int  size = list.size();
    AccountManager::ClearAccounts(list);
    int newSize = list.size();
    ASSERT_EQ(0, newSize);
}

TEST(AccountManager, Test_CheckValidID) {
    // Test if find the right id for all existing accounts
    am.CreateNewAccount("n3", "s3", "f3", "c3", "ct3", "p3");
    createdAccounts++;
    am.CreateNewAccount("n4", "s4", "f4", "c4", "ct4", "p4");
    createdAccounts++;
    auto list = am.GetAccounts();
    int size = list.size();
    for (int ii = 0; ii <= createdAccounts - 2; ++ii)
        ASSERT_FALSE(am.CheckValidID_Test(ii + 1));
    for (int ii = createdAccounts - 2; ii <= createdAccounts; ++ii)
        ASSERT_TRUE(am.CheckValidID_Test(ii));

}

TEST(AccountManager, Test_GetFileName_FromID) {
    // ID must be 5
    am.CreateNewAccount("n5", "s5", "f5", "c5", "ct5", "p5");
    char fileName[150] = "";
    auto account = am.GetAccount_FromID(4);
    AccountManager::GetFileName(reinterpret_cast<ACCOUNT_INFO &>(account), fileName);
    ASSERT_EQ("n5s5f5", fileName);
}