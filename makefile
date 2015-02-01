all:
	clang++ -Wc++11-extensions -std=c++14 ./src/cpp/* -o ./bin/run
	# g++ -std=c++14 -fdiagnostics-color src/cpp/* -o bin/run
