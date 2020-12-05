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
	SDL_Rect* rect = new SDL_Rect();
	SDL_Rect* crop = new SDL_Rect();
	
	std::for_each(mLayers.begin(), mLayers.end(), [&wnd, &rect, &crop](std::vector<RenderObject*> layer) {
		std::for_each(layer.begin(), layer.end(), [&wnd, &rect, &crop](RenderObject* obj) {if (obj->IsVisible())



		{
			crop->x = obj->GetAnim()->GetCurrentCell();
			crop->y = obj->GetAnim()->GetCurrentCell();
			crop->w = obj->GetSheet()->GetCellSize();
			crop->h = obj->GetSheet()->GetCellSize();

			rect->x = obj->GetPos().first;
			rect->y = obj->GetPos().second;
			if (obj->IsVisible())SDL_BlitSurface(obj->GetSheet()->GetTexture(), crop, wnd, rect); // First rectangle references the cell and how to retrieve it from at last, the second relates to its position - T
		}
		});


		});
}

void Scene::Select(int x, int y)
{
	std::find_if(mLayers.rbegin(), mLayers.rend(), [x, y](std::vector<RenderObject*> layer) {

		return std::find_if(layer.begin(), layer.end(), [x, y](RenderObject* obj) {
			if (obj->InBounds(x, y))
				obj->Select();
			return(obj->InBounds(x, y));
			
			} ) != layer.end();

		});
}

void Scene::AddObject(RenderObject* obj, Layer layerNum)
{
	mLayers[layerNum].push_back(obj);
}
