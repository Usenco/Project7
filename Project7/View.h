#pragma once
#include <iostream>
#include <string>
#include <list>
#include "ClientController.h"
#include "ReceptionController.h"
#include "TrainerController.h"

namespace fitnessapp_controller 
{
	class ClientController;
	class TrainerController;
	class ReceptionController;
}

namespace fitnessapp_view {

	class BaseView 
	{
	public:
		BaseView();
		std::string BaseTemplate = "";
		std::list<std::pair<std::string, std::string>> Request;
		std::list<std::pair<std::string, std::string>> Response;

		static fitnessapp_controller::ClientController *ClCon;
		static fitnessapp_controller::ReceptionController* RecCon;
		static fitnessapp_controller::TrainerController *TrCon;

		virtual void EventHandler(int number) =0;

		void Show();
	};


	class View
	{
	public:
		static std::string view(std::string view_string, std::list<std::pair<std::string, std::string>> Request);
		static void Show(BaseView* v);

	private:

	};

	class ReceptionView : public BaseView 
	{
	public:
		ReceptionView();

		void EventHandler(int number) override;
		
	};
	class ActionReceptionTrainerView : public BaseView
	{
	public:
		ActionReceptionTrainerView();

		void EventHandler(int number) override;

	};
	class ActionReceptionGroupView : public BaseView
	{
	public:
		ActionReceptionGroupView();

		void EventHandler(int number) override;

	};
	class ActionReceptionClientView : public BaseView
	{
	public:
		ActionReceptionClientView();

		void EventHandler(int number) override;

	};


	class TrainerView : public BaseView
	{
	public:
		TrainerView();

		void EventHandler(int number) override;

	};
	class ClientView : public BaseView
	{
	public:
		ClientView();

		void EventHandler(int number) override;

	};
	class MainView : public BaseView
	{
	public:
		MainView();

		void EventHandler(int number) override;

	};
	class ActionTrainerClientView : public BaseView
	{
	public:
		ActionTrainerClientView();

		void EventHandler(int number) override;

	};
}