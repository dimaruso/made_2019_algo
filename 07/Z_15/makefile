CC = g++

all: Salesman

Salesman : main.o Generator.o Cruscal.o Metrics.o
	$(CC) - o Salesman main.o Generator.o Cruscal.o Metrics.o

main.o : main.cpp Generator.h Cruscal.h Metrics.h
	$(CC) - c main.cpp

WeightEdge.o : WeightEdge.cpp WeightEdge.h
	$(CC) - c WeightEdge.cpp

Metrics.o : Metrics.cpp Metrics.h
	$(CC) - c Metrics.cpp

DSU.o : DSU.cpp DSU.h
	$(CC) - c DSU.cpp

Generator.o : Generator.cpp WeightEdge.h
	$(CC) - c Generator.cpp

Cruscal.o : Cruscal.cpp WeightEdge.h DSU.h
	$(CC) - c Cruscal.cpp

run : Salesman
	./ Salesman

clean :
  rm - rf * .o Salesman
