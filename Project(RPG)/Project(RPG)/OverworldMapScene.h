#pragma once
#include "Scene.h"
#include "Actions.h"
#include "OverworldMap.h"
#include <SDL.h>

class OverworldMapScene : public Scene
{
private:

	OverworldMap* pOvMap;
	RenderObject* pOverworld;

protected:

public:

	OverworldMapScene();
	void Update(double dTime, Act act) override;

};


