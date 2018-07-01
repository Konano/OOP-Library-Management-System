#ifndef RECORD_H
#define RECORD_H

#include "main.h"
#include <QString>
#include <qdebug.h>

class Record
{
    static int total;
    int ID, readerID, bookID;
    int type;					// 1:借阅, 2:归还
    // time_t time;
public:
    Record(const int readerID, const int bookID, const string typestr) //, const time_t time
        : ID(++total), readerID(readerID), bookID(bookID) //, time(time)
       		{
       			if (typestr == "BORROW") type=1;
       			if (typestr == "RETURN") type=2;
       		}
    int GetReaderID() const { return readerID; }
    int GetBookID() const { return bookID; }
    string GetType() const;
};

#endif // RECORD_H


