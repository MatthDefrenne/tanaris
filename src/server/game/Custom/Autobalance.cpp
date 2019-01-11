#include "Autobalance.h"
#include "Chat.h"
#include "Language.h"
#include "WorldSession.h"

std::map<uint32 /* instance Id*/, std::map<uint32 /*creature guid*/, uint64 /*creature max health*/>> Autobalance::m_creatures = {};
std::map<uint32 /*creature guid*/, uint64 /*creature max health*/> Autobalance::m_creaturesGUID = {};

void resetCreature(Creature* creature) {
    uint32 instanceId = creature->GetMap()->GetInstanceId();
    uint32 creatureMaxHealth = Autobalance::m_creaturesGUID[creature->GetGUID()];
    creature->SetCreateHealth(creatureMaxHealth);
    creature->SetMaxHealth(creatureMaxHealth);
    creature->SetStatFlatModifier(UNIT_MOD_HEALTH, BASE_VALUE, (float)creatureMaxHealth);
    creature->ResetPlayerDamageReq();
    creature->SetHealth(creatureMaxHealth);
    Autobalance::m_creatures[instanceId].insert(std::make_pair(creature->GetGUID(), creature->GetMaxHealth())); // We add the creature guid and he health. by instance Id
}


void setHealthCreature(Map* dungeon, Creature* creature) {

    if (!creature)
        return;

    if (!dungeon->IsRaid())
        return;

    uint32 playersCount = dungeon->GetPlayersCountExceptGMs();
    InstanceMap* map = dungeon->ToInstanceMap();

    if (!map)
        return;

    uint32 maxPlayers = map->GetMaxPlayers();

    uint32 diffPlayer = maxPlayers - playersCount;

    if (diffPlayer == 0)
        return; // If the group are fully grouped.

    if (diffPlayer < 5 && maxPlayers == 10)
        diffPlayer = 5;

    if (diffPlayer < 10 && maxPlayers == 25)
        diffPlayer = 5;

    uint64 creatureMaxHealth = creature->GetMaxHealth();

    switch (maxPlayers)
    {
    case 5:
        for (size_t i = 0; i < diffPlayer; i++)
            creatureMaxHealth *= 0.62;
        break;
    case 10:
        for (size_t i = 0; i < diffPlayer; i++)
            creatureMaxHealth *= 0.75;
        break;
    case 20:
        for (size_t i = 0; i < diffPlayer; i++)
            creatureMaxHealth *= 0.85;
        break;
    case 25:
        for (size_t i = 0; i < diffPlayer; i++)
            creatureMaxHealth *= 0.85;
        break;
    case 40:
        for (size_t i = 0; i < diffPlayer; i++)
            creatureMaxHealth *= 0.90;
        break;
    default:
        break;
    }

    creature->SetCreateHealth(creatureMaxHealth);
    creature->SetMaxHealth(creatureMaxHealth);
    creature->SetStatFlatModifier(UNIT_MOD_HEALTH, BASE_VALUE, (float)creatureMaxHealth);
    creature->ResetPlayerDamageReq();
    creature->SetHealth(creatureMaxHealth);

}

Autobalance::Autobalance()
{
}


Autobalance::~Autobalance()
{
}

void Autobalance::Update(Creature * creature)
{

    if (!creature)
        return;

    if (!creature->GetMap()->IsRaid())
        return;

    if (!creature->IsAlive())
        return;

    if (creature->IsInCombat() && !creature->IsSummon())
        return;

   

    auto itX = Autobalance::m_creaturesGUID.find(creature->GetGUID());

    if (itX == Autobalance::m_creaturesGUID.end())
        // We save the creature max health if we don't have it
        Autobalance::m_creaturesGUID[creature->GetGUID()] = creature->GetMaxHealth();


    auto it = Autobalance::m_creatures.find(creature->GetMap()->GetInstanceId());

    if (it != Autobalance::m_creatures.end()) {
        // if we found the instance Id
        auto itJ = it->second.find(creature->GetGUID());
        if (itJ == it->second.end()) {
            // if we don't found the creature guid, we reset them.
            resetCreature(creature);
            setHealthCreature(creature->GetMap(), creature);
        }
    }
    else {
        Autobalance::m_creatures[creature->GetMap()->GetInstanceId()] = {};
    }

}

void Autobalance::DestroyMapCreature(Map* map, bool leave)
{
    if (!map->IsRaid())
        return;

    uint32 playerCount = map->GetPlayersCountExceptGMs();

    if (playerCount <= 1)
        return;

    Autobalance::m_creatures[map->GetInstanceId()].clear(); // we reset the map so the loop come on in Unit::update(Unit*);

    if (!map->GetPlayers().isEmpty())
    {
        for (Map::PlayerList::const_iterator itr = map->GetPlayers().begin(); itr != map->GetPlayers().end(); ++itr)
        {
            if (Player* playerInMap = itr->GetSource()->ToPlayer())
                ChatHandler(playerInMap->GetSession()).PSendSysMessage("[Autobalance] : %s will be adapted for %u", map->GetMapName(), playerCount);
        }
    }
}

void Autobalance::UpdateDamage(Unit* unit, uint32& damage)
{
    if (!unit)
        return;

    if (!unit->GetMap()->IsRaid())
        return;

    if (Player* player = unit->ToPlayer())
        return;

    uint32 playersCount = unit->GetMap()->GetPlayersCountExceptGMs();
    InstanceMap* map = unit->GetMap()->ToInstanceMap();

    uint32 maxPlayers = map->GetMaxPlayers();

    uint32 diffPlayer = maxPlayers - playersCount;

    if (diffPlayer == 0)
        return; // If the group are fully grouped.

    if (diffPlayer < 5 && maxPlayers == 10)
        diffPlayer = 5;

    if (diffPlayer < 10 && maxPlayers == 25)
        diffPlayer = 5;


    switch (maxPlayers)
    {
    case 5:
        for (size_t i = 0; i < diffPlayer; i++)
            damage *= 0.63;
        break;
    case 10:
        for (size_t i = 0; i < diffPlayer; i++)
            damage *= 0.75;
        break;
    case 25:
        for (size_t i = 0; i < diffPlayer; i++)
            damage *= 0.85;
        break;
    case 40:
        for (size_t i = 0; i < diffPlayer; i++)
            damage *= 0.75;
        break;
    default:
        break;
    }

}
