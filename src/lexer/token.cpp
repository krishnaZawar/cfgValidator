#include "tokenType.h"
#include <string>

using std::string;

#ifndef token_class
#define token_class

class Token{
    public:
        TokenType type;
        string value;

        Token(TokenType type, string value){
            this->type = type;
            this->value = value;
        }
};

#endif // token_class