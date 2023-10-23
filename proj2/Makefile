###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Sara Francis

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

## Final executable for CalcYouLater Program
CalcYouLater: parser.o got_int.o Datum.o DatumStack.o RPNCalc.o main.o
	${CXX} ${LDFLAGS} $^ -o $@ 

## This rule builds RPNCalc_tests.o
RPNCalc_tests.o: RPNCalc_tests.cpp RPNCalc.h
	$(CXX) $(CXXFLAGS) -c RPNCalc_tests.cpp

## This rule builds parser.o
parser.o: parser.cpp
	$(CXX) $(CXXFLAGS) -c parser.cpp

## This rule builds got_int.o
got_int.o: got_int.cpp
	$(CXX) $(CXXFLAGS) -c got_int.cpp

## This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h 
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

## This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h Datum.h DatumStack.h 
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

## This rule builds executable for unit_test
unit_test: unit_test_driver.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) $^

## This rule builds executable for RPNCalc_tests
RPNCalc_tests: RPNCalc_tests.o RPNCalc.o DatumStack.o Datum.o got_int.o 
	parser.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 

## This rule builds main.o
main.o: Datum.o DatumStack.o parser.o got_int.o RPNCalc.o main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

## Clean Commmand
clean:
	rm CalcYouLater
	rm DatumStack.o
	rm main.o
	rm RPNCalc.o

## Provide Command
provide:
	provide comp15 proj2_calcyoulater Datum.h \
						DatumStack.cpp DatumStack.h \
						add.cyl fact.cyl fib_debug.cyl  \
						fib.cyl got_int.cpp main.cpp \
						unit_tests.h Makefile README \
						ref.stderr my.stderr n_fibs.cyl \
						RPNCalc_tests.cpp RPNCalc.h RPNCalc.cpp \
						test_file_allErrors.cyl parser.cpp

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^