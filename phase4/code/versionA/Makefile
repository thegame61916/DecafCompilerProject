CCC = clang++
CCFLAGS= -O3 -Wno-write-strings
LEX = flex
LFLAGS= -8    
BISON= bison
YFLAGS= -d -t -y
 
RM = /bin/rm -f
 
llvm: llvm.o y.tab.o lex.yy.o
		${CCC} ${CCFLAGS} lex.yy.o y.tab.o llvm.o -ll `llvm-config --cppflags --ldflags --libs core` -o llvm
 
llvm.o: llvm.cpp
		${CCC} -c -w llvm.cpp `llvm-config --cppflags --ldflags --libs core`
 
y.tab.o: llvm.y
		${BISON} ${YFLAGS} llvm.y
		${CCC} ${CCFLAGS} -c -w y.tab.c `llvm-config --cppflags --ldflags --libs core`
 
lex.yy.o: llvm.l
		${LEX} $(LFLAGS) llvm.l
		${CCC} ${CCFLAGS} lex.yy.c -c -w `llvm-config --cppflags --ldflags --libs core`
 
clean:
		/bin/rm -f lex.yy.* y.tab.* *.o llvm
