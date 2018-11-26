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

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// initialize total customer and account  capacity
int const CUSTOMER_CAPACITY = 20;
int const ACCOUNT_CAPACITY = 2;

// account struct
struct account 
{   
    int number;
    int type;
    double balance;
    string typeName;
};

// customer class
class Customer
{
    
public:

    // class functions
    void prepeareAccounts();
    bool validateAccount(int accountType);
    void setAccount(int accountNr, int accountType, double balance);
    string info();
    string displayCustomer();
    string displayAccount();
    void printCustomerInfo();
    void printAccountInfo(account cAccount);
    void getCustomer(string type);
    account findAccount(int accountNr);
    void updateAccount(account updatedAccount);
    bool closeAccount(int accountNr);
    
    // friends
    friend string printBalance(double value);
    
    // overloaded
    Customer& operator= (const Customer &customer);
    
    // getters & setters
    int getSSN();
    string getLastName();
    int getAccountAmount();
    double getTotalBalance();
    string getFullName();
    account * getAccounts();
    
    // constructors
    Customer();
    Customer(int SSN, string firstName, string lastName);

private:
    
    // member fields
    int SSN;
    string firstName;
    string lastName;
    int accountType;
    double balance;
    
    // used to keep track of amount of accounts
    account accounts[ACCOUNT_CAPACITY];
    int activeAccounts = 0;

};