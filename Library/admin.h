#ifndef ADMIN_H
#define ADMIN_H

#include "main.h"
#include "user.h"
#include <QString>
#include <qdebug.h>

using namespace std;

class Admin : public User
{
public:
    Admin(const int ID, const QString username, const QString password)
        : User(ID, username, password) {}
    virtual ~Admin(){}

    using User::GetName;
    using User::GetPwd;
    bool isAdmin() const{ return true; }
    int CanBorrow() const{ return 0; }
};
#endif // ADMIN_H
