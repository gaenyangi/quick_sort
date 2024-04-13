all: compile run

compile: sorting.cpp
	g++ sorting.cpp -o sorting

run: sorting
	./sorting input.txt output.txt
clean: sorting
	rm sorting
