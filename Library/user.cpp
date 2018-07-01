#include "user.h"

int User::total = 0;

bool User::CheckPassword(const QString &password) const
{
    return password == this->password;
}

void User::Modify(const QString new_name, const QString new_pwd)
{
	this->username = new_name;
	this->password = new_pwd;
}

User* NowUser;
