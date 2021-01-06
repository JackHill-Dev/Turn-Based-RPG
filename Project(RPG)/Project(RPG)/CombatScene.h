#pragma once
#include "Scene.h"
#include "Card.h"

class CombatScene :
    public Scene
{
public:
    struct tile
    {
        RenderObject* square = NULL;
        std::pair<float, float> pos;
        bool availiable = true;
    };
    CombatScene(Interface* objmg);
    void Update(double dTime, Act act,std::pair<int, int> mouse) override;
    CombatScene* Load(std::vector<Character*> player, std::vector<Character*> enemy);
private:
    void Cast(Card* card, std::pair<Character*, tile*>* caster, std::pair<Character*, tile*>* target);
    void LoadHand();
    std::vector<Character> chars{};
    
    //std::vector<Character*> enemy{};
    std::vector<Card*> playerHand{};
};

