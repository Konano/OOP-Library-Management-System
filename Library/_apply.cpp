#include "apply.h"

int Apply::total = 0;

string Apply::GetType() const
{
	if (type==1) return "BORROW";
	if (type==2) return "RETURN";
}