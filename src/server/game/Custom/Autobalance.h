#pragma once
#include "Group.h"
#include "Player.h"
#include "Map.h"
#include "Creature.h"

class Autobalance
{
public:


    struct playersWithoutBonus {
        uint32 prevHealth;
        uint32 prevAP;
        uint32 prevSP;
    };
    static std::map<ObjectGuid, playersWithoutBonus> MplayersWithoutBonus;
    static void PlayerEnterInMap(Player* player);
    static void ApplyBonusModification(Player* player, uint32 diff);
    static void RemoveBonusModification(Player* player, uint32 diff);
    static void AdapteEachPlayersInGroup(Player* player, uint32 diff);

};

