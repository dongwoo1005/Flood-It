#variables
CC=g++
CFLAGS=-c -Wall

all: flood 

flood: textdisplay.o cell.o cellb.o grid.o gridb.o window.o main.o
	$(CC) textdisplay.o cell.o cellb.o grid.o gridb.o window.o main.o -o flood -lX11

textdisplay.o: textdisplay.cc
	$(CC) $(CFLAGS) textdisplay.cc

cell.o: cell.cc
	$(CC) $(CFLAGS) cell.cc

cellb.o: cellb.cc
	$(CC) $(CFLAGS) cellb.cc

grid.o: grid.cc
	$(CC) $(CFLAGS) grid.cc

gridb.o: gridb.cc
	$(CC) $(CFLAGS) gridb.cc

window.o: window.cc
	$(CC) $(CFLAGS) window.cc

main.o: main.cc
	$(CC) $(CFLAGS) main.cc
