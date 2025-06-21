#include "generics.h"

/*
    Grammar representation in map:
        key : prodHead
        value : vector<string>
                    each string holds a possible prodBody

    Grammar Rules:
        1. Any production head should follow CapitalCase
        2. Any non terminal should be either in single quotes or follow camelCase
*/

Grammar grammar = {
    {"Start", 
        {{"TokenBlock", "ProdList"}}},
    {"TokenBlock",
        {{"'Tokens'", "':'", "TokenList", "'.'"},
        {"'Tokens'", "':'", "'.'"}}},
    {"TokenList", 
        {{"identifier", "','", "TokenList"},
        {"identifier"}}},
    {"ProdList", 
        {{"ProdStatement", "MoreProdStatements"}}},
    {"MoreProdStatements", 
        {{"ProdStatement", "MoreProdStatements"},
        {}}},
    {"ProdStatement", 
        {{"identifier", "':'", "ProdBody", "';'"}}},
    {"ProdBody", 
        {{"SubPart", "MoreSubParts"}}},
    {"MoreSubParts", 
        {{"SubPart", "MoreSubParts"},
        {}}},
    {"SubPart", 
        {{"identifier"},
        {"stringLiteral"}}}
};

Grammar augmentedGrammar = {
    {"AugmentedStart",
        {{"Start"}}},
    {"Start", 
        {{"TokenBlock", "ProdList"}}},
    {"TokenBlock",
        {{"'Tokens'", "':'", "TokenList", "'.'"},
        {"'Tokens'", "':'", "'.'"}}},
    {"TokenList", 
        {{"identifier", "','", "TokenList"},
        {"identifier"}}},
    {"ProdList", 
        {{"ProdStatement", "MoreProdStatements"}}},
    {"MoreProdStatements", 
        {{"ProdStatement", "MoreProdStatements"},
        {}}},
    {"ProdStatement", 
        {{"identifier", "':'", "ProdBody", "';'"}}},
    {"ProdBody", 
        {{"SubPart", "MoreSubParts"}}},
    {"MoreSubParts", 
        {{"SubPart", "MoreSubParts"},
        {}}},
    {"SubPart", 
        {{"identifier"},
        {"stringLiteral"}}}
};