#ifndef APPLY_H
#define APPLY_H
#include "main.h"
#include <QString>
#include <qdebug.h>

class Apply
{
    static int total;
    int readerID, bookID;
    int type;				// 1:借阅, 2:归还
    bool deal = false;		// 是否已经处理
    bool accept = false;	// 是否批准
    time_t time;
public:
    Apply(const int type, const int readerID, const int bookID, const time_t time)
        : readerID(readerID), bookID(bookID), type(type), time(time) { total++; }
    void Accept();		// 批准
    void Reject();		// 拒绝
    QString info();	// 输出借阅信息
};



#endif // APPLY_H
