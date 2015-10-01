all:
	clang++ -Wc++11-extensions -std=c++14 -g ./src/*.cpp -o ./bin/run.out

clang:
	clang++ -Wc++11-extensions -std=c++14 ./src/*.cpp ./src/stopwatch/stopwatch.cpp -o ./bin/run.out

gcc:
	g++ -std=c++14 -fdiagnostics-color src/*.cpp ./src/stopwatch/stopwatch.cpp -o bin/run.out

bst:
	clang++ ./utils/bst.cpp ./src/stopwatch/stopwatch.cpp -o bin/bst.out

analyze:
	clang++ --analyze -Xanalyzer -analyzer-output=text -Wc++11-extensions -std=c++14 ./src/*.cpp

format:
	clang-format ./src/*.cpp ./src/inc/*.h -i

graph_generation:
	clang++ -Wc++11-extensions -std=c++14 ./utils/generate_graph.cpp -o ./bin/gen.out
