#pragma once

#include "Reception.h"

namespace fitnessapp {

	void Reception::SetClients(std::list<Client*> Clients) {
		this->Clients = Clients;
	}
	void Reception::SetTrainers(std::list<Trainer*> Trainers) {
		this->Trainers = Trainers;
	}
	void Reception::SetGroups(std::list<Group*> Groups) {
		this->Groups = Groups;
	}
	std::list<Client*> Reception::GetClients() {
		return Clients;
	}
	std::list<Trainer*> Reception::GetTrainers() {
		return Trainers;
	}
	std::list<Group*> Reception::GetGroups() {
		return Groups;
	}

	void Reception::ChangeDataOfGroup(Group* group)
	{
		for (auto var : Groups)
		{
			if (*(InternalDivision*)var == *(InternalDivision*)group)
			{
				delete var;
				var = group;
				break;
			}
		}
	}
	void Reception::ChangeDataOfTrainer(Trainer* trainer)
	{
		for (auto var : Trainers)
		{
			if (*(fitnessapp::Person*)((Employee*)var) == *(fitnessapp::Person*)((Employee*)trainer))
			{
				delete var;
				var = trainer;
				break;
			}
		}
	}
	void Reception::ChangeDataOfClient(Client* client)
	{
		for (auto var : Clients)
		{
			if (*(fitnessapp::Person*)((Employee*)var) == *(fitnessapp::Person*)((Employee*)client))
			{
				delete var;
				var = client;
				break;
			}
		}
	}
	Reception* Reception::GetReception(std::string email, std::string password)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			std::string tmp_email = "";
			std::string tmp_password = "";
			short flag = 0;
			unsigned int tmp_id = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
					continue;
				}
				switch (flag)
				{
				case 1:
					tmp_email += str[i];
					break;
				case 2:
					tmp_password += str[i];
					break;
				case 0:
					if (tmp_id)tmp_id = tmp_id * 10;
					tmp_id += ((int)str[i]) - 48;
					break;
				default:
					break;
				}
			}
			if (tmp_email == email && tmp_password == password) {
				return new Reception();
			}
		}

		file.close();

		return nullptr;
	}
}