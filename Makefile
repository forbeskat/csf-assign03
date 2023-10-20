CC = g++
CFLAGS = -g -Wall -Wextra -pedantic -std=c++11

SRCS = cache.cpp
OBJS = $(SRCS:.cpp=.o)

EXECUTABLE = csim

# Targets

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)

solution.zip:
	rm -f solution.zip
	zip solution.zip Makefile README.txt *.h *.cpp
