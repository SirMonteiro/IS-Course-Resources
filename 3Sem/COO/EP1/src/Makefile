all: build run

Ball.class: Ball.java
	javac Ball.java

Player.class: Player.java
	javac Player.java

Score.class: Score.java
	javac Score.java

build: Ball.java Player.java Score.java
	javac Ball.java Player.java Score.java

run: Ball.class Player.class Score.class
	java -Dsun.java2d.opengl=true Pong

runSafe: Ball.class Player.class Score.class
	java Pong 1 true

clean:
	rm -f Ball.class Player.class Score.class
