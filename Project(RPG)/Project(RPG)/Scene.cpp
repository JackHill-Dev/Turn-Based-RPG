#include "Scene.h"
#include "ManagerStruct.h"

Scene::Scene(ObjectManager* objmg)
{
	mgr = objmg;
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

void Scene::Draw(SDL_Renderer* rnd)
{
	// Need to move this otherwise a variable is pointlessly getting set every frame TODO: Ask TH & EH where's best to set this
	SDL_Rect* rect = new SDL_Rect(); // TODO:Place these on the stack - JP, TH
	SDL_Rect* crop = new SDL_Rect();
	
	std::for_each(mLayers.begin(), mLayers.end(), [rnd, &rect, &crop](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [rnd, &rect, &crop](RenderObject* obj) {if (obj->IsVisible())


		{
			crop->x = obj->GetAnim()->GetCurrentFrame().first;
			crop->y = obj->GetAnim()->GetCurrentFrame().second;
			crop->w = obj->GetSheet()->GetCellSize().first;
			crop->h = obj->GetSheet()->GetCellSize().second;

			rect->x = obj->GetPos().first;
			rect->y = obj->GetPos().second;
			rect->w = obj->GetSheet()->GetTextureSize().first;
			rect->h = obj->GetSheet()->GetTextureSize().second;
			if (obj->IsVisible())
				SDL_RenderCopy(rnd, obj->GetSheet()->GetTexture(), crop, rect);
				
		}
		});


		});

	
}
// When mouse is inside bounds of a render object in current scene
void Scene::Select(int x, int y, Managers* mgrs)
{
	std::find_if(mLayers.rbegin(), mLayers.rend(), [x, y, &mgrs](std::vector<RenderObject*> layer) {

		return std::find_if(layer.begin(), layer.end(), [x, y, &mgrs](RenderObject* obj) {
			if (obj->InBounds(x, y))
				obj->Select(mgrs);
			return(obj->InBounds(x, y));
			
			} ) != layer.end();

		});
}

void Scene::Clear(SDL_Renderer* rnd)
{
	SDL_RenderClear(rnd);
}

RenderObject* Scene::AddObject(std::string obj, int x, int y, Layer layerNum)
{
	RenderObject* obje = mgr->RequestObject(obj);

	mLayers[layerNum].push_back(obje);
	obje->SetAnim("default");
	obje->SetPos(std::make_pair(x, y));

	return obje;

}
