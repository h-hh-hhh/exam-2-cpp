// exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>

#include "md5.h"
#include "account.h"

class Settings {
public:
    static Settings& getInstance() {
        static Settings instance;
        instance.init();
        return instance;
    }
    void init() {
        if (!nextTest) {
            nextTest = 3;
            // tests
            tests.push_back(Test(0));
            tests.push_back(Test(1));
            tests.push_back(Test(2));
            {
                tests[0].add(Question(
                    "What is 2+2",
                    "1",
                    "2",
                    "3",
                    "4",
                    2,
                    5
                ));
                tests[0].add(Question(
                    "What is 3+3",
                    "3",
                    "4",
                    "5",
                    "6",
                    4,
                    7
                ));
                tests[1].add(Question(
                    "Where is Ukraine",
                    "Europe",
                    "Asia",
                    "Africa",
                    "Australia",
                    1,
                    6
                ));
                tests[1].add(Question(
                    "What is russia",
                    "country",
                    "continent",
                    "terrorist organization",
                    "football team",
                    3,
                    6
                ));
                tests[2].add(Question(
                    "Formula line",
                    "y = ax+b",
                    "y = x^2",
                    "y = Vx",
                    "y = ax^2+bx+c",
                    1,
                    6
                ));
                tests[2].add(Question(
                    "Formula area for rectangle",
                    "S = 2ab",
                    "S = 2(a+b)",
                    "S = ab",
                    "S = a+b",
                    3,
                    6
                ));
            }
        }
    }
    Account* getAccount() {
        return account;
    }
    std::vector<Test>& getTests() {
        return tests;
    }
    int login(std::string username, std::string password) {
        if (!(accounts.count(username))) return 2; // no such account found
        if (!(accounts[username]->checkPassword(password))) return 1; // wrong password
        if (account->getEmpty()) delete account;
        account = accounts[username];
        return 0; // good password
    }
    void logout() {
        account = new EmptyAccount();
    }
    int reg(std::string username, std::string password, bool isAdmin) {
        if (isAdmin && !adminExists) {
            accounts[username] = new AdminAccount(username, password);
            adminExists = 1;
            return 0;
        }
        else if (isAdmin && adminExists) {
            return 1; // admin already exists
        }
        else if (!(accounts.count(username))) {
            accounts[username] = new UserAccount(username, password);
            return 0;
        }
        else {
            return 2; // user already exists
        }
    }
private:
    Settings() {}
    Account* account = new EmptyAccount();
    bool adminExists = 0;
    int nextTest = 0;
    std::map<std::string, Account*> accounts;
    std::vector<Test> tests;
public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

};

int menu(int choice) {
    int c;
    switch (choice) {
    case 1: // empty
        std::cout
            << "1. register admin\n"
            << "2. register user\n"
            << "3. log in\n"
            << "0. exit\n";
        break;
    case 0: // non-admin
        std::cout
            << "1. take test\n"
            << "2. show average\n"
            << "0. exit\n";
        break;
    case 2: // admin
        break;
    }
    std::cin >> c;
    return c;
}

int main() {
    std::string inputS1, inputS2;
    int mode, c;
    for (;/*ever*/;) {
        mode = ((Settings::getInstance().getAccount()->getAdmin() << 1) | (int)(Settings::getInstance().getAccount()->getEmpty()));
        c = menu(mode);
        if (mode == 1) {
            switch (c) {
            case 0:
                return 0;
                break;
            case 1:
                std::cout << "Username: ";
                std::getline(std::cin >> std::ws, inputS1);
                std::cout << "Password: ";
                std::getline(std::cin >> std::ws, inputS2);
                if (Settings::getInstance().reg(inputS1, inputS2, true)) {
                    std::cout << "Admin already exists!" << std::endl;
                }
                else {
                    std::cout << "Registered successfully" << std::endl;
                }
                break;
            case 2:
                std::cout << "Username: ";
                std::getline(std::cin >> std::ws, inputS1);
                std::cout << "Password: ";
                std::getline(std::cin >> std::ws, inputS2);
                if (Settings::getInstance().reg(inputS1, inputS2, false)) {
                    std::cout << "User already exists!" << std::endl;
                }
                else {
                    std::cout << "Registered successfully" << std::endl;
                }
                break;
            case 3:
                std::cout << "Username: ";
                std::getline(std::cin >> std::ws, inputS1);
                std::cout << "Password: ";
                std::getline(std::cin >> std::ws, inputS2);
                switch (Settings::getInstance().login(inputS1, inputS2)) {
                case 0:
                    std::cout << "Login successful" << std::endl;
                    break;
                case 1:
                case 2:
                    std::cout << "Login failed! Check your username or password" << std::endl;
                    break;
                }
            }
        }
        if (mode == 2) { // admin
            
        }
        if (mode == 0) { // non-admin
            switch (c) {
            case 0:
                return 0;
                break;
            case 1:
                std::cout << "Enter the test id to take: ";
                std::cin >> c;
                Settings::getInstance().getAccount()->takeTest(Settings::getInstance().getTests()[c]);
                break;
            case 2:
                std::cout << "Your average is " << Settings::getInstance().getAccount()->getAverage() << std::endl;
            }
        }
    }
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
