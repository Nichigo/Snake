#@https://github.com/TheNetAdmin/Makefile-Templates/blob/master/SmallProject/Template/Makefile
# tool macros
CC := g++
CCFLAG := -Wall
DBGFLAG := -g
CCOBJFLAG := $(CCFLAG) -c
LINKER_FLAGS = -lSDL2 -lSDL2_image

# path macros
OBJ_PATH := obj
SRC_PATH := src

# compile macros
TARGET_NAME := snake-game
TARGET := $(TARGET_NAME)
MAIN_SRC := main.cpp

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ)
CLEAN_LIST := $(TARGET) \
			  $(DISTCLEAN_LIST)

# default rule
default: all

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) $(CCFLAG) $(LINKER_FLAGS) -o $@ $? $(LINKER_FLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAG) -o $@ $<

# phony rules
.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
