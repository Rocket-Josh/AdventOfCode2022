#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DayThree.h"
#include "Utils.h"

int daythree_partone();
int daythree_parttwo();


int daythree_partone()
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


	const char* filePath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeData.txt";
	//const char* filePath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeExample.txt";

	FILE* ptr = loadfile_frompath(filePath);

	if (!ptr)
	{
		printf("Failed to open file");
		return 1;
	}

	int total = 0;
	int bufferLength = 255;
	char line_buf[255];

	while (fgets(line_buf, bufferLength, ptr))
	{
		size_t len = strlen(line_buf);

		// Check for hidden characters (New Line characters) 
		//	if new line char is found, ignore it by setting the character to '\0' (null character)
		//	then recalculate the length to account for this.
		if (line_buf[len - 1] == '\n')
		{
			line_buf[len - 1] = '\0';
			len = strlen(line_buf);
		}

		// Calculate the lengths of both the left and right side of the line
		size_t splitPoint = len / 2;

		char* s1 = NULL;
		char* s2 = NULL;

		split_string(line_buf, splitPoint, &s1, &s2);

		if (s1 == NULL || s2 == NULL)
		{
			fprintf(stderr, "Out of Memory");
			exit(1);
		}

		// Store the characters we've already checked on this line
		//	we don't want to tally the points twice
		char checkedChars[255] = "";
		checkedChars[0] = '\0';

		// Iterate the LHS string and compare with RHS
		//	if we have a matching character on both sides, we need to
		//	tally the score
		for (int i = 0; i < strlen(s1); ++i)
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
			total += get_score(s1[i]);
		}

		free(s1);
		free(s2);
	}

	printf("Rucksack total score: %d\n", total);
	fclose(ptr);
	return 0;
}

int daythree_parttwo()
{
	// Group of 3 (lines)
	// Find char present in all 3 lines
	// Tally up score for that char (ONCE)

	const char* filePath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeData.txt";
	//const char* filePath = "C:\\Repos\\AdventOfCode\\AdventOfCode2022\\AdventOfCode2022\\AoC_C\\DataFiles\\DayThreeExample.txt";

	FILE* ptr = loadfile_frompath(filePath);

	if (ptr == NULL)
	{
		fprintf(stderr, "Out of memory");
		return 1;
	}

	int totalScore = 0;

	// Keeps track of which line we are currently on
	//	helps with manipulation of the correct line
	int lineCounter = 0;
	// Size of a group. Used to track how many lines
	//	to observe at once in one group
	int grp_size = 3;
	// Store all the lines for this group
	char line_grp[3][255];
	// Initialise the array of strings to be empty
	memset(line_grp, 0, sizeof(line_grp));

	int buffer = 255;
	char line_buf[255];
	while (fgets(line_buf, buffer, ptr))
	{
		// Add the current line to the 2D array of strings
		strncat(line_grp[lineCounter], line_buf, strlen(line_buf));

		// If we aren't at the end of a group (every 3rd line) skip to next line
		//	and increment our counter
		if (lineCounter < grp_size - 1)
		{
			lineCounter++;
			continue;
		}

		// The group identifier. If NULL then it means the character being checked
		//	is not present in all 3 lines. By the end of each group this should not be NULL
		char curr_group_id = NULL;
		// Iterate over the current line (3rd line)
		//	and compare it to the other two previous lines
		for (int i = 0; i < strlen(line_buf); i++)
		{
			// If at this point we still have the 'curr_group_id' set, that means all
			//	lines in this group had that character meaning we can stop our search
			if (curr_group_id != NULL)
			{
				break;
			}

			// Ignore special characters
			if (line_buf[i] == '\n' || line_buf[i] == '\0')
			{
				continue;
			}

			// Iterate over the other lines in the group
			//	(We are line 3 currently, so look at lines 1 and 2)
			for (int j = 0; j < grp_size - 1; j++)
			{
				// If we are looking at a potential group id (its not null)
				//	check if it is in the current line
				//	If not in current line set id to null and go to next character
				if (curr_group_id != NULL)
				{
					if (strchr(line_grp[j], curr_group_id) == NULL)
					{
						curr_group_id = NULL;
						break;
					}
				}
				// Otherwise if there is no potential group ID currently (it IS null)
				//	check if the current line contains this character
				//	if not go to next character
				else if (strchr(line_grp[j], line_buf[i]) == NULL)
				{
					break;
				}

				// If this line contains the character, set the potential group id and check next line
				curr_group_id = line_buf[i];
			}
		}
		totalScore += get_score(curr_group_id);
		memset(line_grp, 0, sizeof(line_grp));
		lineCounter = 0;
	}

	printf("D3P2 Total Score: %d\n", totalScore);
	fclose(ptr);
	return 0;
}


