#pragma once

#include "Scene.h"

namespace Toolbox
{
	class MenuScene : public Scene
	{
	public:
		void Input();
		void Tick() {}
		void Update(const float dt) {}
		void Draw(const float dt);

		MenuScene(Game* game);
	private:
		void CheckClicked();
		sf::Sprite bg;
		sf::Sprite btn_play;
	};
}