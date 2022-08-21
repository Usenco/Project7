#pragma once

#include <string>
#include <list>

#include "Employee.h"
#include "Client.h"
#include "function.h"


namespace fitnessapp {

	class Client;

	class Trainer : public Employee
	{
	private:
		std::list<int> ArrayOfClient;

		static std::string NameOfFile;
		static std::string NameOfFileVithPasswords;
	public:
		Trainer()
		{

		}
		void SetArrayOfClient(std::list<int> ArrayOfClient);
		std::list<int> GetArrayOfClient();

		void SetRecomendation(Person& client, std::string recomendation);
		Client* FindClientByPerson(Person& person);
		void SetMarkToClient(Person& client, short mark);
		void AddClient(int client);
		void RemoveClient(int client);

		static Trainer* GetPerson(std::string, std::string, std::string);
		static Trainer* GetPerson(int id);
		static std::list<Trainer*> GetAllTrainer();

		static void UpateTrainer(Trainer* client);
		static void RemoveTrainer(int client);

		static Trainer* unparse(std::string);
		static std::string parse(Trainer* trainer);

		static void SaveEnterData(unsigned int id, std::string email, std::string password);
		static void Save(Trainer* trainer);

		static Trainer* GetTrainer(std::string email, std::string password);
	};
}