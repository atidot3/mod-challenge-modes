#ifndef HELPER_H
#define HELPER_H

#include "Player.h"
#include "Item.h"
#include "Chat.h"
#include "SpellMgr.h"

  //CoreAlert Messages
  void SendPlayerCoreAlert(Player* player, const std::string& message)
  {
    if (player)
    {
        // Send the message to the player only in organge color
        ChatHandler(player->GetSession()).SendSysMessage("|cffff7f00" + message + "|r");
    }
  }

  // Remove Items Equipped used by SemiHardcore
  void RemoveEquippedItemsAndResetMoney(Player* player)
  {
    // Remove the player's equipped items and inform the player
    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            // Log the item name being removed (optional)
            if (pItem->GetTemplate())
                ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());

            // Destroy the equipped item
            player->DestroyItem(INVENTORY_SLOT_BAG_0, i, true);
        }
    }

    // Remove all player cash
    player->SetMoney(0);
  }


  // Remove Items Equipped but won't reset money here if need to call it
  void RemoveEquippedItemsNow(Player* player)
  {
    // Remove the player's equipped items and inform the player
    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            // Log the item name being removed (optional)
            if (pItem->GetTemplate())
                ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());

            // Destroy the equipped item
            player->DestroyItem(INVENTORY_SLOT_BAG_0, i, true);
        }
    }

  }

  // Remove Items Equipped Armor but leaves Weapons (Wild Man Check)
  void RemoveNonWeaponItems(Player* player)
  {
         // Loop through equipped slots and remove non-weapon items.
        for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        {
            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i); // Get item in each equipment slot
            if (item && item->GetTemplate()->Class != ITEM_CLASS_WEAPON)  // Check if it's not a weapon
            {
                player->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);  // Remove the item
            }
        }
   }

  // Remove Items all from bags (Leaves player equipped alone)
  void RemoveAllItemsInBags(Player* player)
  {
        // Loop through all bag slots and remove all items.
        for (uint8 bagIndex = INVENTORY_SLOT_BAG_0; bagIndex < INVENTORY_SLOT_BAG_END; ++bagIndex)  // Ensures to not exceed INVENTORY_SLOT_BAG_END so no errors pop
        {
            Bag* bag = player->GetBagByPos(bagIndex);  // Get each bag
            if (bag)
            {
                for (uint8 slot = 0; slot < bag->GetBagSize(); ++slot)  // Loop through bag items
                {
                    Item* item = player->GetItemByPos(bagIndex, slot);  // Get item in the bag slot
                    if (item)  // If item exists, destroy it
                    {
                        player->DestroyItem(bagIndex, slot, true);  // Remove the item
                    }
                }
            }
        }    
   }
   
  // Function to check if the item has any enchantments applied
  bool HasItemEnchantment(Item* item)
  {
    if (!item)
        return false;

    // Check if the item has an enchantment in any of the enchantment slots (we'll check up to 7)
    for (uint32 slot = 0; slot < 7; ++slot)  // AzerothCore typically has 7 enchantment slots
    {
        // Pass the correct EnchantmentSlot enum
        EnchantmentSlot enchantmentSlot = static_cast<EnchantmentSlot>(slot); 
        uint32 enchantmentId = item->GetEnchantmentId(enchantmentSlot);  // Get the enchantment ID from the slot
        if (enchantmentId > 0)  // If the enchantment ID is greater than 0, the item has an enchantment
        {
            return true; // Item has an enchantment
        }
    }

    return false; // No enchantment found
  }

   // Main Function to Check if Player has an Equipped Item with an Enchantment
   bool HasEquippedItemWithEnchantment(Player* player)
   {
    for (uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot); // Get item in each equipment slot
        if (item)
        {
            // Check if the item has an enchantment (using the helper function)
            if (HasItemEnchantment(item))
            {
                return true; // Found an item with an enchantment
            }
        }
    }
    return false; // No item with an enchantment found
  }

   // Function to check if the player has items with quality higher than normal (Rare or higher).
   bool CheckItemsInBags(Player* player)
   {   
         bool foundHighQualityItem = false;

        // Check equipped items
        for (uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
        {
            Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);  // Get item in each equipment slot
            if (item)
            {
                // Check if item has a quality higher than normal (Rare or higher)
                ItemTemplate const* itemTemplate = item->GetTemplate();
                if (itemTemplate && itemTemplate->Quality > ITEM_QUALITY_NORMAL)
                {
                    foundHighQualityItem = true;
                    break;  // Exit loop early if a high-quality item is found
                }
            }
        }

        // Check bag items if no high-quality item was found
        if (!foundHighQualityItem)
        {
            // Loop through the bag slots from INVENTORY_SLOT_BAG_0 to INVENTORY_SLOT_BAG_END
            for (uint8 bagIndex = INVENTORY_SLOT_BAG_0; bagIndex < INVENTORY_SLOT_BAG_END; ++bagIndex)
            {
                Bag* bag = player->GetBagByPos(bagIndex);  // Get each bag
                if (bag)
                {
                    for (uint8 slot = 0; slot < bag->GetBagSize(); ++slot)  // Loop through bag items
                    {
                        Item* item = player->GetItemByPos(bagIndex, slot);  // Get item in the bag slot
                        if (item)
                        {
                            // Check if item has a quality higher than normal (Rare or higher)
                            ItemTemplate const* itemTemplate = item->GetTemplate();
                            if (itemTemplate && itemTemplate->Quality > ITEM_QUALITY_NORMAL)
                            {
                                foundHighQualityItem = true;
                                break;  // Exit loop early if a high-quality item is found
                            }
                        }
                    }
                }
                if (foundHighQualityItem) break;  // Exit early from bag loop if a high-quality item is found
            }
        }

        // If a high-quality hits true moves to next step in main script
        if (foundHighQualityItem)
        {
			return true;
        }
        else
        {
           return false;
        }				
   }	

class DuelHandler {
public:
    // Function to handle duel requests
    void OnDuelRequest(Player* challenger, Player* target);
};

// Define the challenge modes to check
int getChallengeMode(Player* player) {
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_HARDCORE, player))
        return SETTING_HARDCORE;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_SEMI_HARDCORE, player))
        return SETTING_SEMI_HARDCORE;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_SELF_CRAFTED, player))
        return SETTING_SELF_CRAFTED;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_ITEM_QUALITY_LEVEL, player))
        return SETTING_ITEM_QUALITY_LEVEL;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_SLOW_XP_GAIN, player))
        return SETTING_SLOW_XP_GAIN;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_VERY_SLOW_XP_GAIN, player))
        return SETTING_VERY_SLOW_XP_GAIN;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_QUEST_XP_ONLY, player))
        return SETTING_QUEST_XP_ONLY;
    if (sChallengeModes->challengeEnabledForPlayer(SETTING_IRON_MAN, player))
        return SETTING_IRON_MAN;

    return -1; // No challenge mode active
}

// DuelHandler class  - has few bugs in message spam to fix (My guess getChallengeMode check is tripping it out)
void DuelHandler::OnDuelRequest(Player* challenger, Player* target)
{
    // Get the challenge mode for both the challenger and target
    int challengerMode = getChallengeMode(challenger);
    int targetMode = getChallengeMode(target);

    // Flag to check if a message has already been sent
    bool messageSent = false;

    // If both players are not in any challenge mode, proceed silently
    if (challengerMode == -1 && targetMode == -1)
    {
        return; // Duel proceeds silently without messages
    }

    // If one player is in a challenge mode and the other is not, cancel the duel
	// NOTE: is a slight bug in message system may show wrong name on target
    if (challengerMode != targetMode)
    {
        if (!messageSent) {
            std::string challengerName = target->GetName();
            std::string message = challengerName + ", you can only duel players who are in the same Challenge mode as you!";
            std::string targetMessage = challengerName + " tried to duel you, but you are in a different Challenge mode!";

            // Log the mismatch in challenge modes
            //LOG_DEBUG("duel", "Duel interrupted: players are not in the same challenge mode."); // Turn on for logs

            // Send a single message to the challenger (you can also send to the target if needed)
            SendPlayerCoreAlert(target, message.c_str()); // was (challengerName, message.c_str()); before change to target due to a bug
           // SendPlayerCoreAlert(target, targetMessage.c_str());  // Optional

            // Set flag indicating message has been sent
            messageSent = true;

            // Cancel the duel
            challenger->DuelComplete(DUEL_INTERRUPTED);
            target->DuelComplete(DUEL_INTERRUPTED);
        }

        return; // Stop further processing
    }

    // If both players are in the same challenge mode (or neither are), allow the duel to proceed
    if (challengerMode != -1)  // Both are in a valid challenge mode
    {
        if (!messageSent) {
            // Only send this message once to both players about the duel proceeding
            std::string duelMessage = "You have been challenged to a Duel!";

            // Send the notification only once to both players
            SendPlayerCoreAlert(challenger, duelMessage.c_str());
            SendPlayerCoreAlert(target, duelMessage.c_str());

            // Set flag indicating message has been sent
            messageSent = true;
        }


    }

    // Duel logic here later... to be done for Duel to death
}


#endif // HELPER_H