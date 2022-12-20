#include <stdlib.h>
#include "DayFour.h"
#include "Utils.h"

int dayfour_partone();
int dayfour_parttwo();

int dayfour_partone()
{
	// GIVEN:		A pair of ranges (int-int) 
	// PROBLEM:		Sometimes one pair totally include their other pair (IE 2-8 fully encompasses 3-7)
	//	DATA S:			CSV string defining range in format 'x-y'
	//  DATA E:			Two strings (remove CSV). 
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
	while (fgets(line_buf, buffer, ptr))
	{
		char* leftStr;
		char* rightStr;

		if (split_string_del(line_buf, ',', &leftStr, &rightStr) == 1)
		{
			continue;
		}
		
		int minLeft = 0;
		int minRight = 0;
		int maxLeft = 0;
		int maxRight = 0;

		char* minNo;
		char* maxNo;

		if (split_string_del(leftStr, '-', &minNo, &maxNo) == 1)
		{
			continue;
		}

		minLeft = atoi(minNo);
		maxLeft = atoi(maxNo);

		if (split_string_del(rightStr, '-', &minNo, &maxNo) == 1)
		{
			continue;
		}

		minRight = atoi(minNo);
		maxRight = atoi(maxNo);

		if (minRight >= minLeft && maxRight <= maxLeft)
		{
			++overlapCounter;
		}
		else if (minLeft >= minRight && maxLeft <= maxRight)
		{
			++overlapCounter;
		}

	}

	printf("Total instances of pair overlap are: %d\n", overlapCounter);
	fclose(ptr);
	return 0;
}

int dayfour_parttwo()
{
	return 0;
}