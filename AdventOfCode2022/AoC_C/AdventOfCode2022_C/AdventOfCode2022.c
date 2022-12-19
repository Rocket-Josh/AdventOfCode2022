#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define BOOL char
#define TRUE 1
#define FALSE 0

void DayThree();

int main()
{
	DayThree();
}

void DayThree()
{
	// 2 large 'compartments'
	// All items of a type are to go into exactly one of the compartments
	// Failed to follow above rule for exactly one item type per rucksack
	// 
	// INPUT: List of all items currently in each rucksack
	// PROBLEM: Need to find the errors (Mis-placed items)
	// 
	// Every item type is defined by a single lower/uppercase letter ('a' and 'A' are two different item types)
	// Each rucksack is on one line
	// First half of line is compartment A, second half is compartment B
	// Lowercase items have 'priority' value of 1-26 (a-z)
	// Uppercase items have 'priority' value of 27-52 (A-Z)
	//
	// Challenge: Sum of the priorities of items that appear in both compartments

	// Data Start	: Text file
	// Data End		: per line left and right

	const char* filePath = "C:\\Users\\Joshua18\\source\\repos\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeData.txt";
	//const char* filePath = "C:\\Users\\Joshua18\\source\\repos\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeExample.txt";

	int bufferLength = 255;
	char line_buf[255];
	FILE* ptr = fopen(filePath, "r");

	if (!ptr)
	{
		printf("Failed to open file");
		return EXIT_FAILURE;
	}

	int total = 0;
	while (fgets(line_buf, bufferLength, ptr))
	{
		int len = strlen(line_buf);

		// Check for hidden characters (New Line characters) 
		//	if new line char is found, ignore it by setting the character to '\0' (null character)
		//	then recalculate the length to account for this.
		if (line_buf[len - 1] == '\n')
		{
			line_buf[len - 1] = '\0';
			len = strlen(line_buf);
		}

		// Calculate the lengths of both the left and right side of the line
		int lhs = len / 2;
		int rhs = len - lhs;

		// Copy the lhs of the string into a new char array (string)
		char* s1 = malloc(lhs + 1);
		memcpy(s1, line_buf, lhs);
		s1[lhs] = '\0';

		// Copy the rhs of the string into a separate char array
		char* s2 = malloc(rhs + 1);
		memcpy(s2, line_buf + lhs, rhs);
		s2[rhs] = '\0';

		// Store the characters we've already checked on this line
		//	we don't want to tally the points twice
		char checkedChars[255] = "";
		checkedChars[0] = '\0';

		// Iterate the LHS string and compare with RHS
		//	if we have a matching character on both sides, we need to
		//	tally the score
		for (int i = 0; i < strlen(s1); i++)
		{
			if (strchr(s2, s1[i]) == NULL)
			{
				continue;
			}

			if (strchr(checkedChars, s1[i]) != NULL)
			{
				continue;
			}

			// Append this character to our 'tracked' string
			//	so we don't count this character twice
			strncat(checkedChars, &s1[i], 1);
			total += getScore(s1[i]);
		}

		free(s1);
		free(s2);
	}

	printf("Rucksack total score: %d\n", total);
	fclose(ptr);
}

int getScore(char c)
{
	// 1-based scoring system
	int num = 1;
	if (c >= 'A' && c <= 'Z')
	{
		// If uppercase, offset the score by 26
		num += c - 'A' + 26;
	}
	else if (c >= 'a' && c <= 'z')
	{
		num += c - 'a';
	}
	else
	{
		// non-alphabetical character was passed in
		return 0;
	}

	return num;
}

