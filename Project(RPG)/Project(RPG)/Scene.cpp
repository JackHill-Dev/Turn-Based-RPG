#include "Scene.h"


void Scene::Update(double dTime, Act act)
{
	std::for_each(mLayers.begin(), mLayers.end(), [dTime, act](std::vector<RenderObject> layer) {
		std::for_each(layer.begin(), layer.end(), [dTime, act](RenderObject obj) {obj.Update(dTime, act); });
		});
};

void Scene::Draw(SDL_Surface* wnd)
{
	std::for_each(mLayers.begin(), mLayers.end(), [&wnd](std::vector<RenderObject> layer) {
		std::for_each(layer.begin(), layer.end(), [&wnd](RenderObject obj) {if (obj.IsVisible())SDL_BlitSurface(obj.GetSheet()->GetTexture(), nullptr, wnd, nullptr); });
		});
}

void Scene::Select(int x, int y)
{
	std::find_if(mLayers.rbegin(), mLayers.rend(), [x, y](std::vector<RenderObject> layer) {

		return std::find_if(layer.begin(), layer.end(), [x, y](RenderObject obj) {
			if (obj.InBounds(x, y))
				obj.Select();
			return(obj.InBounds(x, y));
			
			} ) != layer.end();

		});
}