#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

class telephone
{
	char** names;
	char** numbers;

	int capacity = INIT_CAPACITY;
	int n = 0;

public:
	void init_directory();
	void process_command();
	int read_line(char[], int);

	void load(char*);
	void add(char*, char*);
	void status();
	void find(char*);
	int search(char*);
	void remove(char*);
	void save(char*);

	void reallocate();
};

