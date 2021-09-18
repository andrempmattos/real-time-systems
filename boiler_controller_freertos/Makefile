CC := gcc
BIN := runner

BUILD_DIR := build

FREERTOS_DIR := ./freertos

#INCLUDE_DIRS := -I.
INCLUDE_DIRS += -I ./inc
INCLUDE_DIRS += -I ${FREERTOS_DIR}/include
INCLUDE_DIRS += -I ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS += -I ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils

SOURCE_FILES := $(wildcard ./src/*.c)
SOURCE_FILES += $(wildcard ${FREERTOS_DIR}/*.c)
# Memory manager (use malloc() / free() )
SOURCE_FILES += ${FREERTOS_DIR}/portable/MemMang/heap_3.c
# posix port
SOURCE_FILES += ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES += ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/port.c


CFLAGS := -ggdb3 -O0
LDFLAGS := -ggdb3 -O0 -pthread -lpcap

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)

${BIN} : $(BUILD_DIR)/$(BIN)

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ $(CFLAGS) $(INCLUDE_DIRS) ${LDFLAGS} -o $@


-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) ${INCLUDE_DIRS} -MMD -c $< -o $@

.PHONY: clean

clean:
	-rm -rf $(BUILD_DIR)