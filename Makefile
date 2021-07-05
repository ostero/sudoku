all:
	g++ -std=c++11 solution.cpp -o prog

clean:
	rm -rf prog solution a.out
