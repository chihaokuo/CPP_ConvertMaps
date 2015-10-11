// Author: Chi-Hao Kuo
// Created: 10/7/2015
// Updated: 10/9/2015

// string utility library declaration

#pragma once

#include <string> // string
#include <vector> // vector

namespace StringUtility
{
	static const char SPACE = ' ';

	// check if ch equals to any of the character in seperate_char list 
	bool CompareChar(const char ch, const std::vector<char> &seperate_char);

	// seperate a string with words by seperate_char
	std::vector<std::string> SimpleTokenizer(const std::string &str, const char seperate_char);
	// seperate a string with words by characters in seperate_char list
	std::vector<std::string> SimpleTokenizer(const std::string &str, const std::vector<char> &seperate_char);

	// convert a string to uppercase
	void Uppercase(std::string &str);

	// convert a string to lowercase
	void Lowercase(std::string &str);

	// search character within a given string from certain index
	bool SearchChar(const std::string &str, unsigned int start_index, const char ch, unsigned int &index);

	// search word within a given string from certain index
	bool SearchWord(const std::string &str, unsigned int start_index, const char *word, unsigned int word_size, unsigned int &index);

	// swap char1 from a given string to word2
	void CharReplace(std::string &str, const char ch1, const char *word2);

	// swap word1 from a given string to word2
	void StringReplace(std::string &str, const char *word1, unsigned int word1_size, const char *word2);
}