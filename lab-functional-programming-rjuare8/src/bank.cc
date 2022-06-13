#include "bank.hpp"

// Parametrized constructor.
//
// @param accounts - vector of Account pointers to initialize the bank with
Bank::Bank(const std::vector<Account*>& accounts) { accounts_ = accounts; }

// Prints out all accounts in this bank
void Bank::print_accounts() {
  std::for_each(accounts_.begin(), accounts_.end(), print_balance);
}

// Adds a surplus to every account in the bank
//
// @param amount - the amount in USD to add to the accounts
void Bank::add_surplus(double amount) {
  std::transform(
      accounts_.begin(), accounts_.end(), accounts_.begin(), add_money(amount));
}

// Finds all accounts in the bank which have negative balance
//
// @return a vector of Account pointers where each account has negative balance
std::vector<Account*> Bank::accounts_in_debt() {
  std::vector<Account*> debtors;
  std::copy_if(
      accounts_.begin(), accounts_.end(), std::back_inserter(debtors), in_debt);
  return debtors;
}
// Finds all accounts in the bank which have a balance higher than a threshold
//
// @param threshold - the amount a balance should be above to be considered rich
// @return a vector of Account pointers where each account has a balance higher
// than the threshold
std::vector<Account*> Bank::rich_accounts(double threshold) {
  std::vector<Account*> to_eat;
  std::copy_if(accounts_.begin(),
               accounts_.end(),
               back_inserter(to_eat),
               is_rich(threshold));
  return to_eat;
}

// Finds the average balance across all accounts in the bank
// @return the average balance
double Bank::average_balance() {
  return std::accumulate(
             accounts_.begin(), accounts_.end(), 0, accumulate_sum) /
         static_cast<double>(accounts_.size());
}

// TODO: Implement Everything Below this point

// NOTE: This is a function
// Prints out the name and balance for an account
//
// @param a pointer to the account to print
std::function<void(Account*)> Bank::print_balance{[](Account* account) {
  std::cout << account->name << ": " << account->balance << std::endl;
}};

// NOTE: This is a function that returns a function.
//
// @param amount - the amount that the function should add
// @return a function that takes in an Account pointer as input and returns void
//         the function should increment the Account's balance by the value
//         specified in amount
std::function<Account*(Account*)> Bank::add_money(double amount) {
  return [amount](Account* account) {
    account->balance += amount;

    return account;
  };
}

// NOTE: This is a function
// Checks if an account has negative balance
//
// @param a pointer to the account
// @return true if the account's balance is negative, false otherwise
std::function<bool(Account*)> Bank::in_debt{
    [](Account* account) { return account->balance < 0; }};
// NOTE: This is a function that returns a function
// Checks is an account has a balance above the threshold
//
// @param threshold - the amount in USD a balance should be above to be
// considered rich
// @return a function that takes in an Account pointer as input and returns a
// boolean
//         this function returns true if the account's balance is above the
//         threshold, false otherwise
std::function<bool(Account*)> Bank::is_rich(double threshold) {
  return [threshold](Account* account) { return account->balance > threshold; };
}

// NOTE: this is a function
// Accumulates a sum of balances.  This function should just the accounts
// balance to the double
//
// @param the total sum to add onto
// @param a pointer to the account
// @return the sum of double passed in + the account's balance
std::function<double(double, Account*)> Bank::accumulate_sum{
    [](double sum, Account* account) {
      sum += account->balance;
      return sum;
    }};
