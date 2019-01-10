#include "Autobalance.h"
#include "Chat.h"
#include "Language.h"
#include "WorldSession.h"
std::map<ObjectGuid, Autobalance::playersWithoutBonus> Autobalance::MplayersWithoutBonus = {};


void Autobalance::RemoveBonusModification(Player* player, uint32 diff) {

    auto it = Autobalance::MplayersWithoutBonus.find(player->GetGUID());

    if (it != Autobalance::MplayersWithoutBonus.end()) {
        player->ApplySpellPowerBonus(it->second.prevSP, true);
        player->SetStatFlatModifier(UNIT_MOD_ATTACK_POWER, TOTAL_VALUE, it->second.prevAP);
        player->SetMaxHealth(it->second.prevHealth);
    }
}

void Autobalance::AdapteEachPlayersInGroup(Player* player, uint32 diff) {
    Group::MemberSlotList const& members = player->GetGroup()->GetMemberSlots();

    for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        Group::MemberSlot const& slot = *itr;
        if (Player* member = ObjectAccessor::FindPlayer((*itr).guid)) {
            if (member->GetMap()->IsRaid()) {
                Autobalance::RemoveBonusModification(member, diff);
                Autobalance::ApplyBonusModification(member, diff);
           }
        }
    }
}

void Autobalance::ApplyBonusModification(Player* player, uint32 diff) {
    TC_LOG_ERROR("PHASE", "2");

    auto it = Autobalance::MplayersWithoutBonus.find(player->GetGUID());
    TC_LOG_ERROR("PHASE", "3");

    uint32 prevHealth = player->GetMaxHealth();
    uint32 prevSP = player->GetBaseSpellPowerBonus();
    uint32 prevAP = player->GetTotalAttackPowerValue(BASE_ATTACK);
    TC_LOG_ERROR("PHASE", "%u", prevAP);

    TC_LOG_ERROR("PHASE", "%u", prevSP);

    if (it == Autobalance::MplayersWithoutBonus.end()) {
        Autobalance::MplayersWithoutBonus[player->GetGUID()] = { prevHealth, prevAP, prevSP };
    }
    player->ApplySpellPowerBonus(prevSP *(1 *diff), true);
    player->SetStatFlatModifier(UNIT_MOD_ATTACK_POWER, TOTAL_VALUE, prevAP * (0.90 *diff));
    player->SetMaxHealth(prevHealth *= (0.50 * diff));
    player->SetFullHealth();

}

void Autobalance::PlayerEnterInMap(Player* player) {

    if (!player)
        return;

    if (!player->GetMap()->IsRaid())
        return;

    if (!player->GetGroup())
        return;

    Group* group = player->GetGroup();
    MapDifficulty  const *map = player->GetMap()->GetMapDifficulty();

     if (!map)
         return;

     if (map->maxPlayers == 40 || map->maxPlayers == 20)
         return;

     uint32 playerDiff = map->maxPlayers - group->GetMembersCount();

     if (playerDiff == 0)
         return; // group fully grouped;


     TC_LOG_ERROR("PHASE", "1");
     Autobalance::AdapteEachPlayersInGroup(player, playerDiff);
}
