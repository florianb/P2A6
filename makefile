CC = clang++
CCFLAGS = -Wall
#CCFLAGS = 
OBJ = main.o
VALFLAGS = --leak-check=full
PROG = account
ARGS = -m
#ARGS = 
LOG = | tee -a lastmake.txt
MAKELOG = 2>&1 | tee lastmake.txt

debug:
	clear
	make clean
	make main ${MAKELOG} && clear && valgrind ${VALFLAGS} ./$(PROG) $(ARGS) ${LOG}

only:
	clear
	make clean
	make main ${MAKELOG}

main: $(OBJ)
	$(CC) $(CCFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(PROG) *.o

labor:
	clear
	make clean
	make CC='g++' main ${MAKELOG} && clear && ./$(PROG) $(ARGS) ${LOG}