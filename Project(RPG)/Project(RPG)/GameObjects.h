#pragma once
#include <map>
#include "Globals.h"
#include "RenderObject.h"
#include "SpriteSheet.h"
#include "Animation.h"

// Define objects with an identifier and a render object that refers to a specific spritesheet.
const std::map<std::string,RenderObject*> definedObjects
{
	{
		// Background Objects

		{"OverlayObj", new RenderObject("overlay")},
		{"tictactoeObj", new RenderObject("tictactoe")},

		// Button Objects

		{"StartButtonObj", new RenderObject("StartButton")},
		{"HostGameButtonObj", new RenderObject("HostGameButton")},
		{"JoinButtonObj", new RenderObject("JoinButton")},
		{"LeaveGameButtonObj", new RenderObject("LeaveGameButton")},
		{"RematchButtonObj", new RenderObject("RematchButton")},

		// General UI Objects

		{"NoughtsAndCrossesBannerObj", new RenderObject("NoughtsAndCrossesBanner")},
		{"PlayerInfoObj", new RenderObject("PlayerInfo")},
		{"TurnAndGameInfoObj", new RenderObject("TurnAndGameInfo")},

		// Noughts and Crosses Game Objects

		{"BoardPieceObj", new RenderObject("BoardPiece")},
		{"NoughtObj", new RenderObject("Nought")},
		{"CrossObj", new RenderObject("Cross")},
	}
};

// Define sheets with an identifier, a sheet(Path, texture sizes(x,y), cell sizes(x,y) and cell count)
const std::map<std::string, SpriteSheet*> definedSheets
{
	{
		// Background Spritesheets

		{"overlay", new SpriteSheet("Assets/Backgrounds/Overlay.png", 1920, 1080, 1920, 1080, false)},
		{"tictactoe", new SpriteSheet("Assets/Backgrounds/Tic_tac_toe.png", 1200, 1067, 1200, 1067, false)},
		
		// Button Spritesheets		
		
		{"StartButton", new SpriteSheet("Assets/Sprites/Buttons/StartButtonNAC.png", 200, 52, 200, 52, false)},
		{"HostGameButton", new SpriteSheet("Assets/Sprites/Buttons/HostGameButton.png", 200, 85, 200, 85, false)},
		{"JoinButton", new SpriteSheet("Assets/Sprites/Buttons/JoinButton.png", 200, 85, 200, 85, false)},
		{"LeaveGameButton", new SpriteSheet("Assets/Sprites/Buttons/LeaveGameButton.png", 300, 101, 300, 101, false)},
		{"RematchButton", new SpriteSheet("Assets/Sprites/Buttons/RematchButton.png", 300, 101, 300, 101, false)},

		// General UI Spritesheets
		
		{"NoughtsAndCrossesBanner", new SpriteSheet("Assets/Sprites/NoughtsAndCrossesBanner.png", 640, 131, 640, 131, false)},
		{"PlayerInfo", new SpriteSheet("Assets/Sprites/PlayerInfo.png", 300, 585, 300, 585, false)},
		{"TurnAndGameInfo", new SpriteSheet("Assets/Sprites/TurnAndGameInfo.png", 400, 160, 400, 160, false)},

		// Noughts and Crosses Game SpriteSheets
		{"BoardPiece", new SpriteSheet("Assets/Sprites/BoardPiece.png", 150, 156, 150, 156, false)},
		{"Nought", new SpriteSheet("Assets/Sprites/Nought.png", 140, 138, 140, 138, false)},
		{"Cross", new SpriteSheet("Assets/Sprites/Cross.png", 140, 138, 140, 138, false)},						
	}
};

const std::map<std::string, std::vector<Animation>> definedAnimations
{
	{
		// Effects Animations

		{"Magic", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
		{"swordSlashEffect", {Animation("default", {std::make_pair(0,0), std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0)})}},
		{"ArrowShot", {Animation("default", {std::make_pair(3,0), std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0),std::make_pair(7,0)})}},
		{"health", {Animation("default", {std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0),std::make_pair(6,0),std::make_pair(7,0),std::make_pair(8,0), std::make_pair(9,0)})}},
		{"BossAttack", {Animation("default", {std::make_pair(0,0),std::make_pair(1,0),std::make_pair(2,0),std::make_pair(3,0),std::make_pair(4,0),std::make_pair(5,0), std::make_pair(6,0)})}},
	}
};
