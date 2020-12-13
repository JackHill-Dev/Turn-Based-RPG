#include "Scene.h"

Scene::Scene()
{

	std::vector<RenderObject*> rObjects;

	for (int i = 0; i < layerNum; ++i)
	{
		mLayers.push_back(rObjects);
	}
}

void Scene::Update(double dTime, Act act)
{
	std::for_each(mLayers.begin(), mLayers.end(), [dTime, act](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [dTime, act](RenderObject* obj) {obj->Update(dTime, act); });
		});
};

void Scene::Draw(SDL_Surface* wnd)
{
	mSurface = wnd; // Need to move this otherwise a variable is pointlessly getting set every frame TODO: Ask TH & EH where's best to set this
	SDL_Rect* rect = new SDL_Rect(); // TODO:Place these on the stack - JP, TH
	SDL_Rect* crop = new SDL_Rect();
	
	std::for_each(mLayers.begin(), mLayers.end(), [&wnd, &rect, &crop](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [&wnd, &rect, &crop](RenderObject* obj) {if (obj->IsVisible())


		{
			crop->x = obj->GetAnim()->GetCurrentFrame();
			crop->y = obj->GetAnim()->GetCurrentFrame();
			crop->w = obj->GetSheet()->GetCellSize().first;
			crop->h = obj->GetSheet()->GetCellSize().second;

			rect->x = obj->GetPos().first;
			rect->y = obj->GetPos().second;
			if (obj->IsVisible())SDL_BlitSurface(obj->GetSheet()->GetTexture(), crop, wnd, rect); // First rectangle references the cell and how to retrieve it from at last, the second relates to its position - T
		}
		});


		});

	
}
// When mouse is inside bounds of a render object in current scene
void Scene::Select(int x, int y, SceneManager* sceneMgr, GameManager* gameMgr)
{
	std::find_if(mLayers.rbegin(), mLayers.rend(), [x, y, &sceneMgr, &gameMgr](std::vector<RenderObject*> layer) {

		return std::find_if(layer.begin(), layer.end(), [x, y, &sceneMgr, &gameMgr](RenderObject* obj) {
			if (obj->InBounds(x, y))
				obj->Select(sceneMgr, gameMgr);
			return(obj->InBounds(x, y));
			
			} ) != layer.end();

		});
}

void Scene::Clear()
{
	SDL_FillRect(mSurface, nullptr, SDL_MapRGB(mSurface->format, 0, 0, 0));
}

RenderObject* Scene::AddObject(std::string obj, int x, int y, Layer layerNum)
{
	RenderObject* obje = ObjectManager::Instance().RequestObject(obj);

	mLayers[layerNum].push_back(obje);
	obje->SetAnim("default");
	obje->SetPos(std::make_pair(x, y));

	return obje;

}
