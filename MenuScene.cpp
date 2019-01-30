#include "MenuScene.h"
#include "GameScene.h"
#include "DEFINITIONS.h"

namespace Toolbox 
{
	MenuScene::MenuScene(Game* game) 
	{
		// Initialise gameptr, background, buttons.
		gameptr = game;
		gameptr->LoadTexture("MENU", "Sprites/MainMenu.png");
		bg.setTexture(gameptr->GetTexture("MENU"));

		gameptr->LoadTexture("PLAYBUTTON", "Sprites/PlayButton.png");
		btn_play.setTexture(gameptr->GetTexture("PLAYBUTTON"));
		
		// Set button to centre of the screen.		
		btn_play.setPosition(WIDTH/2.0f - btn_play.getTexture()->getSize().x / 2.0f, 
		HEIGHT/2.0f - btn_play.getTexture()->getSize().y / 2.0f);
	}

	void MenuScene::Input() 
	{
		sf::Event event;
		while (gameptr->window.pollEvent(event)) 
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				gameptr->window.close();
				break;
			case sf::Event::MouseButtonPressed:
				// Check for LMB press over buttons
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					CheckClicked();
					return;
				}
				break;
			}
		}
	}
	void MenuScene::Draw(const float dt) 
	{
		// Draw the background and button
		gameptr->window.draw(bg);
		gameptr->window.draw(btn_play);
	}

	void MenuScene::CheckClicked() 
	{
		// Load up the next scene if clicked
		if (gameptr->SpriteClicked(btn_play)) 
			gameptr->PushScene(new GameScene(gameptr));
	}

}