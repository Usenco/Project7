#pragma once

#include <string>
#include <list>
#include <fstream>

namespace fitnessapp
{
	class GeneralClass
	{
	private:
		static unsigned int index;
		static std::string NameOfFile;
	protected:

		unsigned int id = 0;

		static std::list<GeneralClass*> unparse_array(std::string str, int& i);

		static void SaveIndex();

	public:
		GeneralClass();

		int GetId();
	};
	
}