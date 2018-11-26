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
#include <iomanip>
#include <sstream>


// print balance to 2 decimals with dollar sign
string printBalance(double value) 
{
    stringstream stream;
    stream << fixed << setprecision(2) << value;
    return "$" + stream.str();
}

Customer::Customer() 
{
    prepeareAccounts();
}

// prepeare customer accounts
void Customer::prepeareAccounts()
{
    // set all accounts to empty accounts
    for (int i = 0; i < 2; i++) {
        
        // create empty account
        account newAccount = {0, 0, 0, "UNKNOWN"};
        accounts[i] = newAccount;
    }
}

Customer::Customer(int cSSN, string cFirstName, string cLastName)
: SSN(cSSN), firstName(cFirstName), lastName(cLastName)
{
    prepeareAccounts();
}

bool Customer::validateAccount(int accountType)
{
    string errorMsg = "Account Creation Failed - ";
    
    // if accounts are full, return immediatly
    if (activeAccounts == 2) {
        cout << errorMsg << "No room for new account" << endl;
        return false;
    }
    
    
    // see if account of type allready exists
    for (int i = 0; i < 2; i++) {
        if (accounts[i].type == accountType)
        {
            
            string typeName = accountType == 1 ? "checkings" : "savings";
            cout << errorMsg << getFullName() << " cannot have two " << typeName << " accounts." << endl;
            return false;
        }
    }
    
    return true;
}

// set a new account to given customer
void Customer::setAccount(int accountNr, int accountType, double balance)
{   
    
    // create and set new account
    string typeName = accountType == 1 ? "checkings" : "savings";
    account newAccount = {accountNr, accountType, balance, typeName};
    accounts[activeAccounts] = newAccount;
    activeAccounts++;
}

// display a customers info
string Customer::info() 
{
    string info = "SSN: ";
    info += to_string(SSN);
    info += "\nName: " + firstName;
    info += " " + lastName;
    return info;
}

// display a users account info
string Customer::displayCustomer()
{   
    // create empty customer info
    string customerInfo = "      " + firstName + " " + lastName + ": " + to_string(SSN) + " - ";
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // append info to string
            customerInfo += to_string(accounts[i].number) + "(" + printBalance(accounts[i].balance) + "), ";
        }
    }
    
    // return string containing customer info
    return customerInfo.substr(0, customerInfo.size() - 2); // remove trailing ", ";
}


// display a users account info
string Customer::displayAccount()
{   
    // create empty account info
    string accountInfo = "";
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // append info to string
            accountInfo += "      " + to_string(accounts[i].number) + ": " + printBalance(accounts[i].balance);
            accountInfo += " (" + accounts[i].typeName.substr(0, accounts[i].typeName.size() - 1) + ")\n";
        }
    }
    
    // return string containing account info
    return accountInfo;
}


// get the total balance of users accounts
double Customer::getTotalBalance()
{
    double totalBalance = 0;
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // add total balance
            totalBalance += accounts[i].balance;
            
        }
    }
    
    // return accumulated balance
    return totalBalance;
}

// search in users account for mathcing account number
account Customer::findAccount(int accountNr)
{
    account tempAccount = {0, 0, 0, "UNKNOWN"};
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // see if any of accounts has matching account number
            if (accounts[i].number == accountNr)
            {
                // return users SSN for further validation
                return accounts[i];
            }
        }
    }
    
    // no matching account found
    return tempAccount;
}

// close a given account
bool Customer::closeAccount(int accountNr)
{
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // see if any of accounts has matching account number
            if (accounts[i].number == accountNr)
            {
                
                // create deleted / removed info output
                string name = firstName + " " + lastName;
                cout << "\nAccount Closed" << endl;
                cout << "\n      Name: " + name << endl;
                printAccountInfo(accounts[i]);
                
                // set account to non initialized account
                accounts[i] = {0, 0, 0, "UNKNOWN"};
                
                // deduct accounts
                activeAccounts--;
                
                // if number of accounts is 0, delete customer
                if (activeAccounts == 0)
                {
                    cout << "Customer " << name << " is also deleted." << endl;
                    return true;
                }
                
            }
            
        }
    }
    
    // dont delete
    return false;
}

// print customer info
void Customer::printCustomerInfo()
{

    cout << "\n      Name: " + firstName + " " + lastName << endl;
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            // print account info;
            printAccountInfo(accounts[i]);
        }
    }
}

// print account info
void Customer::printAccountInfo(account cAccount)
{
    string info = "";
    info += "      Account Number: " + to_string(cAccount.number) + "\n";
    info += "      Account Type: ";
    info +=        toupper(cAccount.typeName[0]);
    info +=        cAccount.typeName.substr(1, cAccount.typeName.size() - 2) + "\n";
    info += "      Balance: " + printBalance(cAccount.balance) + "\n";
    cout << info << endl;
}


// update a given account
void Customer::updateAccount(account updatedAccount)
{
    for (int i = 0; i < 2; i++)
    {   
        // find active account
        if (accounts[i].typeName != "UNKNOWN")
        {   
            if (accounts[i].number == updatedAccount.number)
            {
                accounts[i] = updatedAccount;
            }
        }
    }
}


// GETTERS AND SETTERS
int Customer::getSSN() 
{
    return SSN;
}

string Customer::getLastName()
{
    return lastName;
}

int Customer::getAccountAmount()
{
    return activeAccounts;
}

string Customer::getFullName()
{
    return firstName + " " + lastName;
}

account * Customer::getAccounts()
{
    return accounts;
}