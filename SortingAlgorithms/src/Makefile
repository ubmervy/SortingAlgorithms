# working dirs

SRCDIR = ../src/
OBJDIR = ../obj/
EXECDIR = ../bin/

CC=g++

CFLAGS=-std=c++11 -I../h/ -c -Wall -Wno-reorder

LDFLAGS=

#SOURCES = main.cpp FileLoader.cpp Context.cpp FileSorter.cpp Sequence.cpp SortResult.cpp SortStrategy.cpp HeapSortStrategy.cpp InsertionSortStrategy.cpp MergeSortStrategy.cpp QuickSortStrategy.cpp ShellSortStrategy.cpp SelectionSortStrategy.cpp
SOURCES=$(wildcard $(SRCDIR)*.cpp)
OBJECTS = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,${SOURCES})
EXECUTABLE=$(EXECDIR)sortalgs

#all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

