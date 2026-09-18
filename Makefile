all: tct

tct: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall TimeCodeTests.cpp TimeCode.cpp -o tct

tct-debug: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall -g TimeCodeTests.cpp TimeCode.cpp -o tct-debug

clean:
	rm -f tct tct-debug