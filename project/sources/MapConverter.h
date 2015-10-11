// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/10/2015

// map converter declaration
// load map files from http://www.movingai.com/benchmarks/

#pragma once

#include "FileProcessor.h"

class MapConverter : public FileProcessor
{
private:
	unsigned int max_convert_size_;		// max map size to convert
	unsigned int mapsize_;				// real map size
	bool has_exception_;				// flag: if there's exception, set to true

public:
	// constructor
	MapConverter() : max_convert_size_(0), mapsize_(0), has_exception_(false) {}
	// destructor
	~MapConverter() {}

	// get max map size (maximum of width and height)
	unsigned int GetMapSize(void);

	// set max convert size (more than this size than do not convert)
	void SetMaxConvertSize(unsigned int max);

	// reformat map files
	void ReformatMap(void);

	// check if the map is less than max size
	bool IsMapGoodSize(void);

	// change file extension name to txt
	void ChangeFileExt(void);

	// process file
	void ProcessFile(const char *filename);
};