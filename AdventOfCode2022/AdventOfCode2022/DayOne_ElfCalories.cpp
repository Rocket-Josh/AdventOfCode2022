#include "DayOne_ElfCalories.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void AnalyseFile(std::ifstream& file);
void TotalTopThreeElves(const std::vector<int>& elfCalories);

const std::string _testDataFilePath = "C:\\Users\\Joshua18\\source\\repos\\AdventOfCode2022\\DataFiles\\TestData.txt";

std::vector<int> elfCalories;

int currCalories = 0;
int highestCalories = 0;


void DayOne_ElfCalories::DayOne()
{
	std::ifstream dataFile;
	dataFile.open(_testDataFilePath);
	if (dataFile.is_open())
	{
		AnalyseFile(dataFile, 1, true);

		std::cout << "Highest Calories: " << highestCalories << std::endl;
		TotalTopThreeElves(elfCalories);

		dataFile.close();
	}
	else
	{
		std::cout << "Failed to open file at " + _testDataFilePath + ". DayOne Failed." << std::endl;
		return;
	}
}

/// <summary>
/// Implementation of virtual function.
/// Calculates total calories for each elf, and determines elf with most calories.
/// Checks each line, if not empty line then adds the value to the total calories,
/// if the line is empty then it means it is a new elf. It adds the current count to
/// the vector of ints, it compares highest count to current and if current is higher
/// then overrides.
/// </summary>
/// <param name="line">Contents (string) of the current line</param>
void DayOne_ElfCalories::Process(std::string line, const int& problemPart)
{
	// Blank line so we should add new element (new elf) in vector
	if (line.empty())
	{
		elfCalories.insert(std::upper_bound(elfCalories.begin(), elfCalories.end(), currCalories), currCalories);

		if (currCalories > highestCalories)
		{
			highestCalories = currCalories;
			std::cout << "New Highest: " << highestCalories << std::endl;
		}

		currCalories = 0;
		return;
	}

	currCalories += std::stoi(line);
}

/// <summary>
/// Determines the elves with the highest 3 scores (calories) then totals
/// them together.
/// </summary>
/// <param name="elfCalories"></param>
void TotalTopThreeElves(const std::vector<int>& elfCalories)
{
	int topThreeTotal = 0;
	int c = 0;
	for (int i = elfCalories.size() - 1; c < 3; c++, i--)
	{
		topThreeTotal += elfCalories[i];
	}

	std::cout << "Total of the top three elves is: " << topThreeTotal << std::endl;
}