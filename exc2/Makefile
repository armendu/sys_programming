####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES:				
.PHONY: clean all dox

####################################################################
# Path Definitions                                                 #
####################################################################
OUT_DIR     = ./output
OBJ_DIR     = $(OUT_DIR)/build
EXE_DIR     = $(OUT_DIR)/exe
DOX_DIR     = $(OUT_DIR)/docu
SRC_DIR     = ./src
INCLUDE_DIR = ./include

####################################################################
# Flag Definitions                                                 #
####################################################################
FLAGS = -Wall -c -ansi -g
INCLUDEPATHS =-I$(INCLUDE_DIR)

####################################################################
# Create build and ouput directory								   #
####################################################################
$(OBJ_DIR):
	mkdir -p $(OUT_DIR)
	mkdir -p $(OBJ_DIR)
	@echo "Created build directory."

$(EXE_DIR):
	mkdir -p $(EXE_DIR)
	@echo "Created executable directory."

####################################################################
# Build instructions			 								   #
####################################################################
all: $(OBJ_DIR) $(EXE_DIR) $(EXE_DIR)/exc2

$(EXE_DIR)/exc2: $(OBJ_DIR)/main.o
	gcc $(OBJ_DIR)/main.o -o $(EXE_DIR)/exc2

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/main.c 
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c

dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/exc2.dox

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR) 
