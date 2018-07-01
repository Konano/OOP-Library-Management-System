#ifndef BOOK_H
#define BOOK_H

#include "main.h"
#include <QString>
#include <qdebug.h>

using namespace std;

class Book
{
    static int total;
    int ID;
    QString name, writer, publisher, ISBN;
    int number;					// 总馆藏数
    int available_number;		// 现可借册数
public:
    Book(const int ID, const QString name, const QString writer, const QString publisher, const QString ISBN, const int number, const int available_number) :
        ID(ID?ID:++total), name(name), writer(writer), publisher(publisher), ISBN(ISBN), number(number), available_number(available_number)
            { total = max(total, ID); }

    int GetID() const { return ID; }
    int LentTotal() const { return number-available_number; }
    int AvailableTotal() const { return available_number; }
    QString GetISBN() const { return ISBN; }
    QString GetName() const { return name; }
    QString GetWriter() const { return writer; }
    QString GetPublisher() const { return publisher; }

    void Lent() { available_number--; }				// 图书被借出
    void Return() { available_number++; } 		    // 图书被归还
    void Modify (const QString &name, const QString &writer, const QString &publisher, const QString &ISBN, const int &number);
};

#endif // BOOK_H
