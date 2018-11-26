/*
 *  Title: project2.cpp
 *
 *  Abstract: 
 *  - This program simulates an imaginary banking system.
      The bank can store up to a maximum of 20 customers
      And each customer can have up to 2 unique accounts
      (Checking / Savings). Customers can transfer money,
      Delete and display theyr account data. The bank
      can display total data like total money and customers.

 *   
 *  Author: Sander Hellesoe
 *  ID: 7337
 *  Date: 11/24/2018
 */

#include "Customer.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// HEADS
string toLowerCase(string str);
void displayMenu(Customer * customers[]);
void promptUserForOption(Customer * customers[]);
void readCustomerData(Customer * customers[]);
bool closeAccount(Customer * customers[]);
void specificCustomerInfo(Customer * customers[]);
void customerInfo(Customer * customers[]);
void bankInfo(Customer * customers[]);
void transferMoney(Customer * customers[]);
void customerList(Customer * customers[]);
bool accountExists(Customer * customers[], int accountNr);
bool inSystem(Customer * customers[], int SSN, int number, string customerName, int accountType, double balance);
int accountSpot(Customer * customers[]);
void updateAccount(Customer * customers[], int SSN, account cAccount);
void sortAndDisplay(Customer * customers[]);

// display menu
void displayMenu(Customer * customers[]) 
{
    
    cout << "\nSelect your choice:" << endl;
    
    cout << "   1. Read Customer data file\n";
    cout << "   2. Close an account\n";
    cout << "   3. Customer Info\n";
    cout << "   4. Bank Info\n";
    cout << "   5. Transfer Money\n";
    cout << "   6. Customer List\n";
    cout << "   7. Exit" << endl;
    
    // prompt user for option
    promptUserForOption(customers);
}

// convert a given string to lowercase / used for comparison
string toLowerCase(string str)
{
    
    string lcString = "";
    for (int i = 0; i < str.length(); i++)
    {
        lcString += tolower(str[i]);
    }
    
    return lcString;
}

// prompt user to select an option
void promptUserForOption(Customer * customers[])
{
    
    // get option from user
    string option;
    cin >> option;
    
    // read customer data from file
    if (option == "1")
    {
        readCustomerData(customers);
    }
    
    // close users account
    else if (option == "2")
    {
        closeAccount(customers);
    }
    
    // display customer info
    else if (option == "3")
    {
        specificCustomerInfo(customers);
        
    }
    
    // display bank info
    else if (option == "4")
    {
        bankInfo(customers);
        customerInfo(customers);
    }
    
    // transfer money
    else if (option == "5")
    {
        transferMoney(customers);
    }
    
    // display customer list
    else if (option == "6")
    {
        customerList(customers);
    }
    
    // exit program
    else if (option == "7")
    {
        cout << "Bye" << endl;
        exit(0);
    }
    
    displayMenu(customers);
    
}

void readCustomerData(Customer * customers[]) 
{
    // file stream object
    ifstream inFile;
    
    // ask user for file to open
    cout << "Enter file name: ";
    string fileName;
    cin >> fileName;
   
    // open given file
    inFile.open(fileName);

    // test for errors.
    if (!inFile)
    {
        cout << "Error opening the file.\n";
        return;
    }
    
    // read given file
    cout << "Read data..." << endl;
    
    int size;
    inFile >> size;
    
    // customer and account fileds
    int SSN;
    string firstName;
    string lastName;
    int number;
    int type;
    double balance;
    
    
    for (int i = 0; i < size; i++)
    {
        
        // assign data to fields
        inFile >> SSN;
        inFile >> firstName;
        inFile >> lastName;
        inFile >> number;
        inFile >> type;
        inFile >> balance;
        
        // check if account nr is allready in bank system
        if (!accountExists(customers, number))
        {
            // if SSN is not present create customer and attempt to set account
            if (!inSystem(customers, SSN, number, (firstName + " " + lastName), type, balance))
            {
                // find free spot to place customer
                int index = accountSpot(customers);
                
                // validate index
                if (index != -1)
                {
                    // create customer and set account
                    customers[index] = new Customer(SSN, firstName, lastName);
                    customers[index]->setAccount(number, type, balance);
                }
            }
        }
        
        else {
            cout << "Account Creation Failed - Account number " << number << " allready exists" << endl;
        }
    }
    
    cout << "Done." << endl;
}

// find index to place account
int accountSpot(Customer * customers[])
{
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        // find free spot to place customer and validate account type
        if (!customers[i])
        {   
            return i;      
        }
    }
    
    // no more spots, array is full
    cout << "Unable to add any more accounts. Bank capacity reached" << endl;
    return -1;
}

bool inSystem(Customer * customers[], int SSN, int number, string customerName, int accountType, double balance)
{
    
    // check if SSN is allready present 
    for (int i= 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {   

            // SSN exists to different user
            if (customers[i]->getSSN() == SSN && customers[i]->getFullName() != customerName)
            {
                cout << "Account Creation Failed - A customer with SSN " << to_string(SSN) << " allready exists." << endl;
                return true;
            }
            
            // SSN exists to same user
            else if (customers[i]->getSSN() == SSN && customers[i]->getFullName() == customerName)
            {   
                // customer allreade have account
                if (customers[i]->validateAccount(accountType))
                {
                    customers[i]->setAccount(number, accountType, balance);
                    return true;
                }
                
                // set account to customer
                else {
                   cout << "Account Creation Failed - Account number " << to_string(number) << " allready exists." << endl;
                   return true;
                }
            }
        }
    }
    
    return false;
}

bool accountExists(Customer * customers[], int accountNr)
{
    for (int i= 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {   
            for (int j = 0; j < 2; j++)
            {
                if (customers[i]->getAccounts()[j].number == accountNr)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool closeAccount(Customer * customers[])
{
    account foundAccount = {0, 0, 0, "UNKNOWN"};
    int foundIndex;
    int accountNr;
    int ownerSSN;
    
    // get account number to close
    cout << "Enter Account Number: ";
    cin >> accountNr;
    
    // find account numbers owner
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {   
        if (customers[i]) {
            
            // if account was found, owners SSN is returned for further validation
            foundAccount = customers[i]->findAccount(accountNr);
            if (foundAccount.typeName != "UNKNOWN")
            {
                foundIndex = i;
                ownerSSN = customers[i]->getSSN();
                break;
            }
        }
    }
    
    // if foundAccount is unknown, no account with nr was found
    if (foundAccount.typeName == "UNKNOWN") {
        
        // invalid delete
        cout << "Incorrect account number." << endl;
        return false;
    
    }
    
    // prompt user for SSN to confirm deletion of account
    cout << "Enter Customer SSN: ";
    int confirmOwnerSSN;
    cin >> confirmOwnerSSN;
    
    // validate codes
    if (ownerSSN == confirmOwnerSSN)
    {
        // close account and notify user
        if (customers[foundIndex]->closeAccount(accountNr))
        {
            customers[foundIndex] = nullptr;
            delete customers[foundIndex];
            
        }
        return true;
    }
    
    // invalid delete
    cout << "Incorrect SSN." << endl;
    return false;
    
}

// display info for a specific customer
void specificCustomerInfo(Customer * customers[])
{
    // prompt user for option
    cout << "SSN(1) / Last Name(2) / Account Number(3): ";
    string optionName;
    string option;
    cin >> option;
    
    if (option == "1" || option == "2" || option == "3")
    {
        
        // get name
        if (option == "1")
        {
            optionName = "SSN";
        }
        
        else if (option == "2")
        {
            optionName = "last name";
        }
        
        else {
            optionName = "account number";
        }
        
        // prompt user for action
        string find;
        cout << "Enter an " << optionName << ": ";
        cin >> find;
        
        
        for (int i = 0; i < CUSTOMER_CAPACITY; i++)
        {   
            if (customers[i]) {
                
                if (option == "1")
                {
                    if (to_string(customers[i]->getSSN()) == find)
                    {
                        customers[i]->printCustomerInfo();
                        return;
                    }
                }
                
                else if (option == "2")
                {
                    if (toLowerCase(customers[i]->getLastName()) == toLowerCase(find))
                    {
                        customers[i]->printCustomerInfo();
                    }
                }
                
                else {
                    if (customers[i]->findAccount(stoi(find)).typeName != "UNKNOWN")
                    {
                        customers[i]->printCustomerInfo();
                        return;
                    }
                }
            }
        }
    }
    
    else {
        cout << "Invalid Option. Select 1 - 3." << endl;
        specificCustomerInfo(customers);
        return;
    }
    
    // if no matching customers
    cout << "No customer with " << optionName << " found." << endl;
    
}

// display info regarding all customers in bank
void customerInfo(Customer * customers[])
{
    // get total number of active customers
    int totalNumOfCustomers = 0;
    double totalBalance = 0;
    string customersInfo = "\n";
    
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {   
            // increment total number of customers
            totalNumOfCustomers++;
            
            // increment total balance
            totalBalance += customers[i]->getTotalBalance();
            
            // append customer data to customers info string
            customersInfo += customers[i]->displayCustomer() + "\n";
        }
    }
    
    stringstream stream;
    stream << fixed << setprecision(2) << totalBalance;
    cout << "\nNumber of Customers: " << totalNumOfCustomers << customersInfo << endl;
    cout << "Total Balance: $" << stream.str() << endl;
    
}

// display bank info
void bankInfo(Customer * customers[])
{
    
    // get total number of active accounts
    int totalNumOfAccounts = 0;
    string accountsInfo = "\n";
    
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {   
            // add to total number of accounts count
            totalNumOfAccounts += customers[i]->getAccountAmount();
            
            // append account data to accounts info string
            accountsInfo += customers[i]->displayAccount();
        }
    }
    
    cout << "\nNumber of Accounts: " << totalNumOfAccounts << accountsInfo << endl;
    
}

void transferMoney(Customer * customers[])
{
    // prompt user for source account
    cout << "Source Account: ";
    string sourceAccountNr;
    cin >> sourceAccountNr;

    // promt user for destination account
    cout << "Destination Account: ";
    string destinationAccountNr;
    cin >> destinationAccountNr;

    // prompt user for money amount
    cout << "Money Amount: $";
    string moneyAmount;
    cin >> moneyAmount;
    
    // create temp accounts
    account sourceAccount = {0, 0, 0, "UNKNOWN"};
    account destAccount = {0, 0, 0, "UNKNOWN"};
    
    // keep track of customers SSN
    int sourceSSN;
    int destSSN;
    
    // find accounts
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {
            // find account to transfer from
            if (sourceAccount.typeName == "UNKNOWN")
            {
                sourceAccount = customers[i]->findAccount(stoi(sourceAccountNr));
                if (sourceAccount.typeName != "UNKNOWN")
                {
                    sourceSSN = customers[i]->getSSN();
                }
            }
            
            // find account to transfer to
            if (destAccount.typeName == "UNKNOWN")
            {
                destAccount = customers[i]->findAccount(stoi(destinationAccountNr)); 
                if (destAccount.typeName != "UNKNOWN")
                {
                    destSSN = customers[i]->getSSN();
                }
            }
        }
    }
    
    // validate if accounts were found
    if (sourceAccount.typeName == "UNKNOWN" || destAccount.typeName == "UNKNOWN")
    {
        cout << "Transfer Fail – Incorrect account number(s)" << endl;
        return;
    }
    
    // validate if customer own both accounts
    int transferFee = 5;
    double moneyDeduct = sourceAccount.balance - stod(moneyAmount);
    if (sourceSSN == destSSN) {

        // check if both accounts are the same account
        if (sourceAccount.number == destAccount.number)
        {
            cout << "Transfer Fail – Cannot transfer from and to the same account." << endl;
            return;
        }
        
        // reduce fee to 0 if customer owns both accounts
        transferFee = 0;
    }
    
    // if accounts were found, validate that source account has sufficent money amount to perform transfer
    if (moneyDeduct < transferFee)
    {
        cout << "Transfer Fail – Insufficient amount." << endl;
        return;
    }
    
    // all checks passed, proceed to transfer
    sourceAccount.balance = moneyDeduct - transferFee;
    destAccount.balance = destAccount.balance + stod(moneyAmount);
    cout << "Transfer Succeed." << endl;
    cout << "New Balance" << endl;
    
    // update accounts
    updateAccount(customers, sourceSSN, sourceAccount);
    updateAccount(customers, destSSN, destAccount);
    
    // display new balances
    stringstream sourceStream;
    
    // updated source account
    sourceStream << fixed << setprecision(2) << sourceAccount.balance;
    cout << "       " << sourceAccount.number << ": $" << sourceStream.str() << endl;
    
    // updated destination account
    stringstream destStream;
    destStream << fixed << setprecision(2) << destAccount.balance;
    cout << "       " << destAccount.number << ": $" << destStream.str() << endl;
}

// update a customers giver account
void updateAccount(Customer * customers[], int SSN, account cAccount)
{
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {
            // find account owner
            if (customers[i]->getSSN() == SSN)
            {
                // update account
                customers[i]->updateAccount(cAccount);
            }
        }
    }
}

void customerList(Customer * customers[])
{
    // sort before displaying
    cout << "========== Customer List ==========\n" << endl;
    sortAndDisplay(customers);
    cout << "===================================" << endl;
}

void sortAndDisplay(Customer * customers[]) 
{
    Customer * customer = new Customer(); // temporary customer used to sort
    
    // sort
    for (int i = 0; i < CUSTOMER_CAPACITY - 1; i++)
    {
        for (int j = 0; j < CUSTOMER_CAPACITY - i - 1; j++)
        {
            if (customers[j] && customers[j + 1])
            {
                if (customers[j]->getSSN() > customers[j + 1]->getSSN())
                {
                    // swap
                    customer = customers[j];
                    customers[j] = customers[j + 1];
                    customers[j + 1] = customer;
                }
            }
        }
    }
    
    // display
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        if (customers[i])
        {
            cout << customers[i]->info() << "\n" << endl;
        }
    }
    
    // remove pointer
    customer = nullptr;
    delete customer;
}


int main() {
    
    // initialize customers array
    Customer * customers[CUSTOMER_CAPACITY];

    // initialize all values to a null pointer
    for (int i = 0; i < CUSTOMER_CAPACITY; i++)
    {
        customers[i] = nullptr;
    }
    
    cout << "Welcome to CSUMB Bank" << endl;
    
    // display menu to user
    displayMenu(customers);
    
}