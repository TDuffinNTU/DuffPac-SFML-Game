#pragma once
#include "Game.h"

// FOLLOWING CODE SOURCED FROM (OR HEAVILY INFLUENCED BY):
// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml-part-1-state-manager/123

namespace Toolbox 
{
	class Scene 
	// The Scene class is the parent class of all "scenes" in the game
	// They encompass the input, logic, and drawing code that the user sees and interacts with
	{
	public:
		// Pointer to the Game class. This allows states to access game methods and functions (ie. RenderWindows)
		class Game* gameptr;

		// Input() and Update() are called every frame, for handling Input and Update code
		// Tick can be set up to be called at regular time intervals
		// Draw is where objects such as sprites are drawn to the screen
		virtual void Input() = 0;
		virtual void Tick() = 0;
		virtual void Update(const float dt) = 0;
		virtual void Draw(const float dt) = 0;
	};
}