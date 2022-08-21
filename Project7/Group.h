#pragma once

#include <string>
#include <list>

#include "Department.h"
#include "Trainer.h"
#include "Client.h"

namespace fitnessapp {

	class Client;
	class Trainer;
	class Department;

	class Group : public InternalDivision
	{
	private:
		static std::string NameOfFile;

		std::string Name;
		std::string Describe;
		std::list<int> ArrayOrClinets;
		int TrainerOfGroup;
		//int department;
	public:
		void SetName(std::string Name);
		void SetDescribe(std::string Describe);
		void SetArrayOrClinets(std::list<int> ArrayOrClinets);
		void SetTrainerOfGroup(int TrainerOfGroup);
		//void SetDepartment(int department);
		std::string GetName();
		std::string GetDescribe();
		std::list<int> GetArrayOrClinets();
		int GetTrainerOfGroup();
		//int GetDepartment();
		void AddClient(int id);
		void RemoveClient(int id);

		static Group* GetInternalDivision(int id);
		static Group* GetInternalDivisionByNumber(int number);
		static std::list<Group*> GetAllGroup();

		static void UpateGroup(Group* client);
		static void RemoveGroup(int client);

		static Group* unparse(std::string);
		static std::string parse(Group* group);

		static void Save(Group* group);
	};
}