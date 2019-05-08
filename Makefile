
release:
	g++ -Wall -o logroller logroller.cpp fetcharg.cpp

debug:
	g++ -g -Wall -o logroller logroller.cpp fetcharg.cpp

test:
	g++ -g -Wall -o fetch fetch.cpp fetcharg.cpp
	g++ -g -Wall -o barf barf.c

