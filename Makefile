CC := g++
CFLAGS := -Wall -Wpedantic -Wextra -Werror -DDEVENV

MODULE = button

LIB_DIR := lib
TEST_DIR := test
TEST_EXE := test.exe
BUILD_DIR := build
UNITY_DIR := unity
TEST_MODULE := $(TEST_DIR)_$(MODULE)

INCLUDES := $(LIB_DIR)/$(MODULE) $(TEST_DIR)/$(UNITY_DIR) $(TEST_DIR)/$(TEST_MODULE)
INCLUDES := $(INCLUDES:%=-I./%)

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) \
					$(wildcard $(TEST_DIR)/$(UNITY_DIR)/*.cpp) \
					$(wildcard $(TEST_DIR)/$(TEST_MODULE)/*.cpp))
OBJECTS := $(OBJECTS:%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "=============== TARGETS ==================="
	@echo "==> clean: to clean the project"
	@echo "==> check: to build and run the test"
	@echo "==========================================="

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) --coverage $^ -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(MODULE)/%.cpp
	@$(CC) -c --coverage -MMD $(CFLAGS) $< $(INCLUDES) -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/*/%.cpp
	@$(CC) -c -MMD $(CFLAGS) $< $(INCLUDES) -o $@

-include $(OBJECTS:%.o=%.d)

check: $(BUILD_DIR) $(BUILD_DIR)/$(TEST_EXE)
	@echo "================================================="
	@echo "================ RUN TEST ======================="
	@echo "================================================="
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --html-details -o $(BUILD_DIR)/index.html

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: check all clean
