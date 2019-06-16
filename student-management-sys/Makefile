####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES:				
.PHONY: clean all dox splint

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
# SPLINTFLAGS = +standard -skipposixheaders -mustfreeonly -likelybool -temptrans -usedef

SPLINTFLAGS = +posixlib +standard -mustfreeonly -likelybool \
			  -temptrans -nullstate -mustdefine -compdef -compdestroy \
			  -dependenttrans -noeffect
## -warnposix -preproc 
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
all: $(OBJ_DIR) $(EXE_DIR) $(EXE_DIR)/student_management_sys 

$(EXE_DIR)/student_management_sys: $(OBJ_DIR)/main.o $(OBJ_DIR)/f_ser.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/s_manage.o $(OBJ_DIR)/cmd_modes.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/f_ser.o $(OBJ_DIR)/opt_proc.o $(OBJ_DIR)/s_manage.o $(OBJ_DIR)/cmd_modes.o -o $(EXE_DIR)/student_management_sys

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c

$(OBJ_DIR)/f_ser.o: $(SRC_DIR)/f_ser.c $(INCLUDE_DIR)/f_ser.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/f_ser.o $(SRC_DIR)/f_ser.c

$(OBJ_DIR)/opt_proc.o: $(SRC_DIR)/opt_proc.c $(INCLUDE_DIR)/opt_proc.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/opt_proc.o $(SRC_DIR)/opt_proc.c

$(OBJ_DIR)/s_manage.o: $(SRC_DIR)/s_manage.c $(INCLUDE_DIR)/s_manage.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/s_manage.o $(SRC_DIR)/s_manage.c

$(OBJ_DIR)/cmd_modes.o: $(SRC_DIR)/cmd_modes.c $(INCLUDE_DIR)/cmd_modes.h
	gcc $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/cmd_modes.o $(SRC_DIR)/cmd_modes.c
dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/student_management_sys.dox

splint:
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/main.c
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/f_ser.c

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR) 