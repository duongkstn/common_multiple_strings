#include <iostream>
#include <cstring>
#include "suffix_tree_simple.h"
#include "utf8.h"
using namespace std;

int diff(int s, int e, int real_end) {
    if (e != -1) return e - s;
    return real_end - s;
}

void Suffix_tree_simple::walk_down(int index){
    int node = select_node();
    int difference = diff(start[node], end[node], real_end);
    if (difference < active_length) {
        active_node = node;
        active_length = active_length - difference;
        active_edge = start[child[node][input[index]]];

    } else {
        ++ active_length;
    }
}

void Suffix_tree_simple::from_string(std::vector<std::string> strings){
    number_strings = strings.size();
    end_index = new int[number_strings];
    current_node = new int[number_strings];
    result = new int[number_strings + 1];

    for (int i = 0; i < number_strings; ++ i){
        std::vector <uint32_t> codepoints = to_UTF(strings[i]);
        for (int j = 0; j < codepoints.size(); ++ j) {
            input.push_back(alphabet.map[codepoints[j]]);
            mark.push_back(i);
        }
        input.push_back(alphabet.num_pure_chars + i);
        mark.push_back(i);
        end_index[i] = input.size() - 1;
        current_node[i] = -1;
        result[i] = -1;
    }
    result[number_strings] = -1;
    child.push_back(std::unordered_map<int, int>());
    start.push_back(1);
    end.push_back(0);
    index.push_back(-1);
    suffix_link.push_back(-1);
    active_edge = -1;
    active_length = 0;
    active_node = 0;
}

int Suffix_tree_simple::select_node() {
    return child[active_node][input[active_edge]];
}

int Suffix_tree_simple::select_node(int index) {
    if (child[active_node].find(input[index]) == child[active_node].end()) // not found
        return -1;
    return child[active_node][input[index]];
}

int Suffix_tree_simple::next_char(int i) {
    int node = select_node();
    
    int difference = diff(start[node], end[node], real_end);
    if (difference >= active_length) {
        return input[start[child[active_node][input[active_edge]]] + active_length];
    }
    if (difference + 1 == active_length) {
        if (child[node].find(input[i]) != child[node].end()) return input[i];
    } else {
        active_node = node;
        active_length = active_length - difference - 1;
        active_edge = active_edge + difference + 1;
        return next_char(i);
    }
    throw "throwed";
}

void Suffix_tree_simple::build() {
    for (int i = 0; i < input.size(); ++ i) {
        int last_created_internal_node = -1;
        ++ real_end;
        ++ remaining;
        while (remaining > 0){
            if (active_length == 0) {
                int selected_node = select_node(i);
                if (selected_node != -1) {
                    active_edge = start[selected_node];
                    ++ active_length;
                    break;
                } else {
                    start.push_back(i);
                    end.push_back(-1);
                    child.push_back(unordered_map<int, int>());
                    child[0][input[i]] = start.size() - 1;
                    index.push_back(0);
                    suffix_link.push_back(-1);
                    -- remaining;
                }
            } else {
                try{
                    int ch = next_char(i);
                    if (ch == input[i]) {
                        if (last_created_internal_node != -1) suffix_link[last_created_internal_node] = select_node();
                        walk_down(i);
                        break;
                    } else {
                        int node = select_node();
                        int old_start = start[node];
                        start[node] = old_start + active_length;
                        start.push_back(old_start);
                        end.push_back(old_start + active_length - 1);
                        child.push_back(unordered_map<int, int>());
                        index.push_back(-1); // internal
                        suffix_link.push_back(-1);
                        int new_internal_node = start.size() - 1;

                        start.push_back(i);
                        end.push_back(-1);
                        child.push_back(unordered_map<int, int>());
                        index.push_back(0); // leaf
                        suffix_link.push_back(-1);
                        int new_leaf_node = start.size() - 1;

                        child[new_internal_node][input[start[new_internal_node] + active_length]] = node;
                        child[new_internal_node][input[i]] = new_leaf_node;
                        child[active_node][input[start[new_internal_node]]] = new_internal_node;
                        if (last_created_internal_node != -1) {
                            suffix_link[last_created_internal_node] = new_internal_node;
                        }
                        last_created_internal_node = new_internal_node;
                        suffix_link[new_internal_node] = 0;
                        if (active_node != 0) {
                            active_node = suffix_link[active_node];
                        } else {
                            ++ active_edge;
                            -- active_length;
                        }
                        -- remaining;
                    }
                } catch (const char *msg) {
                    int node = select_node();
                    start.push_back(i);
                    end.push_back(-1);
                    child.push_back(unordered_map<int, int>());
                    index.push_back(0);
                    suffix_link.push_back(-1);
                    int new_node = start.size() - 1;

                    child[node][input[i]] = new_node;
                    if (last_created_internal_node != -1){
                        suffix_link[last_created_internal_node] = node;
                    }
                    last_created_internal_node = node;
                    if (active_node != 0) active_node = suffix_link[active_node];
                    else {
                        ++ active_edge;
                        -- active_length;
                    }
                    -- remaining;
                }
            }
        }
    }
    
}
void Suffix_tree_simple::init_array() {
    int total_nodes = index.size();
    num_leaf = new int[total_nodes];
    string_link = new int[total_nodes];
    for (int i = 0; i < total_nodes; ++ i) {
        num_leaf[i] = 0;
        string_link[i] = -1;
    }
    
}

void Suffix_tree_simple::set_index_dfs(int node, int size) {
    if (end[node] == -1) end[node] = size - 1;
    if (index[node] != -1) { // is leaf
        index[node] = node_count;
        if (mark[start[node]] != mark[end[node]]) {// start and end belongs to different strings
            end[node] = end_index[mark[start[node]]];
        }
        if (current_node[mark[start[node]]] == -1) {
            current_node[mark[start[node]]] = node;
        } else if (mark[start[node]] != -1) {
            string_link[node] = current_node[mark[start[node]]];
            current_node[mark[start[node]]] = node;
        }
        num_leaf[node] = 1;
        return;
    }
    index[node] = node_count;
    for (auto &it: child[node]) {
        int child_node = it.second;
        ++ node_count;
        set_index_dfs(child_node, size);
        num_leaf[node] += num_leaf[child_node];
    }
}

void Suffix_tree_simple::free_mem_dfs() {
    delete [] current_node;
    delete [] end_index;

    int total_nodes = index.size();
    ancestor = new int[total_nodes];
    parent = new int[total_nodes];
    size = new int[total_nodes];
    h = new int[total_nodes];
    c = new int[total_nodes];
    for (int i = 0; i < total_nodes; ++ i) {
        ancestor[i] = -1;
        parent[i] = 0;
        size[i] = 0;
        h[i] = 0;
        c[i] = 0;
    }
}

int Suffix_tree_simple::find_set(int v) {
    if (index[v] == index[parent[v]])
        return v;
    int u= find_set(parent[v]);
    return u;
}
void Suffix_tree_simple::make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

void Suffix_tree_simple::union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (index[a] != index[b]) {
        if (size[a] < size[b])
            std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

void Suffix_tree_simple::lca(int node) {
    ancestor[node] = node;
    make_set(node);
    for (auto &it: child[node]) {
        int child_node = it.second;
        lca(child_node);
        union_sets(node, child_node);
        ancestor[find_set(node)] = node;
    }

    if (string_link[node] != -1) {
        int v = ancestor[find_set(string_link[node])];
        ++ h[v];

    }
}
void Suffix_tree_simple::free_mem_lca() {
    delete [] ancestor;
    delete [] size;
    delete [] parent;
    delete [] string_link;
    int total_nodes = index.size();
    length_from_root = new int[total_nodes];
    result_link = new int[total_nodes];
    for (int i = 0; i < total_nodes; ++ i) {
        length_from_root[i] = 0;
        result_link[i] = -1;
    }

}

void  Suffix_tree_simple::cal_c(int node) {
    for (auto &it: child[node]) {
        int child_node = it.second;
        length_from_root[child_node] = length_from_root[node] + (end[child_node] - start[child_node] + 1);
        cal_c(child_node);
        h[node] += h[child_node];
        
    }
    c[node] = num_leaf[node] - h[node];
    if (result[c[node]] == -1) {
        result[c[node]] = node;
        result_link[node] = -1;
    } else {
        result_link[node] = result[c[node]];
        result[c[node]] = node;

    }
}


std::vector<std::string> Suffix_tree_simple::query(int i) {
    int u = result[i];
    std::vector<std::string> res;
    if (i > 0 && u != -1) {
        while (u != -1) {
            if (index[u] != 0) { // root
                std::vector< uint32_t > vec;
                for (int index_char = end[u] - length_from_root[u] + 1; index_char <= end[u]; ++ index_char) {
                    if (alphabet.reverse_map.find(input[index_char]) != alphabet.reverse_map.end()) 
                    {
                        vec.push_back(alphabet.reverse_map[input[index_char]]);
                    }
                }
                std::string s = vector_to_string(vec);
                if (s.length() > 0) res.push_back(s);
            }
            u = result_link[u];
        }
    }
    return res;
}
