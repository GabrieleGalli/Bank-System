//
// Created by gabri on 12/07/20.
//

#ifndef BANK_SYSTEM_VIEW_H
#define BANK_SYSTEM_VIEW_H

#include "AccountManager.h"

class View {
private:
    AccountManager *_accountManager;

public:
    explicit View(AccountManager *accountManager) :  _accountManager(accountManager) {}

    ~View() = default;

    void Show(bool visible);
};

#endif //BANK_SYSTEM_VIEW_H
