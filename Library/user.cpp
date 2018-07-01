#include "user.h"

//using namespace std;
int User::total = 0;

void User::ModifyName(const QString new_name)
{
    this->username = new_name;
}

bool User::CheckPassword(const QString &password) const
{
    if(password==this->password)
        return true;
    else return false;
}

int User::GetID()const
{
    return ID;
}

QString User::GetName()const
{
    return username;
}
