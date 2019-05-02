#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NODE Node<T>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <iostream>

enum class FILESTATUS : int {
	SAVE_,
	LOAD_,
};

enum class SELECT : int {
	EXIT,
	CREATE,
	INSERT,
	DELETE,
	SEARCH_AND_MODIFY,
	SAVE,
	LOAD,
	PRINT,
	SAMPLEDATA,
	NONE


};