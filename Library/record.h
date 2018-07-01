#ifndef RECORD_H
#define RECORD_H

#include "main.h"
#include <QString>
#include <qdebug.h>

class Record
{
    static int total;
    int ID, readerID, bookID;
    time_t time;
public:
    Record(const int readerID, const int bookID, const time_t time)
        : ID(++total), readerID(readerID), bookID(bookID), time(time) {}
    QString info();
};

#endif // RECORD_H


