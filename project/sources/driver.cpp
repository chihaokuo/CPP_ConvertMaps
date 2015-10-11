// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/10/2015

// driver for map converter program

#include "MapConverter.h"
#include "StringUtility.h"

#include <iostream>

/*--------------------------------------------------------------------------*
Name:           main

Description:    Main function.

Arguments:      argc: number of argument.
				argv: each arguments.

Returns:        0.
*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		MapConverter file;

		if (argc > 2)
			file.SetMaxConvertSize(std::atoi(argv[2]));

		file.ProcessFile(argv[1]);
	}
	else
	{
		printf_s("Usage: ConvertMaps.exe filename <max_size>\n");
		printf_s("where: filename - file to process.\n");
		printf_s("where: max_size - max height/width of map size.\n");
	}

	return 0;
}