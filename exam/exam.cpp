// exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>

#include "md5.h"
#include "account.h"

class Settings {
public:
    static Settings& getInstance() {
        static Settings instance;
        return instance;
    }
    Account& getAccount() {
        return *account;
    }
    int login(std::string username, std::string password) {
        if (!(accounts.count(username))) return 2; // no such account found
        if (!(accounts[username]->checkPassword(password))) return 1; // wrong password
        account = accounts[username];
        return 0; // good password
    }
    void reg(std::string username, std::string password, bool isAdmin) {
        if (isAdmin)
            accounts[username] = new AdminAccount(username, password);
        else
            accounts[username] = new UserAccount(username, password);
    }
private:
    Settings() {}
    Account* account = new EmptyAccount();
    std::map<std::string, Account*> accounts;
public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

};

int main() {
    Settings::getInstance().reg("among", "us", true);
    std::cout << Settings::getInstance().login("among", "us") << std::endl; // 0
//    std::cout << Settings::getInstance().getAccount();
    std::cout << Settings::getInstance().login("among", "us!") << std::endl; // 1
//    std::cout << Settings::getInstance().getAccount();
    std::cout << Settings::getInstance().login("amogn", "us") << std::endl; // 2
 //   std::cout << Settings::getInstance().getAccount();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
