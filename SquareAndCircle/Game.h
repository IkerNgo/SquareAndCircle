#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event e;
	bool endGame;

	Player player;

	int points;

	Font font;
	Text text;
	Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	//Functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();


public:
	//Contructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Modifiers


	//Functions
	void pollEvent();

	void spawnSwagBalls();
	const int randBallType();
	void updateCollision();
	void updateText();
	void renderText(RenderTarget* target);
	void updatePlayer();
	void update();
	void render();
};

