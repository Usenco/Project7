#pragma once

#include "Client.h"
#include "Trainer.h"
#include "Group.h"
#include "InternalDivision.cpp"
#include "Employee.h"
#include <fstream>

namespace fitnessapp {
	class Reception : public Employee
	{
	private:
		static std::string NameOfFile;
		std::list<Client*> Clients;
		std::list<Trainer*> Trainers;
		std::list<Group*> Groups;
	public:
		void SetClients(std::list<Client*> Clients);
		void SetTrainers(std::list<Trainer*> Trainers);
		void SetGroups(std::list<Group*> Groups);
		std::list<Client*> GetClients();
		std::list<Trainer*> GetTrainers();
		std::list<Group*> GetGroups();

		void ChangeDataOfGroup(Group* group);
		void ChangeDataOfTrainer(Trainer* trainer);
		void ChangeDataOfClient(Client* client);

		static Reception* GetReception(std::string email,std::string password);
	};
}


