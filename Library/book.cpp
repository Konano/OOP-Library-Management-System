#include "book.h"

int Book::total = 0;

//QString Book::info_SingleLine(){
//    //string info = "书名" + this->name + "作者" + this->writer + "出版社" + this->publisher + "ISBN"+ this->ISBN + "ID" + to_string(ID)
//    //+"馆藏数量"+ to_string(number) + "剩余数量"+to_string(available_number);
//    return 0;
//}
//QString Book::info_DoubleLines(){
//    //string info = "书名" + this->name +endl+ "作者" + this->writer + endl+"出版社" + this->publisher + endl+"ISBN"+ this->ISBN + endl+"ID"
//    //+ to_string(ID) +endl+"馆藏数量"+ to_string(number) +endl+ "剩余数量"+to_string(available_number);
//    return 0;
//}

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

