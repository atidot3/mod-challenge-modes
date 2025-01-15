#ifndef AZEROTHCORE_CHALLENGEMODES_H
#define AZEROTHCORE_CHALLENGEMODES_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "GameObjectAI.h"
#include "Pet.h"
#include <map>


enum ChallengeModeSettings
{
    SETTING_HARDCORE           = 0,
    SETTING_SEMI_HARDCORE      = 1,
    SETTING_SELF_CRAFTED       = 2,
    SETTING_ITEM_QUALITY_LEVEL = 3,
    SETTING_SLOW_XP_GAIN       = 4,
    SETTING_VERY_SLOW_XP_GAIN  = 5,
    SETTING_QUEST_XP_ONLY      = 6,
    SETTING_IRON_MAN           = 7,
    HARDCORE_DEAD              = 8
};

enum AllowedProfessions
{
    RUNEFORGING    = 53428,
    POISONS        = 2842,
    BEAST_TRAINING = 5149
};

class ChallengeModes
{
public:
    static ChallengeModes* instance();

    [[nodiscard]] bool enabled() const { return challengesEnabled; }
    [[nodiscard]] bool challengeEnabled(ChallengeModeSettings setting) const;
    [[nodiscard]] std::string GetChallengeNameFromEnum(const uint8& value);
    [[nodiscard]] uint32 getDisableLevel(ChallengeModeSettings setting) const;
    [[nodiscard]] float getXpBonusForChallenge(ChallengeModeSettings setting) const;
    bool challengeEnabledForPlayer(ChallengeModeSettings setting, Player* player) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTitleMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getTalentMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getItemMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] const std::unordered_map<uint8, uint32> *getAchievementMapForChallenge(ChallengeModeSettings setting) const;
    [[nodiscard]] uint32 getItemRewardAmount(ChallengeModeSettings setting) const;

    ItemQualities itemQualityLevelMaxQuality;
    bool modifyXP;
    // Flags for challenge modes enabled
    bool challengesEnabled;
    bool hardcoreEnable;
    bool semiHardcoreEnable;
    bool selfCraftedEnable;
    bool itemQualityLevelEnable;
    bool LowXpGainEnable;
    bool veryLowXpGainEnable;
    bool questXpOnlyEnable;
    bool ironManEnable;

    // Disable levels for each challenge mode
    uint32 hardcoreDisableLevel;
    uint32 semiHardcoreDisableLevel;
    uint32 selfCraftedDisableLevel;
    uint32 itemQualityLevelDisableLevel;
    uint32 LowXpGainDisableLevel;
    uint32 veryLowXpGainDisableLevel;
    uint32 questXpOnlyDisableLevel;
    uint32 ironManDisableLevel;

    // Item reward amounts for each challenge mode
    uint32 hardcoreItemRewardAmount;
    uint32 semiHardcoreItemRewardAmount;
    uint32 selfCraftedItemRewardAmount;
    uint32 itemQualityLevelItemRewardAmount;
    uint32 LowXpGainItemRewardAmount;
    uint32 veryLowXpGainItemRewardAmount;
    uint32 questXpOnlyItemRewardAmount;
    uint32 ironManItemRewardAmount;

    // XP bonuses for each challenge mode
    float hardcoreXpBonus;
    float semiHardcoreXpBonus;
    float selfCraftedXpBonus;
    float itemQualityLevelXpBonus;
    float questXpOnlyXpBonus;
    float LowXpGainBonus;
    float veryLowXpGainBonus;
    float ironManXpBonus;

    // Rewards for each challenge mode, categorized by type
    std::unordered_map<uint8, uint32> hardcoreTitleRewards;
    std::unordered_map<uint8, uint32> semiHardcoreTitleRewards;
    std::unordered_map<uint8, uint32> selfCraftedTitleRewards;
    std::unordered_map<uint8, uint32> itemQualityLevelTitleRewards;
    std::unordered_map<uint8, uint32> LowXpGainTitleRewards;
    std::unordered_map<uint8, uint32> veryLowXpGainTitleRewards;
    std::unordered_map<uint8, uint32> questXpOnlyTitleRewards;
    std::unordered_map<uint8, uint32> ironManTitleRewards;

    std::unordered_map<uint8, uint32> hardcoreItemRewards;
    std::unordered_map<uint8, uint32> semiHardcoreItemRewards;
    std::unordered_map<uint8, uint32> selfCraftedItemRewards;
    std::unordered_map<uint8, uint32> itemQualityLevelItemRewards;
    std::unordered_map<uint8, uint32> LowXpGainItemRewards;
    std::unordered_map<uint8, uint32> veryLowXpGainItemRewards;
    std::unordered_map<uint8, uint32> questXpOnlyItemRewards;
    std::unordered_map<uint8, uint32> ironManItemRewards;

    std::unordered_map<uint8, uint32> hardcoreTalentRewards;
    std::unordered_map<uint8, uint32> semiHardcoreTalentRewards;
    std::unordered_map<uint8, uint32> selfCraftedTalentRewards;
    std::unordered_map<uint8, uint32> itemQualityLevelTalentRewards;
    std::unordered_map<uint8, uint32> LowXpGainTalentRewards;
    std::unordered_map<uint8, uint32> veryLowXpGainTalentRewards;
    std::unordered_map<uint8, uint32> questXpOnlyTalentRewards;
    std::unordered_map<uint8, uint32> ironManTalentRewards;

    std::unordered_map<uint8, uint32> hardcoreAchievementReward;
    std::unordered_map<uint8, uint32> semiHardcoreAchievementReward;
    std::unordered_map<uint8, uint32> selfCraftedAchievementReward;
    std::unordered_map<uint8, uint32> itemQualityLevelAchievementReward;
    std::unordered_map<uint8, uint32> LowXpGainAchievementReward;
    std::unordered_map<uint8, uint32> veryLowXpGainAchievementReward;
    std::unordered_map<uint8, uint32> questXpOnlyAchievementReward;
    std::unordered_map<uint8, uint32> ironManAchievementReward;

    std::unordered_map<std::string, std::unordered_map<uint8, uint32>*> rewardConfigMap =
    {
            { "Hardcore.TitleRewards",                &hardcoreTitleRewards                 },
            { "SemiHardcore.TitleRewards",            &semiHardcoreTitleRewards             },
            { "SelfCrafted.TitleRewards",             &selfCraftedTitleRewards              },
            { "ItemQualityLevel.TitleRewards",        &itemQualityLevelTitleRewards         },
            { "SlowXpGain.TitleRewards",              &LowXpGainTitleRewards                },
            { "VerySlowXpGain.TitleRewards",          &veryLowXpGainTitleRewards            },
            { "QuestXpOnly.TitleRewards",             &questXpOnlyTitleRewards              },
            { "IronMan.TitleRewards",                 &ironManTitleRewards                  },

            { "Hardcore.TalentRewards",               &hardcoreTalentRewards                },
            { "SemiHardcore.TalentRewards",           &semiHardcoreTalentRewards            },
            { "SelfCrafted.TalentRewards",            &selfCraftedTalentRewards             },
            { "ItemQualityLevel.TalentRewards",       &itemQualityLevelTalentRewards        },
            { "SlowXpGain.TalentRewards",             &LowXpGainTalentRewards               },
            { "VerySlowXpGain.TalentRewards",         &veryLowXpGainTalentRewards           },
            { "QuestXpOnly.TalentRewards",            &questXpOnlyTalentRewards             },
            { "IronMan.TalentRewards",                &ironManTalentRewards                 },

            { "Hardcore.ItemRewards",                 &hardcoreItemRewards                  },
            { "SemiHardcore.ItemRewards",             &semiHardcoreItemRewards              },
            { "SelfCrafted.ItemRewards",              &selfCraftedItemRewards               }, 
            { "ItemQualityLevel.ItemRewards",         &itemQualityLevelItemRewards          },
            { "SlowXpGain.ItemRewards",               &LowXpGainItemRewards                 },
            { "VerySlowXpGain.ItemRewards",           &veryLowXpGainItemRewards             },
            { "QuestXpOnly.ItemRewards",              &questXpOnlyItemRewards               },
            { "IronMan.ItemRewards",                  &ironManItemRewards                   },

            { "Hardcore.AchievementReward",           &hardcoreAchievementReward            },
            { "SemiHardcore.AchievementReward",       &semiHardcoreAchievementReward        },
            { "SelfCrafted.AchievementReward",        &selfCraftedAchievementReward         },
            { "ItemQualityLevel.AchievementReward",   &itemQualityLevelAchievementReward    },
            { "SlowXpGain.AchievementReward",         &LowXpGainAchievementReward           },
            { "VerySlowXpGain.AchievementReward",     &veryLowXpGainAchievementReward       },
            { "QuestXpOnly.AchievementReward",        &questXpOnlyAchievementReward         },
            { "IronMan.AchievementReward",            &ironManAchievementReward             }
    };
};

#define sChallengeModes ChallengeModes::instance()

#endif //AZEROTHCORE_CHALLENGEMODES_H
