CFLAGS = -Wall -std=c99
sourceName = GabrielMonteiroDeSouza
binName = EP2_AED2_2024

all: build run

build:
	gcc $(CFLAGS) -o ../$(binName) $(sourceName).c

run:
	../$(binName) ../tests/1/inputTest2.txt ../saida.txt

tests: test1 test2

test1: build
	for i in {0..6}; do \
		../$(binName) ../tests/1/inputTest$$i.txt ../saida.txt; \
		diff ../tests/1/outputTest$$i.txt ../saida.txt; \
	done

test2: build
	for i in {0..12}; do \
		../$(binName) ../tests/2/inputTest$$i.txt ../saida.txt; \
		diff ../tests/2/outputTest$$i.txt ../saida.txt; \
	done


clean:
	rm -f ../EP2_AED2_2024

# make build && ../EP2_AED2_2024 ../tests/2/inputTest5.txt ../saida.txt && cat ../saida.txt
