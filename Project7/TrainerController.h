#pragma once
#include "Trainer.h"
#include "Client.h"
#include "function.h"
#include "View.h"
namespace fitnessapp_view
{
	class TrainerView;
	class ActionTrainerClientView;
}

namespace fitnessapp_controller {

	class TrainerController
	{
	private:
		fitnessapp::Trainer* trainer = nullptr;
	public:

		fitnessapp_view::TrainerView CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request);
		fitnessapp_view::ActionTrainerClientView ActionVithClient(std::list<std::pair<std::string, std::string>> Request);

		void SetRecomendation(std::list<std::pair<std::string, std::string>> Request);
		void SetMarkToClient(std::list<std::pair<std::string, std::string>> Request);

	};
}