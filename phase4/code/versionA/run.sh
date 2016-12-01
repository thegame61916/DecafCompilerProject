flex -8 llvm.l
clang++ -O3 lex.yy.c -c -w `llvm-config --cppflags --libs core`
bison -d -t -y llvm.y
clang++ -O3 -Wno-write-strings -c -w y.tab.c `llvm-config --cppflags --libs core`
clang++ -c llvm.cpp -w `llvm-config --cppflags --libs core`
clang++ -O3 -Wno-write-strings lex.yy.o y.tab.o llvm.o -ll `llvm-config --cppflags --ldflags --libs core` -o llvm
./llvm test_input
