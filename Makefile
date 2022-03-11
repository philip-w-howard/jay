##**************************************
## Makefile
##
## Build routine for jay compiler
##
## Author: Phil Howard 
## phil.howard@oit.edu
##

COPTS=-Wall -g -c  -O0 -std=c++11
OBJS=main.o \
	 jaylex.o \
	 jayparse.o \
	 cVisitor.o \
	 cSymbol.o \
	 cCodeGen.o \
	 emit.o \

LIBS=jay_generated_output.cpp \
	 cLog.cpp \
	 cCsv.cpp \

all: jay

clean:
	rm -f $(OBJS)
	rm -f jaylex.c
	rm -f jayparse.c
	rm -f jayparse.h
	rm -f jay
	rm -f out.xml
	rm -f out2.xml
	rm -f jay_generated_output.cpp
	rm -f libTest

.cpp.o:
	g++ $(COPTS) $? -o $@

.c.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp jayparse.c jaylex.c 
	g++ $(COPTS) main.cpp -o $@

jaylex.o: jaylex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@

jaylex.c: jay.l jayparse.c
	flex -o jaylex.c jay.l

jayparse.c: jay.y
	bison --defines=jayparse.h jay.y -o jayparse.c

jay: $(OBJS)
	g++ $(OBJS) -o jay

#build routine(s) for using the Dippy compiler
#perhaps this deserves its own directory?
comp:
	./jay ./samples/popSim.jay

cLib:
	g++  $(LIBS) -o libTest
