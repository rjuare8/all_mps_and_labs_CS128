#include "bank.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<Account*> accounts = {};
    accounts.push_back(new Account("Greg", 10.00));
    accounts.push_back(new Account("Srinjoy", 15.00));
    accounts.push_back(new Account("Georges", -10.00));
    accounts.push_back(new Account("Elon", 500.00));
    accounts.push_back(new Account("Jeff", 1000.00));

    Bank bank = Bank(accounts);

    std::cout << "Initial Bank Accounts: " << std::endl;
    bank.print_accounts();
    std::cout << std::endl;

    std::cout << "Accounts in Debt: " << std::endl;

    std::vector<Account*> debtors = bank.accounts_in_debt();
    Bank debtors_bank = Bank(debtors);
    debtors_bank.print_accounts();
    std::cout << std::endl;

    bank.add_surplus(15);

    std::cout << "Accounts after adding a surplus of 15: " << std::endl;
    bank.print_accounts();
    std::cout << std::endl;

    std::cout << "Average balance of accounts in this bank: " << bank.average_balance() << std::endl;
    std::cout << std::endl;

    std::cout << "Look at these high rollers with more than 100 dollars in their account: " << std::endl;
    std::vector<Account*> rich_accounts = bank.rich_accounts(100);
    Bank rich_bank = Bank(rich_accounts);  
    rich_bank.print_accounts();
    std::cout << std::endl;

    std::cout << "Let's not tax them." << std::endl;

    return 0;
}
