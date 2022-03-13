all: kruskal gen_test

kruskal:
	g++ --std=c++17 -O2 -o kruskal kruskal.cpp

gen_test:
	g++ --std=c++17 -O2 -o gen_test gen_test.cpp
