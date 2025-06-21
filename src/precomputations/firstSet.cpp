#include "../generics.h"

/*
    Approach:
        For every production 2 cases can arrive:
            1. The current leftmost part of prodBody is a terminal
            2. The current leftmost part of prodBody is a non terminal
        
            For case 1:
                This is a straight forward case where the terminal is the first symbol of the prodHead
            For case 2:
                Here again 2 cases can arrive:
                    1. There is no epsilon in the first set of the non terminal
                        Then everything in the first set of non terminal is added to the first set of prodHead
                    2. There is epsilon in the first set of the non terminal
                        Then everything in the first set of the non terminal is added to the first set of prodHead and the pointer is proceeded to the next subPart of prodBody to identify its first symbols. This is continued until a terminal is encountered or a non terminal with case 1 is encountered. If none of this happens then epsilon is also added to the first set of prodHead
        
*/

#ifndef first_set
#define first_set

set<string> computeFirstSet(Grammar &grammar, FirstFollowSet &firstSet, string prodHead){
    if(firstSet[prodHead].size()){
        return firstSet[prodHead];
    }
    for(auto prodBody : grammar[prodHead]){
        if(prodBody.size() == 0){
            firstSet[prodHead].insert("");
            continue;
        }
        bool hasEpsilon = false;
        for(auto curToken : prodBody){
            hasEpsilon = false;
            if(!isNonTerminal(curToken)){
                firstSet[prodHead].insert(curToken);
                break;
            }
            else if(isNonTerminal(curToken)){
                set<string> temp = computeFirstSet(grammar, firstSet, curToken);
                for(auto symbol : temp){
                    if(symbol == "") hasEpsilon = true;
                    else firstSet[prodHead].insert(symbol);
                }
                if(!hasEpsilon) break;
            }
        }
        if(hasEpsilon) firstSet[prodHead].insert("");
    }
    return firstSet[prodHead];
}

FirstFollowSet computeFirstSets (Grammar grammar){
    FirstFollowSet firstSet;
    for(auto prod : grammar){
        firstSet[prod.first] = computeFirstSet(grammar, firstSet, prod.first);
    }
    return firstSet;
}

#endif // first_set