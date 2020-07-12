//
// Created by gabri on 12/07/20.
//

#include "View.h"
#include "TransactionDate.h"
#include <iostream>

using namespace std;

bool View::Show(bool visible) {
    _accountManager->LoadAccountsFromFile();
    while (visible) {
        int homeChoice;
        cout << endl << endl
             << "Bank-System by Galli Gabriele" << endl
             << "*****************************" << endl << endl
             << "1) Login"    << endl
             << "2) Register" << endl
             << "3) Exit"     << endl;
        cin >> homeChoice;

        switch (homeChoice) {
            case 1: {
                //Login
                int ID;
                char pass[50];
                cout << "Login" << endl
                     << "*****" << endl << endl
                     << "ID: ";
                cin >> ID;
                cout << "Password: ";
                cin >> pass;
                if (_accountManager->CheckValidID(ID) and _accountManager->CheckValidPassword(ID, pass)) {
                    auto account = _accountManager->GetAccount_FromID(ID);
                    auto accountInfo = account->getAccountInfo();
                    AccountManager::LoadTransactionsFromFile(account);
                    int operationChoice = 0;
                    double balance = accountInfo.Amount;
                    cout << endl << endl << endl
                         << "Welcome " << accountInfo.Name << "."  << endl   << endl
                         << "Current Balance: " << balance << "$" << endl
                         << "Available Operations:"   << endl
                         << "********************"    << endl << endl
                         << "1) Deposit"              << endl
                         << "2) Withdrawal"           << endl
                         << "3) Transfer"             << endl
                         << "4) Transactions history" << endl
                         << "5) Exit"                 << endl;
                    cin >> operationChoice;

                    switch (operationChoice) {
                        int day, month, year;
                        double amount;
                        case 1: {
                            //Deposit
                            cout << "How much to deposit?" << endl;
                            cin >> amount;
                            if (amount > 0) {
                                TransactionDate trDateDep;
                                day = trDateDep.getDay();
                                month = trDateDep.getMonth();
                                year = trDateDep.getYear();
                                AccountManager::Deposit(account, amount, day, month, year);
                            } else
                                cout << "Impossible to deposit 0$." << endl;
                            break;
                        }
                        case 2: {
                            //Withdrawal
                            cout << "How much money to withdraw?" << endl;
                            cin >> amount;
                            if (amount > 0 and accountInfo.Amount >= amount) {
                                TransactionDate trDateWith;
                                day = trDateWith.getDay();
                                month = trDateWith.getMonth();
                                year = trDateWith.getYear();
                                AccountManager::Withdrawal(account, amount, day, month, year);
                                balance -= amount;
                            }
                            else if (accountInfo.Amount < amount)
                                cout << "You have not enough money." << endl;
                            else if (amount < 0)
                                cout << "Impossible to withdrawal 0$." << endl;
                            break;
                        }
                        case 3: {
                            //Transfer
                            int toID = 0;
                            cout << "To which ID to make the transfer?" << endl;
                            cin >> toID;
                            if (_accountManager->CheckValidID(toID)) {
                                cout << "How much Transfer to " << toID << "?" << endl;
                                cin >> amount;
                                if (amount > 0) {
                                    TransactionDate trDateTransf;
                                    day = trDateTransf.getDay();
                                    month = trDateTransf.getMonth();
                                    year = trDateTransf.getYear();
                                    _accountManager->MakeInternalTransaction(accountInfo.ID, toID, day, month, year,amount);
                                    balance -= amount;
                                    cout << "Done! " << amount << "$ transferred to " << toID << ". " << endl;
                                }
                            } else
                                cout << "This is not a valid ID." << endl;
                            break;
                        }
                        case 4:
                            //Print all Transactions
                            _accountManager->PrintTransactions(accountInfo.ID);

                        case 5:
                            break;
                    }
                } else {
                    cout << "Incorrect ID or Password." << std::endl;
                    break;
                }
                break;
            }


            case 2: {
                //Register
                char name[50];
                char surname[50];
                char fiscalCode[18];
                char city[50];
                char citizen[20];
                char pass[50];
                cout << "Register" << endl
                     << "********" << endl << endl,
                        cout << "Name: ";
                cin >> name;
                cout << "Surname: ";
                cin >> surname;
                cout << "Fiscal Code: ";
                cin >> fiscalCode;
                cout << "City: ";
                cin >> city;
                cout << "Citizen: ";
                cin >> citizen;
                cout << "New Password: ";
                cin >> pass;
                _accountManager->CreateNewAccount(name, surname, fiscalCode, city, citizen, pass);
                break;
            }
            case 3: {
                cout << "Closing Bank-System..." << endl;
                visible = false;
            }
        }
    }
}

