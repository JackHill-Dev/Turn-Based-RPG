#include "Scene.h"
#include "GameManager.h"
Scene::Scene(GameManager* objmg)
{
	mgr = objmg;
	std::vector<RenderObject*> rObjects;

	for (int i = 0; i < layerNum; ++i)
	{
		mLayers.push_back(rObjects);
	}
}


void Scene::SceneUpdate(double dTime, Act act, std::pair<int, int> mousePos)
{
	Update(dTime, act, mousePos);
	float rTime = dTime / 1000;
	std::for_each(mLayers.begin(), mLayers.end(), [dTime, rTime, act, mousePos](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [dTime, rTime, act, mousePos](RenderObject* obj) {obj->Update(dTime, act, mousePos); obj->GetAnim()->Advance(dTime); });
		});
	
	
}

void Scene::Update(double dTime, Act act, std::pair<int, int> mousePos)
{
	
};

void Scene::Draw(SDL_Renderer* rnd)
{
	// Need to move this otherwise a variable is pointlessly getting set every frame TODO: Ask TH & EH where's best to set this
	SDL_Rect rect; // TODO:Place these on the stack - JP, TH
	SDL_Rect crop;
	
	std::for_each(mLayers.begin(), mLayers.end(), [rnd, &rect, &crop](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [rnd, &rect, &crop](RenderObject* obj) {if (obj->IsVisible())


		{
			crop.x = obj->GetAnim()->GetCurrentFrame().first * obj->GetSheet()->GetCellSize().first;
			crop.y = obj->GetAnim()->GetCurrentFrame().second * obj->GetSheet()->GetCellSize().second;
			crop.w = obj->GetSheet()->GetCellSize().first;
			crop.h = obj->GetSheet()->GetCellSize().second;

			rect.x = obj->GetPos().first;
			rect.y = obj->GetPos().second;
			rect.w = obj->GetSheet()->GetCellSize().first * obj->scale;
			rect.h = obj->GetSheet()->GetCellSize().second * obj->scale;
			SDL_SetTextureColorMod(obj->GetSheet()->GetTexture(), obj->tint.r, obj->tint.g, obj->tint.b);

			if (obj->IsVisible())
				SDL_RenderCopy(rnd, obj->GetSheet()->GetTexture(), &crop, &rect);
				
		}
		});


		});

	
}
// When mouse is inside bounds of a render object in current scene

void Scene::Clear(SDL_Renderer* rnd)
{
	SDL_RenderClear(rnd);
	SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);
	SDL_RenderPresent(rnd);
	//SDL_FillRect(mSurface, nullptr, SDL_MapRGB(mSurface->format, 0, 0, 0));
}

RenderObject* Scene::AddObject(std::string obj, int x, int y, Layer layerNum)
{
	RenderObject* obje = mgr->RequestObject(obj);

	mLayers[layerNum].push_back(obje);
	obje->SetAnim("default");
	obje->SetPos(std::make_pair(x, y));

	return obje;

}
