#include "../generics.h"
#include "item.cpp"

#ifndef closure_class
#define closure_class

class Closure{
    private:
        inline bool itemExists(const Item &item){
            for(int i = 0; i < items.size(); i++){
                if(items[i] == item) {
                    return true;
                }
            }
            return false;
        }
        void computeClosure(){
            for(int i = 0; i < items.size(); i++){
                if(!items[i].isProcessed()){
                    string newProdToken = items[i].getImmediateRight();
                    if(isNonTerminal(newProdToken)){
                        bool hasEpsilon = true;
                        set<string> lookAhead;
                        for(int j = items[i].dotPos+1; j < items[i].prodBody.size(); j++){
                            string curToken = items[i].prodBody[j];
                            if(curToken == ""){
                                hasEpsilon =  true;
                            }
                            else{
                                hasEpsilon = false;
                                if(!isNonTerminal(curToken)){
                                    lookAhead.insert(curToken);
                                    break;
                                }
                                else{
                                    for(auto first : firstSet[curToken]){
                                        if(first == ""){
                                            hasEpsilon = true;
                                        }
                                        else{
                                            lookAhead.insert(first);
                                        }
                                    }
                                }
                            }
                            if(!hasEpsilon) break;
                        }
                        if(hasEpsilon){
                            for(auto token : items[i].lookAhead){
                                lookAhead.insert(token);
                            }
                        }
                        for(auto prodBody : grammar[newProdToken]){
                            Item newItem = Item(newProdToken, prodBody, lookAhead);
                            if(!itemExists(newItem)){
                                items.push_back(newItem);
                            }
                        }
                    }
                }
            }
        }

    public:
        vector<Item> items;
        Grammar grammar;
        FirstFollowSet firstSet;

        Closure(Item item, Grammar grammar,  FirstFollowSet firstSet){
            this->firstSet = firstSet;
            this->grammar = grammar;
            addItem(item);
        }

        void addItem(Item item){
            items.push_back(item);
            computeClosure();
        }

        const bool operator == (const Closure &closure){
            if(closure.items.size() != items.size()){
                return false;
            }
            for(int i = 0; i < items.size(); i++){
                bool found = false;
                for(int j = 0; j < closure.items.size(); j++){
                    if(closure.items[j] == items[i]){
                        found = true;
                        break;
                    }
                }
                if(!found) return false;
            }
            return true;
        }

        void print(){
            for(auto item : items){
                cout<<"\t";
                item.print();
            }
            cout<<endl;
        }
};

#endif // closure_class