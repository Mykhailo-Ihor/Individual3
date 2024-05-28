#pragma once
#include <iostream>
class ProgrammerPosition abstract
{
public:
	virtual void print(std::ostream& os = std::cout) const abstract;
	virtual ~ProgrammerPosition() = default;
};

std::ostream& operator<<(std::ostream& os, const ProgrammerPosition& P)
{
	P.print(os);
	return os;
}

class Junior : public ProgrammerPosition
{
public:
	static constexpr double salary_per_hour = 1.1;
	void print(std::ostream& os = std::cout) const override
	{
		os << "Junior";
	}
};

class Middle : public ProgrammerPosition
{
public:
	static constexpr double salary_per_hour = 2.0;
	void print(std::ostream& os = std::cout) const override
	{
		os << "Middle";
	}
};

class Senior : public ProgrammerPosition
{
public:
	static constexpr double salary_per_hour = 2.5;
	void print(std::ostream& os = std::cout) const override
	{
		os << "Senior";
	}
};
