#pragma once

#include "GeneralClass.h"

namespace fitnessapp
{

	std::list<GeneralClass*> GeneralClass::unparse_array(std::string str, int& i)
	{
		bool start = false;
		int number = 0;

		std::list<GeneralClass*> list;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == '{') {
				start = true;
				continue;
			}
			else if (str[i] == '}') {
				start = false;
				break;
			}
			if (start)
			{
				if (str[i] != ',') {
					if (number)number = number * 10;
					number += ((int)str[i]) - 48;
				}
				else
				{

					GeneralClass* gc = new GeneralClass();
					gc->id = number;

					number = 0;

					list.push_back(gc);

				}
			}
		}

		if (number != 0) {

			GeneralClass* gc = new GeneralClass();
			gc->id = number;

			list.push_back(gc);
		}

		return list;
	}
	void GeneralClass::SaveIndex()
	{
		std::ofstream file(NameOfFile, std::ios_base::trunc);

		if (!file.is_open())throw 1;

		file << GeneralClass::index;

		file.close();
	}
	GeneralClass::GeneralClass()
	{
		if (index == 0) 
		{
			std::ifstream file(NameOfFile);

			if (!file.is_open())throw 1;

			file >> GeneralClass::index;

			file.close();
		}
		GeneralClass::index++;
		id = index;
	}

	int GeneralClass::GetId() { return this->id; }
}