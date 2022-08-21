#pragma once

#include <list>

#include "Employee.cpp"
#include "InternalDivision.cpp"

namespace fitnessapp {
	class Director
	{
	private:
		std::list<Employee*> Employees;
		std::list<InternalDivision*> InternalDivisions;
	public:
		void SetEmployees(std::list<Employee*> Employees);
		void SetInternalDivisions(std::list<InternalDivision*> InternalDivisions);
		std::list<Employee*> GetEmployees();

		std::list<InternalDivision*> GetInternalDivisions();

		void RemoveEmployee(Person& person);
		void AddEmployee(Employee* employee);
		Employee* FindEmployee(Person& person);
		void ChangeDataOfEmployee(Employee* employee);
		void RemoveInternalDivision(InternalDivision* InternalDivision);
		void AddInternalDivision(InternalDivision* InternalDivision);
		InternalDivision* FindInternalDivisionByNumber(int Number);
		void ChangeDataOfInternalDivision(InternalDivision* InternalDivision);
	};
}
