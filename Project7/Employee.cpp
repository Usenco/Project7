#pragma once

#include "Employee.h"

namespace fitnessapp {
	std::string Employee::GetSpecialization()
	{
		return this->Specialization;
	}
	float Employee::GetPayment()
	{
		return this->Payment;
	}
	short Employee::GetStage()
	{
		return this->Stage;
	}
	void Employee::SetSpecialization(std::string Specialization)
	{
		this->Specialization = Specialization;
	}
	void Employee::SetPayment(float Payment)
	{
		this->Payment = Payment;
	}
	void Employee::SetStage(short Stage)
	{
		this->Stage = Stage;
	}

	Employee* Employee::unparse(std::string str, int& i)
	{
		i = 0;

		Employee* employee = new Employee();

		*((Person*)employee) = *Person::unparse(str, i);

		short flag = 0;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':') {
				flag++;
				if (flag == 3) {
					i++;
					return employee;
				}
			}
			else {
				switch (flag)
				{
				case 0:
					if (employee->Stage)employee->Stage = employee->Stage * 10;
					employee->Stage += ((int)str[i]) - 48;
					break;
				case 1:
					if (employee->Payment)employee->Payment = employee->Payment * 10;
					employee->Payment += ((int)str[i]) - 48;
					break;
				case 2:
					employee->Specialization += str[i];
					break;
				default:
					break;
				}
			}
		}

		return employee;
	}
}