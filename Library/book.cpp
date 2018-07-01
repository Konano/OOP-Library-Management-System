#include "book.h"

int Book::total = 0;

void Book::Modify(const int &number)
{
    this->number = number;
}
void Book::Modifyname(const QString &namee)
{
    this->name = namee;
}
void Book::Modifywriter(const QString &writerr)
{
    this->writer = writerr;
}
void Book::Modifypublisher(const QString &publisherr)
{
    this->publisher = publisherr;
}
void Book::ModifyISBN(const QString &ISBNN)
{
    this->ISBN = ISBNN;
}

