#pragma once
#include "Group.h"
#include "Player.h"
#include "Map.h"
#include "Creature.h"

class Autobalance
{
public:
    Autobalance();
    ~Autobalance();

    static void Update(Creature* creature);
    static void DestroyMapCreature(Map* map, bool leave);
    static void UpdateDamage(Unit* creature, uint32 &damage);
    static std::map<uint32 /* instance Id*/, std::map<uint32 /*creature guid*/, uint64 /*creature max health*/>> m_creatures;
    static std::map<uint32 /*creature guid*/, uint64 /*creature max health*/> m_creaturesGUID;

};
