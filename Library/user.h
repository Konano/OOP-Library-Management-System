#ifndef _USER_H
#define _USER_H
#include <QString>
#include "main.h"

using namespace std;

class User
{
    static int total;
    int ID;
    QString username, password;
public:
    User(const int ID, const QString username, const QString password)
        : ID(ID?ID:++total), username(username), password(password)
            { total = max(total, ID); }
    // virtual ~User() = 0;
    virtual ~User(){}

    int GetID() const { return ID; }
    QString GetName() const { return username; }
    QString GetPwd() const { return password; }
    virtual bool isAdmin() const = 0; // 是否是管理员
    virtual int CanBorrow() const = 0; // 是否能借书

    void Modify(const QString new_name, const QString new_pwd);
    bool CheckPassword(const QString &password) const; // 检查密码是否正确
};

#endif


