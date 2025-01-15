# AzerothCore Challenge Modes
Challenge Modes Module for AzerothCore

This module adds the following challenge modes:

- **Hardcore** - Players who die are permanently ghosts and can never be revived.
- **Semi-Hardcore** - Players who die lose all worn equipment and carried gold.
- **Self Crafted** - Players can only wear equipment that they have crafted.
    - Fishing poles are an exception
- **Item Quality Level** - Players can only wear equipment that is of Normal or Poor quality
- **Slow XP Gain** - Players receive 0.5x the normal amount of XP.
- **Very Slow XP Gain** - Players receive 0.25x the normal amount of XP.
- **Quest XP Only** - Players can receive XP only from quests
- **Iron Man Mode** - Enforces the [Iron Man Ruleset](https://wowchallenges.com/challangeinfo/iron-man/)

Challenges can be activated per-character by interacting with the Shrine of Challenge added near the graveyard of each starting area.
Challenges can only be enabled on characters at level 1 (or level 55 for Death Knights).
Challenge-specific XP can be blanket disabled for compatibility with other XP mods (e.g. let mods like [individual-exp](https://github.com/azerothcore/mod-individual-xp) or [dynamic-exp](https://github.com/azerothcore/mod-dynamic-xp) handle the XP awarding).

Multiple challenges can be activated on a single character as long as they do not conflict, such as Hardcore and Semi-Hardcore.

Rewards for reaching level thresholds for each challenge can be added using the Config file, and can include:
- Items
- Titles
- Talent Points
- Increased XP Rate

Rewards are given upon **leveling up** to an indicated level. For example, if you wish to give characters a custom title at level 1 for starting any particular challenge, you should instead award that title at level 2, since newly created characters do not "level up" to level 1 at the start. Likewise, any effects (e.g. GM commands) that let you skip levels entirely will not activate the item awards. For example, if you set an item reward or hitting level 30 while under a challenge, and you GM command a level-up on a character from 28 -> 31, that character will not receive the level 30 award.

Please note that this module uses Player Settings to store enabled challenges, so please ensure EnablePlayerSettings is set to 1 in your worldserver.conf.
