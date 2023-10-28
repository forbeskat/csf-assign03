CFLAGS = -g -std=c++11 -Wall -Wextra -pedantic

cache: csim.o csim_funcs.o
	g++ $(CFLAGS) -o cache csim.o csim_funcs.o

csim_funcs.o: csim_funcs.cpp csim_funcs.h
	g++ $(CFLAGS) -c csim_funcs.cpp
	
csim.o: csim.cpp 
	g++ $(CFLAGS) -c csim.cpp

assign03.zip :
	rm -f assign03.zip
	zip -9r $@ Makefile README.txt csim.cpp csim_funcs.cpp csim_funcs.h

clean:
	rm -f *.o cache assign03.zip