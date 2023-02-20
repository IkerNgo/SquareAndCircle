#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;

enum SwagBallTypes {DEFAULT=0,DAMAGING,HEALING,NROFTYPES};

class SwagBall
{
private:
	CircleShape shape;
	int type;

	void initShape(RenderTarget& window);

public:
	SwagBall(RenderTarget& target, int type);
	virtual ~SwagBall();

	//Accessors
	const CircleShape getShape() const;
	const int& getType() const;

	//Function
	void update();
	void render(RenderTarget& target);
};

