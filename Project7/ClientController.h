#pragma once

#include "Client.h"
#include "Trainer.h"
#include "function.h"
#include "View.h"

namespace fitnessapp_view 
{
	class ClientView;
}

namespace fitnessapp_controller {


	class ClientController
	{
	private:
	public:

		fitnessapp_view::ClientView CheckOfValidAccount(std::list<std::pair<std::string, std::string>> Request);

	};
}
