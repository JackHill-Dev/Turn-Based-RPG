#pragma once
#include "Globals.h"
class CardObject
{
public:
	std::string baseCard = "CardObj";
	std::string cardImage;
	std::string text = "default";

	CardObject(std::string cardImage, std::string text) : cardImage(cardImage), text(text) {};
};

