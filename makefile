.PHONY: clean all
MKDIR = mkdir
++ = g++

ifeq ($(OS),Windows_NT)
	RM = rd /s /q
	FLAGS = -Wall -Iinclude
else 
	RM = rm -rf
	FLAGS = -Wall -lpthread -Iinclude
endif

DIR_OBJ = obj
DIR = $(DIR_OBJ)
SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS = $(SRCS:.cpp=.o)
OBJS := $(notdir $(OBJS))
OBJS := $(addprefix $(DIR_OBJ)/,$(OBJS))

all:$(DIR) Game2048 debug clean

debug:
	@echo $(SRCS)
	@echo $(OBJS)
$(DIR):
	$(MKDIR) $@
Game2048:$(OBJS)
	$(++) $^ $(FLAGS) -o $@
	@echo making $@
$(DIR_OBJ)/%.o: %.cpp
	$(++) -c $^ $(FLAGS) -o $@
	@echo making $@
$(DIR_OBJ)/%.o: */%.cpp
	$(++) -c $^ $(FLAGS) -o $@
	@echo making $@
clean:
	$(RM) $(DIR)