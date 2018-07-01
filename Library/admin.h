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
    Admin(const QString username, const QString password, const bool alive = true)
        : User(username, password, alive) {}
    virtual ~Admin(){}
    bool isAdmin() const{ return true; }
    int CanBorrow() const{ return 0; }
};
#endif // ADMIN_H
