#include "ClientController.h"

fitnessapp_view::ClientView fitnessapp_controller::ClientController::CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request)
{
    std::string email = "";
    std::string password = "";
    fitnessapp::Client* client;
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

    client = fitnessapp::Client::GetClient(email, password);

    if (client == nullptr)throw 1;

    fitnessapp_view::ClientView rv;

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
        if (t == nullptr)continue;
        tmp_string += "FirstName:" + t->GetFirst_name()+',';
        tmp_string += "LastName:" + t->GetLast_name() + ',';
        tmp_string += "Specialization:" + t->GetSpecialization() + ',';
        tmp_string += ';';
    }
    Response.push_back(std::pair<std::string, std::string>("Trainers",tmp_string ));
    tmp_string = "";
    for (auto var : client->GetGroups())
    {
        fitnessapp::Group* t = fitnessapp::Group::GetInternalDivision(var);
        if (t == nullptr)continue;
        tmp_string += "Number:" + std::to_string(t->GetNumber()) + ',';
        tmp_string += "Name:" + t->GetName() + ',';
        tmp_string += "Describe:" + t->GetDescribe() + ',';
        tmp_string += ';';
    }
    Response.push_back(std::pair<std::string, std::string>("Groups", tmp_string));

    rv.Request.clear();
    rv.Request = Response;

    return rv;

}
