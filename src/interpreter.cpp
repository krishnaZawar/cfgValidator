#include<stack>
#include "gotoTable.cpp"
#include "lexer/lexer.cpp"

using std::stack;
using std::stoi;

#ifndef interpreter_class
#define interpreter_class

class Interpreter{
    private:
        Lexer lexer;
        Grammar grammar;
        RuleNumberMp grammarMp;
        GotoTable table;

        stack<int> stateStack;
        stack<string> grammarStack;

        int getShiftState(string s){
            int state = 0;

            for(int i = 2; i < s.length(); i++){
                state = state*10 + (s[i] - '0');
            }

            return state;
        }
        int getReduceState(string s){
            int prodNum = 0;
            for(int i = 2; i < s.length(); i++){
                prodNum = prodNum * 10 + (s[i] - '0');
            }
            return prodNum;
        }

    public:
        Interpreter(Grammar grammar, RuleNumberMp grammarMp, GotoTable table){
            lexer = Lexer();
            this->table = table;
            this->grammar = grammar;
            this->grammarMp = grammarMp;
        }

        void interpret(string input){
            vector<Token> tokens = lexer.getTokens(input);

            int idx = 0;

            stateStack = stack<int> ();
            grammarStack =  stack<string> ();

            stateStack.push(0);

            while(true){
                Token token = tokens[idx];
                int state = stateStack.top();
                
                string action;

                if(token.type == IDENTIFIER){
                    action = table.table[state]["identifier"];
                }
                else if(token.type == STRINGLITERAL){
                    action = table.table[state]["stringLiteral"];
                }
                else if(token.type == ENDOFFILE){
                    action = table.table[state]["$"];
                }
                else{
                    action = table.table[state]["'" + token.value + "'"];
                }
                
                if(action == ""){
                    throw string("parsing error");
                }

                if(action == "acc"){
                    break;
                }

                if(action[0] == 's'){
                    int nextState = getShiftState(action);
                    grammarStack.push(token.value);
                    stateStack.push(nextState);
                    idx++;
                }
                else if(action[0] == 'r'){
                    int prodNum = getReduceState(action);

                    string prodHead = grammarMp[prodNum].first;
                    vector<string> prodBody = grammarMp[prodNum].second;

                    for(int i = 0; i < prodBody.size(); i++){
                        grammarStack.pop();
                        stateStack.pop();
                    }

                    grammarStack.push(prodHead);
                    int nextState = stoi(table.table[stateStack.top()][prodHead]);
                    stateStack.push(nextState);
                }
                else{
                    throw string("unknown action");
                }
            }
            cout<<"valid input"<<endl;
        }
};  

#endif // interpreter_class