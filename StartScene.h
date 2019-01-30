#pragma once
#include "Scene.h"

namespace Toolbox 
{
	class StartScene : public Scene 
	{
	public:
		void Input();
		void Tick() {};
		void Update(const float dt);
		void Draw(const float dt);

		StartScene(Game* game);
	private:
		const float SPLASH_TIME = 1.5f;
		sf::Sprite bg;
		sf::Clock splash_clock;
	};
}