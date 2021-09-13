#ifndef SUFFIX_TREE_SIMPLE_H
#define SUFFIX_TREE_SIMPLE_H

#include "alphabet.h"
#include <string>
#include <unordered_map>
#include <vector>

class Suffix_tree_simple
{
public:
	Alphabet alphabet;
	int number_strings;
	std::vector< std::unordered_map< int, int > > child;
	std::vector< int > start;
	std::vector< int > end;
	std::vector< int > index;
	std::vector< int > suffix_link;
	int *length_from_root;
	int *num_leaf;
	int *h;
	int *c;
	int *string_link;
	int *ancestor;
	int *parent;
	int *result_link;
	int *size;
	int remaining;
	int real_end;
	int node_count;
	std::vector< int > input;
	std::vector< int > mark;
	int *end_index;
	int *current_node;
	int *result;

	int active_edge;
	int active_length;
	int active_node;

public:
	Suffix_tree_simple() : remaining(0), real_end(-1), node_count(0){};
	void from_string(std::vector< std::string > strings);
	void walk_down(int i);
	int select_node();
	int select_node(int index);
	int next_char(int i);
	void build();
	void init_array();
	void set_index_dfs(int node, int size);
	void free_mem_dfs();
	int find_set(int v);
	void make_set(int v);
	void union_sets(int a, int b);
	void lca(int node);
	void free_mem_lca();
	void cal_c(int node);
	std::vector< std::string > query(int i);
	int length_longest_substring(int i);
	std::vector< std::string > filter_substrings_by_length(int i, int length_input);
};

#endif