#include "Define.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "WorldSession.h"
#include "DatabaseEnv.h"
#include "StoreManager.h"

#define MENU_ID 99999 // Our menuID used to match the sent menu to select hook (playerscript)

class PlayerGossipStore : public PlayerScript
{
public: 
    PlayerGossipStore() : PlayerScript("PlayerGossipStore") {}

    void OnGossipSelect(Player* player, uint32 menu_id, uint32 /*sender*/, uint32 action) override
    {

        if (menu_id != MENU_ID) // Not the menu coded here? stop.
            return;

        ClearGossipMenuFor(player);

        if (action == 99999) {

            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Donations points : " + StoreManager::GetStringPoints(player), GOSSIP_SENDER_MAIN, 0);

            for (auto it = StoreManager::StoreCategories.begin(); it != StoreManager::StoreCategories.end(); it++)
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, it->second, GOSSIP_SENDER_MAIN, it->first);
            }
            player->PlayerTalkClass->GetGossipMenu().SetMenuId(99999);        // Sets menu ID so we can identify our menu in Select hook. Needs unique number for the menu
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
        }

        if (action < 1000) {
            std::map<int, StoreManager::StoreElement> TempMap = StoreManager::LoadElementsByCategoryId(action);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Donations points : " + StoreManager::GetStringPoints(player), GOSSIP_SENDER_MAIN, 0);
            for (auto it = TempMap.begin(); it != TempMap.end(); it++)
            {
                if (it->first)
                    AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "[" + it->second.text + "]" + " : " + std::to_string(it->second.cost) + " Donations Points", GOSSIP_SENDER_MAIN, it->first);

            }
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "<- Back", GOSSIP_SENDER_MAIN, 99999);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
        }
        else {
            StoreManager::Buy(action, player);
        }


        /*
        switch(action)
        {
        case 9:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Donations points : " + std::to_string(GetDonationsPoints(player)), GOSSIP_SENDER_MAIN, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Gold", GOSSIP_SENDER_MAIN, 0);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Levels", GOSSIP_SENDER_MAIN, 1);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Ground mounts", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Flying mounts", GOSSIP_SENDER_MAIN, 3);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Reputations", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Professions", GOSSIP_SENDER_MAIN, 5);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Crafting composants", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Transmogrifications", GOSSIP_SENDER_MAIN, 7);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Premium", GOSSIP_SENDER_MAIN, 8);
            // SetMenuId must be after clear menu and before send menu!!
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;

        case 0: // golds
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "5000 golds = 3 donations points", GOSSIP_SENDER_MAIN, 1000);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "10000 golds = 6 donations points", GOSSIP_SENDER_MAIN, 1001);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "20000 golds = 10 donations points", GOSSIP_SENDER_MAIN, 1002);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "40000 golds = 20 donations points", GOSSIP_SENDER_MAIN, 1003);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "80000 golds = 35 donations points", GOSSIP_SENDER_MAIN, 1004);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "160000 golds = 45 donations points", GOSSIP_SENDER_MAIN, 1005);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
            break;
        case 1: // Levels
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Instant niveau 68 + 2500 golds = 5 donations points", GOSSIP_SENDER_MAIN, 1006);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Instant niveau 80 + 5000 golds = 20 donations points", GOSSIP_SENDER_MAIN, 1007);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;
        case 2:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Magic Rooster Egg = 10 donations points", GOSSIP_SENDER_MAIN, 1008);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Spectral Tiger =  10 donations points", GOSSIP_SENDER_MAIN, 1009);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Big Battle Bear = 10 donations points", GOSSIP_SENDER_MAIN, 1011);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Wooly White Rhino = 10 donations points", GOSSIP_SENDER_MAIN, 1012);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Swift Zhevra = 10 donations points", GOSSIP_SENDER_MAIN, 1013);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Big Battle Bear = 10 donations points", GOSSIP_SENDER_MAIN, 1014);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Celestial Steed = 10 donations points", GOSSIP_SENDER_MAIN, 1015);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Black Qiraji Resonating Crystal = 10 donations points", GOSSIP_SENDER_MAIN, 1016);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;
        case 3:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "X-51 Nether-Rocket X-TREME | cost 10 donations points", GOSSIP_SENDER_MAIN, 1017);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Big Love Rocket | cost 10 donations points", GOSSIP_SENDER_MAIN, 1018);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Brutal Nether Drake | cost 10 donations points", GOSSIP_SENDER_MAIN, 1019);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Reins of the Black Proto-Drake | cost 10 donations points", GOSSIP_SENDER_MAIN, 1020);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
            break;
        case 4:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to Explorers' League | cost 5 donations points", GOSSIP_SENDER_MAIN, 1021);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to Frenzyheart Tribe | cost 5 donations points", GOSSIP_SENDER_MAIN, 1022);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to The Kalu'ak | cost 5 donations points", GOSSIP_SENDER_MAIN, 1023);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to The Oracles | cost 5 donations points", GOSSIP_SENDER_MAIN, 1024);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to The Wyrmrest Accord | cost 5 donations points", GOSSIP_SENDER_MAIN, 1025);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to Kirin Tor | cost 5 donations points", GOSSIP_SENDER_MAIN, 1026);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Exalted to Knights of the Ebon Blade | cost 5 donations points", GOSSIP_SENDER_MAIN, 1027);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
            break;
        case 5:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\trade_alchemy:30|t Alchemy 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1028);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Ingot_05:30|t Blacksmithing 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1029);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Misc_LeatherScrap_02:30|t Leatherworking 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1030);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:30|t Tailoring 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1031);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\inv_misc_wrench_01:30|t Engineering 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1032);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\trade_engraving:30|t Enchanting 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1033);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\inv_misc_gem_01:30|t Jewelcrafting 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1034);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Scroll_08:30|t Inscription 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1035);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\INV_Misc_Herb_07:30|t Herbalism 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1036);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\inv_misc_pelt_wolf_01:30|t Skinning 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1037);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "|TInterface\\icons\\trade_mining:30|t Mining 450 = 5 donations points", GOSSIP_SENDER_MAIN, 1038);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;
        case 6:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Titansteel Bar x15 = 3 donations points", GOSSIP_SENDER_MAIN, 1039);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Frozen Orb x3 = 3 donations points", GOSSIP_SENDER_MAIN, 1040);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Titansteel Bar x20 = 3 donations points", GOSSIP_SENDER_MAIN, 1041);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Frost Lotus x20 = 3 donations points", GOSSIP_SENDER_MAIN, 1042);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Dream Shard x15 = 3 donations points", GOSSIP_SENDER_MAIN, 1043);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Arctic Fur x10 = 3 donations points", GOSSIP_SENDER_MAIN, 1044);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Fire x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1045);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Earth x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1046);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Life x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1047);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Air x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1048);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Water x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1049);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Eternal Shadow x50 = 3 donations points", GOSSIP_SENDER_MAIN, 1050);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;
        case 7:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 1 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1051);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 2 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1052);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 3 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1053);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 4 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1054);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 5 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1055);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Tier 6 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1056);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Saison 1 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1057);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Saison 2 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1058);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Saison 3 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1059);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Saison 4 transmogrification set = 15 donations points", GOSSIP_SENDER_MAIN, 1060);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());

            break;
        case 8:
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Buy premium for 1 month = 2 donations points", GOSSIP_SENDER_MAIN, 1009);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Buy premium for 3 months = 3 donations points", GOSSIP_SENDER_MAIN, 1009);
            AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, "Buy premium for life = 10 donations points", GOSSIP_SENDER_MAIN, 1009);
            AddGossipItemFor(player, 0, "<- back", GOSSIP_SENDER_MAIN, 9);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, player->GetGUID());
            break;
            */
    }
};

void AddSC_PlayerGossipStore() // Add to scriptloader normally
{
    new PlayerGossipStore();
}
