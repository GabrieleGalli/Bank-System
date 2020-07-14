//
// Created by gabri on 08/07/20.
//

#include "gtest/gtest.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // XXX Running all tests, only Test_CreateNewAccount, Test_ClearAccounts, Test_GetNewID will be passed.
    //     Other tests require to delete Accounts.dat and accounts (.bin) from ../cmake-build-debug/Google_tests before run.
    return RUN_ALL_TESTS();
}