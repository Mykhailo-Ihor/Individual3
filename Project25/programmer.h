#pragma once
#include "position.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

class ProgrammerBase {
protected:
	int hours_worked;
public:
	ProgrammerBase(int hw = 0) : hours_worked(hw) {}
	virtual ~ProgrammerBase() = default;
	virtual void print() const abstract;
	virtual double get_salary() const abstract;
	int get_hours_worked() const { return hours_worked; }
	virtual std::string get_position() const abstract;
	virtual void work(int hours) { hours_worked += hours; }
	bool operator<(const ProgrammerBase& p) const
	{
		return hours_worked < p.hours_worked;
	}
};

template <typename ProgPosition>
class Programmer : public ProgrammerBase {
public:
	typedef ProgPosition position_type;
protected:
	position_type position;
public:
	Programmer(int hw = 0) : position(position_type()), ProgrammerBase(hw) {}
	void print() const override;
	double get_salary() const override {
		return ProgPosition::salary_per_hour * hours_worked;
	}
	virtual std::string get_position() const override 
	{
		std::ostringstream oss;
		oss << position;
		return oss.str();
	}
};

template <typename ProgPosition>
class TechLead : public Programmer<ProgPosition> {
private:
	int team_size;
	static constexpr double salary_increase = 0.01;
public:
	using position_type = ProgPosition;
	TechLead(int hw = 0, int ts = 0) : Programmer<ProgPosition>(hw), team_size(ts) {}
	void print() const override;

	double get_salary() const override {
		return Programmer<ProgPosition>::get_salary() * (1 + get_salary_bonus() * 0.01);
	}
	double get_salary_bonus() const {
		return salary_increase * team_size;
	}
};

template<typename ProgPosition>
inline void Programmer<ProgPosition>::print() const
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

template<typename ProgPosition>
inline void TechLead<ProgPosition>::print() const
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


void add_programmers(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v) {
	std::ifstream fin(filename);
	std::string line;

	while (std::getline(fin, line)) {
		std::istringstream iss(line);
		std::string position;
		double hours;
		iss >> position >> hours;

		if (position == "Junior") {
			v.push_back(std::make_unique<Programmer<Junior>>(hours));
		}
		else if (position == "Middle") {
			v.push_back(std::make_unique<Programmer<Middle>>(hours));
		}
		else if (position == "Senior") {
			v.push_back(std::make_unique<Programmer<Senior>>(hours));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
}

void add_tech_leads(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v) 
{
	std::ifstream fin(filename);
	std::string line;

	while (std::getline(fin, line)) {
		std::istringstream iss(line);
		std::string position;
		double hours;
		int team_size;
		iss >> position >> hours >> team_size;

		if (position == "Junior") {
			v.push_back(std::make_unique<TechLead<Junior>>(hours, team_size));
		}
		else if (position == "Middle") {
			v.push_back(std::make_unique<TechLead<Middle>>(hours, team_size));
		}
		else if (position == "Senior") {
			v.push_back(std::make_unique<TechLead<Senior>>(hours, team_size));
		}
		else
		{
			std::string line;
			getline(fin, line);
		}
	}
}
