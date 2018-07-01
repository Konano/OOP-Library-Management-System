#include "record.h"

int Record::total = 0;

string Record::GetType() const
{
	if (type==1) return "BORROW";
	if (type==2) return "RETURN";
}
