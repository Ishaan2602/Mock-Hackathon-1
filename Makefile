CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
TARGET = build/main
SRCS = src/main.cpp src/lexer.cpp src/parser.cpp src/interpreter.cpp
OBJS = $(SRCS:src/%.cpp=build/%.o)

exec: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: exec
	./build/main

clean:
	rm -rf build

.PHONY: all clean
