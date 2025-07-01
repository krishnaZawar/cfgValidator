#include "../generics.h"

/*
    Approach:
        The follow set of start will always have '$'
        There are three ways to compute follow set.
            1. A -> pBq
                    follow(B) = first(q)
            2. A -> pB
                    follow(B) = follow(A) U follow(B)
            3. A -> pBq, first(q) has ""
                    follow(B) = (first(q) - {""}) U follow(A)
*/

#ifndef follow_set
#define follow_set

FirstFollowSet computeFollowSets(Grammar grammar, FirstFollowSet firstSet, string startProd){
    FirstFollowSet followSet;

    followSet[startProd].insert("$");

    bool changed = true;

    while(changed){
        changed = false;
        for(auto prod : grammar){
            string prodHead = prod.first;
            for(auto prodBody : grammar[prodHead]){
                for(int i = 0; i < prodBody.size(); i++){
                    if(isNonTerminal(prodBody[i])){
                        int oldSize = followSet[prodBody[i]].size();
                        bool allHaveEpsilon = true;
                        for(int j = i+1; j < prodBody.size(); j++){
                            if(prodBody[j] == "") {
                                continue;
                            }
                            bool epsilon = false;
                            if(isNonTerminal(prodBody[j])){
                                for(auto first : firstSet[prodBody[j]]){
                                    if(first == ""){
                                        epsilon = true;
                                    }
                                    else{
                                        followSet[prodBody[i]].insert(first);
                                    }
                                }
                            }
                            else{
                                followSet[prodBody[i]].insert(prodBody[j]);
                            }
                            allHaveEpsilon = epsilon;
                            if(!allHaveEpsilon) break;
                        }
                        if(i == prodBody.size()-1 || allHaveEpsilon){
                            for(auto follow : followSet[prodHead]){
                                followSet[prodBody[i]].insert(follow);
                            }
                        }
                        if(oldSize != followSet[prodBody[i]].size()) changed = true;
                    }
                }
            }
        }
    }

    return followSet;
}

#endif // follow_set