SRC=./src
TARGET=./out
GCC = g++
CFLAGS =  -Wall -std=c++11
ARGS = 101
RM = rm -rf

SOURCE_FILES= $(wildcard $(SRC)/*.cpp)
SOURCE_HEADERS = $(wildcard $(SRC)/*.h)

all: CFLAGS += -O2
all: clean test
test: $(SOURCE_FILES)
	$(GCC) $(CFLAGS) -o $(TARGET)/extractor $(SOURCE_FILES) $(SOURCE_HEADERS)
clean:
	$(RM) $(TARGET)/*
debug: CFLAGS += -g3 -Og
debug: clean test
