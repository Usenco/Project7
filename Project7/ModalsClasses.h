#pragma once

#include "Client.h"
#include "Department.h"
#include "GeneralClass.h"
#include "Reception.h"
#include "Trainer.h"
#include "Group.h"
#include "View.h"
#include "ReceptionController.h"

unsigned int fitnessapp::GeneralClass::index = 0;
std::string fitnessapp::Client::NameOfFile = "Client.txt";
std::string fitnessapp::Client::NameOfFileVithPasswords = "ClientPassword.txt";
std::string fitnessapp::Department::NameOfFile = "Department.txt";
std::string fitnessapp::Reception::NameOfFile = "Reception.txt";
std::string fitnessapp::Trainer::NameOfFile = "Trainer.txt";
std::string fitnessapp::Trainer::NameOfFileVithPasswords = "TrainerPassword.txt";
std::string fitnessapp::Group::NameOfFile = "Group.txt";
std::string fitnessapp::GeneralClass::NameOfFile = "index.txt";
fitnessapp_controller::ClientController* fitnessapp_view::BaseView::ClCon = new fitnessapp_controller::ClientController();
fitnessapp_controller::ReceptionController* fitnessapp_view::BaseView::RecCon = new fitnessapp_controller::ReceptionController();
fitnessapp_controller::TrainerController*  fitnessapp_view::BaseView::TrCon = new fitnessapp_controller::TrainerController();