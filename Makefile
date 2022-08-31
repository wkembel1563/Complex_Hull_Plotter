CXXFLAGS += --std=c++17

all: chull

debug: CXXFLAGS += -g
debug: clean
debug: tdebug

tdebug:
	$(CXX) $(CXXFLAGS) main.c stack.c point.c -o chull

chull: main.o stack.o point.o
	$(CXX) $(CXXFLAGS) main.o stack.o point.o -o chull

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

stack.o: stack.cpp
	$(CXX) $(CXXFLAGS) -c stack.cpp

point.o: point.cpp
	$(CXX) $(CXXFLAGS) -c point.cpp

clean:
	rm -f *.o *~ *.gch chull a.out
