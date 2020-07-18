//
// Created by gabri on 08/07/20.
//

#include <iostream>
#include "Account.h"


//----------------------------------------------------------------------------------------------------------------------

void Account::ClearTransactionsList(std::list<Transaction *> *tlist) {
    // Takes a list of transaction info and clear it
    if (not tlist->empty()) {
        for (;;) {
            auto trans = tlist->back();
            if (trans == nullptr)
                break;
            tlist->remove(trans);
            delete trans;
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------
bool Account::SetID(int ID) {
    _accountInfo.ID = ID;
    return true;
}
bool Account::SetName(const std::string& name) {
    size_t len = name.length();
    if((len == 0) || (len >= sizeof(_accountInfo.Name)))
        return false;
    strcpy(_accountInfo.Name, name.c_str());
    return true;
}
bool Account::SetSurname (const std::string& surname) {
    size_t len = surname.length();
    if((len == 0) || (len >= sizeof(_accountInfo.Surname)))
        return false;
    strcpy(_accountInfo.Surname, surname.c_str());
    return true;
}
bool Account::SetFiscalCode(const std::string& fiscalCode) {
    size_t len = fiscalCode.length();
    if((len == 0) || (len >= sizeof(_accountInfo.FiscalCode)))
        return false;
    strcpy(_accountInfo.FiscalCode, fiscalCode.c_str());
    return true;
}
bool Account::SetCity(const std::string& city) {
    size_t len = city.length();
    if((len == 0) || (len >= sizeof(_accountInfo.City)))
        return false;
    strcpy(_accountInfo.City, city.c_str());
    return true;
}
bool Account::SetCitizen(const std::string& citizen) {
    size_t len = citizen.length();
    if((len == 0) || (len >= sizeof(_accountInfo.Citizen)))
        return false;
    strcpy(_accountInfo.Citizen, citizen.c_str());
    return true;
}
bool Account::SetPassword(const std::string& pass) {
    size_t len = pass.length();
    if((len == 0) || (len >= sizeof(_accountInfo.Password)))
        return false;
    strcpy(_accountInfo.Password, pass.c_str());
    return true;
}
bool Account::SetAmount(double amount) {
    _accountInfo.Amount = amount;
    return true;
}
bool Account::UpdateAmount(double amount){
    _accountInfo.Amount += amount;
    return true;
}

std::string Account::GetName() const {
    return std::string(_accountInfo.Name);
}
std::string Account::GetSurname () const {
    return std::string(_accountInfo.Surname);
}
std::string Account::GetFiscalCode() const {
    return std::string(_accountInfo.FiscalCode);
}
std::string Account::GetCity() const {
    return std::string(_accountInfo.City);
}
std::string Account::GetCitizen() const {
    return std::string(_accountInfo.Citizen);
}
std::string Account::GetPassword() const {
    return std::string(_accountInfo.Password);
}
double Account::GetAmount() const {
    return _accountInfo.Amount;
}
double Account::CalculateAmount() const {
    // Calculate the total amount of an account adding every transaction's amount
    double amount = 0;
    for (auto t : _transactions)
        amount += t->GetAmount();

    return amount;
}
