BUILD_DIR=$(CURDIR)/build
SRC_DIR=$(CURDIR)/src
SRC_BUILD_DIR=$(BUILD_DIR)/src
TEST_DIR=$(CURDIR)/test
TEST_BUILD_DIR=$(BUILD_DIR)/test

# source files for library
LIB_SRC_DIRS=$(SRC_DIR) $(SRC_DIR)/hash $(SRC_DIR)/movegen \
	$(SRC_DIR)/position $(SRC_DIR)/util
LIB_SOURCES=$(foreach d,$(LIB_SRC_DIRS),$(wildcard $(d)/*.c))
LIB_STRIPPED_SOURCES=$(patsubst $(SRC_DIR)/%,%,$(LIB_SOURCES))
LIB_SRC_OBJECTS=$(patsubst %.c,$(SRC_BUILD_DIR)/%.o,$(LIB_STRIPPED_SOURCES))

# source files for executable 
EXE_SRC_DIRS=$(SRC_DIR)/command $(SRC_DIR)/commandline $(SRC_DIR)/prophet4
EXE_SOURCES=$(foreach d,$(EXE_SRC_DIRS),$(wildcard $(d)/*.c))
EXE_STRIPPED_SOURCES=$(patsubst $(SRC_DIR)/%,%,$(EXE_SOURCES))
EXE_SRC_OBJECTS=$(patsubst %.c,$(SRC_BUILD_DIR)/%.o,$(EXE_STRIPPED_SOURCES))
#$(info $(EXE_SRC_OBJECTS))

# test source files
TEST_DIRS=$(TEST_DIR) $(TEST_DIR)/hash $(TEST_DIR)/movegen $(TEST_DIR)/position $(TEST_DIR)/util
TEST_SOURCES=$(foreach d,$(TEST_DIRS),$(wildcard $(d)/*.cpp))
STRIPPED_TEST_SOURCES=$(patsubst $(TEST_DIR)/%,%,$(TEST_SOURCES))
TEST_OBJECTS=$(patsubst %.cpp,$(TEST_BUILD_DIR)/%.o,$(STRIPPED_TEST_SOURCES))

# dependencies
GTEST_OBJ=$(TEST_BUILD_DIR)/gtest-all.o

# compiler flags
COMMON_INCLUDES= -I $(CURDIR)/include
COMMON_CFLAGS= -Wall -Werror -Wextra
CFLAGS = $(COMMON_INCLUDES) $(COMMON_CFLAGS) -O3 -DNDEBUG
#CFLAGS = $(COMMON_INCLUDES) $(COMMON_CFLAGS) -g -O0
TEST_CXXFLAGS= $(COMMON_INCLUDES) $(COMMON_CFLAGS) -I $(GTEST_DIR) -I $(GTEST_DIR)/include

COMMON_LIBS = -lpthread
LIBS = -L. -lprophet4lib $(COMMON_LIBS)

# phony targets
.PHONY: ALL clean test

ALL: $(EXE_SRC_OBJECTS) libprophet4lib.a
	$(CC) $(CFLAGS) -lm -o prophet4 $(EXE_SRC_OBJECTS) $(LIBS)

# source build objects
$(SRC_BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	@echo "Compiling source file: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# test build objects
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(dir $@)
	@echo "Compiling test file: $<"
	@$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# Google Test object
$(GTEST_OBJ): $(GTEST_DIR)/src/gtest-all.cc
	mkdir -p $(dir $@)
	@echo "Compiling Google Test object: $<"
	@$(CXX) $(TEST_CXXFLAGS) -c $< -o $@


libprophet4lib.a: $(LIB_SRC_OBJECTS) 
	ar rcs libprophet4lib.a $(LIB_SRC_OBJECTS)

test: $(LIB_SRC_OBJECTS) $(TEST_OBJECTS) $(GTEST_OBJ)
	@$(CXX) $(TEST_CXXFLAGS) \
	-o prophet4_test $(LIB_SRC_OBJECTS) $(TEST_OBJECTS) \
	$(GTEST_OBJ) $(COMMON_LIBS)

clean:
	rm -f ./prophet4
	rm -f ./libprophet4lib.a
	rm -f ./prophet4_test
	rm -rf $(BUILD_DIR)