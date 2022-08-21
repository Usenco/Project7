
#include "Department.h"

namespace fitnessapp {

	void Department::SetName(std::string Name) {
		this->Name = Name;
	}
	void Department::SetTrainer(int Trainer) {
		this->trainer = Trainer;
	}
	std::string Department::GetName() {
		return Name;
	}
	int Department::GetTrainer() {
		return trainer;
	}
	Department* Department::GetInternalDivision(int id)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		file >> N;

		for (size_t i = 0; i < N; i++)
		{
			char str[100];
			file.getline(str, 100);
			int tmp_id = 0;

			short flag = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 0:
						if (tmp_id)tmp_id = tmp_id * 10;
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == id) {
				return unparse(str);
			}
		}

		file.close();

		return nullptr;
	}
	Department* Department::GetInternalDivisionByNumber(int number)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		file >> N;

		for (size_t i = 0; i < N; i++)
		{
			char str[100];
			file.getline(str, 100);
			int tmp_id = 0;

			short flag = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 1:
						if (tmp_id)tmp_id = tmp_id * 10;
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == number) {
				return unparse(str);
			}
		}

		file.close();

		return nullptr;
	}
	Department* Department::unparse(std::string str)
	{
		int i = 0;
		Department* depart = (Department*)InternalDivision::unparse(str, i);

		short flag = 0;
		unsigned int tmp_id_trainer = 0;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':')flag++;
			else {
				switch (flag)
				{
				case 0:
					depart->Name += str[i];
					break;
				case 4:
					if (tmp_id_trainer)tmp_id_trainer = tmp_id_trainer * 10;
					tmp_id_trainer += ((int)str[i]) - 48;

					depart->trainer = tmp_id_trainer;

					break;
				default:
					break;
				}
			}
		}

		return depart;
	}
}