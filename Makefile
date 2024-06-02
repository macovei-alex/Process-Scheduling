CXX = g++
CXXFLAGS = -Wall
STRUCTS = Implementation/structs
UTIL = Implementation/utility
ALG = Implementation/algorithms
TESTS = Unit_test/Tests/tests
RNG = Random_data_generator/random_data_generator
MAIN = Implementation/main

all: main.exe

main.exe: structs.o utility.o algorithms.o tests.o random_data_generator.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: $(MAIN).cpp $(RNG).h $(TESTS).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

random_data_generator.o: $(RNG).cpp $(RNG).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests.o: $(TESTS).cpp $(TESTS).h $(ALG).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

algorithms.o: $(ALG).cpp $(ALG).h $(UTIL).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

utility.o: $(UTIL).cpp $(UTIL).h $(STRUCTS).h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
structs.o: $(STRUCTS).cpp $(STRUCTS).h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del main.exe *.o