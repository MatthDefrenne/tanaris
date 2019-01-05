#include "FlexDungeon.h"


void SendMessageToGroup(Group* group, Map* map, uint32 playersDiff) {

    if (!group)
        return;

    if (playersDiff == 0)
        return;

    Group::MemberSlotList const& members = group->GetMemberSlots();


    for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        Group::MemberSlot const& slot = *itr;
        if (Player* member = ObjectAccessor::FindPlayer((*itr).guid)) {
            ChatHandler(member->GetSession()).PSendSysMessage("There miss %u player(s) for %s your group will be adapted.", playersDiff, map->GetMapName());
        }
    }

}

void BuffGroup(Group* group, bool apply) {

    if (!group)
        return;

    Group::MemberSlotList const& members = group->GetMemberSlots();


    for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        Group::MemberSlot const& slot = *itr;
        if (Player* member = ObjectAccessor::FindPlayer((*itr).guid)) {
            if (member) {
                if (apply)
                    member->AddAura(80000, member);
                else
                    member->RemoveAura(80000);
            }
          
        }
    }
}


void FlexDungeon::PlayerEnterInMap(Player* player, Map* map)
{

    if (!player)
        return;

    if (!map->IsRaid())
        return;


    Group* group = player->GetGroup();

    if (!group)
        return;

    BuffGroup(group, false);

    MapDifficulty const* mapDiff = map->GetMapDifficulty();

    if (mapDiff->maxPlayers == 40) // Skip raid vanilla
        return;

    if (!mapDiff)
        return;
    
    uint32 maxPlayers = mapDiff->maxPlayers;
    uint32 playersDiff = maxPlayers - group->GetMembersCount();
    TC_LOG_ERROR("ERROR", "ERROR 8");

    if (group->GetMembersCount() < 5 && maxPlayers == 10) {

        ChatHandler(player->GetSession()).PSendSysMessage("To benefit from the flex raid you must be at least 5 in your group");
        TC_LOG_ERROR("ERROR", "ERROR 9");
        return;
    }
    if (group->GetMembersCount() < 5 && maxPlayers == 25) {
        ChatHandler(player->GetSession()).PSendSysMessage("To benefit from the flex raid you must be at least 10 in your group");
        TC_LOG_ERROR("ERROR", "ERROR 9 bis");
        return;
    }

    for (uint32 i = 0; i < playersDiff; i++)
        BuffGroup(group, true);

    SendMessageToGroup(group, player->GetMap(), playersDiff);

}

void FlexDungeon::PlayerLeaveMap(Player* player, Map * map)
{

    if(!map->IsDungeon() || !map->IsRaid())
         player->RemoveAura(80000);

}

void FlexDungeon::PlayerRemovedFromGroup(Group * group)
{
    TC_LOG_ERROR("ERROR", "ERROR 1");
    if (!group)
        return;

    if (!group->InInstance())
        return;
    TC_LOG_ERROR("ERROR", "ERROR 2");

    BuffGroup(group, false);
    TC_LOG_ERROR("ERROR", "ERROR 3");

    Player* player = ObjectAccessor::FindPlayer(group->GetLeaderGUID());
    TC_LOG_ERROR("ERROR", "ERROR 4");

    if (!player->GetMap()->IsRaid())
        return;

    if (!player)
        return;
    TC_LOG_ERROR("ERROR", "ERROR 5");

    MapDifficulty const* mapDiff = player->GetMap()->GetMapDifficulty();
    TC_LOG_ERROR("sql.driver", "%u", mapDiff->maxPlayers);

    if (mapDiff->maxPlayers == 40) // Skip raid vanilla
        return;

    if (!mapDiff)
        return;

    TC_LOG_ERROR("ERROR", "ERROR 7");

    uint32 maxPlayers = mapDiff->maxPlayers;

    uint32 playersDiff = maxPlayers - group->GetMembersCount();
    TC_LOG_ERROR("ERROR", "ERROR 8");

    if (group->GetMembersCount() < 5 && maxPlayers == 10) {

        ChatHandler(player->GetSession()).PSendSysMessage("To benefit from the flex raid you must be at least 5 in your group");
        TC_LOG_ERROR("ERROR", "ERROR 9");
        return;
    }
    if (group->GetMembersCount() < 5 && maxPlayers == 25) {

        ChatHandler(player->GetSession()).PSendSysMessage("To benefit from the flex raid you must be at least 10 in your group");
        TC_LOG_ERROR("ERROR", "ERROR 9 bis");
        return;
    }

    TC_LOG_ERROR("ERROR", "ERROR 10");

    if (playersDiff == 0)
        return;
    TC_LOG_ERROR("ERROR", "ERROR 11");

    for (uint32 i = 0; i < playersDiff; i++)
        BuffGroup(group, true);
    TC_LOG_ERROR("ERROR", "ERROR 12");

    SendMessageToGroup(group, player->GetMap(), playersDiff);
    TC_LOG_ERROR("ERROR", "ERROR 13");

}
