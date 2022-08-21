#pragma once

#include <string>
#include <list>

#include "InternalDivision.cpp"
#include "Trainer.h"

namespace fitnessapp {

	class Trainer;

	class Department : public InternalDivision
	{
	private:
		static std::string NameOfFile;

		std::string Name;
		int trainer;
	public:
		void SetName(std::string Name);
		void SetTrainer(int Trainer);
		std::string GetName();
		int GetTrainer();

		static Department* GetInternalDivision(int id);
		static Department* GetInternalDivisionByNumber(int number);

		static Department* unparse(std::string);
	};

}