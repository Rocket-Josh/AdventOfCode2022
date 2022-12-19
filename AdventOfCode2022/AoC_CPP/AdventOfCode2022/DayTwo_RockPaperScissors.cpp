#include "DayTwo_RockPaperScissors.h"
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

enum RPS
{
	R = 1,
	P = 2,
	S = 3
};

int PartOne_CalculateResult(const RPS& them, const RPS& me);
int PartTwo_CalculateResult(const RPS& them, const std::string& requiredResult);
RPS ChrToRPS(const char& ch);
RPS StrToRPS(const std::string str);

const std::string _dayTwo_TestData = "C:\\Users\\Joshua18\\source\\repos\\AdventOfCode2022\\DataFiles\\DayTwo_RPS_Data.txt";

int points = 0;

void DayTwo_RockPaperScissors::DayTwo()
{
	// 2 elves
	// Many rounds
	// choose R P or S
	// R > S > P > R
	// Draw is allowed
	// THEM: A = R, B = P, C = S
	// THEM: A > C > B > A
	// ME  : X = R, Y = P, Z = S
	// ME  : X > Z > Y > X

	// RES : X = Lose, Y = Draw, Z = Win

	// Total score = sum of scores for each round
	// Score = shapeScore + Outcome
	// Points:		R = 1, P = 2, S = 3
	// Outcomes:	L = 0, D = 3, W = 6

	// Calculate total score according to strategy

	// Part One
	std::ifstream dataFile;
	dataFile.open(_dayTwo_TestData);
	if (dataFile.is_open())
	{
		FileProcessing::AnalyseFile(dataFile, 1, false);
		dataFile.close();
	}
	else
	{
		std::cout << "Failed to open file at " + _dayTwo_TestData + ". DayOne Failed." << std::endl;
		return;
	}

	std::cout << "PART ONE: Total score for presumed success is: " << points << std::endl;

	points = 0;
	dataFile.open(_dayTwo_TestData);
	if (dataFile.is_open())
	{
		FileProcessing::AnalyseFile(dataFile, 2, false);
		dataFile.close();
	}
	else
	{
		std::cout << "Failed to open file at " + _dayTwo_TestData + ". DayOne Failed." << std::endl;
		return;
	}
	std::cout << "PART TWO: Total score for presumed success is: " << points << std::endl;
}

/// <summary>
/// Implementation of virtual function.
/// Splits string into a vector delimited by a ' '
/// Then calculates victory and total score
/// </summary>
/// <param name="line"></param>
void DayTwo_RockPaperScissors::Process(std::string line, const int& problemPart)
{
	std::vector<std::string> rpsRes;
	rpsRes = FileProcessing::SplitString(line, ' ');
	assert(rpsRes.size() > 0);
	RPS them = StrToRPS(rpsRes[0]);
	if (problemPart == 1)
	{
		points += PartOne_CalculateResult(them, StrToRPS(rpsRes[1]));
	}

	if (problemPart == 2)
	{
		points += PartTwo_CalculateResult(them, rpsRes[1]);
	}
}


/// <summary>
/// Calculate the result of that game including winning or losing
/// as well as the score used for that move.
/// </summary>
/// <param name="them">RPS object representing opponent's move</param>
/// <param name="me">RPS object representing my move</param>
/// <returns>Total score of victory, loss or draw PLUS pts for my move</returns>
int PartOne_CalculateResult(const RPS& them, const RPS& me)
{
	int pts = (int)me;
	if (them == me)
	{
		return 3 + me;
	}

	switch (them)
	{
	case R:
		pts += me == P ? 6 : 0;
		break;
	case P:
		pts += me == S ? 6 : 0;
		break;
	case S:
		pts += me == R ? 6 : 0;
		break;
	default:
		std::cout << "Something went wrong. It was not a draw, and 'them' didn't match any case" << std::endl;
		break;
	}

	return pts;
}

int PartTwo_CalculateResult(const RPS& them, const std::string& requiredResult)
{
	int pts = 0;

	// Need to lose
	if (requiredResult == "X")
	{
		pts += 0;
		switch (them)
		{
		case R:
			pts += 3;
			break;
		case P:
			pts += 1;
			break;
		case S:
			pts += 2;
			break;
		}
	}

	// Draw
	if (requiredResult == "Y")
	{
		pts += 3;
		switch (them)
		{
		case R:
			pts += 1;
			break;
		case P:
			pts += 2;
			break;
		case S:
			pts += 3;
			break;
		}
	}

	// Win
	if (requiredResult == "Z")
	{
		pts += 6;
		switch (them)
		{
		case R:
			pts += 2;
			break;
		case P:
			pts += 3;
			break;
		case S:
			pts += 1;
			break;
		}
	}

	return pts;
}



// Helper Functions \\

/// <summary>
/// Convert a character to a 'RPS' object (enum)
/// RPS = Rock Paper Scissors object
/// </summary>
/// <param name="ch">character representing RPS. Valid ones are a,b,c,x,y,z</param>
/// <returns>RPS enum ('R', 'P', or 'S')</returns>
RPS ChrToRPS(const char& ch)
{
	switch (ch)
	{
	case 'X': case 'x':
	case 'A': case 'a':
		return R;
	case 'Y': case 'y':
	case 'B': case 'b':
		return P;
	case 'Z': case 'z':
	case 'C': case 'c':
		return S;
	default:
		std::cout << "Supplied character was not valid. Supplied: " << ch << std::endl;
		break;
	}

	assert(false);
	return R;
}


/// <summary>
/// Convert a string to a 'RPS' object (enum)
/// RPS = Rock Paper Scissors object
/// </summary>
/// <param name="ch">character representing RPS. Valid ones are a,b,c,x,y,z</param>
/// <returns>RPS enum ('R', 'P', or 'S')</returns>
RPS StrToRPS(const std::string str)
{
	if (str == "X" || str == "x" || str == "A" || str == "a")
	{
		return R;
	}
	else if (str == "Y" || str == "y" || str == "B" || str == "b")
	{
		return P;
	}
	else if (str == "Z" || str == "z" || str == "C" || str == "c")
	{
		return S;
	}

	std::cout << "Supplied string was not valid. Supplied: " << str << std::endl;

	assert(false);
	return R;
}