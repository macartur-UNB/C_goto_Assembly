# executable name
NAME						= c_goto_assembly
EXECUTABLE					= bin/$(NAME)

# paths
SOURCE						= src/
LIB							= lib/
INCLUDE						= include/
TEST						= test/

# files
YACC_FILE					= parse
LEXICON_FILE				= gramma
C_FILES 					= $(SOURCE)*.c 
TEST_SRC					= $(TEST)*.c

#flags
CC							=	gcc
CFLAGS						= -lm -lfl
CUNIT_FLAGS					= -lcunit -lcurses 

# PROCEDURES STRINGS
BISON						= bison -d 	-o   $(SOURCE)$(YACC_FILE).c 	$(LIB)$(YACC_FILE).y
FLEX						= flex   	-o   $(SOURCE)$(LEXICON_FILE).c  $(LIB)$(LEXICON_FILE).l

# make commands
all:
	$(BISON)
	$(FLEX)
	$(CC) $(C_FILES) $(CFLAGS) -I $(INCLUDE) -o $(EXECUTABLE)
	rm $(SOURCE)$(YACC_FILE).c  $(SOURCE)$(YACC_FILE).h $(SOURCE)$(LEXICON_FILE).c 

# run tests
run_test:
	$(CC) -lm $(TEST_SRC) $(C_FILES) -o $(TEST)test $(CUNIT_FLAGS) -I $(INCLUDE) 
	./test/test

# run the executable
run:
	./$(EXECUTABLE) 

#try compile the main.asm
test: main.c main.asm
	nasm -f elf32 main.asm -o bin/main.o
	gcc -m32 bin/main.o -o bin/test 

# clear the executable
clean:
	rm -rf test/test main.asm $(EXECUTABLE) 
