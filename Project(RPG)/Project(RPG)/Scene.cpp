#include "Scene.h"
#include "GameManager.h"
Scene::Scene(Interface* objmg)
{
	mgr = objmg;
	std::vector<RenderObject*> rObjects;

	for (int i = 0; i < layerNum; ++i)
	{
		mLayers.push_back(rObjects);
	}

	mFont = TTF_OpenFont("Assets/Fonts/Silver.ttf", 32);
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
	SDL_Rect rect;
	SDL_Rect crop;
	
	std::for_each(mLayers.begin(), mLayers.end(), [rnd, &rect, &crop](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [rnd, &rect, &crop](RenderObject* obj) {if (obj->IsVisible())


		{
			crop.x = obj->GetAnim()->GetCurrentFrame().first * obj->GetSheet()->GetCellSize().first;
			crop.y = obj->GetAnim()->GetCurrentFrame().second * obj->GetSheet()->GetCellSize().second;
			crop.w = obj->GetSheet()->GetCellSize().first;
			crop.h = obj->GetSheet()->GetCellSize().second;

			
			rect.w = obj->GetSheet()->GetCellSize().first * obj->scale; //scaling currentky buggy with inbounds, need to fix -T
			rect.h = obj->GetSheet()->GetCellSize().second * obj->scale;

			rect.x = obj->GetPos().first - rect.w/2;
			rect.y = obj->GetPos().second - rect.h/2;

			SDL_SetTextureColorMod(obj->GetSheet()->GetTexture(), obj->tint.r, obj->tint.g, obj->tint.b);

			if (obj->IsVisible())
				SDL_RenderCopy(rnd, obj->GetSheet()->GetTexture(), &crop, &rect);
		}
		});


		});

	for (auto t : mSceneText)
	{
		rect.x = t.second.pos.first;
		rect.y = t.second.pos.second;
		rect.w = 90;
		rect.h = 70;
		SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(rnd, TTF_RenderText_Solid(mFont, t.second.text.c_str(), t.second.textColor));;
	    
		SDL_RenderCopy(rnd, fontTexture, nullptr, &rect);
	}

	
	++counter;
}
// When mouse is inside bounds of a render object in current scene

void Scene::Clear(SDL_Renderer* rnd)
{
	SDL_RenderClear(rnd);
	SDL_SetRenderDrawColor(rnd, 255, 0, 0, 255);
	SDL_RenderPresent(rnd);
}


RenderObject* Scene::AddObject(std::string obj, int x, int y, Layer layerNum)
{
	RenderObject* obje = mgr->RequestObject(obj);

	mLayers[layerNum].push_back(obje);

	obje->SetAnim("default");
	obje->SetPos(std::make_pair(x, y));
	return obje;

	return obje;

}
