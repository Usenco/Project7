#pragma once

#include "GeneralClass.h"

namespace fitnessapp {
	class InternalDivision : public GeneralClass
	{
	private:
		unsigned int Number;

	public:

		InternalDivision() : GeneralClass()
		{
			Number = 0;
		}

		void SetNumber(unsigned int Number)
		{
			this->Number = Number;
		}
		unsigned int GetNumber()
		{
			return this->Number;
		}
		bool operator==(const InternalDivision& InternalDivision)
		{
			return this->Number == InternalDivision.Number;
		}

		static InternalDivision* unparse(std::string str, int& i)
		{
			InternalDivision* ID = new InternalDivision();

			ID->id = 0;
			short flag = 0;

			for (; str[i] != '\0'; i++)
			{
				if (str[i] == ':') {
					flag++;
					if (flag == 2) {
						i++;
						return ID;
					}
				}
				else {
					switch (flag)
					{
					case 0:
						if (ID->id)ID->id = ID->id * 10;
						ID->id += ((int)str[i]) - 48;
						break;
					case 1:
						if (ID->Number)ID->Number = ID->Number * 10;
						ID->Number += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}

			return ID;
		}
	};
}