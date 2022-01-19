CXX = g++
CXXFLAGS = -Wall

test: graph.o mytest.cpp
	$(CXX) $(CXXFLAGS) graph.o mytest.cpp -o test

driver: graph.o driver.cpp
	$(CXX) $(CXXFLAGS) graph.o driver.cpp -o driver

hist.o: graph.h graph.cpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

run:
	./test

run2:
	./driver
	
val:
	valgrind ./test

clean:
	rm *~
	rm *.o