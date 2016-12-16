all:    BTreeSource.o lab7.o
    gcc -o lab7 BTreeSource.o lab7.o
    make memorytest

BTreeSource.o:  BTreeSource.c BTreeHeader.h
    gcc -c BTreeHeader.h BTreeSource.c

lab7.o: lab7.c BTreeHeader.h
    gcc -c lab7.c BTreeHeader.h

make memorytest:
    gcc lab7.c BTreeSource.c -o lab7
    valgrind  --leak-check=full ./lab7

clean:
    rm lab7 *.o *.gch