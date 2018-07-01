#include "reader.h"

using namespace std;

void Reader::Borrow()
{
    this->now_borrow++;
}

void Reader::Return()
{
    this->now_borrow--;
}

void Reader::Modify(const int &max_borrow)
{
    this->max_borrow = max_borrow;
}
