APP = demo
TARGET = $(APP).out

CC  = g++

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
LIBS = -lGLEW -lglfw -lGL

CPPFLAGS= -Wall -std=c++11
LDFLAGS = $(LIBS)

all:$(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS)

run: $(TARGET)
	./$<

clean: 
	rm -f *.o
