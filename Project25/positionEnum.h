#pragma once
#include <iostream>

enum class PositionEnum
{
	Junior,
	Middle,
	Senior
};

std::ostream& operator<<(std::ostream& os, PositionEnum p);
std::istream& operator>>(std::istream& is, PositionEnum& p);
