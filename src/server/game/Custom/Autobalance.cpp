#include "Autobalance.h"
#include "Chat.h"
#include "Language.h"
#include "WorldSession.h"

std::map<uint32 /* instance Id*/, std::map<uint32 /*creature guid*/, uint64 /*creature max health*/>> Autobalance::m_creatures = {};
std::map<uint32 /*creature guid*/, uint64 /*creature max health*/> Autobalance::m_creaturesGUID = {};

void resetCreature(Creature* creature) {
    uint32 instanceId = creature->GetMap()->GetInstanceId();
    uint32 creatureMaxHealth = Autobalance::m_creaturesGUID[creature->GetGUID()];
    creature->SetMaxHealth(creatureMaxHealth);
    creature->SetFullHealth();
    Autobalance::m_creatures[instanceId].insert(std::make_pair(creature->GetGUID(), creature->GetMaxHealth())); // We add the creature guid and he health. by instance Id
}


void setHealthCreature(Map* dungeon, Creature* creature) {

    uint32 playersCount = dungeon->GetPlayersCountExceptGMs();
    InstanceMap* map = dungeon->ToInstanceMap();

    uint32 maxPlayers = map->GetMaxPlayers();

    uint32 diffPlayer = maxPlayers - playersCount;

    if (diffPlayer == 0)
        return; // If the group are fully grouped.

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

    creature->SetMaxHealth(creatureMaxHealth);

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

    if (creature->IsInCombat() && !creature->IsSummon())
        return;

    Map* dungeon = creature->GetMap();

    if (!dungeon->IsRaid())
        return;

    auto itX = Autobalance::m_creaturesGUID.find(creature->GetGUID());

    if (itX == Autobalance::m_creaturesGUID.end())
        // We save the creature max health if we don't have it
        Autobalance::m_creaturesGUID[creature->GetGUID()] = creature->GetMaxHealth();


    auto it = Autobalance::m_creatures.find(dungeon->GetInstanceId());

    if (it != Autobalance::m_creatures.end()) {
        // if we found the instance Id
        auto itJ = it->second.find(creature->GetGUID());
        if (itJ == it->second.end()) {
            // if we don't found the creature guid, we reset them.
            resetCreature(creature);
            setHealthCreature(dungeon, creature);
        }
    }
    else {
        Autobalance::m_creatures[dungeon->GetInstanceId()] = {};
    }

}

void Autobalance::DestroyMapCreature(Map* map, bool leave)
{
    if (!map->IsRaid())
        return;

    uint32 playerCount = map->GetPlayersCountExceptGMs();

    Autobalance::m_creatures[map->GetInstanceId()].clear(); // we reset the map so the loop come on in Unit::update(Unit*);

    if (!map->GetPlayers().isEmpty())
    {
        for (Map::PlayerList::const_iterator itr = map->GetPlayers().begin(); itr != map->GetPlayers().end(); ++itr)
        {
            Player* playerInMap = itr->GetSource()->ToPlayer();
                //ChatHandler(playerInMap->GetSession()).PSendSysMessage(playerInMap->GetSession()->GetTrinityString(LANG_AUTOBALANCE), map->GetMapName(), playerCount);
        }
    }
}

void Autobalance::UpdateDamage(Unit * unit, uint32& damage)
{
    Creature* creature = unit->ToCreature();

    if (!creature)
        return;

    if (!creature->GetMap()->IsRaid())
        return;


    uint32 playersCount = creature->GetMap()->GetPlayersCountExceptGMs();
    InstanceMap* map = creature->GetMap()->ToInstanceMap();

    uint32 maxPlayers = map->GetMaxPlayers();


    uint32 diffPlayer = maxPlayers - playersCount;

    if (diffPlayer == 0)
        return; // If the group are fully grouped.


    switch (maxPlayers)
    {
    case 5:
        for (size_t i = 0; i < diffPlayer; i++)
            damage *= 0.62;
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
