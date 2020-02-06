CC=g++
InDir=-I /usr/local/include/boost
LIBS=-L /usr/local/include/boost -lboost_serialization
CFLAGS=-std=c++11 $(InDir) $(LIBS)
SOURCE=boost_test.cpp
TARGET=res

all :
	$(CC) $(SOURCE) $(CFLAGS) -o $(TARGET)
