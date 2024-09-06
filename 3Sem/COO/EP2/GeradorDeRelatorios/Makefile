ARGS=quick preco_c todos 0

all: build run

build: src/GeradorDeRelatorios.java src/Produto.java src/ProdutoPadrao.java
	javac -d build -sourcepath src src/GeradorDeRelatorios.java

run: build/GeradorDeRelatorios.class
	java -classpath build GeradorDeRelatorios $(ARGS)

clean: build/GeradorDeRelatorios.class
	rm -f build/*.class
