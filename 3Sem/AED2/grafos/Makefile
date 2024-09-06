all: grafoMatrizadj grafoListaadj clean

grafoMatrizadj.o: grafoMatrizadj.c grafoMatrizadj.h
	gcc -c grafoMatrizadj.c

grafoMatrizadj: grafoMatrizadj.o mainMatrizadj.o
	gcc -o grafoMatrizadj grafoMatrizadj.o mainMatrizadj.o

grafoListaadj: grafoListaadj.o mainListaAdj.o
	gcc -o grafoListaadj grafoListaadj.o mainListaAdj.o

grafoListaadj.o: grafoListaadj.c grafoListaadj.h
	gcc -c grafoListaadj.c

mainMatrizadj.o: main.c grafoMatrizadj.h grafoListaadj.h
	gcc -c -include grafoMatrizadj.h -o mainMatrizadj.o main.c

mainListaAdj.o: main.c grafoMatrizadj.h grafoListaadj.h
	gcc -c -include grafoListaadj.h -o mainMatrizadj.o main.c

clean:
	rm -f *.o

cleanBin:
	rm -f grafoMatrizadj grafoListaadj

cleanAll: clean cleanBin
