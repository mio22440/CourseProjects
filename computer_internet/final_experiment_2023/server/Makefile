
#编译使用的平台 Windows Linux
HOST_OS = Linux

#可执行文件名称
EXCUTABLE = srv

#要编译的文件
obj-y += conc_tcp_srv_echo.o

#编译参数
CLINK_FLAGS += -g
CFLAGS		+= -g -O0

#相关配置
ifeq ($(HOST_OS), Windows)
	CC  	= gcc
	LD  	= gcc
	DBG		= gdb

	RM 		= del
	MK_DIR 	= mkdir
	RM_DIR 	= rmdir /s /q

#	LINK_SCRIPT = link.ld

	OUT_BIN = $(EXCUTABLE).exe

	CINCLUDE_FILE_FLAG = -Iinclude
else
	CC  	= gcc
	LD  	= gcc
	DBG		= gdb

	RM 		= del
	MK_DIR 	= mkdir
	RM_DIR 	= rm -rf

#	LINK_SCRIPT = link_linux.ld

	OUT_BIN = $(EXCUTABLE)

	CINCLUDE_FILE_FLAG = -Iinclude
endif

#如果要使用链接脚本
#CLINK_FLAGS += -Wl,-T "$(LINK_SCRIPT)"

OUT_MAP = $(EXCUTABLE).map

#不需要处理的目录路径
SRC_DIR = src
OUT_DIR = output
#需要处理的目录路径
OBJ_DIR_ORIG = $(OUT_DIR)/obj
BIN_DIR_ORIG = $(OUT_DIR)/bin

#处理要编译的文件
OBJ_TARGET_ORIG = $(patsubst %,$(OBJ_DIR)/%,$(obj-y))

ifeq ($(HOST_OS), Windows)
OBJ_DIR = $(subst /,\\,$(OBJ_DIR_ORIG))
BIN_DIR = $(subst /,\\,$(BIN_DIR_ORIG))
OBJ_TARGET = $(subst /,\\,$(OBJ_TARGET_ORIG))
else
OBJ_DIR = $(OBJ_DIR_ORIG)
BIN_DIR = $(BIN_DIR_ORIG)
OBJ_TARGET = $(OBJ_TARGET_ORIG)
endif

all: $(OUT_BIN)

ifeq ($(HOST_OS), Windows)
$(OUT_BIN): $(BIN_DIR) $(OBJ_TARGET)
	$(LD) $(CLINK_FLAGS) -Wl,-Map,$(BIN_DIR)\\$(OUT_MAP) -o $(BIN_DIR)\\$@ $(OBJ_TARGET)

$(BIN_DIR):
	$(MK_DIR) $(OUT_DIR)
	$(MK_DIR) $(OBJ_DIR)
	$(MK_DIR) $(BIN_DIR)

$(OBJ_DIR)\\%.o: $(SRC_DIR)\\%.c
	$(CC) $(CINCLUDE_FILE_FLAG) $(CFLAGS) -o $@ -c $<

run: $(BIN_DIR)\\$(OUT_BIN)
	@$(BIN_DIR)\\$(OUT_BIN)

dbg: $(BIN_DIR)\\$(OUT_BIN)
	gdb $(BIN_DIR)\\$(OUT_BIN)
else
$(OUT_BIN): $(BIN_DIR) $(OBJ_TARGET)
	$(LD) $(CLINK_FLAGS) -Wl,-Map,$(BIN_DIR)/$(OUT_MAP) -o $(BIN_DIR)/$@ $(OBJ_TARGET)

$(BIN_DIR):
	$(MK_DIR) $(OUT_DIR)
	$(MK_DIR) $(OBJ_DIR)
	$(MK_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CINCLUDE_FILE_FLAG) $(CFLAGS) -o $@ -c $<

run: $(BIN_DIR)/$(OUT_BIN)
	@$(BIN_DIR)/$(OUT_BIN)

dbg: $(BIN_DIR)/$(OUT_BIN)
	gdb $(BIN_DIR)/$(OUT_BIN)
endif


clean:
	$(RM_DIR) $(OUT_DIR)


