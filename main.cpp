#include <iostream>
#include "AccountManager.h"
#include "View.h"

int main() {
    AccountManager am;
    View view(&am);
    view.Show(true);

    return 0;
}
