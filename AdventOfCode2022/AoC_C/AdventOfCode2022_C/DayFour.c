#include <stdlib.h>
#include "DayFour.h"
#include "Utils.h"

int dayfour_partone();
int dayfour_parttwo();
int strpairs_to_ints(char* line_buf, int* minLeft, int* maxLeft, int* minRight, int* maxRight);

int dayfour_partone()
{
	// GIVEN:		A pair of ranges (int-int) 
	// PROBLEM:		Sometimes one pair totally include their other pair (IE 2-8 fully encompasses 3-7)
	//	DATA S:			CSV string defining range in format 'x-y'
	//  DATA E:			Four Numbers (ints)
	// CHALLENGE:	How many instances does a pair fully contain the other pair?

	const char* filepath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayFourData.txt";
	//const char* filepath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayFourExample.txt";

	FILE* ptr = loadfile_frompath(filepath);
	if (ptr == NULL)
	{
		fprintf(stderr, "Out of memory");
		return 1;
	}

	int overlapCounter = 0;
	int buffer = 255;
	char line_buf[255];

	int* minLeft = malloc(sizeof(int));
	int* minRight = malloc(sizeof(int));
	int* maxLeft = malloc(sizeof(int));
	int* maxRight = malloc(sizeof(int));

	while (fgets(line_buf, buffer, ptr))
	{
		if (strpairs_to_ints(line_buf, minLeft, maxLeft, minRight, maxRight))
		{
			continue;
		}

		// Determine any total overlap (where one pair encompasses all values of the other pair)
		if (*minRight >= *minLeft && *maxRight <= *maxLeft)
		{
			++overlapCounter;
		}
		else if (*minLeft >= *minRight && *maxLeft <= *maxRight)
		{
			++overlapCounter;
		}
	}

	printf("Total instances of pair overlap are: %d\n", overlapCounter);

	free(minLeft);
	free(maxLeft);
	free(minRight);
	free(maxRight);

	fclose(ptr);
	return 0;
}

int dayfour_parttwo()
{
	// GIVEN:		A pair of ranges (int-int) 
	// PROBLEM:		Sometimes pairs include values/ranges from the other pair (IE {4-6},{5-8}, first pair contains values 5 and 6 from second pair)
	//	DATA S:			CSV string defining range in format 'x-y'
	//  DATA E:			Four numbers (ints) 
	// CHALLENGE:	How many instances does a pair contain any values from the other pair?

	const char* filepath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayFourData.txt";
	//const char* filepath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayFourExample.txt";

	FILE* ptr = loadfile_frompath(filepath);
	if (ptr == NULL)
	{
		fprintf(stderr, "Out of memory");
		return 1;
	}

	int overlapCounter = 0;
	int buffer = 255;
	char line_buf[255];

	int* minLeft = malloc(sizeof(int));
	int* minRight = malloc(sizeof(int));
	int* maxLeft = malloc(sizeof(int));
	int* maxRight = malloc(sizeof(int));

	while (fgets(line_buf, buffer, ptr))
	{

		if (strpairs_to_ints(line_buf, minLeft, maxLeft, minRight, maxRight))
		{
			continue;
		}

		// Determine any overlap (partial or total)
		if (*minLeft >= *minRight && *minLeft <= *maxRight)
		{
			++overlapCounter;
		}
		else if (*minRight >= *minLeft && *minRight <= *maxLeft)
		{
			++overlapCounter;
		}
		else if (*maxLeft >= *minRight && *maxLeft <= *maxRight)
		{
			++overlapCounter;
		}
		else if (*maxRight >= *minLeft && *maxRight <= *maxLeft)
		{
			++overlapCounter;
		}
	}

	printf("D4P2: Total partial overlaps: %d\n", overlapCounter);

	free(minLeft);
	free(maxLeft);
	free(minRight);
	free(maxRight);

	fclose(ptr);
	return 0;
}

/// <summary>
/// Extracts the 4 int values from the known/provided line string
/// </summary>
/// <param name="line_buf">Source string from file</param>
/// <param name="minLeft">Pointer to store the lowest left value</param>
/// <param name="maxLeft">Pointer to store the highest left value</param>
/// <param name="minRight">Pointer to store the lowest right value</param>
/// <param name="maxRight">Pointer to store the highest right value</param>
/// <returns></returns>
int strpairs_to_ints(char* line_buf, int* minLeft, int* maxLeft, int* minRight, int* maxRight)
{

	char* leftStr;
	char* rightStr;

	// Split the string by providing a character delimiter
	//	Splits into the left pair ({x-y}) and right pair ({p-q})
	if (split_string_del(line_buf, ',', &leftStr, &rightStr) == 1)
	{
		return 1;
	}

	char* minNo;
	char* maxNo;

	// Extracts the 2 number values from the left pair ('x', and 'y')
	if (split_string_del(leftStr, '-', &minNo, &maxNo) == 1)
	{
		return 1;
	}

	// Convert the char* to numbers and assign to the int pointers
	*minLeft = atoi(minNo);
	*maxLeft = atoi(maxNo);

	// Extracts the 2 number values from the right pair ('p', and 'q')
	if (split_string_del(rightStr, '-', &minNo, &maxNo) == 1)
	{
		return 1;
	}

	*minRight = atoi(minNo);
	*maxRight = atoi(maxNo);

	free(minNo);
	free(maxNo);
	return 0;
}