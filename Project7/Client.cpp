

#include "Client.h"

namespace fitnessapp {

	void Client::SetBalance(int Balance) {
		this->Balance = Balance;
	}
	void Client::SetRecomendation(std::string Recomendation) {
		this->Recomendation = Recomendation;
	}
	void Client::SetMark(short Mark) {
		this->Mark = Mark;
	}
	int Client::GetBalance() {
		return Balance;
	}
	std::string Client::GetRecomendation() {
		return Recomendation;
	}
	short Client::GetMark() {
		return Mark;
	}
	bool Client::operator==(const Client& client)
	{
		return (Person)client == (Person)(*this);
	}
	void Client::AddGroup(int group)
	{
		groups.push_back(group);
	}
	void Client::AddTrainer(int trainer)
	{
		trainers.push_back(trainer);
	}
	void Client::RemoveGroup(int id)
	{
		for (auto var : groups)
		{
			if (var == id) 
			{
				groups.remove(var);
			}
		}
	}
	void Client::RemoveTrainer(int id)
	{
		for (auto var : trainers)
		{
			if (var == id)
			{
				trainers.remove(var);
			}
		}
	}
	std::list<int> Client::GetGroups()
	{
		return this->groups;
	}
	std::list<int> Client::GetTrainer()
	{
		return this->trainers;
	}


	Client* Client::GetPerson(std::string First_Name, std::string Last_Name, std::string Date_Of_Birth)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

		for (size_t i = 0; !file.eof(); i++)
		{
			char str[100];
			file.getline(str, 100);
			std::string tmp_FName ="";
			std::string tmp_LName="";
			std::string tmp_DOB="";

			short flag = 0;

			for (size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == ':')
				{
					flag++;
					continue;
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

	Client* Client::GetPerson(int id)
	{
		std::ifstream file(NameOfFile);

		if (!file.is_open())throw 1;

		int N = 0;
		//file >> N;

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
					continue;
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

	void Client::UpateClient(Client* client)
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
					continue;
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
				file_string += Client::parse(client);
				break;
			}
			else 
			{
				file_string += str;
			}
		}

		file.close();

		std::ofstream ofile(NameOfFile,std::ios_base::trunc);

		ofile << file_string;

		ofile.close();
		
	}

	void Client::RemoveClient(int client)
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
					continue;
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

	Client* Client::unparse(std::string str)
	{
		int i = 0;
		Client* client = new Client();

		*((Person*)client) = *Person::unparse(str, i);

		short flag = 0;
		client->Balance = 0;
		client->Mark = 0;

		std::string test;

		for (; str[i] != '\0'; i++)
		{
			if (str[i] == ':')
			{
				flag++;
				continue;
			}
			else {
				switch (flag)
				{
				case 0:
					if (client->Balance)client->Balance = client->Balance * 10;
					client->Balance += ((int)str[i]) - 48;
					break;
				case 1:
					client->Recomendation += str[i];
					break;
				case 2:
					if (client->Mark)client->Mark = client->Mark * 10;
					client->Mark += ((int)str[i]) - 48;
					break;
				case 3:
					for (auto var : GeneralClass::unparse_array(str, i))
					{
						client->trainers.push_back( var->GetId() );
					}
					break;
				case 4:
					for (auto var : GeneralClass::unparse_array(str, i))
					{
						client->groups.push_back(var->GetId());
					}
					break;
				default:
					break;
				}
			}
		}

		return client;
	}

	std::string Client::parse(Client* client)
	{
		std::string pars_string = "";
		pars_string += std::to_string(client->GetId()) += ':';
		pars_string += client->GetFirst_name() += ':';
		pars_string += client->GetLast_name() += ':';
		pars_string += client->GetDate_of_Birth() += ':';
		pars_string += std::to_string(client->GetBalance()) += ':';
		pars_string += client->GetRecomendation() += ':';
		pars_string += std::to_string(client->GetMark()) += ':';
		pars_string += '{';
		for (auto var : client->GetTrainer())
		{
			pars_string += std::to_string(var) += ',';
		}
		pars_string += "}:";
		pars_string += '{';
		for (auto var : client->GetGroups())
		{
			pars_string += std::to_string(var) += ',';
		}
		pars_string += "}:";

		return pars_string;
	}

	std::list<Client*> Client::GetAllClient()
	{
		std::list<Client*> result_list;

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

	void Client::SaveEnterData(unsigned int id, std::string email, std::string password)
	{
		std::ofstream ofile(NameOfFileVithPasswords, std::ios_base::app);

		ofile << id << ':' << m_sha256(email) << ':' << m_sha256(password) << std::endl;

		ofile.close();
	}

	void Client::Save(Client* client)
	{
		std::ofstream ofile(NameOfFile, std::ios_base::app);

		ofile << parse(client) << std::endl;

		ofile.close();
	}

	Client* Client::GetClient(std::string email, std::string password)
	{
		std::ifstream file(NameOfFileVithPasswords);

		if (!file.is_open())throw 1;

		//int N = 0;
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
				if (str[i] == ':') 
				{
					flag++;
					continue;
				}
				switch (flag)
				{
				case 1:
					tmp_email += str[i];
					break;
				case 2:
					tmp_password += str[i];
					break;
				case 0:
					if (tmp_id)tmp_id = tmp_id * 10;
					tmp_id += ((int)str[i]) - 48;
					break;
				default:
					break;
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