#include <iostream>
#include "AccountManager.h"
#include "View.h"

int main() {
    auto am = new(AccountManager);
    View view(am);
    view.Show(true);

    return 0;
}
