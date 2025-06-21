#include <vector>
#include <iostream>
#include "token.cpp"

using std::vector;
using std::string;

#ifndef lexer_class
#define lexer_class

class Lexer{
    private:
        vector<string> keywords;
        vector<char> specialCharacters;
        vector<char> skippables;

        template<class datatype>
        inline bool existsIn(const datatype &find, const vector<datatype> &items){
            for(int i = 0; i < items.size(); i++){
                if(items[i] == find) return true;
            }
            return false;
        }

        bool isAlpha(char ch){
            return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
        }
        bool isDigit(char ch){
            return ch >= '0' && ch <= '9';
        }
    
    public:
        Lexer() {
            keywords = {
                "Tokens"
            };
            specialCharacters = {
                ',', '.', ';', ':'
            };
            skippables = {
                ' ', '\t', '\n'
            };
        }

        vector<Token> getTokens(string input){
            int ptr = 0;

            vector<Token> tokens;

            while(ptr < input.size()){
                while(existsIn(input[ptr], skippables)){
                    ptr++;
                }
                
                if(ptr >= input.size()){
                    break;
                }

                if(input[ptr] == '\''){
                    string value = "";
                    ptr++;
                    while(ptr < input.size() && input[ptr] != '\''){
                        value += input[ptr];
                        ptr++;
                    }ptr++;
                    tokens.push_back(Token(STRINGLITERAL, value));
                }
                else if(existsIn(input[ptr], specialCharacters)){
                    std::string value = "";
                    value += input[ptr];
                    ptr++;
                    tokens.push_back(Token((value == ";")? ENDOFLINE : SPECIALCHARACTER, value));
                }
                else if(isAlpha(input[ptr])){
                    std::string value = "";
                    while(ptr < input.size() && (isAlpha(input[ptr]) || isDigit(input[ptr]))){
                        value += input[ptr];
                        ptr++;
                    }
                    if(existsIn(value, keywords)){
                        tokens.push_back(Token(KEYWORD, value));
                    }
                    else{
                        tokens.push_back(Token(IDENTIFIER, value));
                    }
                }
                else{
                    throw string("unidentified token");
                }
            }

            tokens.push_back(Token(ENDOFFILE, "$"));
            return tokens;
        }
};

#endif // lexer_class