#pragma once

#include <list>
#include <string>
#include "function.cpp"
#include <fstream>
#include "Reception.h"
#include "View.h"

namespace fitnessapp_view
{
	class ReceptionView;
	class ActionReceptionTrainerView;
	class ActionReceptionGroupView;
	class ActionReceptionClientView;
}

namespace fitnessapp_controller {

	class ReceptionController
	{
	private:
		std::string Login;
		std::string Password;

		bool CompareDataInFile(std::string email,std::string password);
	public:
		fitnessapp_view::ReceptionView CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request);
		fitnessapp_view::ActionReceptionTrainerView ActionVithTrainer(std::list<std::pair<std::string, std::string>> Request);
		fitnessapp_view::ActionReceptionGroupView ActionVithGroup(std::list<std::pair<std::string, std::string>> Request);
		fitnessapp_view::ActionReceptionClientView ActionVithClient(std::list<std::pair<std::string, std::string>> Request);
		void UpdateDataOfClient(std::list<std::pair<std::string, std::string>> Request);
		void UpdateDataOfTrainer(std::list<std::pair<std::string, std::string>> Request);
		void UpdateDataOfGroup(std::list<std::pair<std::string, std::string>> Request);
		void AddClient(std::list<std::pair<std::string, std::string>> Request);
		void AddTrainer(std::list<std::pair<std::string, std::string>> Request);
		void AddGroup(std::list<std::pair<std::string, std::string>> Request);
		void RemoveClient(std::list<std::pair<std::string, std::string>> Request);
		void RemoveTrainer(std::list<std::pair<std::string, std::string>> Request);
		void RemoveGroup(std::list<std::pair<std::string, std::string>> Request);
	};
}
