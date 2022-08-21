#pragma once

#include "Person.h"


namespace fitnessapp {
	Person::Person() : GeneralClass()
	{
	}
	std::string Person::GetFirst_name()
	{
		return this->First_name;
	}
	std::string Person::GetLast_name()
	{
		return this->Last_name;
	}
	std::string Person::GetDate_of_Birth()
	{
		return this->Date_of_Birth;
	}
	void Person::SetFirst_name(std::string First_name)
	{
		this->First_name = First_name;
	}
	void Person::SetLast_name(std::string Last_name)
	{
		this->Last_name = Last_name;
	}
	void Person::SetDate_of_Birth(std::string Date_of_Birth)
	{
		this->Date_of_Birth = Date_of_Birth;
	}
	bool Person::operator==(const Person& person)
	{
		return this->First_name == person.First_name &&
			this->Last_name == person.Last_name &&
			this->Date_of_Birth == person.Date_of_Birth;
	}

	Person* Person::unparse(std::string str, int& i)
	{
		Person* person = new Person();

		short flag = 0;
		bool forid = 0;
		person->id = 0;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':') {
				flag++;
				if (flag == 4) {
					i++;
					return person;
				}
			}
			else {
				switch (flag)
				{
				case 0:
					if (forid)person->id = person->id * 10;
					person->id += ((int)str[i]) - 48;
					forid = true;
					break;
				case 1:
					person->First_name += str[i];
					break;
				case 2:
					person->Last_name += str[i];
					break;
				case 3:
					person->Date_of_Birth += str[i];
					break;
				default:
					break;
				}
			}
		}

		return person;
	}
}