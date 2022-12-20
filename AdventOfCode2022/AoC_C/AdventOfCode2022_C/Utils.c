#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* loadfile_frompath(const char* filePath);
char* strndup(const char* s, size_t n);
void split_string(char* src, size_t index, char** outLeft, char** outRight);
int split_string_del(char* src, char delimiter, char** outLeft, char** outRight);
int get_score(char c);


FILE* loadfile_frompath(const char* filePath)
{
	FILE* ptr = fopen(filePath, "r");
	return ptr;
}

char* strndup(const char* s, size_t n)
{
	size_t len = strlen(s);
	if (len > n) len = n;

	char* new_str = malloc(len + 1);
	if (new_str == NULL) return NULL;

	new_str[len] = 0;
	return (char*)memcpy(new_str, s, len);
}

void split_string(char* src, size_t index, char** outLeft, char** outRight)
{
	char* left = strndup(src, index);
	char* right = strndup(src + index, strlen(src + index));

	*outLeft = left;
	*outRight = right;
}

int split_string_del(char* src, char delimiter, char** outLeft, char** outRight)
{
	size_t index = 0;

	for (int i = 0; i < strlen(src); i++)
	{
		if (src[i] != delimiter)
		{
			continue;
		}

		index = i;
		break;
	}

	char* left = strndup(src, index);
	char* right = strndup(src + index + 1, strlen(src + index));

	*outLeft = left;
	*outRight = right;

	if (left == NULL || right == NULL)
	{
		fprintf(stderr, "Failed to parse both left and right sides of delimiter ('%c')\n", delimiter);
		return 1;
	}

	return 0;
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