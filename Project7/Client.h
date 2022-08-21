#pragma once

#include <string>
#include <list>

#include "Person.h"
#include "Group.h"
#include "Trainer.h"

namespace fitnessapp {

	class Group;
	class Trainer;
	class Person;

	class Client : public Person
	{
	private:
		static std::string NameOfFile;
		static std::string NameOfFileVithPasswords;

		int Balance;
		std::string Recomendation;
		short Mark;
		std::list<int> groups;
		std::list<int> trainers;
	public:
		Client()
		{
			Balance = 0;
			Mark = 0;
		}
		void SetBalance(int Balance);
		void SetRecomendation(std::string Recomendation);
		void SetMark(short Mark);
		int GetBalance();
		std::string GetRecomendation();
		short GetMark();
		bool operator==(const Client& client);
		void AddGroup(int group);
		void AddTrainer(int trainer);
		void RemoveGroup(int id);
		void RemoveTrainer(int id);
		std::list<int> GetGroups();
		std::list<int> GetTrainer();

		static Client* GetPerson(std::string,std::string,std::string);
		static Client* GetPerson(int id);
		static std::list<Client*> GetAllClient();

		static void UpateClient(Client* client);
		static void RemoveClient(int client);

		static Client* unparse(std::string);
		static std::string parse(Client* client);

		static void SaveEnterData(unsigned int id, std::string email, std::string password);
		static void Save(Client* client);
		static Client* GetClient(std::string email, std::string password);
	};
}
