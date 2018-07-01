#ifndef APPLY_H
#define APPLY_H
#include "main.h"
#include <QString>
#include <qdebug.h>

class Apply
{
    static int total;
    int ID, readerID, bookID;
    int type;				// 1:借阅, 2:归还
    // bool deal = false;		// 是否已经处理
    // bool accept = false;	// 是否批准
    // time_t time;
public:
    Apply(const string typestr, const int readerID, const int bookID) // , const time_t time
        : ID(++total), readerID(readerID), bookID(bookID) // , time(time)
            {
                if (typestr == "BORROW") type=1;
                if (typestr == "RETURN") type=2;
            }
    int GetReaderID() const { return readerID; }
    int GetBookID() const { return bookID; }
    string GetType() const;
    // void Accept();		// 批准
    // void Reject();		// 拒绝
};

#endif // APPLY_H
