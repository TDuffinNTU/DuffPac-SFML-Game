#include "StartScene.h"
#include "MenuScene.h"

namespace Toolbox 
{
	StartScene::StartScene(Game* game) 
	{
		// Set game pointer to local variable, initialise background
		this->gameptr = game;
		gameptr->LoadTexture("SPLASH", "Sprites/SplashScreen.png");
		bg.setTexture(gameptr->GetTexture("SPLASH"));
	}

	void StartScene::Input() 
	{
		// Event loop incase user closes the window
		sf::Event event;
		while (gameptr->window.pollEvent(event)) 
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				gameptr->window.close();
				break;
			}
		}
	}	

	void StartScene::Update(const float dt) 
	{
		// Wait for some time before swapping to the menu scene
		if (splash_clock.getElapsedTime().asSeconds() > SPLASH_TIME) 
		{
			gameptr->SwapScene(new MenuScene(gameptr));
		}
	}

	void StartScene::Draw(const float dt) 
	{
		// Draw the background
		gameptr->window.draw(bg);
	}
}