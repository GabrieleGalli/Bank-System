# Bank-System
The application is designed to store accounts and various transactions on binary files.
At startup the application loads the files and updates the lists of accounts and transactions so that you can do operations on them.

Accounts can be created and transactions can be made within the bank (via ID): Deposit, Withdrawal, Transfer.

The Account class provides methods for setting up and reading an account's credentials and attributes, as well as maintaining a list of transactions that are stored on files.

The AccountManager class maintains a list of accounts which is loaded on startup and updated when a new account is created.
This class allows you to do various operations on the account including: transactions, checks on credentials, upload files and write on them.

FileStructure is used to define the structure of the files, both the one that contains all the accounts and those that manage the transactions for each account. Structures are used to define the structure of the binary files, in order to facilitate their reading and writing in blocks.

The Transaction class defines a generic transaction. Provides methods to manage the date, sender, recipient and transaction amount.

View is the interface the user turns to to manage his account or create a new one.

The project also contains the google test library for the main functions.

Three accounts with their credentials have been preloaded in order to test the operation. (Preloaded Accounts)

A test main is also provided.
