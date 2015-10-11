// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/9/2015

// map converter implementation
// load map files from http://www.movingai.com/benchmarks/

#include <cassert>
#include <iostream>

#include "MapConverter.h"
#include "StringUtility.h"

/*--------------------------------------------------------------------------*
Name:           GetMapSize

Description:    Get max map size (maximum of width and height).

Arguments:      None.

Returns:        Maximum value of width and height.
*---------------------------------------------------------------------------*/
unsigned int MapConverter::GetMapSize(void)
{
	assert(is_loaded_ && "No file loaded!");

	try
	{
		// get tokens from 2nd line (height #number)
		std::vector<std::string> tokens = StringUtility::SimpleTokenizer(strlist_[1], ' ');
		int height = std::stoi(tokens[1]);
		// get tokens from 3nd line (width #number)
		tokens = StringUtility::SimpleTokenizer(strlist_[2], ' ');
		int width = std::stoi(tokens[1]);

		return (unsigned int)(height > width ? height : width);
	}
	catch (const std::invalid_argument& ia)
	{
		std::cerr << "Invalid argument: " << ia.what() << '\n';

		return 0;
	}
}

/*--------------------------------------------------------------------------*
Name:           SetMaxConvertSize

Description:    Set max convert size (more than this size than do not convert)

Arguments:      None.

Returns:        Maximum value of width and height.
*---------------------------------------------------------------------------*/
void MapConverter::SetMaxConvertSize(unsigned int max)
{
	max_convert_size_ = max;
}

/*--------------------------------------------------------------------------*
Name:           ReformatMap

Description:    Reformat map files.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
void MapConverter::ReformatMap(void)
{
	// map format: http://www.movingai.com/benchmarks/formats.html
	// new format is to remove all begin lines, put size as first line, empty second line
	// then all passable terrains are "0 ", and obstacles are "-1 "

	assert(is_loaded_ && "No file loaded!");

	strlist_[0].assign(std::to_string(mapsize_));			// map size
	strlist_.erase(strlist_.begin() + 1);					// remove height
	strlist_.erase(strlist_.begin() + 1);					// remove width
	strlist_[1].clear();									// one empty line

	for (unsigned int i = 1; i < strlist_.size(); ++i)
	{
		StringUtility::CharReplace(strlist_[i], '.', "0 ");
		StringUtility::CharReplace(strlist_[i], 'G', "0 ");
		StringUtility::CharReplace(strlist_[i], 'S', "0 ");
		StringUtility::CharReplace(strlist_[i], '@', "-1 ");
		StringUtility::CharReplace(strlist_[i], 'O', "-1 ");
		StringUtility::CharReplace(strlist_[i], 'T', "-1 ");
		StringUtility::CharReplace(strlist_[i], 'W', "-1 ");
	}
}

/*--------------------------------------------------------------------------*
Name:           IsMapGoodSize

Description:    Check if the map is less than max size.

Arguments:      None.

Returns:        true: map size is smaller or equalthan max.
				false: map size is bigger than max.
*---------------------------------------------------------------------------*/
bool MapConverter::IsMapGoodSize(void)
{
	assert(is_loaded_ && "No file loaded!");

	// if not specify max size, no check
	if (max_convert_size_ == 0)
		return true;

	if (mapsize_ <= max_convert_size_)
		return true;
	
	return false;
}

/*--------------------------------------------------------------------------*
Name:           ChangeFileExt

Description:    Add map size and change extension to txt from filename.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
void MapConverter::ChangeFileExt(void)
{
	assert(is_loaded_ && "No file loaded!");

	// format: "_(size).txt"
	std::string str = std::to_string(mapsize_);
	str.insert(str.begin(), '_');
	str.append(".txt");

	filename_.replace(filename_.size() - 4, 4, str);
}

/*--------------------------------------------------------------------------*
Name:           ProcessFile

Description:    Process file.

Arguments:      filename: file to process.

Returns:        None.
*---------------------------------------------------------------------------*/
void MapConverter::ProcessFile(const char *filename)
{
	// load file, set map size from height/width line
	// if map isn't too large, reformat the file content, add size and .txt to filename
	// and save the file

	LoadFile(filename);

	mapsize_ = GetMapSize();

	if (IsMapGoodSize())
	{
		ReformatMap();
		ChangeFileExt();
		SaveFile(filename_.c_str());
	}
	else
	{
		printf("Map too large.\n");
	}
}