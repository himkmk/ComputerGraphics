# per-project variable definitions
ARCH	:= -m64 # m64 (x64) or m32 (x86)
C_SRC 	:= $(shell find * -type f -name "*.c")
CC_SRC	:= $(shell find * -type f -name "*.cpp")

# name derived from vc project; so, don't delete vcxproj even in Linux
NAME = $(subst .vcxproj,,$(notdir $(wildcard *.vcxproj)))

# directories and header dependency
BIN := ../bin
INC := -I. -Igl -Igles
OBJ := .obj

#**************************************
# nearly fixed compiler flags/objects
C_FLAGS  := -c $(ARCH) -Wall $(INC)
CC_FLAGS := $(C_FLAGS) -std=c++17
C_OBJS   := $(addprefix $(OBJ)/,$(C_SRC:.c=.o))
CC_OBJS  := $(addprefix $(OBJ)/,$(CC_SRC:.cpp=.o))

#**************************************
# os-dependent configuration: Ubuntu/Linux or MinGW
ifneq ($(OS), Windows_NT)
	TARGET = $(addsuffix .out,$(BIN)/$(NAME))
	LD_FLAGS = -lglfw -ldl # not glfw3
	MK_INT_DIR = @mkdir -p $(@D)
	RM_INT_DIR = @rm -rf $(OBJ)
	RM_TARGET = @rm -rf $(TARGET)
else
	TARGET = $(addsuffix .exe,$(BIN)/$(NAME))
	LD_FLAGS = -lglfw3 # not glfw
	MK_INT_DIR = @bash -c "mkdir -p $(@D)"
	RM_INT_DIR = @bash -c "rm -rf $(OBJ)"
	RM_TARGET = @bash -c "rm -rf $(TARGET)"
endif

#**************************************
# default target redirected to $(TARGET)
all: $(TARGET)

#**************************************
# main target: Use TAB for actions
$(TARGET): $(C_OBJS) $(CC_OBJS)
	g++ $^ -o $@ $(LD_FLAGS)

#**************************************
# compile c files using gcc
$(C_OBJS): $(OBJ)/%.o: %.c
	$(MK_INT_DIR)
	gcc -MMD -MP $(C_FLAGS) $< -o $@
-include $(C_OBJS:.o=.d)

#**************************************
# compile cpp files using g++
$(CC_OBJS): $(OBJ)/%.o: %.cpp
	$(MK_INT_DIR)
	g++ -MMD -MP $(CC_FLAGS) $< -o $@
-include $(CC_OBJS:.o=.d)

#**************************************
# run executable
run: $(TARGET)
	@${TARGET} ${ARGS}

#**************************************
# clean intermediate object files
# ||: mute rm errors for non-existing files
.PHONY: clean
clean:
	$(RM_INT_DIR) ||:

#**************************************
# clean even executable
.PHONY: clear
clear: clean
	$(RM_TARGET) ||:

#**************************************
# force to build
force: clean $(TARGET)
