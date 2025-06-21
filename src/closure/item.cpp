#include "../generics.h"

#ifndef item_class
#define item_class

class Item{
    public:
        int dotPos;
        string prodHead;
        vector<string> prodBody;
        set<string> lookAhead;
        
        Item() {}
        Item(string prodHead, vector<string> prodBody, set<string> lookAhead){
            this->prodHead = prodHead;
            this->prodBody = prodBody;
            this->lookAhead = lookAhead;
            dotPos = 0;
        }
        bool isProcessed(){
            return dotPos == prodBody.size();
        }
        void proceed(){
            dotPos = (dotPos+1 < prodBody.size())? dotPos+1 : prodBody.size();
        }
        const bool operator == (const Item &item){
            return dotPos == item.dotPos && prodHead == item.prodHead && prodBody == item.prodBody && lookAhead == item.lookAhead;
        }
        string getImmediateRight(){
            return prodBody[dotPos];
        }

        void print(){
            cout<<prodHead<<"-> ";
            for(int i = 0; i < prodBody.size(); i++){
                if(dotPos == i) cout<<" . ";
                cout<<prodBody[i]<<" ";
            }
            if(dotPos == prodBody.size()) cout<<" . ";
            cout<<" , ";
            for(auto symbol : lookAhead){
                cout<<symbol<<" ";
            }cout<<endl;
        }
};

#endif // item_class