#include <iostream>
#include "md5.h"
#include "account.h"

Account::Account(std::string username, std::string password, bool isAdmin, bool isEmpty) :
	username(username),
	isAdmin(isAdmin),
	isEmpty(isEmpty)
{
	pwHash = GetMD5String(password);
}

bool Account::checkPassword(std::string password) {
	return GetMD5String(password) == pwHash;
}

int EmptyAccount::changePassword(std::string oldPassword, std::string newPassword) {
	return 2; // obvious
}

int AdminAccount::changePassword(std::string oldPassword, std::string newPassword) {
	if (GetMD5String(oldPassword) != pwHash) return 1; // wrong password
	pwHash = GetMD5String(newPassword);
	return 0; // success
}

int UserAccount::changePassword(std::string oldPassword, std::string newPassword) {
	return 2; // a user account can't change its password
}

std::ostream& operator<<(std::ostream& out, Account* a) {
    out << "Username: "
        << a->getUsername()
        << "\nPassword hash (MD5): "
        << a->getPwHash()
		<< "\nIs admin: "
		<< a->getAdmin()
		<< "\nIs empty: "
		<< a->getEmpty();
    return out;
}