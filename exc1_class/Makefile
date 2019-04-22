####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES: all				
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

$(EXE_DIR)/exc1: $(OBJ_DIR)/main.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/f_ser.o 
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/f_ser.o -o $(EXE_DIR)/exc1

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/opt_proc.c 
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c 

$(OBJ_DIR)/opt_proc.o: $(SRC_DIR)/opt_proc.c $(INCLUDE_DIR)/opt_proc.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/opt_proc.o $(SRC_DIR)/opt_proc.c

$(OBJ_DIR)/f_ser.o: $(SRC_DIR)/f_ser.c $(INCLUDE_DIR)/f_ser.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/f_ser.o $(SRC_DIR)/f_ser.c

dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/exc1.dox

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR) 
