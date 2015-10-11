// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/7/2015

// file processor implementation

#include <fstream>				// ifstream

#include "FileProcessor.h"

/*--------------------------------------------------------------------------*
Name:           LoadFile

Description:    Load a file.

Arguments:      filename: file name.

Returns:        true: file load successful.
				false: unable to load file.
*---------------------------------------------------------------------------*/
bool FileProcessor::LoadFile(const char *filename)
{
	filename_.assign(filename);

	std::ifstream infile(filename);

	if (!infile.is_open())
	{
		printf_s("Error: File %s is not loaded.\n", filename);
		return false;
	}

	while (!infile.eof())
	{
		while (infile.good())
		{
			std::string tmp_str;

			std::getline(infile, tmp_str);
			strlist_.emplace_back(tmp_str);
		}
	}

	printf_s("Success: File %s loaded.\n", filename);

	is_loaded_ = true;

	infile.close();

	return true;
}

/*--------------------------------------------------------------------------*
Name:           SaveFile

Description:    Save a file.

Arguments:      filename: file name.

Returns:        true: file save successful.
				false: unable to save file.
*---------------------------------------------------------------------------*/
bool FileProcessor::SaveFile(const char *filename)
{
	std::ofstream outfile(filename, std::ios_base::out);

	if (!outfile.is_open())
	{
		printf_s("Error: File %s can't be created.\n", filename);
		return false;
	}

	for (std::vector<std::string>::iterator it = strlist_.begin(); it != strlist_.end(); ++it)
	{
		outfile << *it;

		if ((it + 1) != strlist_.end())
			outfile << '\n';
	}

	outfile.close();

	return true;
}

/*--------------------------------------------------------------------------*
Name:           ClearStringList

Description:    Clear content loaded from file.

Arguments:      None.

Returns:        None.
*---------------------------------------------------------------------------*/
void FileProcessor::ClearStringList(void)
{
	strlist_.clear();
	filename_.clear();
	is_loaded_ = false;
}

/*--------------------------------------------------------------------------*
Name:           LineCount

Description:    Number of lines in content.

Arguments:      None.

Returns:        Number of lines.
*---------------------------------------------------------------------------*/
int FileProcessor::LineCount(void)
{
	return strlist_.size();
}