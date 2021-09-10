#ifndef ALPHABET_H
#define ALPHABET_H
#include <unordered_map>
class Alphabet {
    public:
        std::unordered_map<uint32_t, int> map;
        std::unordered_map<int, uint32_t> reverse_map;
        int num_pure_chars;
        Alphabet();
};

#endif