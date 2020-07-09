#include <iostream>
#include "AccountManager.h"

int main() {
    AccountManager am;

    if (not am.LoadAccountsFromFile()) {
        std::cout << "Creating new accounts..." << std::endl;
        am.CreateNewAccount("babbo", "bello",     "1234", "prato", "pratese", "abcd");
        am.CreateNewAccount("gabri", "piu bello", "555",  "prato", "pratese", "abcd");
        am.CreateNewAccount("mamma", "brutta",    "4567", "prato", "pratese", "abcd");
    }
    else std::cout << "Loaded Accounts ::" << am.GetNumAccounts() << std::endl;

    am.PrintAccounts(true);

    am.WriteAccountsToFile();

    //return 1;

    am.PrintTransactions(2);

    // It mustn't possible to create two accounts with the same fiscal code
    am.CreateNewAccount("pietro", "nonno", "1234", "prato", "pratese", "abcd");
}
