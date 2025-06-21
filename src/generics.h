#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>

using std::vector;
using std::string;
using std::unordered_map;
using std::set;
using std::pair;
using std::to_string;
using std::cout;
using std::endl;

typedef unordered_map<string, vector<vector<string>>> Grammar;
typedef unordered_map<int, pair<string, vector<string>>> RuleNumberMp;
typedef unordered_map<string, set<string>> FirstFollowSet;
typedef unordered_map<int, unordered_map<string, string>> GotoTableStore;

#ifndef generics_h
#define generics_h

inline bool isNonTerminal(string token){
    return token[0] >= 'A' && token[0] <= 'Z';
}

#endif // generics_h