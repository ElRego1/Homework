// Copyright 2019 Luca Istrate, Danut Matei
#include "./aegraph.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include <cassert>
std::string strip(std::string s) {
    // deletes whitespace from the beginning and end of the string
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}
std::pair<std::string, std::string> split_first(std::string s,
char delimiter = ',') {
    // returns a pair that contains: <first_cut, rest_of_graph>

    int numOpen = 0;

    int len = s.size();
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == delimiter && numOpen == 0)
            return std::make_pair(
                    strip(s.substr(0, i)), strip(s.substr(i+1, len)));
        if (c == '[')
            numOpen += 1;
        if (c == ']')
            numOpen -= 1;
    }

    return {strip(s), std::string()};
}
std::vector<std::string> split_level(std::string s, char delimiter = ',') {
    // splits 's' into separate entities (atoms, subgraphs)

    std::vector<std::string> result;
    auto snd = s;
    while (true) {
        auto p = split_first(snd, delimiter);
        auto fst = p.first;
        snd = p.second;

        result.push_back(fst);

        if (snd.empty())
            return result;
    }
}
int AEGraph::num_subgraphs() const {
    return subgraphs.size();
}
int AEGraph::num_atoms() const {
    return atoms.size();
}
int AEGraph::size() const {
    return num_atoms() + num_subgraphs();
}
bool AEGraph::operator<(const AEGraph& other) const {
    return this->repr() < other.repr();
}
bool AEGraph::operator==(const AEGraph& other) const {
    return this->repr() == other.repr();
}
bool AEGraph::operator!=(const AEGraph& other) const {
    return this->repr() != other.repr();
}
AEGraph AEGraph::operator[](const int index) const {
    // offers an easier way of accessing the nested graphs
    if (index < num_subgraphs()) {
        return subgraphs[index];
    }

    if (index < num_subgraphs() + num_atoms()) {
        return AEGraph('(' + atoms[index - num_subgraphs()] + ')');
    }

    return AEGraph("()");
}
std::ostream& operator<<(std::ostream &out, const AEGraph &g) {
    out << g.repr();
    return out;
}
AEGraph::AEGraph(std::string representation) {
    // constructor that creates an AEGraph structure from a
    // serialized representation
    char left_sep = representation[0];
    char right_sep = representation[representation.size() - 1];

    assert((left_sep == '(' && right_sep == ')')
        || (left_sep == '[' && right_sep == ']'));

    // if the left separator is '(' then the AEGraph is the entire
    // sheet of assertion
    if (left_sep == '(') {
        is_SA = true;
    } else {
        is_SA = false;
    }

    // eliminate the first pair of [] or ()
    representation = representation.substr(1, representation.size() - 2);

    // split the graph into separate elements
    auto v = split_level(representation);
    // add them to the corresponding vector
    for (auto s : v) {
        if (s[0] != '[') {
            atoms.push_back(s);
        } else {
            subgraphs.push_back(AEGraph(s));
        }
    }

    // also internally sort the new graph
    this->sort();
}
std::string AEGraph::repr() const {
    // returns the serialized representation of the AEGraph

    std::string left, right;
    if (is_SA) {
        left = '(';
        right = ')';
    } else {
        left = '[';
        right = ']';
    }

    std::string result;
    for (auto subgraph : subgraphs) {
        result += subgraph.repr() + ", ";
    }

    int len = atoms.size();
    if (len != 0) {
        for (int i = 0; i < len - 1; i++) {
            result += atoms[i] + ", ";
        }
        result += atoms[len - 1];
    } else {
        if (subgraphs.size() != 0)
            return left + result.substr(0, result.size() - 2) + right;
    }

    return left + result + right;
}
void AEGraph::sort() {
    std::sort(atoms.begin(), atoms.end());

    for (auto& sg : subgraphs) {
        sg.sort();
    }

    std::sort(subgraphs.begin(), subgraphs.end());
}
bool AEGraph::contains(const std::string other) const {
    // checks if an atom is in a graph
    if (find(atoms.begin(), atoms.end(), other) != atoms.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}
bool AEGraph::contains(const AEGraph& other) const {
    // checks if a subgraph is in a graph
    if (find(subgraphs.begin(), subgraphs.end(), other) != subgraphs.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}
std::vector<std::vector<int>> AEGraph::get_paths_to(const std::string other)
    const {
    // returns all paths in the tree that lead to an atom like <other>
    std::vector<std::vector<int>> paths;

    int len_atoms = num_atoms();
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_atoms; i++) {
        if (atoms[i] == other && size() > 1) {
            paths.push_back({i + len_subgraphs});
        }
    }

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i].contains(other)) {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }

    return paths;
}
std::vector<std::vector<int>> AEGraph::get_paths_to(const AEGraph& other)
    const {
    // returns all paths in the tree that lead to a subgraph like <other>
    std::vector<std::vector<int>> paths;
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i] == other && size() > 1) {
            paths.push_back({i});
        } else {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }

    return paths;
}

// @Copyright Lica Robert-Mihai & Popescu Diana-Elena
// email: licarobert21@gmail.com

// S recursive function to go deep in the graph and is specialized in finding
// possible doublecuts
void AEGraph::recursiv_possible_double_cuts(std::vector<std::vector<int>> &info,
  char past_ok, std::vector<int> &parcurgere, unsigned int& pos_info) const {
    // past_ok checks if we have found consecutive edges that can be double cut
    if (past_ok) {
        int temp = parcurgere.back();
        parcurgere.pop_back();
        info.resize(pos_info + 1);
        info[pos_info] = parcurgere;
        ++pos_info;
        parcurgere.push_back(temp);
    }
    if (subgraphs.size() > 1) {
        // gets through all subgraphs
        for (unsigned int i = 0; i < subgraphs.size(); ++i) {
            parcurgere.push_back(i);
            subgraphs[i].recursiv_possible_double_cuts(info, 0,
                parcurgere, pos_info);
            parcurgere.pop_back();
        }
    } else if (subgraphs.size() == 1 && num_atoms() == 0) {
        // if only one subgraph and no atoms
        parcurgere.push_back(0);
        subgraphs[0].recursiv_possible_double_cuts(info, 1, parcurgere,
            pos_info);
        parcurgere.pop_back();
    }
}
std::vector<std::vector<int>> AEGraph::possible_double_cuts() const {
    std::vector<std::vector<int>> info;
    std::vector<int> parcurgere;
    unsigned int pos_info = 0;
    for (unsigned int i = 0; i < subgraphs.size(); i++) {
      parcurgere.push_back(i);
      // get through all the graph using recursive function
      subgraphs[i].recursiv_possible_double_cuts(info, 0, parcurgere, pos_info);
      parcurgere.pop_back();
    }
    return info;
}

AEGraph AEGraph::double_cut(std::vector<int> where) const {
    AEGraph m = *this;
    AEGraph *tmp = &m;
    AEGraph *p;
    for (unsigned int i = 0; i < where.size() - 1; i++) {
        // iterate to get 1 edge away from edge to delete
        tmp = &(tmp -> subgraphs[where[i]]);
    }
    p = &(tmp -> subgraphs[where[where.size() - 1]].subgraphs[0]);
    // attach back all the subgraphs && atoms
    for (unsigned int i = 0; i < p -> subgraphs.size(); i++) {
        tmp -> subgraphs.push_back(p -> subgraphs[i]);
    }
    for (unsigned int i = 0; i < p -> atoms.size(); i++) {
        tmp -> atoms.push_back(p -> atoms[i]);
    }
    // delete the redundant subgraph
    tmp -> subgraphs.erase(tmp -> subgraphs.begin() + where[where.size() - 1]);
    return m;
}

// puts the indexes in a path
void AEGraph::put_in_info(std::vector<std::vector<int>> &info) const{
    for (int i = 0; i < num_subgraphs(); ++i) {
        info.push_back({i});
    }
    for (int i = 0; i < num_atoms(); ++i) {
        info.push_back({i + num_subgraphs()});
    }
}
std::vector<std::vector<int>> AEGraph::possible_erasures(int level) const {
    std::vector<std::vector<int>> info;
    if (level == -1) {
        level = 0;
        this -> put_in_info(info);
    } else if (!(level % 2)) {
        if (num_atoms() + num_subgraphs() > 1) {
            this -> put_in_info(info);
        }
    }
    for (int i = 0; i < num_subgraphs(); ++i) {
        auto r = subgraphs[i].possible_erasures(level + 1);
        for (auto& v : r)
        v.insert(v.begin(), i);
        copy(r.begin(), r.end(), back_inserter(info));
    }
    return info;
}

// a recursive function to go deep in the graph and make deletions
void AEGraph::go_deep_and_erase(std::vector<int> where, unsigned int &index) {
    ++index;
    if (index < where.size() - 1) {
        // get 1 edge above what needs to be deleted
       subgraphs[where[index]].go_deep_and_erase(where, index);
    } else {
        if (where.back() + 1 <= num_subgraphs()) {
            // if there are any subgraphs
            subgraphs.erase(subgraphs.begin() + where.back());
        } else {
            // if there are atoms
            atoms.erase(atoms.begin() + where.back() - subgraphs.size());
        }
    }
}
AEGraph AEGraph::erase(std::vector<int> where) const {
    AEGraph p = *this;
    unsigned int index = 0;
    // if graph is empty, return graph
    if (p.subgraphs.size() == 0 && p.atoms.size() == 0) {
        return p;
    }
    if (where.size() > 1) {
        p.subgraphs[where[0]].go_deep_and_erase(where, index);
    } else {
        // if where is 1 => we are already where we need to delete
        if (where.back() + 1 <= num_subgraphs()) {
           p.subgraphs.erase(p.subgraphs.begin() + where.back());
        } else {
           p.atoms.erase(p.atoms.begin() + where[0] - p.subgraphs.size());
        }
    }
    return p;
}

std::vector<std::vector<int>> AEGraph::possible_deiterations() const {
    std::vector<std::vector<int>> rezultat, temp;
    for (unsigned int i = 0; i < atoms.size(); ++i) {
        for (unsigned int j = 0; j < subgraphs.size(); ++j) {
            if (subgraphs[j].contains(atoms[i])) {
                temp = subgraphs[j].get_paths_to(atoms[i]);
                for (unsigned int k = 0; k < temp.size(); ++k) {
                    temp[k].insert(temp[k].begin(), j);
                    rezultat.push_back(temp[k]);
                }
            }
        }
    }

    for (unsigned int i = 0; i < subgraphs.size(); ++i) {
        for (unsigned int j = 0; j < subgraphs.size(); ++j) {
            if (i != j) {
                if (subgraphs[j].contains(subgraphs[i])) {
                    temp = subgraphs[j].get_paths_to(subgraphs[i]);
                    for (unsigned int k = 0; k < temp.size(); ++k) {
                        temp[k].insert(temp[k].begin(), j);
                        rezultat.push_back(temp[k]);
                    }
                }
            }
        }
    }

    return rezultat;
}

AEGraph AEGraph::deiterate(std::vector<int> where) const {
    AEGraph p = *this;
    unsigned int index = 0;
    p.subgraphs[where[0]].go_deep_and_erase(where, index);

    return p;
}
