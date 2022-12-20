#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

void DayThree_PartOne();
void DayThree_PartTwo();
int get_score();

int main()
{
	DayThree_PartOne();
}

FILE* LoadDayThreeFile(char* filePath)
{

	FILE* ptr = fopen(filePath, "r");

	return ptr;
}

char* strndup(const char* s, size_t n)
{
	size_t len = strlen(s);
	if (len > n) len = n;

	char* new_str = malloc(len+1);
	if (new_str == NULL) return NULL;

	new_str[len] = 0;
	return (char *)memcpy(new_str, s, len);
}

void split_string(char* src, size_t index, char** outLeft, char** outRight)
{
	char* left = strndup(src, index);
	char* right = strndup(src + index, strlen(src + index));

	*outLeft = left;
	*outRight = right;
}

void DayThree_PartOne()
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

	FILE* ptr = LoadDayThreeFile(filePath);

	if (!ptr)
	{
		printf("Failed to open file");
		return;
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
}


int get_score(char c)
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

