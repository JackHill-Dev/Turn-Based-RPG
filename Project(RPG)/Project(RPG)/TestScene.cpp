#include "TestScene.h"
TestScene::TestScene(ObjectManager* rng) : Scene(rng)
{
	AddObject("maleObj", 250, 250, UI);
}