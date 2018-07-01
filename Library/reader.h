#ifndef READER_H
#define READER_H

#include <QString>
#include <qdebug.h>
#include "main.h"
#include "user.h"

//using namespace std;

class Reader : public User
{
    int max_borrow;			// 最大可借阅数
    int now_borrow;			// 现借阅数
public:
    Reader(const int ID, const QString username, const QString password, const int max_borrow, const int now_borrow = 0)
        : User(ID, username, password), max_borrow(max_borrow), now_borrow(now_borrow) {}
    virtual ~Reader(){}

    bool isAdmin() const { return false; }
    using User::GetName;
    using User::GetPwd;
    int NowBorrow() const { return now_borrow; }
    int MaxBorrow() const { return max_borrow; }
    int CanBorrow() const { return max_borrow - now_borrow; }

    void Borrow();
    void Return();
    void Modify (const int &max_borrow);
};


#endif // READER_H
