#include "positionEnum.h"

std::ostream& operator<<(std::ostream& os, PositionEnum p)
{
	switch (p)
	{
	case PositionEnum::Junior:
		os << "Junior";
		break;
	case PositionEnum::Middle:
		os << "Middle";
		break;
	case PositionEnum::Senior:
		os << "Senior";
		break;
	}
	return os;
}

std::istream& operator>>(std::istream& is, PositionEnum& p)
{
	std::string position;
	is >> position;
	if (position == "Junior")
	{
		p = PositionEnum::Junior;
	}
	else if (position == "Middle")
	{
		p = PositionEnum::Middle;
	}
	else if (position == "Senior")
	{
		p = PositionEnum::Senior;
	}
	return is;
}
