#pragma once
#include <fstream>
#include <assert.h>
#include <vector>
#include <string>

class FileProcessing
{
public:
	virtual void Process(std::string line, const int& part) = 0;

	/// <summary>
	/// Shared code.
	/// Takes in an ifstream and processes each line by passing the contents
	/// of the line into a virtual 'Process' function.
	/// </summary>
	/// <param name="dataFile">Stream of the text file</param>
	/// <param name="problemPart">Which part of the problem are we one (part one, part two etc)</param>
	/// <param name="lineCanBeEmpty">Optional param. If false, will assert if the line is empty and terminate.</param>
	void AnalyseFile(std::ifstream& dataFile, const int& problemPart, bool lineCanBeEmpty = false)
	{
		std::string line;
		int points = 0;
		std::vector<std::string> rpsRes;
		while (std::getline(dataFile, line))
		{
			if (!lineCanBeEmpty)
			{
				assert(line.empty() == false);
			}

			Process(line, problemPart);
		}
	}


	/// <summary>
	/// Split a string based on a supplied delimiter character
	/// </summary>
	/// <param name="str">Input string to be processed</param>
	/// <param name="del">Delimiter character to split the string by</param>
	/// <returns>Return vector strings separated by (not including) the delimiter value</returns>
	std::vector<std::string> SplitString(const std::string str, char del)
	{
		std::vector<std::string> result;
		std::string tmp = "";
		for (int i = 0; i < (int)str.size(); i++)
		{
			if (str[i] != del)
			{
				tmp += str[i];
			}
			else
			{
				result.push_back(tmp);
				tmp = "";
			}
		}

		result.push_back(tmp);
		return result;
	}
};

