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
    Book(const QString name, const QString writer, const QString publisher, const QString ISBN, const int number, const int available_number) :
        name(name), writer(writer), publisher(publisher), ISBN(ISBN), number(number), available_number(available_number)
            { ID = ++total; }
    void Lend();				// 图书被借出
    void ComeBack(); 			// 图书被归还
    void Modify(const int &number);	// 图书信息修改
    void Modifyname(const QString &namee);
    void Modifywriter(const QString &writerr);
    void Modifypublisher(const QString &publisherr);
    void ModifyISBN(const QString &ISBNN);
    // QString info_SingleLine();	// 图书信息（一行）
    // QString info_DoubleLines();	// 图书信息（多行）
    int LentTotal() { return number-available_number; }
    int AvailableTotal() { return available_number; }
    int GetID() { return ID; }
    QString GetISBN(){return ISBN;}
    QString GetName(){return name;}
    QString GetWriter(){return writer;}
    QString GetPublisher(){return publisher;}

};

#endif // BOOK_H
