// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/7/2015

// file processor declaration

// load text file and put content into strlist_

#pragma once

#include <vector>
#include <string>

class FileProcessor
{
protected:
	// loaded filename
	std::string filename_;
	// content of the file
	std::vector <std::string> strlist_;
	// flag to check if there's file loaded
	bool  is_loaded_;

public:
	// constructor
	FileProcessor() : is_loaded_(false) {}
	// destructor
	~FileProcessor() {}

	// load a file
	bool LoadFile(const char *filename);

	// save a file
	bool SaveFile(const char *filename);

	// clear content loaded from file
	void ClearStringList(void);

	// number of lines in content
	int LineCount(void);
};