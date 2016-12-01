The file "decaf.l" contains the flex code to parse a decaf program and "decaf.y" contains the corresponding bison code for decaf grammar rules. It prints the successfully parsed rule's output in file "bison_output.txt" and flex output goes to "flex_output.txt". In case there is some Syntax error it'll output "Syntax error" else "Success" on Terminal. If Syntax error is encountered then parsing will stop there and program will exit, nothing will be added to bison_ouput.txt after encountering a syntax error.
The program ignores comments and white spaces. But if unclosed comment is there then it'll print "Syntax error".
Commands to run the program:
1. bison -d decaf.y
2. flex decaf.l
3. g++ decaf.tab.c lex.yy.c -lfl
3. ./a.out test_input

Here "test_input" is the input file name.
