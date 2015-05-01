# executable name
NAME						= c_goto_assembly

# source path
SOURCE						= src/

# files
YACC_FILE					= $(SOURCE)parse
LEXICON_FILE				= $(SOURCE)gramma

C_FILES 					= *.c 

#flags
CC							=	gcc
CFLAGS						= -lm -o $(NAME) -lfl

# PROCEDURES STRINGS
BISON						= bison -d 	-o$(YACC_FILE).c $(YACC_FILE).y
FLEX						= flex   	-o$(LEXICON_FILE).c  $(LEXICON_FILE).l

# make commands
all:
	echo "$(NAME)"
	$(BISON)
	$(FLEX)
	$(CC) $(YACC_FILE).c $(LEXICON_FILE).c $(CFLAGS)
	rm $(YACC_FILE).c  $(YACC_FILE).h $(LEXICON_FILE).c 

run:
	./$(NAME)

clean:
	rm $(NAME) $(YACC_FILE).h  $(YACC_FILE).c $(LEXICON_FILE).c
