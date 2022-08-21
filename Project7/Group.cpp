

#include "Group.h"

namespace fitnessapp {

	void Group::SetName(std::string Name) {
		this->Name = Name;
	}
	void Group::SetDescribe(std::string Describe) {
		this->Describe = Describe;
	}
	void Group::SetArrayOrClinets(std::list<int> ArrayOrClinets) {
		this->ArrayOrClinets = ArrayOrClinets;
	}
	void Group::SetTrainerOfGroup(int TrainerOfGroup) {
		this->TrainerOfGroup = TrainerOfGroup;
	}
	/*void Group::SetDepartment(int department) {
		this->department = department;
	}*/
	std::string Group::GetName() {
		return Name;
	}
	std::string Group::GetDescribe() {
		return Describe;
	}
	std::list<int> Group::GetArrayOrClinets() {
		return ArrayOrClinets;
	}
	int Group::GetTrainerOfGroup() {
		return TrainerOfGroup;
	}
	/*int Group::GetDepartment() {
		return department;
	}*/
	void Group::AddClient(int id)
	{
		ArrayOrClinets.push_back(id);
	}
	void Group::RemoveClient(int id)
	{
		for (auto var : ArrayOrClinets)
		{
			if (var == id)ArrayOrClinets.remove(var);
		}
	}

	Group* Group::GetInternalDivision(int id)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
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
	Group* Group::GetInternalDivisionByNumber(int number)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
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
	std::list<Group*> Group::GetAllGroup()
	{
		std::list<Group*> result_list;

		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			result_list.push_back(unparse(str));
		}

		file.close();

		return result_list;
	}
	void Group::UpateGroup(Group* client)
	{
		std::ifstream file(NameOfFile);

		std::string file_string = "";

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		int num_pos = 0;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			unsigned int tmp_id = 0;

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
						else num_pos = file.tellg();
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == client->GetId()) {
				file_string += Group::parse(client);
				break;
			}
			else
			{
				file_string += str;
			}
		}

		file.close();

		std::ofstream ofile(NameOfFile, std::ios_base::trunc);

		ofile << file_string;

		ofile.close();
	}
	void Group::RemoveGroup(int client)
	{
		std::ifstream file(NameOfFile);

		std::string file_string = "";

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		int num_pos = 0;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			unsigned int tmp_id = 0;

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
						else num_pos = file.tellg();
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == client) {
				break;
			}
			else
			{
				file_string += str;
			}
		}

		file.close();

		std::ofstream ofile(NameOfFile, std::ios_base::trunc);

		ofile << file_string << std::endl;

		ofile.close();
	}
	Group* Group::unparse(std::string str)
	{
		int i = 0;
		Group* group = new Group();

		*((InternalDivision*)group) = *InternalDivision::unparse(str, i);

		short flag = 0;
		unsigned int tmp_id_depart = 0;
		unsigned int tmp_id_trainer = 0;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':')flag++;
			else {
				switch (flag)
				{
				case 0:
					group->Name += str[i];
					break;
				case 1:
					group->Describe += str[i];
					break;
				case 2:
					for (auto var : GeneralClass::unparse_array(str, i))
					{
						group->ArrayOrClinets.push_back(var->GetId());
					}
					break;
				case 3:

					if (tmp_id_trainer)tmp_id_trainer = tmp_id_trainer * 10;
					tmp_id_trainer += ((int)str[i]) - 48;

					group->TrainerOfGroup = tmp_id_trainer;

					break;
				/*case 4:
					if (tmp_id_depart)tmp_id_depart = tmp_id_depart * 10;
					tmp_id_depart += ((int)str[i]) - 48;

					group->department = tmp_id_depart;

					break;*/
				default:
					break;
				}
			}
		}

		return group;
	}
	std::string Group::parse(Group* group)
	{
		std::string pars_string = "";
		pars_string += std::to_string(group->GetId()) += ':';
		pars_string += std::to_string(group->GetNumber()) += ':';
		pars_string += group->GetName() += ':';
		pars_string += group->GetDescribe() += ':';
		pars_string += '{';
		for (auto var : group->GetArrayOrClinets())
		{
			pars_string += std::to_string(var) += ',';
		}
		pars_string += "}:";
		pars_string += std::to_string(group->GetTrainerOfGroup()) += ':';
		//pars_string += std::to_string(group->GetDepartment()) += ':';
		

		return pars_string;
	}
	void Group::Save(Group* group)
	{

		std::ofstream ofile(NameOfFile, std::ios_base::app);

		ofile << parse(group) << std::endl;

		ofile.close();
	}
}