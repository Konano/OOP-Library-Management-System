#ifndef RECORD_H
#define RECORD_H

#include "main.h"
#include <QString>
#include <qdebug.h>
#include <cstring>

using namespace std;

class Record
{
    static int total;
    int ID, readerID, bookID;
    int type;					// 1:借阅, 2:归还
    bool reject = false;		// 是否同意
    bool accept = false;		// 是否拒绝
    // time_t time;
public:
    Record(const string typestr, const string deal, const int readerID, const int bookID) //, const time_t time
        : ID(++total), readerID(readerID), bookID(bookID) //, time(time)
       		{
       			if (typestr == "BORROW") type = 1;
       			if (typestr == "RETURN") type = 2;
       			if (deal == "REJECT") reject = true;
       			if (deal == "ACCEPT") accept = true;
       		}
    int GetReaderID() const { return readerID; }
    int GetBookID() const { return bookID; }
    bool GetDeal() const { return (reject || accept); }
    bool GetAccept() const { return accept; }
    bool GetReject() const { return reject; }
    string GetType() const;

    void Reject() { reject = true; }
    void Accept();
};

#endif // RECORD_H


