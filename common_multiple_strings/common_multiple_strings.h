#ifndef COMMON_MULTIPLE_STRINGS_H
#define COMMON_MULTIPLE_STRINGS_H
#include "auxiliary/suffix_tree_simple.h"
#include <iostream>
#include <vector>

class Common_multiple_strings
{
public:
	int number_strings;
	Suffix_tree_simple tree;
	Common_multiple_strings(){};
	void from_path(std::string &path);
	void from_strings(std::vector< std::string > strings);
	void build();
	std::vector< std::string > query(int k);
	int length_longest_substring(int i);
	std::vector< std::string > filter_substrings_by_length(int i, int length_input);
};

#endif