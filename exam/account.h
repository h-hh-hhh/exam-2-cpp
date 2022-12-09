#pragma once

class Account {
public:
    Account() {}
    Account(std::string username, std::string password, bool isAdmin, bool isEmpty);
    virtual int changePassword(std::string oldPassword, std::string newPassword) = 0;
    bool checkPassword(std::string password);
    std::string getUsername() { return username; }
    std::string getPwHash() { return pwHash; }
protected:
    std::string username;
    std::string pwHash;
    bool isAdmin;
    bool isEmpty;
};

class EmptyAccount : public Account {
public:
    EmptyAccount() :
        Account("", "", false, true)
    {}
    int changePassword(std::string oldPassword, std::string newPassword);
};

class AdminAccount : public Account {
public:
    AdminAccount(std::string username, std::string password) :
        Account(username, password, true, false)
    {}
    int changePassword(std::string oldPassword, std::string newPassword);
protected:
};

class UserAccount : public Account {
public:
    UserAccount(std::string username, std::string password) :
        Account(username, password, false, false)
    {}
    int changePassword(std::string oldPassword, std::string newPassword);
protected:
};

std::ostream& operator<<(std::ostream& out, AdminAccount a);
std::ostream& operator<<(std::ostream& out, UserAccount a);