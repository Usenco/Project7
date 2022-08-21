#include "Trainer.h"


namespace fitnessapp {



	void Trainer::SetArrayOfClient(std::list<int> ArrayOfClient) {
		this->ArrayOfClient = ArrayOfClient;
	}
	std::list<int> Trainer::GetArrayOfClient() {
		return this->ArrayOfClient;
	}

	void Trainer::SetRecomendation(Person& client, std::string recomendation)
	{
		for (auto var : ArrayOfClient)
		{
			if (*(Person*)var == client)
			{
				Client *c = Client::GetPerson(var);
				c->SetRecomendation(recomendation);
				Client::UpateClient(c);
				
				break;
			}
		}
	}
	Client* Trainer::FindClientByPerson(Person& person)
	{
		for (auto var : ArrayOfClient)
		{
			Client* c = Client::GetPerson(var);
			if (*(Person*)c == (Person&)person)
			{
				return c;
			}
		}
	}
	void Trainer::SetMarkToClient(Person& client, short mark)
	{
		for (auto var : ArrayOfClient)
		{
			Client* c = Client::GetPerson(var);
			if (*(Person*)c == (Person&)client)
			{
				c->SetMark(mark);
				break;
			}
		}
	}
	void Trainer::AddClient(int client)
	{
		ArrayOfClient.push_back(client);
	}
	void Trainer::RemoveClient(int client)
	{
		for (auto var : ArrayOfClient)
		{
			if (var == client)ArrayOfClient.remove(var);
		}
	}
	Trainer* Trainer::GetPerson(std::string First_Name, std::string Last_Name, std::string Date_Of_Birth)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			std::string tmp_FName = "";
			std::string tmp_LName = "";
			std::string tmp_DOB = "";

			short flag = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 1:
						tmp_FName += str[i];
						break;
					case 2:
						tmp_LName += str[i];
						break;
					case 3:
						tmp_DOB += str[i];
						break;
					default:
						break;
					}
				}
			}
			if (tmp_FName == First_Name && tmp_LName == Last_Name && tmp_DOB == Date_Of_Birth) {
				return unparse(str);
			}
		}

		file.close();

		return nullptr;
	}
	Trainer* Trainer::GetPerson(int id)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			int tmp_id = 0;

			short flag = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 0:
						if (tmp_id)tmp_id = tmp_id * 10;
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == id) {
				return unparse(str);
			}
		}

		file.close();

		return nullptr;
	}

	std::list<Trainer*> Trainer::GetAllTrainer()
	{
		std::list<Trainer*> result_list;

		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			result_list.push_back(unparse(str));
		}

		file.close();

		return result_list;
	}

	void Trainer::UpateTrainer(Trainer* client)
	{
		std::ifstream file(NameOfFile);

		std::string file_string = "";

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		int num_pos = 0;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			unsigned int tmp_id = 0;

			short flag = 0;
			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 0:
						if (tmp_id)tmp_id = tmp_id * 10;
						else num_pos = file.tellg();
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == client->GetId()) {
				file_string += Trainer::parse(client);
				break;
			}
			else
			{
				file_string += str;
			}
		}

		file.close();

		std::ofstream ofile(NameOfFile, std::ios_base::trunc);

		ofile << file_string;

		ofile.close();
	}

	void Trainer::RemoveTrainer(int client)
	{
		std::ifstream file(NameOfFile);

		std::string file_string = "";

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		int num_pos = 0;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			unsigned int tmp_id = 0;

			short flag = 0;
			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
				}
				else
				{
					switch (flag)
					{
					case 0:
						if (tmp_id)tmp_id = tmp_id * 10;
						else num_pos = file.tellg();
						tmp_id += ((int)str[i]) - 48;
						break;
					default:
						break;
					}
				}
			}
			if (tmp_id == client) {
				continue;
			}
			else
			{
				file_string += str;
				file_string += '\n';
			}
		}

		file.close();

		std::ofstream ofile(NameOfFile, std::ios_base::trunc);

		ofile << file_string << std::endl;

		ofile.close();
	}

	Trainer* Trainer::unparse(std::string str)
	{
		int i = 0;
		Trainer* trainer = new Trainer();

		*((Employee*)trainer) = *Employee::unparse(str, i);

		short flag = 0;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':')flag++;
			else {
				switch (flag)
				{
				case 0:
					for (auto var : GeneralClass::unparse_array(str, i))
					{
						trainer->ArrayOfClient.push_back(var->GetId());
					}
					break;
				default:
					break;
				}
			}
		}

		return trainer;
	}
	std::string Trainer::parse(Trainer* trainer)
	{
		std::string pars_string = "";
		pars_string += std::to_string(trainer->GetId()) += ':';
		pars_string += trainer->GetFirst_name() += ':';
		pars_string += trainer->GetLast_name() += ':';
		pars_string += trainer->GetDate_of_Birth() += ':';
		pars_string += std::to_string(trainer->GetStage()) += ':';
		pars_string += std::to_string(trainer->GetPayment()) += ':';
		pars_string += trainer->GetSpecialization() += ':';
		pars_string += '{';
		for (auto var : trainer->GetArrayOfClient())
		{
			pars_string += std::to_string(var) += ',';
		}
		pars_string += "}:";

		return pars_string;
	}
	void Trainer::SaveEnterData(unsigned int id, std::string email, std::string password)
	{
		std::ofstream ofile(NameOfFileVithPasswords, std::ios_base::app);

		ofile << id << ':' <<  m_sha256(email) << ':' << m_sha256(password) << std::endl;

		ofile.close();
	}
	void Trainer::Save(Trainer* trainer)
	{
		std::ofstream ofile(NameOfFile, std::ios_base::app);

		ofile << parse(trainer) << std::endl;

		ofile.close();

		SaveIndex();
	}
	Trainer* Trainer::GetTrainer(std::string email, std::string password)
	{
		std::ifstream file(NameOfFileVithPasswords);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			std::string tmp_email = "";
			std::string tmp_password = "";
			short flag = 0;
			unsigned int tmp_id = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')flag++;
				else {
					switch (flag)
					{
					case 0:
						if (tmp_id)tmp_id = tmp_id * 10;
						tmp_id += ((int)str[i]) - 48;
						break;
					case 1:
						tmp_email += str[i];
						break;
					case 2:
						tmp_password += str[i];
						break;
					default:
						break;
					}
				}
			}
			if (tmp_email == email && tmp_password == password) {
				return GetPerson(tmp_id);
			}
		}

		file.close();

		return nullptr;
	}
}