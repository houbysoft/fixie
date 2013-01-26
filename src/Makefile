# Simple makefile, compiles crank, the compiler, by default

COPT=-g
LOPT=-g
OBJS=fixieTokenizer.o fixieParser.o main.o
CC=g++

default: crank

clean:
	rm -f *.o crank

crank: ${OBJS}
	${CC} ${LOPT} ${OBJS} -o $@

%.o: %.cpp
	${CC} ${COPT} -c $<

