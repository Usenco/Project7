#include "ReceptionController.h"

namespace fitnessapp_controller {
    fitnessapp_view::ReceptionView ReceptionController::CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request)
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
        fitnessapp::Reception* reception = fitnessapp::Reception::GetReception(email, password);

        if (reception == nullptr)throw 1;

        fitnessapp_view::ReceptionView rv;

        std::list<std::pair<std::string, std::string>> Response;

        std::string tmp_string;
        for (auto var : fitnessapp::Client::GetAllClient())
        {
            tmp_string += "FirstName:" + var->GetFirst_name() + ',';
            tmp_string += "LastName:" + var->GetLast_name() + ',';
            tmp_string += "DateOfBirth:" + var->GetDate_of_Birth() + ',';
            tmp_string += ';';
        }
        Response.push_back(std::pair<std::string, std::string>("Clients", tmp_string));

        tmp_string = "";
        for (auto var : fitnessapp::Trainer::GetAllTrainer())
        {
            tmp_string += "FirstName:" + var->GetFirst_name() + ',';
            tmp_string += "LastName:" + var->GetLast_name() + ',';
            tmp_string += "DateOfBirth:" + var->GetDate_of_Birth() + ',';
            tmp_string += ';';
        }
        Response.push_back(std::pair<std::string, std::string>("Trainers", tmp_string));

        tmp_string = "";
        for (auto var : fitnessapp::Group::GetAllGroup())
        {
            tmp_string += "Number:" + std::to_string(var->GetNumber()) + ',';
            tmp_string += "Name:" + var->GetName() + ',';
            tmp_string += "Describe:" + var->GetDescribe() + ',';
            tmp_string += ';';
        }
        Response.push_back(std::pair<std::string, std::string>("Groups", tmp_string));

        rv.Request.clear();
        rv.Request = Response;

        return rv;
    }
    fitnessapp_view::ActionReceptionTrainerView ReceptionController::ActionVithTrainer(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j, k, d;
        i = j = k = d = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "FirstName")j = i;
            if (var.first == "LastName")k = i;
            if (var.first == "DateOfBirth")d = i;
            i++;
        }
        fitnessapp::Trainer* trainer = fitnessapp::Trainer::GetPerson(j->second, k->second, d->second);

        fitnessapp_view::ActionReceptionTrainerView rv;

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
            tmp_string += "ID:" + std::to_string(t->GetId()) + ',';
            tmp_string += ';';
        }
        Response.push_back(std::pair<std::string, std::string>("Clients", tmp_string));

        rv.Request.clear();
        rv.Request = Response;

        std::list<std::pair<std::string, std::string>> HideResponse;
        HideResponse.push_back(std::pair<std::string, std::string>("ID", std::to_string(trainer->GetId())));

        rv.Response.clear();
        rv.Response = HideResponse;

        return rv;
    }
    fitnessapp_view::ActionReceptionGroupView ReceptionController::ActionVithGroup(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "Number")j = i;
            i++;
        }
        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Group* group = fitnessapp::Group::GetInternalDivisionByNumber(number);

        fitnessapp_view::ActionReceptionGroupView rv;

        std::list<std::pair<std::string, std::string>> Response;
        
        Response.push_back(std::pair<std::string, std::string>("Number", std::to_string(group->GetNumber())));
        Response.push_back(std::pair<std::string, std::string>("Name", group->GetName()));
        Response.push_back(std::pair<std::string, std::string>("Describe", group->GetDescribe()));
        Response.push_back(std::pair<std::string, std::string>("Trainer", std::to_string(group->GetTrainerOfGroup())));

        std::string tmp_string;
        for (auto var : group->GetArrayOrClinets())
        {
            fitnessapp::Client* t = fitnessapp::Client::GetPerson(var);
            if (t != nullptr) {
                tmp_string += "ID:" + std::to_string(t->GetId()) + ',';
                tmp_string += ';';
            }
        }
        Response.push_back(std::pair<std::string, std::string>("Clients", tmp_string));

        rv.Request.clear();
        rv.Request = Response;

        std::list<std::pair<std::string, std::string>> HideResponse;
        HideResponse.push_back(std::pair<std::string, std::string>("ID", std::to_string(group->GetId())));

        rv.Response.clear();
        rv.Response = HideResponse;
        return rv;
    }
    fitnessapp_view::ActionReceptionClientView ReceptionController::ActionVithClient(std::list<std::pair<std::string, std::string>> Request)
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
        if (client == nullptr)throw 1;

        fitnessapp_view::ActionReceptionClientView rv;

        std::list<std::pair<std::string, std::string>> Response;

        Response.push_back(std::pair<std::string, std::string>("FirstName", client->GetFirst_name()));
        Response.push_back(std::pair<std::string, std::string>("LastName", client->GetLast_name()));
        Response.push_back(std::pair<std::string, std::string>("DateOfBirth", client->GetDate_of_Birth()));
        Response.push_back(std::pair<std::string, std::string>("Balance", std::to_string(client->GetBalance())));
        Response.push_back(std::pair<std::string, std::string>("Recomendation", client->GetRecomendation()));
        Response.push_back(std::pair<std::string, std::string>("Mark", std::to_string(client->GetMark())));
        std::string tmp_string;
        for (auto var : client->GetTrainer())
        {
            fitnessapp::Trainer* t = fitnessapp::Trainer::GetPerson(var);
            if (t != nullptr) {
                tmp_string += "ID:" + std::to_string(t->GetId()) + ',';
                tmp_string += ';';
            }
        }
        Response.push_back(std::pair<std::string, std::string>("Trainers", tmp_string));
        tmp_string = "";
        for (auto var : client->GetGroups())
        {
            fitnessapp::Group* t = fitnessapp::Group::GetInternalDivision(var);
            if (t != nullptr) {
                tmp_string += "ID:" + std::to_string(t->GetId()) + ',';
                tmp_string += ';';
            }
        }
        Response.push_back(std::pair<std::string, std::string>("Groups", tmp_string));

        rv.Request.clear();
        rv.Request = Response;

        std::list<std::pair<std::string, std::string>> HideResponse;
        HideResponse.push_back(std::pair<std::string, std::string>("ID", std::to_string(client->GetId())));

        rv.Response.clear();
        rv.Response = HideResponse;

        return rv;
    }
    void ReceptionController::UpdateDataOfClient(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Client* client = fitnessapp::Client::GetPerson(number);

        for (auto var : Request)
        {
            if (var.first == "FirstName")client->SetFirst_name(var.second);
            else if (var.first == "LastName")client->SetLast_name(var.second);
            else if (var.first == "DateOfBirth")client->SetDate_of_Birth(var.second);
            else if (var.first == "Balance") {
                int number = 0; 
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;
                    
                }
                client->SetBalance(number);
            }
            else if (var.first == "Mark") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;
                    
                }
                client->SetMark(number);
            }
            else if (var.first == "Recomendation") {
                 client->SetRecomendation(var.second);
            }
            else if (var.first == "AddTrainer") {
                int number = 0; 
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->AddTrainer(number);
            }
            else if (var.first == "RemoveTrainer") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->RemoveTrainer(number);
            }
            else if (var.first == "AddGroup") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->AddGroup(number);
            }
            else if (var.first == "RemoveGroup") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->RemoveTrainer(number);
            }
        }
        fitnessapp::Client::UpateClient(client);
    }
    void ReceptionController::UpdateDataOfTrainer(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Trainer* trainer = fitnessapp::Trainer::GetPerson(number);

        for (auto var : Request)
        {
            if (var.first == "AddClients") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                trainer->AddClient(number);

            }
            else if (var.first == "RemoveClients") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                trainer->RemoveClient(number);

            }
        }

        fitnessapp::Trainer::UpateTrainer(trainer);
    }
    void ReceptionController::UpdateDataOfGroup(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Group* group = fitnessapp::Group::GetInternalDivision(number);

        for (auto var : Request)
        {
            if (var.first == "Name")group->SetName(var.second);
            else if (var.first == "Describe")group->SetDescribe(var.second);
            else if (var.first == "AddClients") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)j->second[i]) - 48;

                }
                group->AddClient(number);
                
            }
            else if (var.first == "RemoveClients") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)j->second[i]) - 48;

                }
                group->RemoveClient(number);
                
            }
            else if (var.first == "AddTrainer") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)j->second[i]) - 48;

                }
                group->SetTrainerOfGroup(number);
                
            }
        }

        fitnessapp::Group::UpateGroup(group);
    }
    void ReceptionController::AddClient(std::list<std::pair<std::string, std::string>> Request)
    {
        fitnessapp::Client* client = new fitnessapp::Client();
        std::string email; std::string password;
        for (auto var : Request)
        {
            if (var.first == "FirstName")client->SetFirst_name(var.second);
            else if (var.first == "LastName")client->SetLast_name(var.second);
            else if (var.first == "DateOfBirth")client->SetDate_of_Birth(var.second);
            else if (var.first == "Recomendation")client->SetRecomendation(var.second);
            else if (var.first == "Balance") 
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->SetBalance(number);
            }
            else if (var.first == "Mark")
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                client->SetMark(number);
            }
            else if (var.first == "AddTrainer")
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (var.second[i] == ',')
                    {
                        client->AddTrainer(number);
                        number = 0;
                        continue;
                    }

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }

                if (number != 0)client->AddTrainer(number);
                number = 0;

            }
            else if (var.first == "AddGroup")
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (var.second[i] == ',')
                    {
                        client->AddGroup(number);
                        number = 0;
                        continue;
                    }

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }

                if (number != 0)client->AddGroup(number);
                number = 0;

            }
            else if (var.first == "email")email = var.second;
            else if (var.first == "password")password = var.second;

        }

        fitnessapp::Client::Save(client);
        fitnessapp::Client::SaveEnterData(client->GetId(), email, password);
    }
    void ReceptionController::AddTrainer(std::list<std::pair<std::string, std::string>> Request)
    {
        fitnessapp::Trainer* trainer = new fitnessapp::Trainer();
        std::string email; std::string password;
        for (auto var : Request)
        {
            if (var.first == "FirstName")trainer->SetFirst_name(var.second);
            else if (var.first == "LastName")trainer->SetLast_name(var.second);
            else if (var.first == "DateOfBirth")trainer->SetDate_of_Birth(var.second);
            else if (var.first == "Stage") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;
                }
                trainer->SetStage(number);
            }
            else if (var.first == "Payment") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;
                }
                trainer->SetPayment(number);
            }
            else if (var.first == "Specialization")trainer->SetSpecialization(var.second);
            else if (var.first == "AddClient")
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (var.second[i] == ',')
                    {
                        trainer->AddClient(number);
                        number = 0;
                        continue;
                    }

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                if (number != 0)trainer->AddClient(number);
                number = 0;
            }
            else if (var.first == "email")email = var.second;
            else if (var.first == "password")password = var.second;

        }

        fitnessapp::Trainer::Save(trainer);
        fitnessapp::Trainer::SaveEnterData(trainer->GetId(),email,password);
    }
    void ReceptionController::AddGroup(std::list<std::pair<std::string, std::string>> Request)
    {
        fitnessapp::Group* group = new fitnessapp::Group();
        for (auto var : Request)
        {
            if (var.first == "Number") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                group->SetNumber(number);
            }
            else if (var.first == "Name")group->SetName(var.second);
            else if (var.first == "Describe")group->SetDescribe(var.second);
            else if (var.first == "AddClient")
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {
                    if (var.second[i] == ',')
                    {
                        group->AddClient(number);
                        number = 0;
                        continue;
                    }

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                if (number != 0)group->AddClient(number);
                number = 0;
            }
            else if (var.first == "TrainerOfGroup") 
            {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                group->SetTrainerOfGroup(number);
            }
            /*else if (var.first == "AddDepart") {
                int number = 0;
                for (size_t i = 0; var.second[i] != '\0'; i++)
                {

                    if (number)number = number * 10;
                    number += ((int)var.second[i]) - 48;

                }
                group->SetDepartment(number);
            }*/

        }

        fitnessapp::Group::Save(group);
    }
    void ReceptionController::RemoveClient(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Client::RemoveClient(number);


    }
    void ReceptionController::RemoveTrainer(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Trainer::RemoveTrainer(number);
    }
    void ReceptionController::RemoveGroup(std::list<std::pair<std::string, std::string>> Request)
    {
        std::list<std::pair<std::string, std::string>>::iterator i, j;
        i = j = Request.begin();
        for (auto var : Request)
        {
            if (var.first == "ID")j = i;
            i++;
        }

        int number = 0;
        for (size_t i = 0; j->second[i] != '\0'; i++)
        {
            if (number)number = number * 10;
            number += ((int)j->second[i]) - 48;
        }

        fitnessapp::Group::RemoveGroup(number);
        
    }
}


