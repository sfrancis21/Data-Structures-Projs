###
### Makefile for Gerp Project
### Gerp is a file search simulator 
###
### Author:  Sara Francis and Sarah Svahn

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#Executable for ./gerp
gerp: main.o stringProcessing.o FileSort.o HashSort.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} $^ -o $@

#Creates .o file for main.cpp
main.o: main.cpp FileSort.h stringProcessing.h FSTreeTraversal.cpp HashSort.h \
DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c main.cpp

#Command to create all .o files
stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

FileSort.o: FileSort.cpp FileSort.h HashSort.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c FileSort.cpp

HashSort.o: HashSort.cpp HashSort.h
	$(CXX) $(CXXFLAGS) -c HashSort.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

unit_test: unit_test_driver.o FileSort.o HashSort.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^


#Executable for testing treeTraversal.cpp
#treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
#${CXX} ${LDFLAGS} $^ -o $@ 

#Executable for testing stringProcessing.cpp
#stringProcessing: stringProcessing.o
#${CXX} ${LDFLAGS} $^ -o $@

#Provide command
provide:
	provide comp15 proj3_gerp_leaderboard README \
						FileSort.h \
						FileSort.cpp HashSort.h  \
						HashSort.cpp main.cpp \
						FSTreeTraversal.cpp \
						stringProcessing.h \
						stringProcessing.cpp \
						Makefile pathList.txt \

clean:
	rm gerp
	rm FileSort.o
	rm main.o
	rm HashSort.o
	rm stringProcessing.o
	rm FSTreeTraversal.o




