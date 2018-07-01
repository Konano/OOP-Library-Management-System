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
    bool alive;
public:
    User(const QString username, const QString password, const bool alive)
        : ID(++total), username(username), password(password), alive(alive) {}
    //virtual ~User() = 0;
    virtual ~User(){}
    virtual bool isAdmin() const = 0; // 是否是管理员
    virtual int CanBorrow() const = 0; // 是否能借书
    void ModifyName(const QString new_name); // 修改姓名
    void Modifyalive();
    bool CheckPassword(const QString &password) const; // 检查密码是否正确
    int GetID() const;
    QString GetName() const;
};

#endif


