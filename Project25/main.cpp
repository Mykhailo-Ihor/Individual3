#include "programmer.h"
#include <algorithm>
using namespace std;

namespace std 
{
    template <typename T, typename F>
    ostream& operator << (ostream& os, const pair<T, F>& p)
    {
        os << p.first << ": " << p.second;
        return os;
    }
}

int main()
{
    vector <unique_ptr<ProgrammerBase>> workers;
    add_programmers("programmers.txt", workers);
    add_tech_leads("techleads.txt", workers);
    cout << "Programmers and Tech Leads: " << endl;
    for (auto& programmer : workers)
    {
        programmer->print();
    }
    cout << string(120, '-') << endl;
    cout << "Programmers and Tech Leads sorted by hours worked: " << endl;
    sort(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& a, const unique_ptr<ProgrammerBase>& b) { return *a < *b; });
    for (auto& programmer : workers)
    {
        programmer->print();
    }
    cout << string(120, '-') << endl;
    for_each(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& programmer) {
        int hours = programmer->get_hours_worked();
        programmer->work(hours);
        });
    sort(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& a, const unique_ptr<ProgrammerBase>& b) { return a->get_salary() < b->get_salary(); });
    cout << "Programmers and Tech Leads after working twice as much and sorted by salary: " << endl;
    for (auto& programmer : workers)
    {
        programmer->print();
    }
    map<string, double> salary_map;
    for_each(workers.begin(), workers.end(), [&](const std::unique_ptr<ProgrammerBase>& programmer) {
        auto position = programmer->get_position();
        salary_map[position] += programmer->get_salary();
        });
    cout << string(120, '-') << endl;
    cout << "Total salary by position: " << endl;
    copy(salary_map.begin(), salary_map.end(), ostream_iterator<pair<string, double>>(cout," usd/h\n"));
    system("pause");
    system("cls");
    cout << "Same task but with using PositionEnum: " << endl;
    workers.clear();
    add_programmersEnum("programmers.txt", workers);
    add_tech_leadsEnum("techleads.txt", workers);
    cout << "Programmers and Tech Leads: " << endl;
    for (auto& programmer : workers)
    {
		programmer->print();
	}
    cout << string(120, '-') << endl;
    cout << "Programmers and Tech Leads sorted by hours worked: " << endl;
    sort(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& a, const unique_ptr<ProgrammerBase>& b) { return *a < *b; });
    for (auto& programmer : workers)
    {
		programmer->print();
	}
    cout << string(120, '-') << endl;
    for_each(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& programmer) {
        int hours = programmer->get_hours_worked();
        programmer->work(hours); });
    sort(workers.begin(), workers.end(), [](const unique_ptr<ProgrammerBase>& a, const unique_ptr<ProgrammerBase>& b) { return a->get_salary() < b->get_salary(); });
    cout << "Programmers and Tech Leads after working twice as much and sorted by salary: " << endl;
    for (auto& programmer : workers)
    {
        programmer->print();
    }
    salary_map.clear();
    for_each(workers.begin(), workers.end(), [&](const std::unique_ptr<ProgrammerBase>& programmer) {
		auto position = programmer->get_position();
		salary_map[position] += programmer->get_salary();
		});
    cout << string(120, '-') << endl;
    cout << "Total salary by position: " << endl;
    copy(salary_map.begin(), salary_map.end(), ostream_iterator<pair<string, double>>(cout, " usd/h\n"));
    return 0;
}
