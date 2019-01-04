#pragma once
#include <map>
#include "DatabaseEnv.h"
#include "World.h"
#include "Player.h"
#include "WorldSession.h"

class StoreManager {

public:
    static struct StoreElement {
        int cat_id;
        int cost;
        int promo;
        int itemId;
        std::string type;
        int amount;
        std::string text;
    };

    static std::map<int /*category_id*/, std::string> StoreCategories;
    static std::map<int, StoreElement> StoreElements;

    static void LoadStore();
    static std::map<int, StoreElement> LoadElementsByCategoryId(int categoryId);
    static void Buy(int elementId, Player* player);
    static int GetDonationPoints(Player* player);
    static std::string GetStringPoints(Player* player);
};
