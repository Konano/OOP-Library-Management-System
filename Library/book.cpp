#include "book.h"

int Book::total = 0;

void Book::Lend(){
    if(this->available_number>0) this->available_number--;
    else qDebug() << "目前没有可借阅的书";
}
void Book::ComeBack(){
    this->available_number++;
}

void Book::Modify(const int &number){
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

