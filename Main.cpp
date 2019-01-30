#include "Game.h"
#include "StartScene.h"

int main()
{
	Toolbox::Game game;

	// Push the initial state to the stack, and begin execution.
	game.PushScene(new Toolbox::StartScene(&game));
	game.Run();

	return 0;
}

