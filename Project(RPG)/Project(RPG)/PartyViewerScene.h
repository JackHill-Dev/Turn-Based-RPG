#pragma once
#include "Scene.h"

struct CharacterCard
{
	UIText stamina;
	UIText health;
	UIText mana;
	UIText agility;
	UIText movement;
};

class PartyViewerScene :
    public Scene
{
public:
	PartyViewerScene(Interface* mgr);
protected:
	void Update(double dTime, Act act, std::pair<int, int> mousePos) override;
private:
	RenderObject* mCloseBtn;// Close button
	// Background
	//Scene* prevScene;// Previous scene / Scene that opened the party viwer
	void Init();
	void GetCharacterPortraits();
	void GetCharacterStatistics();
	
	// Temp
	RenderObject* wizard;
	RenderObject* rogue;
	RenderObject* cleric;
	RenderObject* warrior;

	std::vector<Character> mChars;


};

