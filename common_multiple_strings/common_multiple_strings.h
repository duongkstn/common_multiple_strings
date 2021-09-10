#ifndef COMMON_MULTIPLE_STRINGS_H
#define COMMON_MULTIPLE_STRINGS_H
#include <vector>
#include <iostream>
#include "auxiliary/suffix_tree_simple.h"

class Common_multiple_strings {
    public:
        int number_strings;
        Suffix_tree_simple tree;
        Common_multiple_strings() {};
        void from_path(std::string &path);
        void from_strings(std::vector<std::string> strings);
        void build();
        std::vector<std::string> query(int k);
};


#endif