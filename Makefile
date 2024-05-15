BUILD_DIR := ./build
SRC_DIR := ./src
TEST_DIR := ./test

BIN_NAME := $(BUILD_DIR)/dripper
BIN_SRCS := $(shell find $(SRC_DIR) -name '*.c' -type f)
BIN_OBJS := $(BIN_SRCS:%=$(BUILD_DIR)/%.o)
BIN_DEPS := $(BIN_SRCS:%=$(BULD_DIR)/%.d)

TEST_NAME := $(BUILD_DIR)/dripper_test

CFLAGS := -Wall -Werror -g -std=c11
LDFLAGS := $(shell pkg-config --libs raylib)

$(BIN_NAME): $(BIN_OBJS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

$(BUILD_DIR)/%.c.o: %.c
	-mkdir -p $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: run
run: $(BIN_NAME)
	$(BIN_NAME)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(BIN_DEPS)
