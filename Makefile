all: tct nasa pdt

tct: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall TimeCodeTests.cpp TimeCode.cpp -o tct

tct-debug: TimeCodeTests.cpp TimeCode.cpp TimeCode.h
	g++ -Wall -g TimeCodeTests.cpp TimeCode.cpp -o tct-debug

nasa: NasaLaunchAnalysis.cpp TimeCode.cpp TimeCode.h
	g++ -Wall NasaLaunchAnalysis.cpp TimeCode.cpp -o nasa

pdt: PaintDryTimer.cpp TimeCode.cpp TimeCode.h
	g++ -Wall PaintDryTimer.cpp TimeCode.cpp -o pdt

clean:
	rm -f tct tct-debug nasa pdt
