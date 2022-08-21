#pragma once

#include "Person.h"
#include <string>

namespace fitnessapp {
	class Employee : public Person
	{
	private:
		short Stage;
		int Payment;
		std::string Specialization;
	public:
		std::string GetSpecialization();
		float GetPayment();
		short GetStage();
		void SetSpecialization(std::string Specialization);
		void SetPayment(float Payment);
		void SetStage(short Stage);

		static Employee* unparse(std::string str, int& i);
	};
}
