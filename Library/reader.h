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
    Reader(const QString username, const QString password, const int max_borrow, const int now_borrow = 0)
        : User(username, password), max_borrow(max_borrow), now_borrow(now_borrow) {}
    bool isAdmin() const { return false; }
    virtual ~Reader(){}
    void Borrow();			// 借书
    void GiveBack();		// 还书
    void Modify (const int &max_borrow);			// 修改读者信息
    int NowBorrow() const { return now_borrow; }
    int CanBorrow() const { return max_borrow - now_borrow; }
    // QString info_SingleLine();
    // QString info_DoubleLines();
};


#endif // READER_H
