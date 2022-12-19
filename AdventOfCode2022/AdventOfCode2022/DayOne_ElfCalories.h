#pragma once
#include "FileProcessing.h"
class DayOne_ElfCalories : public FileProcessing
{
public:
	void DayOne();
	void Process(std::string line, const int& problemPart);
};

