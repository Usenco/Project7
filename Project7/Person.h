#pragma once

#include "GeneralClass.h"

#include <string>
#include <fstream>

namespace fitnessapp {

	class Person : public GeneralClass
	{
	private:

		std::string First_name;
		std::string Last_name;
		std::string Date_of_Birth;

	public:

		Person();

		std::string GetFirst_name();
		std::string GetLast_name();
		std::string GetDate_of_Birth();
		void SetFirst_name(std::string First_name);
		void SetLast_name(std::string Last_name);
		void SetDate_of_Birth(std::string Date_of_Birth);
		bool operator==(const Person& person);

		static Person* unparse(std::string str, int& i);
	};
}
