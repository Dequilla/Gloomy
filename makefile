#--------------
# Setup
#--------------

PROGRAM=Gloomy

# Directories
SRC_DIR=src
OBJ_DIR=temp
BUILD_DIR=build
INCLUDE_DIR=include

CC=gcc
LIB=-L./usr/local/lib -lglfw3 -lm -lrt -pthread -lGL -lGLU -lX11 -lXxf86vm -lXrandr -ldl -lXinerama -lXcursor
INCLUDES=-I$(INCLUDE_DIR) -I/usr/local/include
FLAGS=-std=c99 -Wall

# Source and obj files
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(subst .c,.o,$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC)))

#---------------
# Builds
#---------------
default_target: run
.PHONY : default_target

#--------------------
# Normal builds start
debug: FLAGS += -DDEBUG -g3 -O0 
debug: clean all
	@echo "Press enter to continue"
	@read _temp_
	gdb -tui $(BUILD_DIR)/$(PROGRAM)

run: FLAGS += -g0 -O3
run: clean all
	@echo "Press enter to continue"
	@read _temp_
	./$(BUILD_DIR)/$(PROGRAM)

release: FLAGS += -g0 -O3
release: clean all
# Normal builds end
#------------------

#------------------
# Test builds start
test: FLAGS += -D_TEST_
test: clean all
	@echo "Press enter to continue"
	@read _temp_
	./$(BUILD_DIR)/$(PROGRAM)

dtest: FLAGS += -DDEBUG -g3 -O0 -D_TEST_
dtest: clean all
	@echo "Press enter to continue"
	@read _temp_
	gdb -tui $(BUILD_DIR)/$(PROGRAM)
# Test builds end
#------------------


#---------------
# Steps
#---------------

all: create_folders build

create_folders:
	mkdir -p $(OBJ_DIR) $(BUILD_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDES) $(FLAGS) -o $@ -c $<
	

build: $(OBJ)
	$(CC) -o $(BUILD_DIR)/$(PROGRAM) $^ $(LIB)

clean:
	rm -rf $(OBJ) $(BUILD_DIR)/*
