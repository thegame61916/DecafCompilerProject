bison -d decaf.y
flex decaf.l
g++ decaf.tab.c lex.yy.c -lfl
./a.out test_input

