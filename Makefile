########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.



#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

INCLUDES=  -I. 

LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


ALL_OBJ0=query_tree.o
PROGRAM_0=query_tree
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=test_tree.o
PROGRAM_1=test_tree
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=test_tree_mod.o
PROGRAM_2=test_tree_mod
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)


#Compiling all

all: 	
		make clean
		clear
		make $(PROGRAM_0)
		make $(PROGRAM_1)
		make $(PROGRAM_2)
		clear

run1bst: 	
		./$(PROGRAM_0) rebase210.txt BST

run1avl: 	
		./$(PROGRAM_0) rebase210.txt AVL

run2bst: 	
		./$(PROGRAM_1) rebase210.txt sequences.txt BST

run2avl: 	
		./$(PROGRAM_1) rebase210.txt sequences.txt AVL

test:
	g++ -o test.cc sequence_map.h



#Clean obj files

clean:
	(rm -f *.o; rm -f test_tree; rm -f query_tree; rm -f test_tree_mod)


(:
