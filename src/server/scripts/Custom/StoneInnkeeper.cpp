#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "ObjectMgr.h"
#include "WorldSession.h"
#include "SpellMgr.h"
#include "SpellDefines.h"
#include "SpellInfo.h"
#include "SharedDefines.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include "DatabaseEnv.h"
#include "Map.h"
#include "DBCStores.h"
#include "WorldSession.h"
#include "DBCStore.h"

class StooneInnkeeperPlayer : public PlayerScript {
public:
    StooneInnkeeperPlayer() : PlayerScript("StooneInnkeeperPlayer") {}


    void OnLogin(Player* player, bool firstLogin) {

        if (firstLogin) {

            QueryResult result = WorldDatabase.PQuery("SELECT map, position_x, position_y, position_z, orientation FROM playercreateinfo WHERE race = %u LIMIT 1", player->getRace());

            if (!result)
                return;


            Field* field = result->Fetch();
            AreaTableEntry const* zone = sAreaTableStore.LookupEntry(player->GetAreaId());

            if (!zone)
                return;

            int locale = player->GetSession()->GetSessionDbcLocale();
            std::string areaName = zone->area_name[locale];

            CharacterDatabase.PExecute("INSERT INTO character_innkeeper_zone  (guid, mapId, x, y, z, o, area_name) VALUES('%u', '%u', '%f', '%f', '%f', '%f', '%s');", (uint32)player->GetGUID(), field[0].GetUInt32(), field[1].GetFloat(), field[2].GetFloat(), field[3].GetFloat(), field[4].GetFloat(), areaName);
        }
    }

};
class StoneInnKeeper : public ItemScript
{
public:
    StoneInnKeeper() : ItemScript("StoneInnKeeper") { }


    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
    {

        if (!player)
            return false;

        if (player->IsInCombat())
            return false;

        if (player->InBattleground())
            return false;


        ClearGossipMenuFor(player); // Clears old options
        QueryResult result = CharacterDatabase.PQuery("SELECT id, area_name FROM character_innkeeper_zone WHERE guid = %u ORDER BY id", player->GetGUID());
        if (result)
        {
            do
            {
                Field* fields = result->Fetch();
                uint32 id = fields[0].GetUInt32();
                std::string area_name = fields[1].GetString();
                AddGossipItemFor(player, 0, "Teleport to " + area_name, GOSSIP_SENDER_MAIN, id);
            } while (result->NextRow());
        }
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
        return false; // Cast the spell on use normally
    }

    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT mapId, x, y, z, o  FROM character_innkeeper_zone WHERE id = %u", action);

        if (!result)
            return;

        Field* fields = result->Fetch();
        uint32 mapId = fields[0].GetUInt32();
        float x = fields[1].GetFloat();
        float y = fields[2].GetFloat();
        float z = fields[3].GetFloat();
        float o = fields[4].GetFloat();

        player->TeleportTo(mapId, x, y, z, o);
        CloseGossipMenuFor(player);
    }
};

void AddSC_StoneInnKeeper() // Add to scriptloader normally
{
    new StooneInnkeeperPlayer();
    new StoneInnKeeper();
}
