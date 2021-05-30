# original by JOB VRANISH
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/


TARGET_EXEC ?= program

OUT_DIR = ./out
BUILD_DIR = ./out/build
SRC_DIRS = ./src
TEST_DIR = ./test
TEST_BUILD_DIR ?= $(OUT_DIR)/test

# Sources
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Include
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -std=c++11 -Wall -Wextra -pedantic -O1

# Project
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c %.h
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

test: ./test/test_lb_queue.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(TEST_BUILD_DIR)/test_lb_queue ./test/test_lb_queue.cpp
	./$(TEST_BUILD_DIR)/test_lb_queue

.PHONY: clean

run:
	./$(BUILD_DIR)/$(TARGET_EXEC)

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
