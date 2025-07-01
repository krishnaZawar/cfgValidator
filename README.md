
# <p align = "center">CFG validator</p>
This a handwritten CLR parser to validate CFG syntax.
CFG (Context Free Grammar) is an essential representation tool used while working on compilers.
 This parser validates whether the structure followed for writing CFG has been followed.


# How to Use
To validate your grammar, follow these simple steps:
1. write your program and save it in "testFile.txt" provided.
2. Run the main file

# Expected File Structure
```
Tokens : < token names separated by commas, this is optional>.
productionHead1 : productionBody1;
productionHead2 : productionBody2;
.
.
```
## examples
example 1:
CFG to validate inputs like {'a', 'aa', 'aaa', ... , 'aaa.....'}.
```
Tokens: .
A : 'a' A;
A : 'a';
```
example 2:
CFG to validate assignment statement
```
Tokens : identifier, number.
Start : AssignmentStatement;
AssignmentStatement : identifier '=' Value ';' ;
Value : identifier;
Value : number;
```

# Future scope of Development
1. Validate the semantics of the written CFG.
2. Allow the user to validate the input expected by his CFG.
