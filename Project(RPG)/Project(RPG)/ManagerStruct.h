#pragma once

class GameManager;
class ObjectManager;
class AudioManager;
class SceneManager;
class InputManager;
class ImportManager;

struct Managers
{
	GameManager* GameMgr;
	ObjectManager* ObjectMgr;
	AudioManager* AudioMgr;
	SceneManager* SceneMgr;
	InputManager* InputMgr;
	ImportManager* ImportMgr;

};