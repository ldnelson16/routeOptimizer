CXX := g++
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment
SRC_DIR := .
BUILD_DIR := build
EXE_DIR := bin

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# Test files
TEST_SOURCES := $(wildcard $(SRC_DIR)/*_tests.cpp)

# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TEST_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))

# Executables
MAIN_EXECUTABLE := $(EXE_DIR)/main.exe
TEST_EXECUTABLES := $(patsubst $(SRC_DIR)/%_tests.cpp,$(EXE_DIR)/%_tests,$(TEST_SOURCES))

.PHONY: all clean

all: $(MAIN_EXECUTABLE)

$(MAIN_EXECUTABLE): $(OBJECTS)
	@mkdir -p $(EXE_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

total-clean:
	rm -rf $(BUILD_DIR)/* $(EXE_DIR)/*

test: $(TEST_EXECUTABLES)
	@for test_exec in $(TEST_EXECUTABLES); do \
		$$test_exec; \
	done

$(EXE_DIR)/%_tests: $(BUILD_DIR)/%_tests.o $(OBJECTS)
	@mkdir -p $(EXE_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%_tests.o: $(SRC_DIR)/%_tests.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
