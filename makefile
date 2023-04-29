APP_NAME = geometry
LIB_NAME = libgeometry

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = cpp
CC = g++

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	
	
TEST_NAME = test
TEST_EXE_PATH = bin/test
TEST_OBJ_PATH = test
	
.PHONY: test
test: $(TEST_EXE_PATH)

$(TEST_EXE_PATH): $(TEST_OBJ_PATH)/main.o $(TEST_OBJ_PATH)/test.o $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	
$(TEST_OBJ_PATH)/test.o: test/test.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	
$(TEST_OBJ_PATH)/main.o: test/main.cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
