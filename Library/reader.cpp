#include "reader.h"

void Reader::Modify(const QString username, const QString password, const int max_borrow)
{
	User::Modify(username, password);
	this->max_borrow = max(max_borrow, this->now_borrow);
}
