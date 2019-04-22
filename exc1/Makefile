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
all: $(OBJ_DIR) $(EXE_DIR) $(EXE_DIR)/exc1 

$(EXE_DIR)/exc1: $(OBJ_DIR)/main.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/string_compare.o $(OBJ_DIR)/f_str.o $(OBJ_DIR)/interactive_prog.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/string_compare.o $(OBJ_DIR)/f_str.o $(OBJ_DIR)/interactive_prog.o -o $(EXE_DIR)/exc1

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/opt_proc.c 
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c 

$(OBJ_DIR)/opt_proc.o: $(SRC_DIR)/opt_proc.c $(INCLUDE_DIR)/opt_proc.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/opt_proc.o $(SRC_DIR)/opt_proc.c

$(OBJ_DIR)/string_compare.o: $(SRC_DIR)/string_compare.c $(INCLUDE_DIR)/string_compare.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/string_compare.o $(SRC_DIR)/string_compare.c

$(OBJ_DIR)/f_str.o: $(SRC_DIR)/f_str.c $(INCLUDE_DIR)/f_str.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/f_str.o $(SRC_DIR)/f_str.c

$(OBJ_DIR)/interactive_prog.o: $(SRC_DIR)/interactive_prog.c $(INCLUDE_DIR)/interactive_prog.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/interactive_prog.o $(SRC_DIR)/interactive_prog.c

dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/exc1.dox

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR) 
