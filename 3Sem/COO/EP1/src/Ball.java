import java.awt.*;
import java.util.Random;

/**
	Esta classe representa a bola usada no jogo. A classe princial do jogo (Pong)
	instancia um objeto deste tipo quando a execução é iniciada.
*/

public class Ball {
	private double cx;
	private double cy;
	private double width;
	private double height;
	private Color color;
	private double speed;
	private double speedMax;
	private double angle;
	private Random random;
	private boolean specialMode;

	/**
		Construtor da classe Ball. Observe que quem invoca o construtor desta classe define a velocidade da bola
		(em pixels por millisegundo), mas não define a direção deste movimento. A direção do movimento é determinada
		aleatóriamente pelo construtor.

		@param cx coordenada x da posição inicial da bola (centro do retangulo que a representa).
		@param cy coordenada y da posição inicial da bola (centro do retangulo que a representa).
		@param width largura do retangulo que representa a bola.
		@param height altura do retangulo que representa a bola.
		@param color cor da bola.
		@param speed velocidade da bola (em pixels por millisegundo).
	*/

	public Ball(double cx, double cy, double width, double height, Color color, double speed){
		this.cx = cx;
		this.cy = cy;
		this.width = width;
		this.height = height;
		this.color = color;
		this.speed = speed - 0.25;
		this.speedMax = speed;
		this.angle = this.getStartAngle();
		this.random = new Random();
		this.specialMode = false;
	}


	/**
		Método chamado sempre que a bola precisa ser (re)desenhada.
	*/

	public void draw(){
		GameLib.setColor(this.color);
		GameLib.fillRect(this.cx, this.cy, this.width, this.height);
	}

	/**
		Método chamado quando o estado (posição) da bola precisa ser atualizado.

		@param delta quantidade de millisegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/

	public void update(long delta){
		this.cx += Math.cos(this.angle) * delta * speed;
		this.cy += Math.sin(this.angle) * delta * speed;
		for (int i = 0; i < Pong.FIELD_HEIGHT/30; i++) {
			GameLib.fillRect(Pong.FIELD_WIDTH/2, Pong.FIELD_HEIGHT/4 + i * 20, 10, 10);
		}

		if (GameLib.isKeyPressed(GameLib.KEY_UP) && GameLib.isKeyPressed(GameLib.KEY_DOWN)) {
			GameLib.drawText("Secret Mode activated! ", Pong.FIELD_HEIGHT/2, GameLib.ALIGN_CENTER);
			this.specialMode = true;
		}

		if (GameLib.isKeyPressed(GameLib.KEY_LEFT) && GameLib.isKeyPressed(GameLib.KEY_RIGHT)) {
			GameLib.drawText("Secret Mode deactivated!", Pong.FIELD_HEIGHT/2, GameLib.ALIGN_CENTER);
			this.specialMode = false;
		}

		if (this.specialMode) {
			this.cx += (-0.5 + Math.random()) * delta;
			this.cy += (-0.5 + Math.random()) * delta;
		}
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com um jogador.

		@param playerId uma string cujo conteúdo identifica um dos jogadores.
	*/

	public void onPlayerCollision(String playerId){
		double tryAngle = Math.PI - this.angle;
		if (this.speed < this.speedMax) this.speed += 0.001;

		switch(playerId) {
			case Pong.PLAYER1:
				if ((tryAngle > 0 && tryAngle < Math.PI/2) || (tryAngle > 3*Math.PI/2 && tryAngle < 2*Math.PI)) {
					this.angle = tryAngle;
				} else {
					this.angle = tryAngle + Math.PI;
				}
				break;
			case Pong.PLAYER2:
				if (tryAngle > Math.PI/2 && tryAngle < 3*Math.PI/2) {
					this.angle = tryAngle;
				} else {
					this.angle = tryAngle + Math.PI;
				}
				break;
		}
	}

	/**
		Método chamado quando detecta-se uma colisão da bola com uma parede.

		@param wallId uma string cujo conteúdo identifica uma das paredes da quadra.
	*/

	public void onWallCollision(String wallId) {

		// switch case with code duplicated to compile using java 8.
		switch (wallId) {
			case Pong.TOP:
				this.angle = 2 * Math.PI - this.angle;
				break;
			case Pong.BOTTOM:
				this.angle = 2 * Math.PI - this.angle;
				break;
            default:
				this.angle = this.getStartAngle();
				if (this.speed < this.speedMax) this.speed += 0.01;
				this.cy = Pong.FIELD_HEIGHT / 4 + 20 * this.random.nextInt(Pong.FIELD_HEIGHT/30);
				this.cx = Pong.FIELD_WIDTH / 2;
		}
			this.specialMode = false;
	}

	/**
		Método que verifica se houve colisão da bola com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/

	public boolean checkCollision(Wall wall){
		double ballRight = this.cx + this.width/2;
		double ballTop = this.cy - this.height/2;
		double ballLeft = this.cx - this.width/2;
		double ballBottom = this.cy + this.height/2;

		double wallRight = wall.getCx() + wall.getWidth()/2;
		double wallTop = wall.getCy() - wall.getHeight()/2;
		double wallLeft = wall.getCx() - wall.getWidth()/2;
		double wallBottom = wall.getCy() + wall.getHeight()/2;


		switch (wall.getId()) {
			case Pong.BOTTOM:
				return ballBottom >= wallTop;
			case Pong.TOP:
				return ballTop <= wallBottom;
			case Pong.RIGHT:
				return ballRight >= wallLeft;
			case Pong.LEFT:
				return ballLeft <= wallRight;
		}
		return false;
	}

	/**
		Método que verifica se houve colisão da bola com um jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/

	public boolean checkCollision(Player player){
		double ballRight = this.cx + this.width/2;
		double ballTop = this.cy - this.height/2;
		double ballLeft = this.cx - this.width/2;
		double ballBottom = this.cy + this.height/2;

		double playerRight = player.getCx() + player.getWidth()/2;
		double playerTop = player.getCy() - player.getHeight() / 2;
		double playerLeft = player.getCx() - player.getWidth() / 2;
		double playerBottom = player.getCy() + player.getHeight() / 2;

		if (!(playerTop <= ballBottom && playerBottom >= ballTop)) return false;

		switch(player.getId()) {
			case Pong.PLAYER1:
				return ballLeft <= playerRight && ballRight >= playerLeft;
			case Pong.PLAYER2:
				return ballRight >= playerLeft && ballLeft <= playerRight;
		}
		return false;
	}

	/**
		Método que devolve a coordenada x do centro do retângulo que representa a bola.
		@return o valor double da coordenada x.
	*/

	public double getCx(){
		return this.cx;
	}

	/**
		Método que devolve a coordenada y do centro do retângulo que representa a bola.
		@return o valor double da coordenada y.
	*/

	public double getCy(){
		return this.cy;
	}

	/**
		Método que devolve a velocidade da bola.
		@return o valor double da velocidade.

	*/

	public double getSpeed(){
		return this.speed;
	}

	private double getStartAngle(){
		double randomRadian;
		do {
			randomRadian = Math.random() * 2 * Math.PI;
		} while (Math.toRadians(60) < randomRadian && randomRadian < Math.toRadians(120) ||
				Math.toRadians(240) < randomRadian && randomRadian < Math.toRadians(300));
		return randomRadian;
	}
}
