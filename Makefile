CFLAGS = -g -std=c++11 -Wall -Wextra -pedantic

csim: csimmain.o csim_funcs.o 
	g++ $(CFLAGS) -o csim csimmain.o csim_funcs.o

csimmain.o: csimmain.cpp 
	g++ $(CFLAGS) -c csimmain.cpp

csim_funcs.o: csim_funcs.cpp csim_funcs.h
	g++ $(CFLAGS) -c csim_funcs.cpp

assign03.zip :
	rm -f assign03.zip
	zip -9r $@ Makefile README.txt csimmain.cpp csim_funcs.cpp csim_funcs.h

clean:
	rm -f *.o csim assign03.zip