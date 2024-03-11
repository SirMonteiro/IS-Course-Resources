all: main clean

main: grafoMatrizadj.o main.o
	gcc -o main grafoMatrizadj.o main.o

main.o: main.c
	gcc -c main.c

grafoMatrizadj.o: grafoMatrizadj.c grafoMatrizadj.h
	gcc -c grafoMatrizadj.c

clean:
	rm -f *.o
