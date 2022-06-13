#ifndef BANK_HPP
#define BANK_HPP

#include "account.hpp"
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

class Bank {
    public:

    // Default constructor. accounts_ should be initialized to an empty vector.
    Bank() = default;

    // Parametrized constructor.
    //
    // @param accounts - vector of Account pointers to initialize the bank with
    Bank(const std::vector<Account*>& accounts);

    // Prints out all accounts in this bank
    void print_accounts();

    // Adds a surplus to every account in the bank
    //
    // @param amount - the amount in USD to add to the accounts
    void add_surplus(double amount);

    // Finds all accounts in the bank which have negative balance
    //
    // @return a vector of Account pointers where each account has negative balance
    std::vector<Account*> accounts_in_debt();
    
    // Finds all accounts in the bank which have a balance higher than a threshold
    //
    // @param threshold - the amount in USD a balance should be above to be considered rich
    // @return a vector of Account pointers where each account has a balance higher than the threshold
    std::vector<Account*> rich_accounts(double threshold);

    // Finds the average balance across all accounts in the bank
    // @return the average balance
    double average_balance();

    private:

    // NOTE: This is a function
    // Prints out the name and balance for an account
    //
    // @param a pointer to the account to print
    static std::function<void(Account*)> print_balance;

    // NOTE: This is a function that returns a function.
    // 
    // @param amount - the amount in dollars that the function should add
    // @return a function that takes in an Account pointer as input and returns void
    //         the function should increment the Account's balance by the value specified in amount
    static std::function<Account*(Account*)> add_money(double amount);
    
    // NOTE: This is a function
    // Checks if an account has negative balance
    //
    // @param a pointer to the account
    // @return true if the account's balance is negative, false otherwise
    static std::function<bool(Account*)> in_debt;

    // NOTE: This is a function that returns a function
    // Checks is an account has a balance above the threshold
    //
    // @param threshold - the amount in USD a balance should be above to be considered rich
    // @return a function that takes in an Account pointer as input and returns a boolean
    //         this function returns true if the account's balance is above the threshold, false otherwise
    static std::function<bool(Account*)> is_rich(double threshold);

    // NOTE: this is a function
    // Accumulates a sum of balances.  This function should just the accounts balance to the double
    //
    // @param the total sum to add onto
    // @param a pointer to the account
    // @return the sum of double passed in + the account's balance
    static std::function<double(double, Account*)> accumulate_sum;

    // List of all the accounts in the bank
    std::vector<Account*> accounts_;
};


#endif