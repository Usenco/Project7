#include "Director.h"

namespace fitnessapp {

	void Director::SetEmployees(std::list<Employee*> Employees) {
		this->Employees = Employees;
	}
	void Director::SetInternalDivisions(std::list<InternalDivision*> InternalDivisions) {
		this->InternalDivisions = InternalDivisions;
	}
	std::list<Employee*> Director::GetEmployees() {
		return Employees;
	}

	std::list<InternalDivision*> Director::GetInternalDivisions() {
		return InternalDivisions;
	}

	void Director::RemoveEmployee(Person& person)
	{
		for (auto var : Employees)
		{
			if (*(Person*)var == person)
			{
				Employees.remove(var);
				break;
			}
		}
	}
	void Director::AddEmployee(Employee* employee)
	{
		Employees.push_back(employee);
	}
	Employee* Director::FindEmployee(Person& person)
	{
		return nullptr;
		/*for (auto var : Employees)
		{
			return var;
			if (*(Person*)var == person)
			{
				return var;
			}
		}*/
	}
	void Director::ChangeDataOfEmployee(Employee* employee)
	{
		for (auto var : Employees)
		{
			if (*(Person*)var == *(Person*)employee)
			{
				delete var;
				var = employee;
				break;
			}
		}
	}
	void Director::RemoveInternalDivision(InternalDivision* InternalDivision)
	{
		for (auto var : InternalDivisions)
		{
			if (*var == *InternalDivision)
			{
				InternalDivisions.remove(var);
				break;
			}
		}
	}
	void Director::AddInternalDivision(InternalDivision* InternalDivision)
	{
		InternalDivisions.push_back(InternalDivision);
	}
	InternalDivision* Director::FindInternalDivisionByNumber(int Number)
	{
		for (auto var : InternalDivisions)
		{
			if (var->GetNumber() == Number)
			{
				return var;
			}
		}
	}
	void Director::ChangeDataOfInternalDivision(InternalDivision* InternalDivision)
	{
		for (auto var : InternalDivisions)
		{
			if (*var == *InternalDivision)
			{
				delete var;
				var = InternalDivision;
				break;
			}
		}
	}
}