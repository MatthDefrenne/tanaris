#include "StoreManager.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "DBCStore.h"
#include "SharedDefines.h"
#include "SpellAuras.h"
#include "DBCStores.h"

std::map<int /*category_id*/, std::string> StoreManager::StoreCategories= {};
std::map<int, StoreManager::StoreElement> StoreManager::StoreElements = {};

std::string StoreManager::GetStringPoints(Player* player) {
    return std::to_string(StoreManager::GetDonationPoints(player));
}
static void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
{
    uint32 classmask = player->getClassMask();

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        // wrong skill
        if (skillLine->skillId != skill_id)
            continue;

        // not high rank
        if (skillLine->forward_spellid)
            continue;


        // skip racial skills
        if (skillLine->racemask != 0)
            continue;

        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;

        SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
        if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
            continue;

        player->LearnSpell(skillLine->spellId, false);
    }
}

static bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer)
{
    uint32 skillCount = 0;

    if (pPlayer->HasSkill(SKILL_MINING))
        skillCount++;

    if (pPlayer->HasSkill(SKILL_SKINNING))
        skillCount++;

    if (pPlayer->HasSkill(SKILL_HERBALISM))
        skillCount++;

    if (skillCount >= 2)
        return true;

    for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
    {
        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
        if (!SkillInfo)
            continue;

        if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
            continue;

        if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
            continue;

        const uint32 skillID = SkillInfo->id;
        if (pPlayer->HasSkill(skillID))
            skillCount++;

        if (skillCount >= 2)
            return true;
    }
    return false;
}

static bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
{
    ChatHandler handler(pPlayer->GetSession());
    char* skill_name;

    SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
    skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

    if (!SkillInfo)
    {
       // TC_LOG_ERROR("server.loading", "Profession NPC: received non-valid skill ID (LearnAllRecipesInProfession)");
    }

    LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

    pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 450, 450);
    //handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

    return true;
}



static bool IsSecondarySkill(SkillType skill)
{
    return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
}

static void CompleteLearnProfession(Player *player, SkillType skill)
{
    if (PlayerAlreadyHasTwoProfessions(player) && !IsSecondarySkill(skill)) {
        ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFYou have already two professions. |r");
        return;
    }
    else
    {
        if (!LearnAllRecipesInProfession(player, skill))
            ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFF Error.|r");
    }
}

void StoreManager::LoadStore()
{


    if (!StoreManager::StoreCategories.empty())
        StoreManager::StoreCategories.clear();

    if (!StoreManager::StoreElements.empty())
        StoreManager::StoreElements.clear();

    QueryResult resultCategories = CharacterDatabase.PQuery("SELECT * FROM stores_categories");

    do
    {
        Field* fields = resultCategories->Fetch();

        uint32 id = fields[0].GetUInt32();
        std::string categoryName = fields[1].GetString();

        StoreManager::StoreCategories[id] = categoryName;

    } while (resultCategories->NextRow());


    QueryResult resultStoreElements = CharacterDatabase.PQuery("SELECT * FROM stores");


    do
    {
        Field* fields = resultStoreElements->Fetch();
        StoreManager::StoreElement element;

        int id = fields[0].GetInt32();
        element.cat_id = fields[1].GetInt32();
        element.cost = fields[2].GetInt32();
        element.promo = fields[3].GetInt32();
        element.itemId = fields[4].GetInt32();
        element.type = fields[5].GetString();
        element.amount = fields[6].GetInt32();
        element.text = fields[7].GetString();
        element.gossipId = fields[7].GetInt32();


        StoreManager::StoreElements.insert(std::make_pair(id, element));

    } while (resultStoreElements->NextRow());

}

std::map<int, StoreManager::StoreElement> StoreManager::LoadElementsByCategoryId(int categoryId)
{

    std::map<int, StoreElement> TempMap;

    for (auto it = StoreManager::StoreElements.begin(); it != StoreManager::StoreElements.end(); it++)
    {
        if (categoryId == it->second.cat_id)
            TempMap[it->first] = it->second;
    }

    return TempMap;
}


void StoreManager::Buy(int elementId, Player* player)
{

    auto it = StoreManager::StoreElements.find(elementId);

    if (it != StoreManager::StoreElements.end()) {

        if (StoreManager::GetDonationPoints(player) < it->second.cost) {
            CloseGossipMenuFor(player);
            ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFYou do not have enough donations points.|r");
            return;
        }

        if (it->second.type == "additem") {
            if (player->AddItem(it->second.itemId, it->second.amount)) {
                player->SaveToDB();
            }
            else {
                return;
            }
        }

        if (it->second.type == "levels") {
            if (player->getLevel() < 80) {
                player->GiveLevel(player->getLevel() + it->second.amount);
            }
            else {
                CloseGossipMenuFor(player);
                ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFYour level is too high.|r");
                return;
            }
        }

        if (it->second.type == "gold") {
            player->ModifyMoney(it->second.amount * 10000);
        }

        if (it->second.type == "professions") {
            if (player->HasSkill(it->second.itemId))
            {
                ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFYou have already this profession.|r");
                CloseGossipMenuFor(player);
                return;
            }
            CompleteLearnProfession(player, SkillType(it->second.itemId));

        }

        if (it->second.type == "reputations") {
            player->SetReputation(it->second.itemId, 999999);
        }

        if (it->second.type == "transmogrification") {
            
        }

        if (it->second.type == "customization_faction") {
            ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFJust logout and login to take effect.|r");
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
        }

        if (it->second.type == "customization_race") {
            ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFJust logout and login to take effect.|r");
            player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
        }

        if (it->second.type == "customization_normal") {
            ChatHandler(player->GetSession()).PSendSysMessage("|cffCCFFFFJust logout and login to take effect.|r");
            player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
        }

        if (it->second.type == "premium") {
            ChatHandler(player->GetSession()).PSendSysMessage("|cff80FF00You have now access to premium for %u month(s) :) |r", it->second.amount);
            LoginDatabase.PQuery("UPDATE account SET premium = NOW() + INTERVAL %u month WHERE id = %u", it->second.amount, player->GetSession()->GetAccountId());
        }

        if (StoreManager::GetDonationPoints(player) >= it->second.cost) {
            CloseGossipMenuFor(player);
            ChatHandler(player->GetSession()).PSendSysMessage("|cff80FF00Thank you for buying on our shop! All Tanaris team thanks you :) |r");
            LoginDatabase.PExecute("UPDATE account SET points = points - %u WHERE id = %u", it->second.cost, player->GetSession()->GetAccountId());
            return;
        }
    }
}
int StoreManager::GetDonationPoints(Player * player)
{
    QueryResult result = LoginDatabase.PQuery("SELECT points FROM account WHERE id = %u", player->GetSession()->GetAccountId());
    Field* fields = result->Fetch();
    uint32 points = fields[0].GetUInt32();

    return points;
}

