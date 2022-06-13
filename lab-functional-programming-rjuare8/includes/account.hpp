#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

struct Account {
  // Default constructor
  Account() = default;

  // Parametrized constructor
  //
  // @param name the name of the person the account is under
  // @param balance the amount in dollars in the account's balance
  Account(std::string name,
         double balance) {
    this->name = name;
    this->balance = balance;
  }

  std::string name;
  double balance;
};

#endif