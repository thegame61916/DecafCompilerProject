g++ Module3.h
bison -dv Module3.y
flex Module3.l
g++ Module3.tab.c lex.yy.c -lfl -o Module3
./Module3 test_input

