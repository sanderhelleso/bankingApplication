# bankingApplication
An imaginary bank application that can store customer’s information for a bank.

## Instructions

In this project, you will develop an imaginary bank application that can store customer’s information for a bank. For this, you should define a class named Customer (= Customer.cpp and Customer.h) which can hold the customer’s first name, last name, SSN, checking account, and/or saving account info. In the project, you can assume that your application can hold maximum 20 customers (= maximum 40 accounts). To maintain the customer’s data, you have to use an array of pointers to Customer objects in the driver program.
<br>
<br>
In the program, you should be able to read customer data in a text file.
For example, this is a sample text file called data1.txt
3
7777 Tom Smith 1000 1 10.00
9999 Joe Otter 5000 1 100.25
8888 Alice Smith 2000 1 50.25
<br>
<br>
The first line indicates the number of customers in the file. Each customer information includes SSN (four digit number), first name, last name, account number (four digit number), account type (1: checking, 2: saving), and current balance. So, the second line indicates that Tom Smith has a checking account with the balance $10.00. Tom’s SSN is 7777 and his account number is 1000. In the project, you can assume that the text file has always correct format (= correct data).
<br>
<br>
<ul>
  <li>Customers can have maximum two accounts (both checking and saving). But they can’t have two checking accounts or two saving accounts at the same time.</li>
  <li>After the operation of “Close an account”, if a customer doesn’t have any account, your program should delete the customer data from the bank. In other words, a customer should have at least one account (= either checking or saving).</Li>
  <li>When you conduct the “Transfer Money”, there will be $5 transfer fee for the transfer between two different customers. If the transfer happens between two accounts of a customer, there’s no transfer fee.</li>
  <li>For the “Customer List” operation, your program should display the customer data in the order of SSN (= ascending order).</li>
  <li>When you display money amount in the program, you should always display the two digits for the cent part. For example, if an account’s balance is $45, it should be displayed as $45.00. As another example, if an account has $45.5, it should be $45.50.</li>
 </ul>

