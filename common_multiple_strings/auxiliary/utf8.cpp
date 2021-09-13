
// Copyright of coccoc-tokenizer

#include "utf8.h"
#include <vector>
std::vector< uint32_t > to_UTF(const std::string &text)
{
	std::vector< uint32_t > codepoints;
	utf8::unchecked::iterator< std::string::const_iterator > it(text.begin()), end_it(text.end());
	while (it != end_it)
	{
		codepoints.push_back(*it);
		it++;
	}
	return codepoints;
}

std::string vector_to_string(const std::vector< uint32_t > &a)
{
	std::string res;
	for (uint32_t it : a)
	{
		utf8::append(it, std::back_inserter(res));
	}
	return res;
}
