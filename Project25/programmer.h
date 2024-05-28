#pragma once
#include "position.h"
#include "positionEnum.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

class ProgrammerBase {
protected:
	int hours_worked;
public:
	ProgrammerBase(int hw = 0) : hours_worked(hw) {}
	virtual ~ProgrammerBase() = default;
	virtual void print() const abstract;
	virtual void readFrom(std::istream& is) { is >> hours_worked; }
	virtual double get_salary() const abstract;
	int get_hours_worked() const { return hours_worked; }
	virtual std::string get_position() const abstract;
	virtual void work(int hours) { hours_worked += hours; }
	bool operator<(const ProgrammerBase& p) const
	{
		return hours_worked < p.hours_worked;
	}
};
std::ostream& operator<<(std::ostream& os, const ProgrammerBase& p);
std::istream& operator>>(std::istream& is, ProgrammerBase& p);

template <typename ProgPosition>
class Programmer : public ProgrammerBase {
protected:
	typedef ProgPosition position_type;
	position_type position;
public:
	Programmer(int hw = 0) : position(position_type()), ProgrammerBase(hw) {}
	~Programmer() = default;
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

template <>
class Programmer<PositionEnum> : public ProgrammerBase
{
protected:
	PositionEnum position;
public:
	Programmer(PositionEnum p = PositionEnum::Junior,int hw = 0) : position(p), ProgrammerBase(hw) {}
	~Programmer() = default;
	void print() const override;
	double get_salary() const override;
	std::string get_position() const override;
};

template <typename ProgPosition>
class TechLead : public Programmer<ProgPosition> {
private:
	int team_size;
	static constexpr double salary_increase = 0.01;
public:
	TechLead(int hw = 0, int ts = 0) : Programmer<ProgPosition>(hw), team_size(ts) {}
	~TechLead() = default;
	void print() const override;
	void readFrom(std::istream& is) override { Programmer<ProgPosition>::readFrom(is); is >> team_size; }
	double get_salary() const override {
		return Programmer<ProgPosition>::get_salary() * (1 + get_salary_bonus() * 0.01);
	}
	double get_salary_bonus() const {
		return salary_increase * team_size;
	}
};

template <>
class TechLead<PositionEnum> : public Programmer<PositionEnum> 
{
private:
	int team_size;
	static constexpr double salary_increase = 0.01;
public:
	TechLead(PositionEnum p = PositionEnum::Junior,int hw = 0, int ts = 0) : Programmer<PositionEnum>(p,hw), team_size(ts) {}
	~TechLead() = default;
	void print() const override;
	void readFrom(std::istream& is) override { Programmer<PositionEnum>::readFrom(is); is >> team_size; }
	double get_salary() const override {
		return Programmer<PositionEnum>::get_salary() * (1 + get_salary_bonus() * 0.01);
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

void add_programmers(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v);
void add_tech_leads(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v);

void add_programmersEnum(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v);
void add_tech_leadsEnum(const std::string& filename, std::vector<std::unique_ptr<ProgrammerBase>>& v);
