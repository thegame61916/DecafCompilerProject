The file "Module3.l" contains the flex code to parse decaf grammar and Module3.y contains the corresponding bison code with decaf grammar rules to generate the parse tree. Module3.h contains all the class definitions for nodes and to print the output corresponding to node in "XML_visitor.txt" file. In case there is some Syntax error it'll output "Syntax error" else "Success" on Terminal. If Syntax error is encountered then parsing will stop there and program will exit, nothing will be added to XML_visitor.txt.
The program ignores comments and white spaces. But if unclosed comment is there then it'll print "Syntax error"
Commands to run the program:
1. g++ Module3.h
2. bison -dv Module3.y
3. flex Module3.l
4. g++ Module3.tab.c lex.yy.c -lfl -o Module3
5. ./Module3 test_input

Here "test_input" is the input file name.
