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
    am.CreateNewAccount("nameTry", "surnameTry", "17894Try", "cityTry", "citizenTry", "passTry");
    createdAccounts++;
    auto newList = am.GetAccounts();
    int  newSize = newList.size();
    ASSERT_EQ(newSize, size + 1);
}

TEST(AccountManager, Test_ClearAccounts) {
    // Test if ClearAccounts actually deletes the list of accounts
    am.CreateNewAccount("nameTry1", "surnameTry1", "17894Try1", "cityTry1", "citizenTry1", "passTry1");
    createdAccounts++;
    auto list = am.GetAccounts();
    int  size = list.size();
    AccountManager::ClearAccounts(list);
    auto newList = am.GetAccounts();
    int  newSize = newList.size();
    ASSERT_EQ(0, newSize);

}

TEST(AccountManager, Test_CheckValidID) {
    // Test if find the right id for all existing accounts
    am.CreateNewAccount("nameTry", "surnameTry", "17894Try", "cityTry", "citizenTry", "passTry");
    createdAccounts++;
    am.CreateNewAccount("nameTry1", "surnameTry1", "17894Try1", "cityTry1", "citizenTry1", "passTry1");
    createdAccounts++;
    auto list = am.GetAccounts();
    int size = list.size();
    for (int ii = 0; ii <= createdAccounts - 2; ++ii)
        ASSERT_FALSE(am.CheckValidID_Test(ii + 1));
    for (int ii = createdAccounts - 2; ii <= createdAccounts; ++ii)
        ASSERT_TRUE(am.CheckValidID_Test(ii));

}