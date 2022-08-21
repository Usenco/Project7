#include "View.h"
std::string fitnessapp_view::View::view(std::string view_string, std::list<std::pair<std::string, std::string>> Request)
{
	bool flag = false;
	bool flag1 = false;
	std::string NameField = "";
	std::string FormatString = "";
	std::string HelpString = "";
	for (size_t i = 0; view_string[i] != '\0'; i++)
	{
		if (view_string[i] == '(') {
			flag = true;
			continue;
		}
		else if (view_string[i] == ')') {
			flag = false;
			i+=2;
			HelpString = "";
			for(;  view_string[i] != ']'; i++)
			{
				HelpString += view_string[i];
			}
			i++;
			std::list<std::pair<std::string, std::string>> HelpRequest;
			for (auto var : Request)
			{
				if (var.first == NameField)
				{
					flag = false;
					std::pair<std::string, std::string> tmp_pair;
					for (size_t n = 0; var.second[n] != '\0'; n++)
					{
						if (var.second[n] == ':') {

							flag = true;
							continue;
						}
						else if (var.second[n] == ',') {
							flag = false;

							HelpRequest.push_back(tmp_pair);
							tmp_pair.first = "";
							tmp_pair.second = "";

							continue;
						}
						else if(var.second[n] == ';')
						{
							flag = false;

							FormatString += View::view(HelpString, HelpRequest);
							HelpRequest.clear();

							continue;
						}
						(flag ? tmp_pair.second : tmp_pair.first) += var.second[n];
					}
					flag = false;
					break;
				}
			}
			NameField = "";
			continue;
		}
		if (view_string[i] == '{') {
			flag = true;
			continue;
		}
		else if (view_string[i] == '}') {
			flag = false;
			for (auto var : Request)
			{
				if (var.first == NameField) 
				{
					FormatString += var.second;
					NameField = "";
     				break;
				}
			}
			continue;
		}

		if (flag)NameField += view_string[i];
		else FormatString += view_string[i];

	}
	return FormatString;
}

void fitnessapp_view::View::Show(BaseView* v)
{
	//while (true) {
		system("cls");
		int number_of_command = 0;
		std::cout << view(v->BaseTemplate, v->Request) << std::endl;
		//std::cin >> number_of_command;

		v->EventHandler(number_of_command);
	//}
}

fitnessapp_view::ReceptionView::ReceptionView()
{
	this->BaseTemplate = 
		"############################################################################################# \n \ " 
		"#  Client:                                                                                  # \n \ "
        "(Clients)[#  {FirstName}:{LastName}:{DateOfBirth}                                             #\n] \ "
		"#  Trainer:                                                                                  # \n \ "
		"(Trainers)[#  {FirstName}:{LastName}:{DateOfBirth}                                             #\n] \ "
		"#  Group:                                                                                  # \n \ "
		"(Groups)[#  {Number}:{Name}:{Describe}                                                    #\n] \ "
		"#  1 - Trainer function                                                                     # \n \ "
		"#  2 - Group function                                                                       # \n \ "
		"#  3 - Client function                                                                      # \n \ "
		"#  4 - Add Trainer                                                                          # \n \ "
		"#  5 - Add Group                                                                            # \n \ "
		"#  6 - Add Client                                                                           # \n \ "
		"############################################################################################# \n \ "
		;
}

void fitnessapp_view::ReceptionView::EventHandler(int number)
{
	std::cin >> number;
	//std::list<std::pair<std::string, std::string>> Request;
	//std::string help_string = "";
	std::pair<std::string, std::string> tmp_pair;
	switch (number)
	{
	case 1:
		std::cout << "First Name of trainer: ";
		tmp_pair.first = "FirstName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Last Name of trainer: ";
		tmp_pair.first = "LastName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Date Of Birth of trainer: ";
		tmp_pair.first = "DateOfBirth";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->ActionVithTrainer(Response).Show();
		break;
	case 2:
		std::cout << "Number Of Group: ";
		tmp_pair.first = "Number";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->ActionVithGroup(Response).Show();
		break;
	case 3:
		std::cout << "First Name of client: ";
		tmp_pair.first = "FirstName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Last Name of client: ";
		tmp_pair.first = "LastName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Date Of Birth of client: ";
		tmp_pair.first = "DateOfBirth";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->ActionVithClient(Response).Show();
		break;
	case 4:
		std::cout << "First Name of trainer: ";
		tmp_pair.first = "FirstName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Last Name of trainer: ";
		tmp_pair.first = "LastName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Date Of Birth of trainer: ";
		tmp_pair.first = "DateOfBirth";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Stage of trainer: ";
		tmp_pair.first = "Stage";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Payment of trainer: ";
		tmp_pair.first = "Payment";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Specialization of trainer: ";
		tmp_pair.first = "Specialization";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter Customer IDs Separated By Commas" << std::endl;
		tmp_pair.first = "AddClient";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter password: ";
		tmp_pair.first = "password";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter email: ";
		tmp_pair.first = "email";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->AddTrainer(Response);

		break;
	case 5:
		std::cout << "Number of group: ";
		tmp_pair.first = "Number";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Name of group: ";
		tmp_pair.first = "Name";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Describe of group: ";
		tmp_pair.first = "Describe";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Trainer of group: ";
		tmp_pair.first = "TrainerOfGroup";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter Client IDs Separated By Commas" << std::endl;
		tmp_pair.first = "AddClient";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->AddGroup(Response);

		break;
	case 6:
		std::cout << "First Name of client: ";
		tmp_pair.first = "FirstName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Last Name of client: ";
		tmp_pair.first = "LastName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Date Of Birth of client: ";
		tmp_pair.first = "DateOfBirth";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Balance of client: ";
		tmp_pair.first = "Balance";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Mark of client: ";
		tmp_pair.first = "Mark";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Recomendation of trainer: ";
		tmp_pair.first = "Recomendation";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter Group IDs Separated By Commas" << std::endl;
		tmp_pair.first = "AddGroup";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter Trainer IDs Separated By Commas" << std::endl;
		tmp_pair.first = "AddTrainer";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter password: ";
		tmp_pair.first = "password";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		std::cout << "Enter email: ";
		tmp_pair.first = "email";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		RecCon->AddClient(Response);

		break;
	default:
		break;
	}
	Response.clear();
}

fitnessapp_view::ActionReceptionTrainerView::ActionReceptionTrainerView()
{
	this->BaseTemplate =
		"############################################################################################# \n\ "
		"#                                   Work Vith Trainer                                       # \n\ "
		"#     First Name: {FirstName}                                                               # \n\ "
		"#     Last Name: {LastName}                                                                 # \n\ "
		"#     Date Of Birth: {DateOfBirth}                                                          # \n\ "
		"#     Stage: {Stage}                                                                    # \n\ "
		"#     Specialization: {Specialization}                                                                          # \n\ "
		"#     Payment: {Payment}                                                                          # \n\ "
		"#     Clients:                                                                             # \n\ "
		"(Clients)[ #         ID:{ID}                                                            # \n\] "
		"#     1 - Remove Trainer                                                                    # \n\ "
		"############################################################################################# \n\ "
		;
}

void fitnessapp_view::ActionReceptionTrainerView::EventHandler(int number)
{
	std::cin >> number;

	//std::list<std::pair<std::string, std::string>> Request;
	std::pair<std::string, std::string> tmp_pair;

	switch (number)
	{
	case 1:

		RecCon->RemoveTrainer(Response);

		break;
	default:
		break;
	}
	Response.clear();
}

fitnessapp_view::ActionReceptionGroupView::ActionReceptionGroupView()
{
	this->BaseTemplate =
		"############################################################################################# \n \ "
		"#  Group:                                                                                   # \n \ "
		"#  Number:{Number}                                                                          # \n \ "
		"#   Name:{Name}                                                                             # \n \ "
	    "#   Describe:{Describe}                                                                     # \n \ "
		"#  Client:                                                                                  # \n \ "
		"#(Clients)[  {ID}  ] # \n \ "
		"#  Trainer:                                                                                 # \n \ "
		"#  {Trainer}                                                                                # \n \ "
		"#  1 - Remove data                                                                          # \n \ "
		"############################################################################################# \n \ "
		;
}

void fitnessapp_view::ActionReceptionGroupView::EventHandler(int number)
{
	std::cin >> number;

	//std::list<std::pair<std::string, std::string>> Request;
	std::pair<std::string, std::string> tmp_pair;

	switch (number)
	{
	case 1:

		RecCon->RemoveGroup(Response);

		break;
	default:
		break;
	}
	Response.clear();
}

//fitnessapp_view::ActionClientView::ActionClientView()
//{
//	this->BaseTemplate =
//		"############################################################################################# \n \ "
//		"#  Trainer:                                                                                 # \n \ "
//		"[#  {C.ID}                                                                                 #] \n \ "
//		"#  Group:                                                                                   # \n \ "
//		"[#  {G.ID}                                                                                 #] \n \ "
//		"#  Client:                                                                                  # \n \ "
//		"#  {C.FirstName}:{C.LasttName}:{C.DateOfBirth}                                              # \n \ "
//		"#  1 - Update data                                                                          # \n \ "
//		"############################################################################################# \n \ "
//		;
//}

fitnessapp_view::MainView::MainView()
{
	this->BaseTemplate =
		"############################################################################################# \n \ "
		"#                                   Who are you                                             # \n \ "
		"#     1 - Client                                                                            # \n \ "
		"#     2 - Trainer                                                                           # \n \ "
		"#     3 - Reception                                                                         # \n \ "
		"############################################################################################# \n \ "
		;
	View::Show(this);
}

void fitnessapp_view::MainView::EventHandler(int number)
{
	std::cin >> number;
	//std::list<std::pair<std::string, std::string>> Request;
	std::string help_string = "";
	switch (number)
	{
	case 1:
		std::cout << "email: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("email",help_string));
		std::cout << "password: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("password", help_string));
		ClCon->CheckOfValidAccount(Response).Show();
		break;
	case 2:
		std::cout << "email: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("email", help_string));
		std::cout << "password: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("password", help_string));
		TrCon->CheckOfValidAccount(Response).Show();
		break;
	case 3:
		std::cout << "email: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("email", help_string));
		std::cout << "password: ";
		std::cin >> help_string;
		Response.push_back(std::pair<std::string, std::string>("password", help_string));
		RecCon->CheckOfValidAccount(Response).Show();
		break;
	default:
		break;
	}
	Response.clear();
}

fitnessapp_view::ActionReceptionClientView::ActionReceptionClientView() : BaseView()
{
	this->BaseTemplate =
		"############################################################################################# \n\ "
		"#                                   Work Vith Client                                        # \n\ "
		"#     First Name: {FirstName}                                                               # \n\ "
		"#     Last Name: {LastName}                                                                 # \n\ "
		"#     Date Of Birth: {DateOfBirth}                                                          # \n\ "
		"#     Recomendation: {Recomendation}                                                        # \n\ "
		"#     Balance: {Balance}                                                                    # \n\ "
		"#     Mark: {Mark}                                                                          # \n\ "
		"#     Trainers:                                                                             # \n\ "
		"(Trainers)[ #         ID:{ID}                                                               # \n\] "
		"#     Groups:                                                                               # \n\ "
		"(Groups)[ #         ID:{ID}                                                                 # \n\] "
		"#  1 - Remove data                                                                          # \n \ "
		"############################################################################################# \n\ "
		;
}

void fitnessapp_view::ActionReceptionClientView::EventHandler(int number)
{
	std::cin >> number;

	//std::list<std::pair<std::string, std::string>> Request;
	std::pair<std::string, std::string> tmp_pair;

	switch (number)
	{
	case 1:

		RecCon->RemoveClient(Response);

		break;
	default:
		break;
	}
	Response.clear();
}

fitnessapp_view::TrainerView::TrainerView() : BaseView()
{
	this->BaseTemplate =
		"############################################################################################# \n\ "
		"#                                   Trainer                                                 # \n\ "
		"#     First Name: {FirstName}                                                               # \n\ "
		"#     Last Name: {LastName}                                                                 # \n\ "
		"#     Date Of Birth: {DateOfBirth}                                                          # \n\ "
		"#     Stage: {Stage}                                                                    # \n\ "
		"#     Specialization: {Specialization}                                                                          # \n\ "
		"#     Payment: {Payment}                                                                          # \n\ "
		"#     Clients:                                                                             # \n\ "
		"(Clients)[ #         First Name:{FirstName}                                                            # \n\ "
		"#         Last Name:{LastName}                                                              # \n\ "
		"#         Recomendation:{Recomendation}                                                              # \n\ "
		"#         Mark:{Mark}                                                   # \n\] "
		"#     1 - Work Vith Client                                                                  # \n\ "
		"############################################################################################# \n\ "
		;
}

void fitnessapp_view::TrainerView::EventHandler(int number)
{
	std::cin >> number;
	
	//std::list<std::pair<std::string, std::string>> Request;
	std::pair<std::string, std::string> tmp_pair;

	switch (number)
	{
	case 1:
		std::cout << "First Name of client: ";
		tmp_pair.first = "FirstName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Last Name of client: ";
		tmp_pair.first = "LastName";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);
		std::cout << "Date Of Birth of client: ";
		tmp_pair.first = "DateOfBirth";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		TrCon->ActionVithClient(Response).Show();
		
		break;
	default:
		break;
	}
	Response.clear();
}

fitnessapp_view::ClientView::ClientView() : BaseView()
{
	this->BaseTemplate =
		"############################################################################################# \n\ "
		"#                                   Client                                                  # \n\ "
		"#     First Name: {FirstName}                                                               # \n\ "
		"#     Last Name: {LastName}                                                                 # \n\ "
		"#     Date Of Birth: {DateOfBirth}                                                          # \n\ "
		"#     Recomendation: {Recomendation}                                                        # \n\ "
		"#     Balance: {Balance}                                                                    # \n\ "
		"#     Mark: {Mark}                                                                          # \n\ "
		"#     Trainers:                                                                             # \n\ "
	    "(Trainers)[ #         First Name:{FirstName}                                                            # \n\ "
		"#         Last Name:{LastName}                                                              # \n\ "
		"#         Specialization:{Specialization}                                                   # \n\] "
		"#     Groups:                                                                               # \n\ "
		"(Groups)[ #         Number:{Number}                                                                   # \n\ "
		"#         Name:{Name}                                                                       # \n\ "
		"#         Describe:{Describe}                                                               # \n\] "
		"############################################################################################# \n\ "
		;
}

void fitnessapp_view::ClientView::EventHandler(int number)
{
}

fitnessapp_view::BaseView::BaseView()
{
	//ClCon = new fitnessapp_controller::ClientController();
	///*fitnessapp_controller::ReceptionController RecCon = new fitnessapp_controller::ReceptionController();*/
	//TrCon = new fitnessapp_controller::TrainerController();
}

void fitnessapp_view::BaseView::Show()
{
	View::Show(this);
}

fitnessapp_view::ActionTrainerClientView::ActionTrainerClientView()
{
	this->BaseTemplate =
		"############################################################################################# \n\ "
		"#                                   Action Vith Client                                      # \n\ "
		"#     First Name: {FirstName}                                                               # \n\ "
		"#     Last Name: {LastName}                                                                 # \n\ "
		"#     Date Of Birth: {DateOfBirth}                                                          # \n\ "
		"#     1 - Set Mark                                                                          # \n\ "
		"#     2 - Set Recomendation                                                                 # \n\ "
		"############################################################################################# \n\ "
		;
}

void fitnessapp_view::ActionTrainerClientView::EventHandler(int number)
{
	std::cin >> number;
	//std::list<std::pair<std::string, std::string>> Request;
	std::pair<std::string, std::string> tmp_pair;

	switch (number)
	{
	case 1:
		std::cout << "Enter Mark To Client: ";
		tmp_pair.first = "Mark";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		TrCon->SetMarkToClient(Response);

		break;
	case 2:
		std::cout << "Enter Recomendation To Client: ";
		tmp_pair.first = "Recomendation";
		std::cin >> tmp_pair.second;
		Response.push_back(tmp_pair);

		TrCon->SetRecomendation(Response);

		break;
	default:
		break;
	}

	Response.clear();
}
