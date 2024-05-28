#include "programmer.h"

std::ostream& operator<<(std::ostream& os, const ProgrammerBase& p)
{
	p.print();
	return os;
}

std::istream& operator>>(std::istream& is, ProgrammerBase& p)
{
	p.readFrom(is);
	return is;
}

void add_programmers(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v)
{
	std::ifstream fin(filename);
	std::string line;

	while (!fin.eof()) {
		std::string position;
		double hours;
		fin >> position >> hours;

		if (position == "Junior") 
		{
			v.push_back(std::make_unique<Programmer<Junior>>(hours));
		}
		else if (position == "Middle") 
		{
			v.push_back(std::make_unique<Programmer<Middle>>(hours));
		}
		else if (position == "Senior") 
		{
			v.push_back(std::make_unique<Programmer<Senior>>(hours));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
	fin.close();
}

void add_tech_leads(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v)
{
	std::ifstream fin(filename);
	std::string line;

	while (!fin.eof()) {
		std::string position;
		double hours;
		int team_size;
		fin >> position >> hours >> team_size;
		if (position == "Junior") 
		{
			v.push_back(std::make_unique<TechLead<Junior>>(hours, team_size));
		}
		else if (position == "Middle") 
		{
			v.push_back(std::make_unique<TechLead<Middle>>(hours, team_size));
		}
		else if (position == "Senior") 
		{
			v.push_back(std::make_unique<TechLead<Senior>>(hours, team_size));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
	fin.close();
}

void add_programmersEnum(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v)
{
	std::ifstream fin(filename);
	std::string line;

	while (!fin.eof()) {
		PositionEnum position;
		double hours;
		fin >> position >> hours;

		if (position == PositionEnum::Junior || position == PositionEnum::Middle || position == PositionEnum::Senior)
		{
			v.push_back(std::make_unique<Programmer<PositionEnum>>(position,hours));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
	fin.close();
}

void add_tech_leadsEnum(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v)
{
	std::ifstream fin(filename);
	std::string line;

	while (!fin.eof()) {
		PositionEnum position;
		double hours;
		int team_size;
		fin >> position >> hours >> team_size;
		if (position == PositionEnum::Junior || position == PositionEnum::Middle || position == PositionEnum::Senior)
		{
			v.push_back(std::make_unique<TechLead<PositionEnum>>(position,hours, team_size));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
	fin.close();
}

void Programmer<PositionEnum>::print() const
{
	std::ios_base::fmtflags default_flags = std::cout.flags();
	std::streamsize default_precision = std::cout.precision();
	std::cout << std::fixed << std::setprecision(0);
	std::cout << "Programmer | Position: " << this->position
		<< " | hours worked: " << std::left << std::setw(5) << this->hours_worked
		<< "| total salary: " << std::left << std::setw(7) << std::setprecision(2) << this->get_salary();
	std::cout.flags(default_flags);
	std::cout.precision(default_precision);
	std::cout << " usd/h" << std::endl;
}
double Programmer<PositionEnum>::get_salary() const
{
	switch (position)
	{
	case PositionEnum::Junior:
		return Junior::salary_per_hour * hours_worked;
	case PositionEnum::Middle:
		return Middle::salary_per_hour * hours_worked;
	case PositionEnum::Senior:
		return Senior::salary_per_hour * hours_worked;
	}
}

std::string Programmer<PositionEnum>::get_position() const
{
	switch (position)
	{
	case PositionEnum::Junior:
		return "Junior";
	case PositionEnum::Middle:
		return "Middle";
	case PositionEnum::Senior:
		return "Senior";
	}
}

void TechLead<PositionEnum>::print() const
{
	std::ios_base::fmtflags default_flags = std::cout.flags();
	std::streamsize default_precision = std::cout.precision();
	std::cout << std::fixed << std::setprecision(0);
	std::cout << std::left << std::setw(10) << "TechLead"
		<< " | Position: " << this->position
		<< " | hours worked: " << std::left << std::setw(5) << this->hours_worked
		<< "| total salary: " << std::left << std::setw(7) << std::setprecision(2) << this->get_salary();
	std::cout.flags(default_flags);
	std::cout.precision(default_precision);
	std::cout << " usd/h | team size: " << team_size
		<< " | salary bonus: " << get_salary_bonus() << '%' << std::endl;
}