#include "user.h"

int User::total = 0;

void User::ModifyName(const QString new_name)
{
    this->username = new_name;
}

bool User::CheckPassword(const QString &password) const
{
    return password == this->password;
}

User* NowUser;
