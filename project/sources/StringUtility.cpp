// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 12/1/2015

// string utility library implementation

/******************************************************************************
Assumption:

I would like to convert map files from Pathfinding Benchmarks at Moving AI Lab 
to the format that can be used for pathfinding project in Game AI course. So
this utility deals with tokenizing the string into several substrings, and 
replacing characters for string. But I also want to make the utility more
general so I can reuse it for other tasks.

The input map is a text file which the first few lines contains the map
information. The map itself has terrain, out of bounds, tree, swamp and water.
The output file format has the first line as map width and height, and there
are only terrain and wall for the map.

Goal for the tool:

1. Tokenize a given string to get substring I want (such as width/height).
2. Replace one or more characters to one other character (map multiple to one).
3. To make it more general. Make it to support character replacement and string
   replacement.
   
Approach:

The task is divided into 3 parts -
1. Separate string into words.
2. Find character or word in a string.
3. Replace character or word in a string.
4. For future use, have a helper function to make character uppercase or lowercase.
******************************************************************************/

#include "StringUtility.h"

namespace StringUtility
{
	/*--------------------------------------------------------------------------*
	Name:           CompareChar

	Description:    Check if ch equals to any of the character in seperate_char list.

	Arguments:      ch: first character to be compared.
					seperate_char: list of second characters to be compared.

	Returns:        true: ch matches any character in seperate_char list.
					false: ch doesn't match any character in seperate_char list.
	*---------------------------------------------------------------------------*/
	bool CompareChar(const char ch, const std::vector<char> &seperate_char)
	{
		// if seperate_char list is empty, no match possible
		if (seperate_char.empty())
			return false;

		for (std::vector<char>::const_iterator it = seperate_char.begin(); it != seperate_char.end(); ++it)
		{
			if (ch == *it)
				return true;
		}

		return false;
	}

	/*--------------------------------------------------------------------------*
	Name:           SimpleTokenizer

	Description:    Seperate a string with words by seperate_char.

	Arguments:      str: input string.
					seperate_char: character used to seperate string.

	Returns:        Tokens list.
	*---------------------------------------------------------------------------*/
	std::vector<std::string> SimpleTokenizer(const std::string &str, const char seperate_char)
	{
		// return vector of words
		std::vector<std::string> vec;

		if (str.empty())
			return vec;

		std::string tmpstr;

		// go through the string, push each char onto tmpstr
		// then push tmpstr onto vec if any char from seperate_char list is found
		// when at the end of the string, if there's char in tmpstr, push it

		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
		{
			if (*it == seperate_char)
			{
				if (!tmpstr.empty())
				{
					vec.push_back(tmpstr);
					tmpstr.clear();
				}
			}
			else
				tmpstr.push_back(*it);
		}

		if (!tmpstr.empty())
			vec.push_back(tmpstr);

		return vec;
	}

	/*--------------------------------------------------------------------------*
	Name:           SimpleTokenizer

	Description:    Seperate a string with words by characters in seperate_char list.

	Arguments:      str: input string.
					seperate_char: list of characters used to seperate string.

	Returns:        Tokens list.
	*---------------------------------------------------------------------------*/
	std::vector<std::string> SimpleTokenizer(const std::string &str, const std::vector<char> &seperate_char)
	{
		// return vector of words
		std::vector<std::string> vec;

		if (str.empty())
			return vec;

		std::string tmpstr;

		// go through the string, push each char onto tmpstr
		// then push tmpstr onto vec if any char from seperate_char list is found
		// when at the end of the string, if there's char in tmpstr, push it

		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
		{
			if (CompareChar(*it, seperate_char))
			{
				if (!tmpstr.empty())
				{
					vec.push_back(tmpstr);
					tmpstr.clear();
				}
			}
			else
				tmpstr.push_back(*it);
		}

		if (!tmpstr.empty())
			vec.push_back(tmpstr);

		return vec;
	}

	/*--------------------------------------------------------------------------*
	Name:           Uppercase

	Description:    Convert a string to uppercase.

	Arguments:      str: input string.

	Returns:        None.
	*---------------------------------------------------------------------------*/
	void Uppercase(std::string &str)
	{
		if (str.empty())
			return;

		std::string::iterator it;

		// if the char in a string is lower case, makes it upper case
		for (it = str.begin(); it != str.end(); ++it)
		{
			if ((*it >= 'a') && (*it <= 'z'))
				*it -= SPACE;
		}
	}

	/*--------------------------------------------------------------------------*
	Name:           Lowercase

	Description:    Convert a string to lowercase.

	Arguments:      str: input string.

	Returns:        None.
	*---------------------------------------------------------------------------*/
	void Lowercase(std::string &str)
	{
		if (str.empty())
			return;

		std::string::iterator it;

		// if the char in a string is lower case, makes it upper case
		for (it = str.begin(); it != str.end(); ++it)
		{
			if ((*it >= 'A') && (*it <= 'Z'))
				*it += SPACE;
		}
	}

	/*--------------------------------------------------------------------------*
	Name:           SearchChar

	Description:    Search character within a given string from certain index.

	Arguments:      str: input string.
					start_index: where to start search.
					ch: character to be searched.
					index: return the first index of the word.

	Returns:        true: character found.
					false: character not found.
	*---------------------------------------------------------------------------*/
	bool SearchChar(const std::string &str, unsigned int start_index, const char ch, unsigned int &index)
	{
		if (str.empty())
			return false;

		unsigned int size = str.size();

		if (start_index >= size)
			return false;

		for (unsigned int i = start_index; i < str.size(); ++i)
		{
			if (str[i] == ch)
			{
				index = i;
				return true;
			}

		}

		return false;
	}

	/*--------------------------------------------------------------------------*
	Name:           SearchWord

	Description:    Search word within a given string from certain index.

	Arguments:      str: input string.
					start_index: where to start search.
					word: word to be searched.
					word_size: size of the word.
					index: return the first index of the word.

	Returns:        true: word found.
					false: word not found.
	*---------------------------------------------------------------------------*/
	bool SearchWord(const std::string &str, unsigned int start_index, const char *word, unsigned int word_size, unsigned int &index)
	{
		if (str.empty())
			return false;

		unsigned int size = str.size();

		if (start_index >= size)
			return false;


		// for each char of the string, compare i+j'th char with j'th char of the word
		// if they match and j is the last index of the word, return true
		// otherwise, no match found

		for (unsigned int i = start_index; i < size; ++i)
		{
			for (unsigned int j = 0; j < word_size; ++j)
			{
				unsigned int tmp_index = i + j;

				if ((tmp_index < size) && (str[tmp_index] == word[j]))
				{
					if (j == (word_size - 1))
					{
						index = i;
						return true;
					}
				}
				else
					break;
			}
		}

		return false;
	}

	/*--------------------------------------------------------------------------*
	Name:           CharReplace

	Description:    Swap char1 from a given string to word2

	Arguments:      str: input string.
					ch1: word to be searched.
					word2: word that replaces word1.

	Returns:        None.
	*---------------------------------------------------------------------------*/
	void CharReplace(std::string &str, const char ch1, const char *word2)
	{
		if (str.empty())
			return;

		int size = str.size();

		for (int i = 0; i < size; ++i)
		{
			unsigned int tmp_index = 0;

			if (SearchChar(str, i, ch1, tmp_index))
				str.replace(tmp_index, 1, word2);
		}
	}

	/*--------------------------------------------------------------------------*
	Name:           StringReplace

	Description:    Swap word1 from a given string to word2.

	Arguments:      str: input string.
					word1: word to be searched.
					word1_size: size of the word1.
					word2: word that replaces word1.

	Returns:        None.
	*---------------------------------------------------------------------------*/
	void StringReplace(std::string &str, const char *word1, unsigned int word1_size, const char *word2)
	{
		if (str.empty())
			return;

		int size = str.size();

		for (int i = 0; i < size; ++i)
		{
			unsigned int tmp_index = 0;

			if (SearchWord(str, i, word1, word1_size, tmp_index))
				str.replace(tmp_index, word1_size, word2);
		}
	}
}

/******************************************************************************
Unit tests:

1. Input: "", separate character: 1  =>  Output: ""
2. Input: "abcde1fghij", separate character: 1, uppercase  
          =>  Output: "ABCDE" and "FGHIJ"
3. Input: "DigiPen Institute of Technology.", separate character: ' ', lowercase, 
          replace i to 1  =>  Output: "d1g1pen", "1nst1tute", "technology"
4. Dragon Age - Origin: compat.map (. to 0, T to 1)
5. Dragon Age - Origin: den204d.map (. to 0, T and @ to 1)
6. for entire project, tested all maps less than 256 width and 256 height.
******************************************************************************/
