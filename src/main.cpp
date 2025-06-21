#include<fstream>
#include "interpreter.cpp"
#include "gotoTable.cpp"
#include "grammar.cpp"

using std::getline;
using std::ifstream;

int main(){

    RuleNumberMp grammarMp;

    int idx = 0;
    for(auto prod : grammar){
        string prodHead = prod.first;
        for(auto prodBody : prod.second){
            grammarMp[idx] = {prodHead, prodBody};
            idx++;
        }
    }

    GotoTable table = GotoTable(grammar, "Start", augmentedGrammar, "AugmentedStart", grammarMp);
    Interpreter interpreter = Interpreter(grammar, grammarMp, table);
    
    ifstream file ("testFile.txt");

    std::string input = "";
    std::string buffer = "";

    while(getline(file, buffer)){
        input += buffer + "\n";
    }

    try{
        interpreter.interpret(input);
    }
    catch(string &e){
        cout<<e<<endl;
    }

    return 0;
}