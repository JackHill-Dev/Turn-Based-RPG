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
	RenderObject* mCloseBtn;

	void Init();
	void GetCharacterPortraits();
	void GetCharacterStatistics();
	UIText DrawStat(std::string statName, int stat, SDL_Color textColor, std::pair<int,int> pos);
	std::vector<Character*> mParty;


};

