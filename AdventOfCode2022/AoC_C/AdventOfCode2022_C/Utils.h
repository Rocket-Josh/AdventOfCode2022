#pragma once
#include <stdio.h>

extern FILE* loadfile_frompath(const char* filePath);
extern char* strndup(const char* s, size_t n);
extern void split_string(char* src, size_t index, char** outLeft, char** outRight);
extern int split_string_del(char* src, char delimiter, char** outLeft, char** outRight);
extern int get_score(char c);