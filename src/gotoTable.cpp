#include "generics.h"
#include "precomputations/firstSet.cpp"
#include "precomputations/followSet.cpp"
#include "closure/item.cpp"
#include "closure/closure.cpp"

#ifndef gotoTable_class
#define gotoTable_class

class GotoTable{
    private:
        FirstFollowSet firstSet;
        FirstFollowSet followSet;

        vector<Closure> closureMp;
        
        Grammar grammar;
        Grammar augmentedGrammar;
        RuleNumberMp grammarMp;
        string augmentedGrammarStart;
        
        int getClosureIdx(const Closure &closure){
            int i = 0;
            for(i = 0; i < closureMp.size(); i++){
                if(closureMp[i] == closure) return i;
            }
            return -1;
        }

        int getProdLocation(Item item){
            int idx = -1;
            for(int i = 0; i < grammarMp.size(); i++){
                string prodHead = grammarMp[i].first;
                vector<string> prodBody = grammarMp[i].second;
                if(prodHead == item.prodHead && prodBody == item.prodBody){
                    idx = i;
                    break;
                }
            }
            return idx;
        }
        
        string buildReduceString(Item item){
            return "r " + to_string(getProdLocation(item));
        }
        
    public:
        GotoTableStore table;
        GotoTable() {}

        GotoTable(Grammar grammar, string grammarStart, Grammar augmentedGrammar, string augmentedGrammarStart, RuleNumberMp grammarMp){
            this->grammar = grammar;
            this->augmentedGrammar = augmentedGrammar;
            this->augmentedGrammarStart = augmentedGrammarStart;
            this->grammarMp = grammarMp;

            firstSet = computeFirstSets(grammar);
            followSet = computeFollowSets(grammar, firstSet, grammarStart);
            
            Item initialItem = Item(augmentedGrammarStart, augmentedGrammar[augmentedGrammarStart][0], {"$"});
            Closure initialClosure = Closure(initialItem, augmentedGrammar, firstSet);

            closureMp.push_back(initialClosure);

            buildTable();
        }

        void buildTable(){
            for(int curClosure = 0; curClosure < closureMp.size(); curClosure++){
                unordered_map<string, vector<Item>> symbolMp;

                for(auto item : closureMp[curClosure].items){
                    if(!item.isProcessed()){
                        string nextToken = item.getImmediateRight();
                        item.proceed();
                        symbolMp[nextToken].push_back(item);
                    }
                }
                
                // -----------------shift-----------------------
                for(auto row : symbolMp){
                    string nextToken = row.first;
                    vector<Item> items = row.second;
                    Closure newClosure = Closure(items[0], augmentedGrammar, firstSet);
                    for(int i = 1; i < items.size(); i++){
                        newClosure.addItem(items[i]);
                    }
                    
                    int newClosureIdx = getClosureIdx(newClosure);

                    if(newClosureIdx == -1){
                        closureMp.push_back(newClosure);
                        newClosureIdx = closureMp.size()-1;
                    }

                    if(isNonTerminal(nextToken)){
                        table[curClosure][nextToken] = to_string(newClosureIdx);
                    }
                    else{
                        table[curClosure][nextToken] = "s " + to_string(newClosureIdx);
                    }
                }
                
                // ------------------------------reduce------------------
                for(auto &item : closureMp[curClosure].items){
                    if(item.isProcessed()){
                        if(item.prodHead == augmentedGrammarStart){
                            table[curClosure]["$"] = "acc";
                        }
                        else{
                            string reduceStr = buildReduceString(item);
                            for(auto lookAhead : item.lookAhead){
                                table[curClosure][lookAhead] = reduceStr;
                            }
                        }
                    }
                }
            }
        }

        void printClosures(){
            for(int i = 0; i < closureMp.size(); i++){
                cout<<i<<" : "<<endl;
                closureMp[i].print();
            }
        }

        void print(){
            for(int i = 0; i < table.size(); i++){
                int closureIdx = i;
                cout<<closureIdx<<" : "<<endl;
                for(auto gotoPair : table[closureIdx]){
                    cout<<"\t"<<gotoPair.first<<" -> "<<gotoPair.second;
                }
                cout<<endl;
            }
        }

        void printFirstSet(){
            for(auto row : firstSet){
                cout<<row.first<<" : ";
                for(auto first : firstSet[row.first]){
                    if(first == "")cout<<"epsilon ";
                    cout<<first<<" ";
                }cout<<endl;
            }
        }

        
        void printFollowSet(){
            for(auto row : followSet){
                cout<<row.first<<" : ";
                for(auto follow : followSet[row.first]){
                    cout<<follow<<" ";
                }cout<<endl;
            }
        }

};

#endif // gotoTable_class