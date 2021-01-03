#pragma once
#include "Scene.h"
#include "Card.h"
#include "Character.h"
#include "CombatScene.h"
class CombatScene :
    public Scene
{
public:
    CombatScene(GameManager* objmg);
    void Update(double dTime, Act act,std::pair<int, int> mouse) override;
    CombatScene* Load(std::vector<Character*> player, std::vector<Character*> enemy);
private:
    void Cast(Card* card, Character* caster, Character* target);
    void LoadHand();
    std::vector<Character> chars{};
    std::vector<Character*> team{};
    std::vector<Character*> enemy{};
    std::vector<Card*> playerHand{};
};

