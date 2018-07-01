#include "book.h"

int Book::total = 0;

void Book::Modify(const QString &name, const QString &writer, const QString &publisher, const QString &ISBN, const int &number)
{
	this->name = name;
	this->writer = writer;
	this->publisher = publisher;
	this->ISBN = ISBN;
	this->number = number;
}

