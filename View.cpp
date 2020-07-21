//
// Created by gabri on 12/07/20.
//

#include "View.h"
#include <iostream>

using namespace std;

bool IsUINT_Number(string strNum) {
    int iNumChars = 0;
    for (char ch : strNum) {
        if ((ch < '0') or (ch < '1'))
            return false;
        iNumChars++;
    }
    if (iNumChars == 0)
        return false;

    return not((iNumChars > 1) and (strNum[0] == '0'));
}

void View::Show(bool visible) {
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
                Account tmp;
                //Login
                string strID, pass;
                int ID;
                cout << "Login" << endl
                     << "*****" << endl << endl;
                for (;;) {
                    cout << "ID: ";
                    cin >> strID;
                    if (not IsUINT_Number(strID))
                        continue;
                    ID = (int) strtol(strID.c_str(), nullptr, 10);
                    if (ID <= 0)
                        continue;
                    break;
                }
                do {
                    cout << "Password: ";
                    cin >> pass;
                }
                while (not tmp.SetPassword(pass));

                if (_accountManager->CheckValidID(ID) and _accountManager->CheckValidPassword(ID, pass)) {
                    auto account = _accountManager->GetAccount_FromID(ID);
                    AccountManager::LoadTransactionsFromFile(account);
                    int operationChoice = 0;
                    double balance = account->GetAmount();
                    cout << endl << endl << endl
                         << "Welcome " << account->GetName() << "."  << endl << endl
                         << "Current Balance: " << balance   << "$"  << endl
                         << "Available Operations:"          << endl
                         << "********************"           << endl << endl
                         << "1) Deposit"                     << endl
                         << "2) Withdrawal"                  << endl
                         << "3) Transfer"                    << endl
                         << "4) Transactions history"        << endl
                         << "5) Exit"                        << endl;
                    cin >> operationChoice;

                    switch (operationChoice) {
                        double amount;
                        case 1: {
                            //Deposit
                            cout << "How much to deposit?" << endl;
                            cin >> amount;
                            if (amount > 0) {
                                AccountManager::Deposit(account, amount);
                                cout << amount << "$ deposited in your account." << std::endl;
                            }
                            else
                                cout << "Impossible to deposit 0$." << endl;
                            break;
                        }
                        case 2: {
                            //Withdrawal
                            cout << "How much money to withdraw?" << endl;
                            cin >> amount;
                            if (amount > 0)
                                if (AccountManager::Withdrawal(account, amount)) {
                                    balance -= amount;
                                    cout << amount << "$ withdrawn from your account." << std::endl;
                                }
                                else
                                    cerr << "You have not enough money." << endl;
                            else
                                cerr << "Impossible to withdrawal 0$." << endl;
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
                                    bool transSuccess = false;
                                    try {
                                        transSuccess = _accountManager->MakeInternalTransaction(account->GetID(), toID, amount);
                                    } catch (std::invalid_argument& e) {
                                        cerr << e.what();
                                        break;
                                    }
                                    if (transSuccess) {
                                        balance -= amount;
                                        cout << "Done! " << amount << "$ transferred to " << toID << ". " << endl;
                                    } else
                                        cerr << "Transaction Error." << endl;
                                } else
                                    cerr << "Invalid amount value." << endl;
                            } else
                                cerr << "This is not a valid ID." << endl;
                            break;
                        }
                        case 4:
                            //Print all Transactions
                            _accountManager->PrintTransactions(account->GetID());
                        case 5:
                            break;
                    }
                } else {
                    cerr << "Incorrect ID or Password." << std::endl;
                    break;
                }
                break;
            }


            case 2: {
                //Register
                string name, surname, fiscalCode, city, citizen, pass;
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

