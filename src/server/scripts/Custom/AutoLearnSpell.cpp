#include "ScriptPCH.h"
#include "DisableMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "AchievementMgr.h"
#include "ArenaTeamMgr.h"
#include "Battleground.h"
#include "CellImpl.h"
#include "ChatTextBuilder.h"
#include "DatabaseEnv.h"
#include "DBCEnums.h"
#include "DisableMgr.h"
#include "GameEventMgr.h"
#include "GameTime.h"
#include "GridNotifiersImpl.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "InstanceScript.h"
#include "Item.h"
#include "Language.h"
#include "Log.h"
#include "Mail.h"
#include "Map.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "World.h"
#include "WorldSession.h"

class LearnSpellsOnLevelUp : public PlayerScript
{
public:
    std::vector<uint32> ignoreSpells;

    LearnSpellsOnLevelUp() : PlayerScript("LearnSpellsOnLevelUp")
    {
        uint32 temp[] = {
            64380, 23885, 23880, 44461, 25346, 10274, 10273, 8418,
            8419, 7270, 7269, 7268, 54648, 12536, 24530, 70909,
            12494, 57933, 24224, 27095, 27096, 27097, 27099, 32841,
            56131, 56160, 56161, 48153, 34754, 64844, 64904, 48085,
            33110, 48084, 28276, 27874,	27873, 7001, 49821, 53022,
            47757, 47750, 47758, 47666, 53001, 52983, 52998, 52986,
            52987, 52999, 52984, 53002, 53003, 53000, 52988, 52985,
            42208, 42209, 42210, 42211, 42212, 42213, 42198, 42937,
            42938, 12484, 12485, 12486, 44461, 55361, 55362, 34913,
            43043, 43044, 38703, 38700, 27076, 42844, 42845, 64891,
            25912, 25914, 25911, 25913, 25902, 25903, 27175, 27176,
            33073, 33074, 48822, 48820, 48823, 48821, 20154, 25997,
            20467, 20425, 67, 26017, 34471, 53254, 13812, 14314,
            14315, 27026, 49064, 49065, 60202, 60210, 13797, 14298,
            14299, 14300, 14301, 27024, 49053, 49054, 52399, 1742,
            24453, 53548, 53562, 52016, 26064, 35346, 57386, 57389,
            57390, 57391, 57392, 57393, 55509, 35886, 43339, 45297,
            45298, 45299, 45300, 45301, 45302, 49268, 49269, 8349,
            15277,
            8502, 8503, 11306, 11307, 25535, 25537, 61650, 61654,
            63685, 45284, 45286, 45287, 45288, 45289, 45290, 45291,
            45292, 45293, 45294, 45295, 45296, 49239, 49240, 26364,
            26365, 26366, 26367, 26369, 26370, 26363, 26371, 26372,
            49278, 49279, 32176, 32175, 21169, 47206, 27285, 47833,
            47836, 42223, 42224, 42225, 42226, 42218, 47817, 47818,
            42231, 42232, 42233, 42230, 48466, 44203, 44205, 44206,
            44207, 44208, 48444, 48445, 33891, 52374, 57532, 59921,
            52372, 49142, 52375, 47633, 47632, 52373, 50536, 27214,
            47822, 11682, 11681, 5857, 1010, 24907, 24905, 53227,
            61391, 61390, 61388, 61387, 64801, 5421, 9635, 1178, 20647,
            20186, 20185, 20184, 20187, 25899, 24406, 50581, 30708, 7160,
        };

        ignoreSpells = std::vector<uint32>(temp, temp + sizeof(temp) / sizeof(temp[0]));
    }

    void OnLevelChanged(Player* player, uint8 oldLevel)
    {
        if (oldLevel < player->getLevel())
            LearnSpellsForNewLevel(player, oldLevel);
    }

    bool IsIgnoredSpell(uint32 spellID)
    {
        for (std::vector<uint32>::const_iterator itr = ignoreSpells.begin(); itr != ignoreSpells.end(); ++itr)
            if (spellID == (*itr))
                return true;
        return false;
    }

    void LearnSpellsForNewLevel(Player* player, uint8 level)
    {
        if (level == player->getLevel() + 1)
            return;


        if ((player->getLevel() == 10)) {
            player->LearnSpell(65917, false);
            player->GetSession()->SendAreaTriggerMessage("Thanks for playing on Tanaris! You are the fee to play on the opening, so, we give you a rare mount! :)");
        }
        uint32 family;
        switch (player->getClass())
        {
        case CLASS_ROGUE:
            family = SPELLFAMILY_ROGUE;
            break;
        case CLASS_DEATH_KNIGHT:
            family = SPELLFAMILY_DEATHKNIGHT;
            break;
        case CLASS_WARRIOR: {
            family = SPELLFAMILY_WARRIOR;
            if (player->getLevel() == 3)
                player->LearnSpell(5308, false);

            if (player->getLevel() == 6)
                player->LearnSpell(3124, false);
        }
                            break;
        case CLASS_PRIEST:
            family = SPELLFAMILY_PRIEST;
            break;
        case CLASS_MAGE:
            family = SPELLFAMILY_MAGE;
            break;
        case CLASS_PALADIN:
            family = SPELLFAMILY_PALADIN;
            break;
        case CLASS_HUNTER: {
            family = SPELLFAMILY_HUNTER;
            if (player->getLevel() == 10) {
                player->LearnSpell(1515, false);
                player->LearnSpell(883, false);
                player->LearnSpell(2641, false);
                player->LearnSpell(6991, false);
                player->LearnSpell(5149, false);
                player->LearnSpell(982, false);
            }
        }
                           break;
        case CLASS_DRUID:
            family = SPELLFAMILY_DRUID;
            break;
        case CLASS_SHAMAN:
            family = SPELLFAMILY_SHAMAN;
            if (player->getLevel() == 2 && !player->HasItemCount(5178, 1)) {
                player->AddItem(5178, 1);
                player->AddItem(5177, 1);
                player->AddItem(5176, 1);
                player->AddItem(5175, 1);
            }
            break;
        case CLASS_WARLOCK:
            family = SPELLFAMILY_WARLOCK;
            break;
        }
        for (uint32 i = 0; i < sSpellMgr->GetSpellInfoStoreSize(); ++i)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(i);
            if (!spellInfo)
                continue;
            if (spellInfo->SpellFamilyName != family)
                continue;
            if (IsIgnoredSpell(spellInfo->Id))
                continue;

            if (spellInfo->PowerType == POWER_FOCUS)
                continue;
 

            
            if (DisableMgr::IsDisabledFor(DISABLE_TYPE_SPELL, spellInfo->Id, player))
                continue;
            if ((spellInfo->AttributesEx7 & SPELL_ATTR7_ALLIANCE_ONLY && player->GetTeam() != ALLIANCE) || (spellInfo->AttributesEx7 & SPELL_ATTR7_HORDE_ONLY && player->GetTeam() != HORDE))
                continue;
            if (spellInfo->BaseLevel != level && sSpellMgr->IsSpellValid(spellInfo, player))
                continue;

            bool valid = false;

            SkillLineAbilityMapBounds bounds = sSpellMgr->GetSkillLineAbilityMapBounds(spellInfo->Id);
            for (SkillLineAbilityMap::const_iterator itr = bounds.first; itr != bounds.second; ++itr)
            {
                if (itr->second->spellId == spellInfo->Id && itr->second->racemask == 0 && itr->second->AutolearnType == 0)
                {
                    valid = true;
                    SpellInfo const* prevSpell = spellInfo->GetPrevRankSpell();
                    if (prevSpell && !player->HasSpell(prevSpell->Id))
                    {
                        valid = false;
                        break;
                    }

                    if (spellInfo->Id == 23455 || spellInfo->Id == 23458 || spellInfo->Id == 23459 || spellInfo->Id == 27803 || spellInfo->Id == 27803 || spellInfo->Id == 27804 || spellInfo->Id == 27805 || spellInfo->Id == 25329)
                        valid = false;


                    if (spellInfo->Id == 23455 || spellInfo->Id == 23458 || spellInfo->Id == 23459 || spellInfo->Id == 27803 || spellInfo->Id == 27803 || spellInfo->Id == 27804 || spellInfo->Id == 27805 || spellInfo->Id == 25329)
                        valid = false;

                    if(spellInfo->Id == 24131
                         || spellInfo->Id == 24134
                        || spellInfo->Id == 24135
                        || spellInfo->Id == 24136
                        || spellInfo->Id == 26186
                        || spellInfo->Id == 49009
                        || spellInfo->Id == 49010
                        || spellInfo->Id == 27069)
                        valid = false;

                    if (spellInfo->Id == 16979)
                        valid = false;

                    if (spellInfo->Id == 49376)
                        valid = false;

                    if (GetTalentSpellPos(itr->second->spellId))
                        if (!prevSpell || !player->HasSpell(prevSpell->Id) || spellInfo->GetRank() == 1)
                            valid = false;
                    break;
                }
            }

            if (valid)
                player->LearnSpell(spellInfo->Id, false);
        }
        LearnSpellsForNewLevel(player, ++level);
    }
};

void AddSC_LearnSpellsOnLevelUp()
{
    new LearnSpellsOnLevelUp();
}
