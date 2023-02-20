#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	this->endGame = false;

	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;

	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Game 2!", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("timesbd.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONT::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(Color::White);

	//Endgame text
	this->endGameText.setFont(this->font);
	this->endGameText.setCharacterSize(50);
	this->endGameText.setFillColor(Color::Red);
	this->endGameText.setPosition(280, 160);
	this->endGameText.setString("YOU LOSE!");
}

//Contructors & Destructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}
Game::~Game()
{
	delete this->window;
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen(); //&& this->endGame == false;
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::pollEvent()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this-> e.type)
		{
		case Event::Closed:
			this-> window->close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			this->swagBalls.push_back(SwagBall((*this->window), this->randBallType()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randBallType()
{
	int type = SwagBallTypes::DEFAULT;
	int randValue = rand() % 100 + 1;

	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds()))
		{
			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
			}

			swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Point: " << this->points << "\n"
		<< "Health: " << this->player.getHp() << "/" << this->player.getHpMax() << "\n";
	this->text.setString(ss.str());
}

void Game::renderText(RenderTarget* target)
{
	target->draw(text);
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
		this->endGame = true;
}

//Functions
void Game::update()
{
	this->pollEvent();

	if (this->endGame == false)
	{
		this->spawnSwagBalls();

		this->updatePlayer();

		this->updateCollision();

		this->updateText();
	}
}

void Game::render()
{
	this->window->clear(Color::Blue);

	this->player.render(this->window);

	for (auto i : this->swagBalls)
	{
		i.render(*this->window);
	}

	this->renderText(this->window);

	//render endgame
	if (this->endGame == true)
		this->window->draw(this->endGameText);

	this->window->display();
}
