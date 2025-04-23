CXX = c++

INCLUDE_DIR = src/common_search

CXXFLAGS = -Wall -I$(INCLUDE_DIR) -std=c++17
# CXXFLAGS = -c -Wall
# g++ -c Wall -Isrc/common_search -std=c++17

build: filereader.o scenario_service.o children.o heuristics.o astar_search.o fringe_search.o search_service.o main.o
	$(CXX) $(CXXFLAGS) filereader.o scenario_service.o heuristics.o children.o fringe_search.o astar_search.o search_service.o main.o -o eksekute


filereader.o: src/scenario_service/filereader.cpp src/scenario_service/filereader.h
	$(CXX) -c $(CXXFLAGS) src/scenario_service/filereader.cpp

scenario_service.o: src/scenario_service/scenario_service.cpp src/scenario_service/scenario_service.h src/scenario_service/filereader.h
	$(CXX) -c $(CXXFLAGS) src/scenario_service/scenario_service.cpp

children.o: src/searches/common/children.cpp src/searches/common/children.h
	$(CXX) -c $(CXXFLAGS) src/searches/common/children.cpp

heuristics.o: src/searches/common/heuristics.cpp src/searches/common/heuristics.h
	$(CXX) -c $(CXXFLAGS) src/searches/common/heuristics.cpp

astar_search.o: src/searches/astar_search.cpp src/searches/astar_search.h src/searches/common/children.h src/searches/common/heuristics.h
	$(CXX) -c $(CXXFLAGS) src/searches/astar_search.cpp

fringe_search.o: src/searches/fringe_search.cpp src/searches/fringe_search.h src/searches/common/children.h src/searches/common/heuristics.h
	$(CXX) -c $(CXXFLAGS) src/searches/fringe_search.cpp

search_service.o: src/search_service.cpp src/search_service.h src/searches/fringe_search.h src/searches/astar_search.h
	$(CXX) -c $(CXXFLAGS)  src/search_service.cpp

main.o: src/main.cpp src/search_service.h src/scenario_service/scenario_service.h
	$(CXX) -c $(CXXFLAGS) src/main.cpp

	

ifneq ("$(wildcard gtest_Makefile)", "")
  include gtest_Makefile
endif

# Clean up
clean:
	# rm -f *.o 
	find . -type f -name '*.o' -delete
