#include "Scene.h"


void Scene::Update(double dTime)
{
	std::for_each(mLayers.begin(), mLayers.end(), [dTime](std::vector<RenderObject> layer) {
		std::for_each(layer.begin(), layer.end(), [dTime](RenderObject obj) {obj.Update(dTime); });
		});
};

void Scene::Draw(SDL_Surface* wnd)
{
	std::for_each(mLayers.begin(), mLayers.end(), [&wnd](std::vector<RenderObject> layer) {
		std::for_each(layer.begin(), layer.end(), [&wnd](RenderObject obj) {if (obj.IsVisible())SDL_BlitSurface(obj.GetSheet()->GetTexture(), nullptr, wnd, nullptr); });
		});
}