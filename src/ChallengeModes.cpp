/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ChallengeModes.h"

#include "SpellMgr.h"
#include "ScriptMgr.h" 
#include "World.h"
#include "Player.h"
#include "WorldSession.h"
#include "Chat.h" 
#include "ObjectMgr.h"
#include "Log.h"
#include "LFGQueue.h"
#include "RandomDeathChatter.h"
#include "Helper.h"
#include "ItemTemplate.h"

// Function to send a system message (similar to a raid warning) only to the player
void SendPlayerRaidWarning(Player* player, const std::string& message)
{
    if (player)
    {
        // Send the message to the player only
        ChatHandler(player->GetSession()).SendSysMessage("|cffff0000" + message + "|r");
    }
}

//Function for server wide messages to been seen by all online
void SendGlobalMessage(const std::string& message)
{
    ChatHandler chatHandler(NULL);  // Pass 'NULL' because we're not targeting a specific player
    chatHandler.SendWorldText(message.c_str());  // Broadcasts the message to all players
}

// Function to stop challenge when player exceeds level 1
void StopChallengeForPlayer(Player* player)
{
    // Disable all the challenges while not touching HARDCORE_DEAD Setting
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_HARDCORE, 0);  
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_SEMI_HARDCORE, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_SELF_CRAFTED, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_ITEM_QUALITY_LEVEL, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_SLOW_XP_GAIN, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_VERY_SLOW_XP_GAIN, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_QUEST_XP_ONLY, 0); 
    player->UpdatePlayerSetting("mod-challenge-modes", SETTING_IRON_MAN, 0); 	

    // Send a raid warning message only to the player
    SendPlayerRaidWarning(player, "** All Challenges are over for this Character! **");
}

ChallengeModes* ChallengeModes::instance()
{
    static ChallengeModes instance;
    return &instance;
}

bool ChallengeModes::challengeEnabledForPlayer(ChallengeModeSettings setting, Player* player) const
{
    if (!enabled() || !challengeEnabled(setting))
    {
        return false;
    }
    return player->GetPlayerSetting("mod-challenge-modes", setting).value;
}

bool ChallengeModes::challengeEnabled(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreEnable;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreEnable;
        case SETTING_SELF_CRAFTED:
            return selfCraftedEnable;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelEnable;
        case SETTING_SLOW_XP_GAIN:
            return LowXpGainEnable;
        case SETTING_VERY_SLOW_XP_GAIN:
            return veryLowXpGainEnable;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyEnable;
        case SETTING_IRON_MAN:
            return ironManEnable;
        case HARDCORE_DEAD:
            break;
    }
    return false;
}

uint32 ChallengeModes::getDisableLevel(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreDisableLevel;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreDisableLevel;
        case SETTING_SELF_CRAFTED:
            return selfCraftedDisableLevel;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelDisableLevel;
        case SETTING_SLOW_XP_GAIN:
            return LowXpGainDisableLevel;
        case SETTING_VERY_SLOW_XP_GAIN:
            return veryLowXpGainDisableLevel;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyDisableLevel;
        case SETTING_IRON_MAN:
            return ironManDisableLevel;
        case HARDCORE_DEAD:
            break;
    }
    return 0;
}

float ChallengeModes::getXpBonusForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreXpBonus;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreXpBonus;
        case SETTING_SELF_CRAFTED:
            return selfCraftedXpBonus;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelXpBonus;
        case SETTING_SLOW_XP_GAIN:
            return LowXpGainBonus;
        case SETTING_VERY_SLOW_XP_GAIN:
            return veryLowXpGainBonus;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyXpBonus;
        case SETTING_IRON_MAN:
            return ironManXpBonus;
        case HARDCORE_DEAD:
            break;
    }
    return 1;
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getTitleMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreTitleRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreTitleRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedTitleRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelTitleRewards;
        case SETTING_SLOW_XP_GAIN:
            return &LowXpGainTitleRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &veryLowXpGainTitleRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyTitleRewards;
        case SETTING_IRON_MAN:
            return &ironManTitleRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getTalentMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreTalentRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreTalentRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedTalentRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelTalentRewards;
        case SETTING_SLOW_XP_GAIN:
            return &LowXpGainTalentRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &veryLowXpGainTalentRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyTalentRewards;
        case SETTING_IRON_MAN:
            return &ironManTalentRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getItemMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreItemRewards;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreItemRewards;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedItemRewards;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelItemRewards;
        case SETTING_SLOW_XP_GAIN:
            return &LowXpGainItemRewards;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &veryLowXpGainItemRewards;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyItemRewards;
        case SETTING_IRON_MAN:
            return &ironManItemRewards;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

uint32 ChallengeModes::getItemRewardAmount(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return hardcoreItemRewardAmount;
        case SETTING_SEMI_HARDCORE:
            return semiHardcoreItemRewardAmount;
        case SETTING_SELF_CRAFTED:
            return selfCraftedItemRewardAmount;
        case SETTING_ITEM_QUALITY_LEVEL:
            return itemQualityLevelItemRewardAmount;
        case SETTING_SLOW_XP_GAIN:
            return LowXpGainItemRewardAmount;
        case SETTING_VERY_SLOW_XP_GAIN:
            return veryLowXpGainItemRewardAmount;
        case SETTING_QUEST_XP_ONLY:
            return questXpOnlyItemRewardAmount;
        case SETTING_IRON_MAN:
            return ironManItemRewardAmount;
        case HARDCORE_DEAD:
            break;
    }
    return 0;
}

const std::unordered_map<uint8, uint32> *ChallengeModes::getAchievementMapForChallenge(ChallengeModeSettings setting) const
{
    switch (setting)
    {
        case SETTING_HARDCORE:
            return &hardcoreAchievementReward;
        case SETTING_SEMI_HARDCORE:
            return &semiHardcoreAchievementReward;
        case SETTING_SELF_CRAFTED:
            return &selfCraftedAchievementReward;
        case SETTING_ITEM_QUALITY_LEVEL:
            return &itemQualityLevelAchievementReward;
        case SETTING_SLOW_XP_GAIN:
            return &LowXpGainAchievementReward;
        case SETTING_VERY_SLOW_XP_GAIN:
            return &veryLowXpGainAchievementReward;
        case SETTING_QUEST_XP_ONLY:
            return &questXpOnlyAchievementReward;
        case SETTING_IRON_MAN:
            return &ironManAchievementReward;
        case HARDCORE_DEAD:
            break;
    }
    return {};
}

class ChallengeModes_WorldScript : public WorldScript
{
public:
    ChallengeModes_WorldScript()
        : WorldScript("ChallengeModes_WorldScript")
    {}

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        LoadConfig();
    }

private:
    static void LoadStringToMap(std::unordered_map<uint8, uint32> &mapToLoad, const std::string &configString)
    {
        std::string delimitedValue;
        std::stringstream configIdStream;

        configIdStream.str(configString);
        // Process each config ID in the string, delimited by the comma - "," and then space " "
        while (std::getline(configIdStream, delimitedValue, ','))
        {
            std::string pairOne, pairTwo;
            std::stringstream configPairStream(delimitedValue);
            configPairStream>>pairOne>>pairTwo;
            auto configLevel = atoi(pairOne.c_str());
            auto rewardValue = atoi(pairTwo.c_str());
            mapToLoad[configLevel] = rewardValue;
        }
    }

    static void LoadConfig()
    {
        sChallengeModes->itemQualityLevelMaxQuality = static_cast<ItemQualities>(sConfigMgr->GetOption<uint32>("ItemQualityLevel.MaxQuality", ItemQualities::ITEM_QUALITY_POOR));
        sChallengeModes->modifyXP = sConfigMgr->GetOption<bool>("ChallengeModes.ModifyXP", true);
        sChallengeModes->challengesEnabled = sConfigMgr->GetOption<bool>("ChallengeModes.Enable", false);
        if (sChallengeModes->enabled())
        {
            for (auto& [confName, rewardMap] : sChallengeModes->rewardConfigMap)
            {
                rewardMap->clear();
                LoadStringToMap(*rewardMap, sConfigMgr->GetOption<std::string>(confName, ""));
            }

            sChallengeModes->hardcoreEnable          = sConfigMgr->GetOption<bool>("Hardcore.Enable", true);
            sChallengeModes->semiHardcoreEnable      = sConfigMgr->GetOption<bool>("SemiHardcore.Enable", true);
            sChallengeModes->selfCraftedEnable       = sConfigMgr->GetOption<bool>("SelfCrafted.Enable", true);
            sChallengeModes->itemQualityLevelEnable  = sConfigMgr->GetOption<bool>("ItemQualityLevel.Enable", true);
            sChallengeModes->LowXpGainEnable        = sConfigMgr->GetOption<bool>("SlowXpGain.Enable", true);
            sChallengeModes->veryLowXpGainEnable    = sConfigMgr->GetOption<bool>("VerySlowXpGain.Enable", true);
            sChallengeModes->questXpOnlyEnable       = sConfigMgr->GetOption<bool>("QuestXpOnly.Enable", true);
            sChallengeModes->ironManEnable           = sConfigMgr->GetOption<bool>("IronMan.Enable", true);

            sChallengeModes->hardcoreDisableLevel          = sConfigMgr->GetOption<uint32>("Hardcore.DisableLevel", 0);
            sChallengeModes->semiHardcoreDisableLevel      = sConfigMgr->GetOption<uint32>("SemiHardcore.DisableLevel", 0);
            sChallengeModes->selfCraftedDisableLevel       = sConfigMgr->GetOption<uint32>("SelfCrafted.DisableLevel", 0);
            sChallengeModes->itemQualityLevelDisableLevel  = sConfigMgr->GetOption<uint32>("ItemQualityLevel.DisableLevel", 0);
            sChallengeModes->LowXpGainDisableLevel        = sConfigMgr->GetOption<uint32>("SlowXpGain.DisableLevel", 0);
            sChallengeModes->veryLowXpGainDisableLevel    = sConfigMgr->GetOption<uint32>("VerySlowXpGain.DisableLevel", 0);
            sChallengeModes->questXpOnlyDisableLevel       = sConfigMgr->GetOption<uint32>("QuestXpOnly.DisableLevel", 0);
            sChallengeModes->ironManDisableLevel           = sConfigMgr->GetOption<uint32>("IronMan.DisableLevel", 0);

            sChallengeModes->hardcoreXpBonus         = sConfigMgr->GetOption<float>("Hardcore.XPMultiplier", 1.0f);
            sChallengeModes->semiHardcoreXpBonus     = sConfigMgr->GetOption<float>("SemiHardcore.XPMultiplier", 1.0f);
            sChallengeModes->selfCraftedXpBonus      = sConfigMgr->GetOption<float>("SelfCrafted.XPMultiplier", 1.0f);
            sChallengeModes->itemQualityLevelXpBonus = sConfigMgr->GetOption<float>("ItemQualityLevel.XPMultiplier", 1.0f);
            sChallengeModes->questXpOnlyXpBonus      = sConfigMgr->GetOption<float>("QuestXpOnly.XPMultiplier", 1.0f);
            sChallengeModes->LowXpGainBonus         = sConfigMgr->GetOption<float>("SlowXpGain.XPMultiplier", 0.50f);
            sChallengeModes->veryLowXpGainBonus     = sConfigMgr->GetOption<float>("VerySlowXpGain.XPMultiplier", 0.25f);
            sChallengeModes->ironManXpBonus          = sConfigMgr->GetOption<float>("IronMan.XPMultiplier", 1.0f);

            sChallengeModes->hardcoreItemRewardAmount         = sConfigMgr->GetOption<uint32>("Hardcore.ItemRewardAmount", 1);
            sChallengeModes->semiHardcoreItemRewardAmount     = sConfigMgr->GetOption<uint32>("SemiHardcore.ItemRewardAmount", 1);
            sChallengeModes->selfCraftedItemRewardAmount      = sConfigMgr->GetOption<uint32>("SelfCrafted.ItemRewardAmount", 1);
            sChallengeModes->itemQualityLevelItemRewardAmount = sConfigMgr->GetOption<uint32>("ItemQualityLevel.ItemRewardAmount", 1);
            sChallengeModes->LowXpGainItemRewardAmount       = sConfigMgr->GetOption<uint32>("SlowXpGain.ItemRewardAmount", 1);
            sChallengeModes->veryLowXpGainItemRewardAmount   = sConfigMgr->GetOption<uint32>("VerySlowXpGain.ItemRewardAmount", 1);
            sChallengeModes->questXpOnlyItemRewardAmount      = sConfigMgr->GetOption<uint32>("QuestXpOnly.ItemRewardAmount", 1);
            sChallengeModes->ironManItemRewardAmount          = sConfigMgr->GetOption<uint32>("IronMan.ItemRewardAmount", 1);

            LoadStringToMap(sChallengeModes->hardcoreAchievementReward, sConfigMgr->GetOption<std::string>("Hardcore.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->semiHardcoreAchievementReward, sConfigMgr->GetOption<std::string>("SemiHardcore.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->selfCraftedAchievementReward, sConfigMgr->GetOption<std::string>("SelfCrafted.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->itemQualityLevelAchievementReward, sConfigMgr->GetOption<std::string>("ItemQualityLevel.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->LowXpGainAchievementReward, sConfigMgr->GetOption<std::string>("SlowXpGain.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->veryLowXpGainAchievementReward, sConfigMgr->GetOption<std::string>("VerySlowXpGain.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->questXpOnlyAchievementReward, sConfigMgr->GetOption<std::string>("QuestXpOnly.AchievementReward", ""));
            LoadStringToMap(sChallengeModes->ironManAchievementReward, sConfigMgr->GetOption<std::string>("IronMan.AchievementReward", ""));
        }
    }
};

class ChallengeMode : public PlayerScript
{
public:
    explicit ChallengeMode(const char *scriptName,
                           ChallengeModeSettings settingName)
            : PlayerScript(scriptName), settingName(settingName)
    { }
    
    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(settingName, player))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You have the %s challenge mode enabled.", settingName);
        }
    }

    static bool mapContainsKey(const std::unordered_map<uint8, uint32>* mapToCheck, uint8 key)
    {
        return (mapToCheck->find(key) != mapToCheck->end());
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/, uint8 /*xpSource*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(settingName, player) || !sChallengeModes->modifyXP)
        {
            return;
        }
        amount *= sChallengeModes->getXpBonusForChallenge(settingName);
    }

    void OnLevelChanged(Player* player, uint8 /*oldlevel*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(settingName, player))
        {
            return;
        }

        const std::unordered_map<uint8, uint32>* titleRewardMap = sChallengeModes->getTitleMapForChallenge(settingName);
        const std::unordered_map<uint8, uint32>* talentRewardMap = sChallengeModes->getTalentMapForChallenge(settingName);
        const std::unordered_map<uint8, uint32>* itemRewardMap = sChallengeModes->getItemMapForChallenge(settingName);
        const std::unordered_map<uint8, uint32>* achievementRewardMap = sChallengeModes->getAchievementMapForChallenge(settingName);
        uint8 level = player->GetLevel();

        if (mapContainsKey(titleRewardMap, level))
        {
            CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(titleRewardMap->at(level));
            if (!titleInfo)
            {
                //LOG_ERROR("mod-challenge-modes", "Invalid title ID {}!", titleRewardMap->at(level));
                return;
            }
            ChatHandler handler(player->GetSession());
            std::string tNameLink = handler.GetNameLink(player);
            const std::string titletoset = player->getGender() == GENDER_MALE ?
                titleInfo->nameMale[handler.GetSessionDbcLocale()] :
                titleInfo->nameFemale[handler.GetSessionDbcLocale()];
            std::string titleNameStr = Acore::StringFormat(titletoset, player->GetName());
            player->SetTitle(titleInfo);
        }

        if (mapContainsKey(talentRewardMap, level))
        {
            player->RewardExtraBonusTalentPoints(talentRewardMap->at(level));
        }

        if (mapContainsKey(achievementRewardMap, level))
        {
            AchievementEntry const* achievementInfo = sAchievementStore.LookupEntry(achievementRewardMap->at(level));
            if (!achievementInfo)
            {
                //LOG_ERROR("mod-challenge-modes", "Invalid Achievement ID {}!", achievementRewardMap->at(level));
                return;
            }

            ChatHandler handler(player->GetSession());
            std::string tNameLink = handler.GetNameLink(player);
            player->CompletedAchievement(achievementInfo);
        }

        if (mapContainsKey(itemRewardMap, level))
        {
            uint32 itemEntry = itemRewardMap->at(level);
            uint32 itemAmount = sChallengeModes->getItemRewardAmount(settingName); // Fetch item amount from config
            player->SendItemRetrievalMail({ { itemEntry, itemAmount } });
        }

        if (sChallengeModes->getDisableLevel(settingName) && sChallengeModes->getDisableLevel(settingName) <= level)
        {
            player->UpdatePlayerSetting("mod-challenge-modes", settingName, 0);
            StopChallengeForPlayer(player); // Just incase above fails
        }
    }

private:
    ChallengeModeSettings settingName;
};

class ChallengeMode_Hardcore : public ChallengeMode
{
public:
    ChallengeMode_Hardcore() : ChallengeMode("ChallengeMode_Hardcore", SETTING_HARDCORE) {}

    void OnLogin(Player* player) override
    {
        // Reworked login checks
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            // Check if the player is dead
            if (player->GetPlayerSetting("mod-challenge-modes", HARDCORE_DEAD).value == 1)
            {			
                SendPlayerRaidWarning(player, "Challenger: Hardcore Challenge Failed with this Character!");            
                return;
            }
            else
            {
                // If the player is alive but in Hardcore mode, send a warning message
                SendPlayerRaidWarning(player, "Challenger: Hardcore Challenge is Active on this Character!");
            }
        }

        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }
        // If Hardcore is enabled and player dead check only trigger if bugs out above
        if (player->GetPlayerSetting("mod-challenge-modes", HARDCORE_DEAD).value == 1)	
        {
            SendPlayerRaidWarning(player, "Challenger: This Hardcore Character has perished, no resurrection, no second chances!");
            //add kick here if needed
        }
    }

    //DEATHS
    // HardCore Death Events using RandomDeathChatter.h scripts	
    // Resurrection Checks Needed for Hard Core Player checks
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }
        // Keeping Player Dead if bugs out the Kick player 
        player->KillPlayer(); 
        player->GetSession()->KickPlayer("The HardCore Character has perished no resurrection, no second chances!");
    }	
    // Released Player Check
    void OnPlayerReleasedGhost(Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1); // To be safe it's on
        SendPlayerRaidWarning(player, "Challenger: This Hardcore Character has fallen! Their journey ends, and now they are but a mere ghost of their former self!!");		
        //player->GetSession()->KickPlayer("The HardCore Character has perished no resurrection, no second chances!");
    }
    
    // NPC Death Events	
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            return;
        }

        // Calling Random HardCore Deaths Chatter Script
        RandomDeathMessageHard deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomHardDieMessage();
        
        // Send the random message to the player   
        SendPlayerRaidWarning(player, randomDeathMessage);	

        // Send the global Random message to all players
        RandomDeathMessageHCWorld deathMessageGenhc;
        std::string randomWorldDeathMessage = deathMessageGenhc.GetRandomHCWorldDieMessage();	
        std::string messagehc = "Challenger " + player->GetName()+ " " + randomWorldDeathMessage;
        SendGlobalMessage(messagehc);

        // Send Fail to Character to end the one life
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);

    }
	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
	
	    // Send the global Random message to all players
        RandomDeathMessageHCWorld deathMessageGenhc;
        std::string randomWorldDeathMessage = deathMessageGenhc.GetRandomHCWorldDieMessage();	
		std::string messagehc = "Challenger " + killed->GetName()+ " " + randomWorldDeathMessage;
        SendGlobalMessage(messagehc);

		// Send Fail to Character to end the one life
        killed->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
    // Block battleground queue for Hardcore players
    bool CanEnterBattleground(Player* player)
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        {
            // Prevent Hardcore players from entering any battlegrounds
            SendPlayerRaidWarning(player, ">> You cannot participate in Battlegrounds while in Hardcore mode!");
            return false;  // Return false to block entry
        }
        return true;  // Allow entry for non-Hardcore players
    }
};

class ChallengeMode_SemiHardcore : public ChallengeMode
{
public:
    ChallengeMode_SemiHardcore() : ChallengeMode("ChallengeMode_SemiHardcore", SETTING_SEMI_HARDCORE) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Semi-Hardcore Challenge is currently active on this character!");
        }
    }
    // Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				
    }

    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player))
        {
            return;
        }
        for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        {
            if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (pItem->GetTemplate() && !pItem->IsEquipped())
                    continue;
                uint8 slot = pItem->GetSlot();
                ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            }
        }
        player->SetMoney(0);
        
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();

        // Send the random message to the player
		SendPlayerRaidWarning(player, randomDeathMessage);
    }
    // PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SelfCrafted : public ChallengeMode
{
public:
    ChallengeMode_SelfCrafted() : ChallengeMode("ChallengeMode_SelfCrafted", SETTING_SELF_CRAFTED) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Self-Crafted Challenge is currently active on this character!");
        }
    }

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        {
            return true;
        }

        // List of specific quest item IDs, if needed here are fishing rods and mine picks
        static const std::set<uint32> questItemIds = {12225,45120,6256,6365,6366,6367,13544,39371,7297,2901,23875,23877,23876,41615,37358}; // Replace with real quest item IDs

        // Check if the item is of class ITEM_CLASS_QUEST (instead of checking ITEM_FLAG_QUESTITEM)
        if (pItem->GetTemplate()->Class == ITEM_CLASS_QUEST) 
        {
            return true; // It's a quest item by class, allow equipping
        }

        // Check if the item is part of the item list (manual items)
        if (questItemIds.find(pItem->GetTemplate()->ItemId) != questItemIds.end())
        {
            return true; // It's a quest item from your list, allow equipping
        }

        // Check if the item has a valid creator GUID (crafting check)
        if (pItem->GetGuidValue(ITEM_FIELD_CREATOR) == player->GetGUID())
        {
            return true; // It's a crafted item created by this player, allow equipping
        }

        // Allow fishing poles to be equipped since you cannot craft them.
        if (!pItem->GetTemplate()->HasSignature() &&
            pItem->GetTemplate()->Class == ITEM_CLASS_WEAPON &&
            pItem->GetTemplate()->SubClass == ITEM_SUBCLASS_WEAPON_FISHING_POLE)
        {
            return true;
        }

        if (!pItem->GetTemplate()->HasSignature())
        {
            return false;
        }

        return false;
    }

    // Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				

    }

    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        {
            return;
        }

        // Calling Random Deaths Chatter Script
        RandomDeathMessageNormal deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomNormalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);		
	}

    // PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, killed))
        {
            return;
        }	
        
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_ItemQualityLevel : public ChallengeMode
{
public:
    ChallengeMode_ItemQualityLevel() : ChallengeMode("ChallengeMode_ItemQualityLevel", SETTING_ITEM_QUALITY_LEVEL) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Quality Level Challenge is currently active on this character!");
            //Check Player for non challenge Items Equipped removes them if found
            if (CheckItemsInBags(player))
            {
                RemoveEquippedItemsNow(player);
            }
        }		
    }
    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        {
            return true;
        }

        // List of specific quest item IDs, if needed here are fishing rods and mine picks
        static const std::set<uint32> questItemIds = {12225,45120,6256,6365,6366,6367,13544,39371,7297,2901,23875,23877,23876,41615,37358}; // Replace with real quest item IDs

        // Check if the item is of class ITEM_CLASS_QUEST (instead of checking ITEM_FLAG_QUESTITEM)
        if (pItem->GetTemplate()->Class == ITEM_CLASS_QUEST) 
        {
            return true; // It's a quest item by class, allow equipping
        }

        // Check if the item is part of the item list (manual items)
        if (questItemIds.find(pItem->GetTemplate()->ItemId) != questItemIds.end())
        {
            return true; // It's a quest item from your list, allow equipping
        }

        // Allow only items with quality up to ITEM_QUALITY_NORMAL (white and green items)
        if (pItem->GetTemplate()->Quality > (uint32_t)sChallengeModes->itemQualityLevelMaxQuality)
        {
            return false; // Block items with quality higher than normal (blue, purple, etc.)
        }

        // Allow crafted items only if their quality is under ITEM_QUALITY_NORMAL
        if (IsCraftedItem(pItem) && pItem->GetTemplate()->Quality > (uint32_t)sChallengeModes->itemQualityLevelMaxQuality)
        {
            return false; // Block crafted items that are above normal quality.
        }

        return true; // Allow the item if it passes all checks.
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
private:
    // Helper to check if the item is crafted
    bool IsCraftedItem(Item* pItem)
    {
        return pItem->GetTemplate()->HasSignature(); // Check if the item has a signature, indicating it's crafted
    }
    // When player dies in Challenge Events Trigger Here
	// Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				

    }

    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        {
            return;
        }

        // Calling Random Deaths Chatter Script
        RandomDeathMessageNormal deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomNormalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);	
	    
		
	}
		        
	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }
};

class ChallengeMode_SlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_SlowXpGain() : ChallengeMode("ChallengeMode_SlowXpGain", SETTING_SLOW_XP_GAIN) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Half XP Challenge is currently active on this character!");
        }
		
    }

    // Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				
		
    }

    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, player))
        {
            return;
        }

        // Calling Random Deaths Chatter Script
        RandomDeathMessageNormal deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomNormalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);	
	
	}
		        
	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_VerySlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_VerySlowXpGain() : ChallengeMode("ChallengeMode_VerySlowXpGain", SETTING_VERY_SLOW_XP_GAIN) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Low XP Only Challenge is currently active on this character!");
        }
    }

    // Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				

    }

    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, player))
        {
            return;
        }

        // Calling Random Deaths Chatter Script
        RandomDeathMessageNormal deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomNormalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);	
	    
		
	}
		        
	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_QuestXpOnly : public ChallengeMode
{
public:
    ChallengeMode_QuestXpOnly() : ChallengeMode("ChallengeMode_QuestXpOnly", SETTING_QUEST_XP_ONLY) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        {
            SendPlayerRaidWarning(player, "Challenger: The Quest XP Only Challenge is currently active on this character!");
        }
    }

    // Tracking Player Resurrect Events
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        {
            return;
        }
		
		//Cast Debuff on player
		player->AddAura(15007, player); // Resurrection Sickness as punishment
		
        // Calling Random Deaths Chatter Script
        RandomDeathMessageRevival deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomRevivalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);				

    }

    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        {
            return;
        }

        // Calling Random Deaths Chatter Script
        RandomDeathMessageNormal deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomNormalMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);	
	    
		
	}
		        
	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        {
            return;
        }
        if (victim)
        {
            // Still award XP to pets - they won't be able to pass the player's level
            Pet* pet = player->GetPet();
            if (pet && xpSource == XPSOURCE_KILL)
                pet->GivePetXP(player->GetGroup() ? amount / 2 : amount);
            amount = 0;
        }
        else
        {
            ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
        }
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_IronMan : public ChallengeMode
{
public:
    ChallengeMode_IronMan() : ChallengeMode("ChallengeMode_IronMan", SETTING_IRON_MAN) {}

    void OnLogin(Player* player) override
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            // Check if the player is dead
            if (player->GetPlayerSetting("mod-challenge-modes", HARDCORE_DEAD).value == 1)
            {			
                SendPlayerRaidWarning(player, "Challenger: Iron Man Challenge Failed with this Character!");            
                return;
            }
            else
            {
                // If the player is alive but in Iron Man mode, send a warning message
                SendPlayerRaidWarning(player, "Challenger: Iron Man Challenge is Active on this Character!");
                
                //Check Player for non challenge Items Equipped removes them if found	  
                if ((CheckItemsInBags(player)) || (HasEquippedItemWithEnchantment(player))) 
                { 
                    RemoveEquippedItemsNow(player); 
                }
            }
        }
      
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        // If Iron Man is enabled and player dead check only trigger if bugs out above
        if (player->GetPlayerSetting("mod-challenge-modes", HARDCORE_DEAD).value == 1)	
        {
            SendPlayerRaidWarning(player, "Challenger: This Iron Man Character has perished, no resurrection, no second chances!");
            //add kick here if needed
        }
    }

    // Iron Man Death Events using RandomDeathChatter.h scripts
    // Resurrection Checks Needed for Iron Man Player checks
    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        // Keeping Player Dead if bugs out the Kick player 
        player->KillPlayer(); 
        player->GetSession()->KickPlayer("The Iron Man Character has perished no resurrection, no second chances!");
    }

	// Released Player Check
    void OnPlayerReleasedGhost(Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1); // To be safe it's on
		SendPlayerRaidWarning(player, "Challenger: This Iron Man Character has fallen! Their journey ends, and now they are but a mere ghost of their former self!!");		
        //player->GetSession()->KickPlayer("The Iron Man Character has perished no resurrection, no second chances!");
    }
	
    // NPC Death Events
    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }

        // Calling Random Iron Man Deaths Chatter Script
        RandomDeathMessageIron deathMessageGen;
        std::string randomDeathMessage = deathMessageGen.GetRandomIronDieMessage();
		
        // Send the random message to the player   
		SendPlayerRaidWarning(player, randomDeathMessage);	

        // Send the global Random message to all players
        RandomDeathMessageIronWorld deathMessageGenhc;
        std::string randomWorldDeathMessage = deathMessageGenhc.GetRandomHCIronDieMessage();	
		std::string messagehc = "Challenger " + player->GetName()+ " " + randomWorldDeathMessage;
        SendGlobalMessage(messagehc);

		// Send Fail to Character to end the one life
        player->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
	
	}

	// PVP Death Events
    void OnPVPKill(Player* killer, Player* killed) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, killed))
        {
            return;
        }	
	
        // Check if the killer is self-inflicted kill (Picks up Non PVP Events a workaround)
        if (killer == killed)
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessageSelf deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomSelfDieMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
        else
        {
            // Calling Random Deaths Chatter Script
            RandomDeathMessagePVP deathMessageGen;
            std::string randomDeathMessage = deathMessageGen.GetRandomPVPMessage();
            
            // Send the random message to the player   
            SendPlayerRaidWarning(killed, randomDeathMessage);		
        }
	
	    // Send the global Random message to all players
        RandomDeathMessageHeroPVP deathMessageGenIr;
        std::string randomWorldDeathMessageIr = deathMessageGenIr.GetRandomHeroPVPWorldDieMessage();	
		std::string messageIr = "Challenger " + killed->GetName()+ " " + randomWorldDeathMessageIr;
        SendGlobalMessage(messageIr);

		// Send Fail to Character to end the one life
        killed->UpdatePlayerSetting("mod-challenge-modes", HARDCORE_DEAD, 1);
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim, xpSource);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        player->SetFreeTalentPoints(0); // Remove all talent points
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }

    void OnTalentsReset(Player* player, bool /*noCost*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        player->SetFreeTalentPoints(0); // Remove all talent points
    }

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        
        // List of specific quest item IDs, if needed here are fishing rods and mine picks
        static const std::set<uint32> questItemIds = {12225,45120,6256,6365,6366,6367,13544,39371,7297,2901,23875,23877,23876,41615,37358}; // Replace with real quest item IDs

        // Check if the item is of class ITEM_CLASS_QUEST (instead of checking ITEM_FLAG_QUESTITEM)
        if (pItem->GetTemplate()->Class == ITEM_CLASS_QUEST) 
        {
            return true; // It's a quest item by class, allow equipping
        }

        // Check if the item is part of the item list (manual items)
        if (questItemIds.find(pItem->GetTemplate()->ItemId) != questItemIds.end())
        {
            return true; // It's a quest item from your list, allow equipping
        }

        return pItem->GetTemplate()->Quality <= sChallengeModes->itemQualityLevelMaxQuality;
    }

    bool CanApplyEnchantment(Player* player, Item* /*item*/, EnchantmentSlot /*slot*/, bool /*apply*/, bool /*apply_dur*/, bool /*ignore_condition*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        // Are there any exceptions in WotLK? If so need to be added here
        return false;
    }

    void OnLearnSpell(Player* player, uint32 spellID) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return;
        }
        // These professions are class skills so they are always acceptable
        switch (spellID)
        {
            case RUNEFORGING:
            case POISONS:
            case BEAST_TRAINING:
                return;
            default:
                break;
        }
        // Do not allow learning any trade skills
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellID);
        if (!spellInfo)
            return;
        bool shouldForget = false;
        for (uint8 i = 0; i < 3; i++)
        {
            if (spellInfo->Effects[i].Effect == SPELL_EFFECT_TRADE_SKILL)
            {
                shouldForget = true;
            }
        }
        if (shouldForget)
        {
            player->removeSpell(spellID, SPEC_MASK_ALL, false);
        }
    }

    // Updated Canuse - still needs work this is a hacky work around
    bool CanUseItem(Player* player, ItemTemplate const* proto, InventoryResult& /*result*/) override
    {
        // Ensure that Iron Man Challenge is enabled for the player
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }

        // Block potions, elixirs, and flasks if detected
        if (proto->Class == ITEM_CLASS_CONSUMABLE &&
            (proto->SubClass == ITEM_SUBCLASS_POTION ||    // Potion subclass
            proto->SubClass == ITEM_SUBCLASS_ELIXIR ||    // Elixir subclass
            proto->SubClass == ITEM_SUBCLASS_FLASK))      // Flask subclass
        {
            // We check player then trap player in IceBlock and send warning or you can use the kick part if want
            // this is a work around for now code won't detect on use of potions, elixirs, and flasks fully
            player->CastStop();
            SendPlayerRaidWarning(player, "Challenger: You cannot use potions, elixirs, or flasks in Iron Man.");
            player->RemoveAllAuras(); // Remove the buff if any
            player->AddAura(15007, player); // Resurrection Sickness as punishment
            player->CastSpell(player, 65918, true);  // For now we knockdown player for 10sec
            
            // player->GetSession()->KickPlayer("You cannot use potions, elixirs, or flasks in Iron Man"); // Or just kick
            return false;  
        }

        // Do not allow food that provides buffs
        if (proto->Class == ITEM_CLASS_CONSUMABLE && proto->SubClass == ITEM_SUBCLASS_FOOD)
        {
            for (const auto & Spell : proto->Spells)
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(Spell.SpellId);
                if (!spellInfo)
                    continue;

                // Check all effects for buffs that apply to the player
                for (uint8 i = 0; i < 3; i++)
                {
                    if (spellInfo->Effects[i].ApplyAuraName == SPELL_AURA_PERIODIC_TRIGGER_SPELL || 
                        spellInfo->Effects[i].ApplyAuraName == SPELL_AURA_MOD_HEALING ||
                        spellInfo->Effects[i].ApplyAuraName == SPELL_AURA_MOD_STAT)
                    {
                        // We check player then trap player in IceBlock and send warning or you can use the kick part if want
                        // this is a work around for now code won't detect on use of potions, elixirs, and flasks fully
                        player->CastStop();
                        SendPlayerRaidWarning(player, "Challenger: You cannot use food that provides buffs in Iron Man.");
                        player->RemoveAllAuras(); // Remove the buff if any
                        player->AddAura(15007, player); // Resurrection Sickness as punishment
                        player->CastSpell(player, 65918, true);  // For now we knockdown player for 10sec
                    
                        //player->GetSession()->KickPlayer("You cannot use food that provides buffs in Iron Man"); // Or just kick
                        return false;
                    }
                }
            }
        }

        return true; // Allow other items
    }

    bool CanGroupInvite(Player* player, std::string& /*membername*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        return false;
    }

    bool CanGroupAccept(Player* player, Group* /*group*/) override
    {
        if (!sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            return true;
        }
        return false;
    }

    // Block battleground queue for Hardcore players
    bool CanEnterBattleground(Player* player)
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            // Prevent Hardcore players from entering any battlegrounds
            SendPlayerRaidWarning(player, ">> You cannot participate in Battlegrounds while in Hardcore mode!");
            return false;  // Return false to block entry
        }
        return true;  // Allow entry for non-Hardcore players
    }
	
    // Stop honor rewards for Hardcore players
    void OnHonorReward(Player* player, uint32& honorPoints, uint32& bonusHonor) 
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            // Cancel honor reward and set points to zero for Hardcore players
            honorPoints = 0;
            bonusHonor = 0;
            SendPlayerRaidWarning(player, ">> No Honor rewards will be granted!");
        }
    }

    // Block reputation gain for Hardcore players
    void OnReputationChanged(Player* player, int32& repAmount, bool /*forced*/)
    {
        if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        {
            repAmount = 0;
            SendPlayerRaidWarning(player, ">> Reputation gain is disabled!");
        }
    }

};

class gobject_challenge_modes : public GameObjectScript
{
private:
    static bool playerSettingEnabled(Player* player, uint8 settingIndex)
    {
        if (!player)
        return false;

        // Retrieve the setting value (ensure it's valid)
        bool settingValue = player->GetPlayerSetting("mod-challenge-modes", settingIndex).value;

        if (settingValue)
        {
            uint8 playerLevel = player->GetLevel();

            // Check if the player has any active challenge modes
            bool hasActiveChallenge = false;

            // Checking for various challenge modes
            const uint8 challengeSettings[] = {
                SETTING_HARDCORE, SETTING_SEMI_HARDCORE, SETTING_SELF_CRAFTED,
                SETTING_ITEM_QUALITY_LEVEL, SETTING_SLOW_XP_GAIN, SETTING_VERY_SLOW_XP_GAIN,
                SETTING_QUEST_XP_ONLY, SETTING_IRON_MAN
            };

            // Cast the uint8 (setting) to the appropriate enum ChallengeModeSettings
            for (uint8 setting : challengeSettings)
            {
                if (sChallengeModes->challengeEnabledForPlayer(static_cast<ChallengeModeSettings>(setting), player))
                {
                    hasActiveChallenge = true;
                    break;
                }
            }

            // Check if the player is a Death Knight and above level 55
            bool isDeathKnightOver55 = (player->getClass() == CLASS_DEATH_KNIGHT) && (playerLevel > 55);
            
            // If player’s level is greater than 1 and no active challenge, stop challenge access (excluding high-level Death Knights)
            if (playerLevel > 1 && !hasActiveChallenge && !isDeathKnightOver55)
            {
                StopChallengeForPlayer(player);
            }
        }

        return settingValue;
    }

public:
    gobject_challenge_modes() : GameObjectScript("gobject_challenge_modes") { }

    struct gobject_challenge_modesAI: GameObjectAI
    {
        explicit gobject_challenge_modesAI(GameObject* object) : GameObjectAI(object) { };

        bool CanBeSeen(Player const* player) override
        {
            if ((player->GetLevel() > 1 && player->getClass() != CLASS_DEATH_KNIGHT) || (player->GetLevel() > 55))
            {
                return false;
            }
            return sChallengeModes->enabled();
        }
    };

    //New menu System
    bool OnGossipHello(Player* player, GameObject* go) override
    {   
        // Check for items and buffs; bypass if Death Knight
        if (player->getClass() != CLASS_DEATH_KNIGHT && (CheckItemsInBags(player) || HasEquippedItemWithEnchantment(player)))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Your items do not meet the requirements for the Challenge Shrine. You must be in beginner items to qualify!");
        }

        // Check if any challenge is already enabled for the player (this hides other challenges if one is active)
        bool challengeActive = sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player) ||
                            sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player) ||
                            (player->getClass() != CLASS_DEATH_KNIGHT && (CheckItemsInBags(player) || HasEquippedItemWithEnchantment(player)));

        // If a challenge is active, do nothing
        if (challengeActive)
        {
            return true;
        }

        // Function to add challenge items to the menu
        auto addChallengeMenuItem = [player](ChallengeModeSettings setting, const std::string& name) {
            if (sChallengeModes->challengeEnabled(setting) && !playerSettingEnabled(player, setting))
            {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, name, 0, setting);
            }
        };

        // If the player is a Death Knight, show only specific challenges
        if (player->getClass() == CLASS_DEATH_KNIGHT)
        {
            addChallengeMenuItem(SETTING_HARDCORE, "Enable Hardcore Challenge");
            addChallengeMenuItem(SETTING_SEMI_HARDCORE, "Enable Semi-Hardcore Challenge");
            addChallengeMenuItem(SETTING_SLOW_XP_GAIN, "Enable Half XP Challenge");
            addChallengeMenuItem(SETTING_VERY_SLOW_XP_GAIN, "Enable Very Low XP Challenge");
            addChallengeMenuItem(SETTING_QUEST_XP_ONLY, "Enable Quest XP Only Challenge");
        }
        else
        {
            // For normal players, display all challenges
            addChallengeMenuItem(SETTING_HARDCORE, "Enable Hardcore Challenge");
            addChallengeMenuItem(SETTING_SEMI_HARDCORE, "Enable Semi-Hardcore Challenge");
            addChallengeMenuItem(SETTING_SELF_CRAFTED, "Enable Self Crafted Challenge");
            addChallengeMenuItem(SETTING_ITEM_QUALITY_LEVEL, "Enable Quality Level Challenge");
            addChallengeMenuItem(SETTING_SLOW_XP_GAIN, "Enable Half XP Challenge");
            addChallengeMenuItem(SETTING_VERY_SLOW_XP_GAIN, "Enable Very Low XP Challenge");
            addChallengeMenuItem(SETTING_QUEST_XP_ONLY, "Enable Quest XP Only Challenge");
            addChallengeMenuItem(SETTING_IRON_MAN, "Enable Iron Man Challenge");
        }

        // Display the menu
        SendGossipMenuFor(player, 12669, go->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 action) override
    {
        player->UpdatePlayerSetting("mod-challenge-modes", action, 1);
        ChatHandler(player->GetSession()).PSendSysMessage("Challenge Initiated Good Luck Hero!");

        // Send the global Random message to all players
        RandomShrineMessageWorld StartMessageChal;
        std::string randomWorldShrineMessage = StartMessageChal.RandomShrineMessageWorldStart();	
		std::string messageShrineStart = "Challenger " + player->GetName()+ " " + randomWorldShrineMessage;
        SendGlobalMessage(messageShrineStart);
        player->PlayDirectSound(7234);
        CloseGossipMenuFor(player);
        return true;
    }

    GameObjectAI* GetAI(GameObject* object) const override
    {
        return new gobject_challenge_modesAI(object);
    }
};

// Add all scripts in one
void AddSC_mod_challenge_modes()
{
    new ChallengeModes_WorldScript();
    new gobject_challenge_modes();
    new ChallengeMode_Hardcore();
    new ChallengeMode_SemiHardcore();
    new ChallengeMode_SelfCrafted();
    new ChallengeMode_ItemQualityLevel();
    new ChallengeMode_SlowXpGain();
    new ChallengeMode_VerySlowXpGain();
    new ChallengeMode_QuestXpOnly();
    new ChallengeMode_IronMan();
}
