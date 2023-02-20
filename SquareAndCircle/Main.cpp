#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));

	//Init game engine
	Game game;

	while (game.running())
	{
		//Update
		game.update();
		

		//Render
		game.render();

	}



	return 0;
}