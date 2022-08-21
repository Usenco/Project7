#include "TrainerController.h"

namespace fitnessapp_controller 
{
    fitnessapp_view::TrainerView TrainerController::CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request)
	{
        std::string email = "";
        std::string password = "";
        for (auto var : Request)
        {
            if (var.first == "email")
            {
                email = m_sha256(var.second);
                if (password != "")break;
            }
            if (var.first == "password")
            {
                password = m_sha256(var.second);
                if (email != "")break;
            }


        }
        this->trainer = fitnessapp::Trainer::GetTrainer(email, password);
        if (trainer == nullptr)throw 1;

        fitnessapp_view::TrainerView rv;

        std::list<std::pair<std::string, std::string>> Response;

        Response.push_back(std::pair<std::string, std::string>("FirstName", trainer->GetFirst_name()));
        Response.push_back(std::pair<std::string, std::string>("LastName", trainer->GetLast_name()));
        Response.push_back(std::pair<std::string, std::string>("DateOfBirth", trainer->GetDate_of_Birth()));
        Response.push_back(std::pair<std::string, std::string>("Stage", std::to_string(trainer->GetStage())));
        Response.push_back(std::pair<std::string, std::string>("Specialization", trainer->GetSpecialization()));
        Response.push_back(std::pair<std::string, std::string>("Payment", std::to_string(trainer->GetPayment())));

        std::string tmp_string;
        for (auto var : trainer->GetArrayOfClient())
        {
            fitnessapp::Client* t = fitnessapp::Client::GetPerson(var);
            if (t == nullptr)continue;
            tmp_string += "FirstName:" + t->GetFirst_name() + ',';
            tmp_string += "LastName:" + t->GetLast_name() + ',';
            tmp_string += "Mark:" + std::to_string(t->GetMark()) + ',';
            tmp_string += "Recomendation:" + t->GetRecomendation() + ',';
            tmp_string += ';';
        }
        Response.push_back(std::pair<std::string, std::string>("Clients", tmp_string));

        rv.Request.clear();
        rv.Request = Response;

        return rv;
	}
    fitnessapp_view::ActionTrainerClientView TrainerController::ActionVithClient(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j, k, d;
        i = j = k = d = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "FirstName")j = i;
            else if (var.first == "LastName")k = i;
            else if (var.first == "DateOfBirth")d = i;
            i++;
        }
        fitnessapp::Client* client = fitnessapp::Client::GetPerson(j->second, k->second, d->second);


        for (auto var : this->trainer->GetArrayOfClient())
        {
            if (var == client->GetId())continue;
            throw 1;
        }

        fitnessapp_view::ActionTrainerClientView rv;

        std::list<std::pair<std::string, std::string>> Response;

        Response.push_back(std::pair<std::string, std::string>("FirstName", client->GetFirst_name()));
        Response.push_back(std::pair<std::string, std::string>("LastName", client->GetLast_name()));
        Response.push_back(std::pair<std::string, std::string>("DateOfBirth", client->GetDate_of_Birth()));

        rv.Request.clear();
        rv.Request = Response;

        std::list<std::pair<std::string, std::string>> HideResponse;
        HideResponse.push_back(std::pair<std::string, std::string>("ClientID", std::to_string(client->GetId())));

        rv.Response.clear();
        rv.Response = HideResponse;

        return rv;
    }
    void TrainerController::SetRecomendation(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ClientID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Client* c = fitnessapp::Client::GetPerson(number);
        for (auto var : Request) {
            if(var.first == "Recomendation")c->SetRecomendation(var.second);
        }
        fitnessapp::Client::UpateClient(c);
    }
    void TrainerController::SetMarkToClient(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ClientID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Client* c = fitnessapp::Client::GetPerson(number);
        for (auto var : Request) {
            if (var.first == "Mark") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;
                }
                c->SetMark(number);
            }
        }
        fitnessapp::Client::UpateClient(c);
    }
}