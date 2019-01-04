#pragma once
#include "Bag.h"
#include "Common.h"
#include "Config.h"
#include "Creature.h"
#include "DatabaseEnv.h"
#include "DBCStructure.h"
#include "Define.h"
#include "Field.h"
#include "GameEventMgr.h"
#include "GossipDef.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "Language.h"
#include "Log.h"
#include "Player.h"
#include "ObjectGuid.h"
#include "ObjectMgr.h"
#include "QueryResult.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "Transaction.h"
#include "WorldSession.h"
#include <sstream>
#include <string>
#include "ObjectMgr.h"
#include "ObjectAccessor.h"
#include "Map.h"
#include "Group.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Log.h"

class FlexDungeon {

public:
    static void PlayerEnterInMap(Player* player, Map* map);
    static void PlayerLeaveMap(Player* player, Map* map);
    static void PlayerRemovedFromGroup(Group* group);
};
