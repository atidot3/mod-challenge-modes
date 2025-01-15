#pragma once
#include <vector>
#include <string>  
#include <cstdlib> // For randomization
#include <ctime>   // For seeding randomness

// Revival Messages
class RandomDeathMessageRevival
{
public:
    RandomDeathMessageRevival()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomRevivalMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Back from the dead and ready to die again!",
            "Resurrected and still clueless. Let's do this!",
            "Like a bad penny, you're back again!",
            "Who needs a second chance? You do. Here you go!",
            "Resurrected! But this time, try not to step in the lava.",
            "You've been brought back to life. Try not to die this time!",
            "You're alive again! Please don’t waste it.",
            "Reborn, and still no better at dodging attacks.",
            "Looks like the afterlife wasn’t for you. Try not to mess it up this time!",
            "Good news: You’re alive! Bad news: You’re still you.",
            "Back from the abyss! Let’s pretend that never happened.",
            "Guess what? You’ve got a second shot at failure!",
            "Resurrected, but the real question is—why?",
            "Your respawn timer is up, and so is your chance at redemption!",
            "Surprise! It’s your second life. Don’t blow it.",
            "Welcome back! The death toll has been greatly exaggerated.",
            "You’ve been revived... just in time for more disaster!",
            "Back from the grave, but not from your bad decisions!",
            "Rise and shine! Or just rise. Maybe no shining this time.",
            "Resurrection complete! Try to stay alive for more than 30 seconds this time.",
            "Guess who’s back? Back from the dead! And probably back to dying.",
            "You’ve been brought back to life! Not sure why, but here we are.",
            "Alive again! Try not to trip on the way out.",
            "Resurrected! Now go make some poor choices... again.",
            "You're back! Let's see how long it takes to screw this up.",
            "Welcome back! Please avoid any fatal mistakes this time.",
            "You've risen from the grave! No promises on staying alive this time.",
            "Reborn! Don’t waste this glorious second chance.",
            "Your body may be back, but your brain is still in the grave.",
            "Resurrected and ready to ruin another round!",
            "Good news: You're not dead. Bad news: You still can be.",
            "Guess who's back! And still terrible at this.",
            "Back in action! Let’s try not to repeat the last few mistakes.",
            "You’ve been revived! Just don’t take another nap in the middle of the battlefield.",
            "You're alive again, which means more chances to fail spectacularly!",
            "Back from the dead and still not ready for battle.",
            "Survived death… for now. Try not to waste your second chance!",
            "You're alive! Let’s see if you can survive the next five minutes.",
            "Resurrected and still clueless about what’s going on.",
            "Back from the abyss! Please, don’t run into the same trap again.",
            "You’ve returned from the grave. But seriously, avoid the fire this time.",
            "Reborn and ready to be an even bigger disaster!",
            "Resurrection complete. Now, let's not screw this up again.",
            "You’ve been revived. Don’t waste this second chance like you wasted the first!",
            "Back in the game and still no better at dodging.",
            "Reanimated! This time, try to avoid dying from stupidity.",
            "Life 2.0! Still better than the first run, right?",
            "You’ve been revived. Let’s try not to immediately walk into danger.",
            "Back from the grave! This time, don’t rush into battle with your eyes closed.",
            "Congratulations, you’re alive again! Let’s not make it a habit.",
            "Resurrected and still unsure if you’re ready for this."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Normal Deaths
class RandomDeathMessageNormal
{
public:
    RandomDeathMessageNormal()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomNormalMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Oops, you ran straight into that one like a pro!",
            "Death by bad decisions. Well, it was a good run.",
            "At least you're dying with style—albeit poorly.",
            "Your health bar was a *lot* shorter than I thought!",
            "Well, that was one way to waste your life!",
            "So close... yet so very dead!",
            "Your enemy may have slain you, but your ego survived… for now.",
            "You've been eliminated from the game. Try again next life!",
            "Now’s a good time to rethink all your life choices.",
            "It wasn’t your fault... except it totally was.",
            "Looks like your respawn timer is now your best friend!",
            "Sometimes you gotta die to learn. Sometimes you just gotta die.",
            "Death by misclick. Oof, we've all been there.",
            "Better luck next time! Unless you’re *really* bad at this.",
            "Hey, you made it to the afterlife. That’s something, right?",
            "You just took a one-way trip to the graveyard!",
            "Your last words: 'I think I can take this guy.'",
            "That was a tactical mistake. Maybe try running next time?",
            "Oof, That was such a Hunter move, try running next time!",
            "Who needs loot when you can have an epic death, right?",
            "Death came swiftly… like that last pizza slice you should’ve eaten.",
            "Congratulations! You’ve been promoted to ghost!",
            "Well, that’s what happens when you charge in headfirst. RIP.",
            "You’ve been slain. Try not to die like that again.",
            "Your lack of dodge skills just got you into trouble!",
            "Your death was sponsored by poor timing and bad decisions.",
            "You’ve been outsmarted by the enemy’s brain… oh wait, it’s just AI.",
            "Death by overconfidence. Should’ve brought backup.",
            "Oops, looks like you didn’t pay attention to your surroundings!",
            "You died, but at least you died like a true hero… well, kind of.",
            "Sometimes the floor is more dangerous than the enemy.",
            "Not the best way to go, but it’s definitely memorable.",
            "Defeated by the ancient art of ‘standing still.’",
            "You’ve been vanquished! Well, at least it wasn’t embarrassing… oh wait.",
            "That was a one-hit wonder. Too bad it was *your* one hit.",
            "I’d say rest in peace, but I think you’ve learned nothing.",
            "Sometimes it’s not the enemy that kills you—it’s your own incompetence.",
            "Death came knocking, and you opened the door.",
            "Here lies the remains of a very questionable decision.",
            "You're dead, and it’s not even a surprise at this point.",
            "Your last mistake was standing still. And breathing.",
            "You've just joined the elite club of the dead. Membership fee: your life.",
            "Don't worry, everyone dies eventually. Yours was just sooner.",
            "I thought you were supposed to be a pro? Guess not.",
            "Well, that was one way to ruin your streak of victory.",
            "Death is just a reset button, but it sure stings!",
            "You’ve been slain by the very thing you were trying to avoid: your own stupidity.",
            "Looks like your chances of survival were, well, *zero*.",
            "That was a tragic, but educational, mistake. Try again!",
            "Well, that was a spectacular failure. See you in the afterlife!",
            "Here lies your dignity—crushed under a giant, metaphorical boot."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// PVP Deaths
class RandomDeathMessagePVP
{
public:
    RandomDeathMessagePVP()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomPVPMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Outplayed! Bet you didn’t see that coming!",
            "PvP? More like *PWNED*!",
            "Looks like you got *rekt* in the most epic way possible!",
            "Your opponent called, they want their victory lap now.",
            "Your skills are no match for their... skills. Sorry!",
            "You’ve been defeated by the superior PvP-er. Better luck next time!",
            "Death by player. The most personal kind of death.",
            "Well, that was a quick and brutal lesson in PvP combat.",
            "Your opponent’s reaction time is better than your life choices.",
            "You’ve just been 1v1'd into the ground!",
            "Guess you were a little too cocky for that battle.",
            "Looks like you lost the PvP lottery. Try again!",
            "That's what happens when you pick the wrong fight.",
            "Congrats, you're now part of the other player's kill streak!",
            "Your PvP strategy: Run straight into battle and pray for a miracle.",
            "Your enemy just showed you how PvP is done. You might want to take notes.",
            "Someone call a medic! Wait... they're already dead.",
            "You just got outplayed, outsmarted, and outclassed. Nice try!",
            "PvP in a nutshell: You lose. A lot.",
            "Death by PvP. It’s a rite of passage, really.",
            "Looks like you’re about to make a *great* ghost!",
            "Just a heads-up, your opponent has more skill points than you.",
            "Congratulations, you’ve been defeated in the most humiliating way possible.",
            "Well, that was embarrassing. Let’s pretend it never happened.",
            "PvP? I think you meant to say ‘PvL’ (Player vs. Luck).",
            "Not even close, my friend. Better start practicing.",
            "Looks like you brought a knife to a gunfight. And lost.",
            "You’ve been bested in the most epic PvP showdown ever… sort of.",
            "Your opponent just taught you the true meaning of PvP.",
            "PvP? More like 'Pick your poison'. You chose wrong.",
            "Well, that was one way to lose with style.",
            "PvP: Where your ego gets destroyed faster than your health bar.",
            "Looks like you got rekt... hard.",
            "Your enemy’s got the moves, and you’re still learning the basics.",
            "PvP – where you’re the punching bag!",
            "You’ve been slayed, served, and immediately forgotten. Tough luck!",
            "Your death just helped someone’s kill streak. You’re famous now.",
            "PvP success rate: 0%. Better luck next time!",
            "You’ve been killed in a way that no one will ever forget… because it was so bad.",
            "Your opponent just turned your victory dreams into nightmares.",
            "Oops! Did you think this was a solo fight? Think again!",
            "PvP: Where heroes are made… and where you’re not one of them.",
            "Death by player: At least it wasn’t an NPC. Maybe.",
            "That’s how the cookie crumbles in PvP. You're the cookie.",
            "You didn’t just lose; you got *obliterated*.",
            "PvP: Player vs. Player, but mostly *Player vs. Disaster*.",
            "You’ve just been made into a PvP highlight reel. Congrats!",
            "Turns out, your enemy was actually a PvP god. Who knew?",
            "Your PvP skills are on a ‘cooldown’… for eternity.",
            "Looks like the arena's going to need a new decoration: your corpse!",
            "PvP is tough. You’re tougher… at losing."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Deaths Caused by Player
class RandomDeathMessageSelf
{
public:
    RandomDeathMessageSelf()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomSelfDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Well, that was a new level of stupid.",
            "Death by… WHAT? Did you really just do that?",
            "Congratulations! You’ve just invented a new way to die.",
            "That was *so* dumb, I don’t even know where to begin.",
            "How did you even manage to mess that up? I’m impressed… sorta.",
            "Was that a strategic *death* or just bad timing?",
            "Well, that was an award-winning way to not survive.",
            "That death was brought to you by the letter 'D' for Dumb.",
            "You just got killed by the most avoidable thing in the game. Well done.",
            "Wow, you died by *that*? I’m honestly speechless.",
            "Looks like you died from a *bad idea* syndrome.",
            "You could’ve died in any other way… but you chose that.",
            "Who needs enemies when you’ve got *yourself* to kill you?",
            "That death was so dumb, I can’t even classify it as a mistake.",
            "Death by stupidity—10/10 would not recommend.",
            "Did you think you were invincible or just *invisible*?",
            "That was a textbook example of 'How to Fail 101.'",
            "You’ve just set the bar for ‘worst way to die.’ Congrats!",
            "Couldn’t have died more unnecessarily if you tried.",
            "I’m impressed by your ability to die in the most avoidable way.",
            "You literally just walked into that death. On purpose.",
            "That’s how you want to go out? Seriously?",
            "Couldn’t have made that death any dumber if you had planned it.",
            "You just *set the record* for the dumbest death of the day!",
            "You died to *that*? That’s almost impressive in its stupidity.",
            "Death by misjudgment... and a serious lack of common sense.",
            "You just became a walking advertisement for ‘how not to play.’",
            "That was the least heroic way to die, ever.",
            "I can’t believe you managed to die *like that*.",
            "Your death was brought to you by pure, unfiltered dumb luck.",
            "Who needs the enemy when you’ve got your own stupidity?",
            "That was so unnecessary, I’m questioning your life choices.",
            "Looks like you tripped over your own ego and fell into death.",
            "I’ve seen smarter ways to die in a beginner tutorial.",
            "You didn’t just die... you actively *chose* to die.",
            "That was a prime example of 'how to lose at life'.",
            "That wasn’t a battle, that was a public service announcement for ‘don’t do that.’",
            "At least you died doing something stupid. Kind of.",
            "Well, you made a mistake... and then decided to *really* commit to it.",
            "You couldn’t have died in a more ridiculous way if you tried!",
            "Was that death part of the plan or just an accident of pure dumb?",
            "Great job, you just proved that dying by your own mistake is an art form.",
            "Wow, you just hit a new level of *bad*. Impressive, really.",
            "Well, that was a textbook example of how to lose in the dumbest way possible."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// HardCore Only Deaths Chatter
class RandomDeathMessageHard
{
public:
    RandomDeathMessageHard()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomHardDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "One life, one chance… and you blew it. Whoops!",
            "Well, that was a *quick* end to your epic adventure!",
            "HardCore mode? More like 'HardCore fail'!",
            "You had one job: don’t die. And you failed. Spectacularly.",
            "One life. One death. Guess that’s all you needed.",
            "HardCore Challenge: 1, You: 0.",
            "That’s what happens when you don’t read the warning: ‘Do not die!’",
            "Your HardCore adventure lasted as long as your attention span. RIP.",
            "You were a HardCore hero... until you weren't.",
            "That’s what happens when you think 'one life' is a suggestion, not a rule.",
            "Death in HardCore: a one-way ticket to failure. Welcome aboard.",
            "One life. One death. And you still managed to mess it up.",
            "HardCore mode? More like ‘HardCore *oops*’!",
            "Well, that was a *short* and very expensive adventure in HardCore.",
            "You had one shot… and you missed it by a mile!",
            "HardCore? More like ‘HardCore failure’!",
            "That was a classic case of ‘so close, yet so far away’ in HardCore.",
            "Looks like HardCore mode just wasn't your thing…",
            "Just like that, your one life is over. Don’t worry, you’ll respawn... eventually. Oh wait...",
            "HardCore Challenge: Where you’re just one bad decision away from *game over*.",
            "Well, it was fun while it lasted… which was, like, 10 minutes.",
            "One life to live... and you chose the wrong one.",
            "HardCore survival tip: Don't do *that* again.",
            "Well, you can check off ‘HardCore death’ from your bucket list.",
            "HardCore death count: 1. Your lifespan: 0.",
            "That’s the problem with HardCore: It’s so... final.",
            "HardCore death. That’s gotta sting. Bad timing, too.",
            "Well, that was the *fastest* way to ruin your HardCore run.",
            "Your one life was more like one bad decision. RIP.",
            "Congratulations, you've achieved the ultimate *HardCore* failure!",
            "You thought you had it under control... and then you didn't.",
            "HardCore Challenge: It’s all fun and games until you hit *death*.",
            "One life left. Too bad you didn’t last long enough to use it.",
            "Well, that was a *HardCore* disaster in the making!",
            "That’s what happens when you don't treat HardCore like it’s *HardCore*.",
            "You made it look easy... and then you made it look *deadly*.",
            "HardCore fail: The more permanent kind.",
            "One life? Yeah, I think we can officially say it’s over."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Iron Man Only Deaths Chatter
class RandomDeathMessageIron
{
public:
    RandomDeathMessageIron()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomIronDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Well, you lasted as long as a blink. RIP Iron Man Challenger.",
            "Guess you weren’t *Iron* enough to survive that one.",
            "You died as an Iron Man Challenger, but don't worry, you'll always be remembered… for five minutes.",
            "Well, that was a *dramatic* way to lose your one and only life.",
            "You had one job: survive. Guess that's too much to ask.",
            "Your one and only life just vanished. Congratulations, you played yourself.",
            "Your Iron Man journey ended faster than your first step. Ouch.",
            "Looks like Iron Man’s suit wasn’t bulletproof after all.",
            "You died? In *Iron Man mode*? That’s gotta be a new record for failure.",
            "Too bad your ‘one life’ was as fragile as your strategy.",
            "One life down, and now you’ve got nothing but regret. Classic Iron Man.",
            "That was a *solid* attempt at the Iron Man Challenge. Almost.",
            "Well, that was an *epic* fail. Guess you’re not Iron Man after all.",
            "Your ‘one life’ just got shredded by that monster. Bye-bye, Iron Man.",
            "Congrats, you’re the newest member of the ‘failed Iron Man Challenge’ club!",
            "Guess you were made of *tin*, not iron. RIP.",
            "That was the fastest Iron Man death in recorded history.",
            "Looks like you took ‘one life’ literally, huh? Oops.",
            "You played the Iron Man Challenge, and the game played you.",
            "One life? You had one *bad* life choice instead.",
            "Iron Man Challenge: 1, You: 0. Hardly a fair fight.",
            "Well, that was a short-lived Iron Man adventure. You’ll do better next time—hopefully.",
            "Your Iron Man Challenge is now in the ‘legendary fail’ category.",
            "One life, zero chances, and now you're in the history books as a fail.",
            "Guess you weren’t as *invincible* as you thought.",
            "HardCore is one thing, but Iron Man mode is like ‘here’s your coffin!’",
            "You survived for five minutes, but hey, that’s five minutes more than nothing!",
            "Your Iron Man Challenge just turned into an Iron Man fail compilation.",
            "Well, that was a short and unforgettable Iron Man Challenge. If only for the wrong reasons.",
            "Your one life was full of promise… and then it just *ended*.",
            "Game over, Iron Man. You played yourself.",
            "Iron Man mode didn’t just take your life. It took your hopes and dreams.",
            "Well, you certainly left your mark on the Iron Man Challenge… unfortunately, it’s just a grave.",
            "One life? More like one epic fail.",
            "Well, that was a *sad* attempt at Iron Man. Better luck next time.",
            "That’s what happens when you don't treat Iron Man mode like it’s *Iron Man mode*.",
            "Your Iron Man story lasted one chapter. Too bad it was the ‘death’ chapter.",
            "You had one life, and you gave it to the wrong enemy. RIP.",
            "Looks like your ‘Iron Man’ Challenge just went straight to *game over*.",
            "You survived your first few minutes of Iron Man mode… then you didn’t.",
            "Well, your Iron Man life just *collapsed* under the weight of its own expectations."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// WildMan Deaths - Here for update that's W.I.P will be out when get some time to add it
class RandomDeathMessageWild
{
public:
    RandomDeathMessageWild()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomWildDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "Guess you didn’t need armor... or your dignity.",
            "Who needs clothes when you’ve got *spirit*? Too bad the spirit wasn’t enough.",
            "Well, you died in your birthday suit. Shame about the lack of survival skills.",
            "Looks like you went out in style... or lack of it.",
            "Your survival was as naked as your character. RIP.",
            "At least you didn’t have to worry about *dirtying* your clothes.",
            "You didn’t need armor... until you *really* needed it.",
            "Just you, your wild spirit, and a massive failure. Totally ‘Wild Man’ approved.",
            "That’s one way to die, but maybe put some pants on next time.",
            "Well, being naked and dead is *one* way to make a statement.",
            "Your death was as exposed as you were.",
            "That’s one way to prove that clothes *are* necessary for survival.",
            "Being naked didn’t save you from that monster. Ouch.",
            "Death in the Wild Man mode: no armor, no hope.",
            "Looks like you couldn’t *barely* handle the Challenge. Get it?",
            "Guess you took the ‘wild’ part too literally.",
            "Well, you really *bared* it all for that death.",
            "Your character might be naked, but your *failure* was fully clothed.",
            "Wild Man Challenge: You didn’t even have a chance… mostly because you had no pants.",
            "Death by Wild Man: *No armor, no problem*... except for the problem of dying.",
            "Being naked didn’t help your defense, but at least you’re *free*… in the afterlife.",
            "You were wild, but sadly, not invincible.",
            "Death in Wild Man mode: It’s like a *naked* tragedy.",
            "Well, you didn’t need armor, but maybe you needed *tactics*.",
            "Your death was as exposed as your lack of protection. RIP.",
            "You died just as you were born: defenseless and naked.",
            "You were wild, but not wild enough to survive.",
            "Guess you didn’t realize that being naked doesn’t make you invincible.",
            "You went in without armor, and left without... anything.",
            "You died in your birthday suit. Talk about *barely* surviving.",
            "Well, that’s one way to go out: naked, alone, and defeated.",
            "Well, at least you were *free*... right until you died.",
            "Guess you shouldn’t have gone wild without your protection gear.",
            "That was a truly *wild* death. Too bad you couldn’t survive the wild.",
            "Being naked didn’t make you immune to death… just look at you now!",
            "Well, you sure *died* like a true Wild Man… naked and unprepared.",
            "Who needs armor when you’ve got *death wishes*?",
            "Well, you went in naked and came out... dead. Classic Wild Man move.",
            "Guess you were too wild for the game to handle. Sorry about your *untamed* death.",
            "At least in death, you're still wild... and naked."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Server Wide Messages on Player Death HardCore Mode Breaking News: 
class RandomDeathMessageHCWorld
{
public:
    RandomDeathMessageHCWorld()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomHCWorldDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "has joined the ‘HardCore Death Club’! No respawns, no second chances!",
            "has left the HardCore arena… permanently. They were too HardCore for their own good.",
            "just got *rekt* in HardCore mode. That’s one less Challenger for the leaderboard!",
            "has tragically perished in HardCore. It was a valiant effort, though.",
            "has been eliminated from the HardCore Challenge. Their one life has expired. RIP.",
            "has been defeated in HardCore mode. The Challenge was just too much… for them!",
            "has been taken out in HardCore mode. They were HardCore, until they weren’t.",
            "has died in HardCore mode. There will be no do-overs, just a lot of *laughter*.",
            "has lost their HardCore Challenge. Time of death: Too soon.",
            "has been eliminated from HardCore. That was a ‘one-and-done’ situation.",
            "is officially out of the HardCore Challenge. Their mistake? *Everything*.",
            "has been killed in HardCore mode. Don’t worry, they’ve left behind some *amazing* death clips."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Server Wide Hero Messages if player is Hard/Iron Mode and killed in PVP
class RandomDeathMessageHeroPVP
{
public:
    RandomDeathMessageHeroPVP()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomHeroPVPWorldDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "has fallen in PVP. Their life was spent in glory, and now... in ashes.",
            "was slain in PvP! Another player claimed their life... but not their glory!",
            "has fallen in PvP! Killed by another, but their legend lives on…",
            "has been slain in the most Epic PVP battle. Their one life was worth every swing!",
            "was slain in PvP, but their final charge was truly a sight to behold.",
            "was killed in PvP, but their valiant last stand will echo through the ages.",
            "was slain in PvP, but their legend is now only more legendary because they lost!",
            "bravely stood against another in PvP… and was killed with style!",
            "was defeated in PvP, but their heroic death will be remembered for ages.",
            "perished at the hands of another in PvP. A death so epic, it will be told for generations…",
            "was killed by another in PvP. A true hero’s fall, their legend lives on…",
            "met their end at the hands of another in PvP. Their legacy? Tragic...",
            "was slain in PvP by another, but they went down like a true hero.",
            "faced another in PvP… and promptly became a permanent part of the battlefield’s soil.",
            "was killed by another in PvP. They fought valiantly, but this was clearly not their day.",
            "fought hard in PvP, but was slain by another with a final blow worthy of a true hero’s fall.",
            "was killed in PvP, A hero’s death is never easy, especially when you don’t dodge anything.",
            "was slain by another in PvP, their sacrifice is now the stuff of legendary stories!"
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Server Wide Messages on Player Death Iron Man Mode
class RandomDeathMessageIronWorld
{
public:
    RandomDeathMessageIronWorld()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string GetRandomHCIronDieMessage()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "just got *destroyed* in Iron Man Mode. One life down, no second chances!",
            "has made their grand exit from Iron Man Mode. Time of death: instant regret.",
            "has been eliminated in Iron Man Mode. There will be no respawns, just laughter.",
            "has been crushed under the weight of their own ‘one life’ philosophy. RIP, Iron Man.",
            "has been permanently removed from Iron Man Mode. Guess they weren’t *iron* enough.",
            "has tragically failed the Iron Man Challenge. May their mistakes be immortalized.",
            "just made the biggest *oops* in Iron Man Mode. One life? More like one fail.",
            "is officially out of Iron Man Mode. Death was the final boss.",
            "has been wiped from Iron Man Mode. They tried to cheat death… and lost.",
            "met their end in Iron Man Mode. Guess they weren’t as ‘tough as iron’ after all.",
            "has failed their Iron Man Challenge. One life, zero survival skills.",
            "is out of Iron Man Mode, permanently. Guess their ‘one life’ didn’t quite work out."
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

// Server alert on player picking up a Challenge from shrine
class RandomShrineMessageWorld
{
public:
    RandomShrineMessageWorld()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    // Function to get one random from a predefined list
    std::string RandomShrineMessageWorldStart()
    {
        // List of possible messages
        const std::vector<std::string> message = {
            "has taken on the Shrine of Challenge! Let’s see how long they last.",
            "is at the Shrine of Challenge, Their fate is in the hands of the gods!",
            "has taken on the Shrine of Challenge! This is either bravery… or madness.",
            "has answered the call of the Shrine of Challenge. Will they rise or fall?",
            "has embraced the Shrine of Challenge. Let’s see if they regret that decision.",
            "is at the Shrine of Challenge, Will they be a hero or a cautionary tale?",
            "is attempting the Shrine of Challenge. Prepare for *epic* failure or triumph.",
            "has begun the Shrine of Challenge. We’re all watching… especially the monsters.",
            "has begun the Shrine of Challenge. Let the gods of fate have their say.",
            "has chosen to test their luck at the Shrine of Challenge. Will it be glory or grief?",
            "is at the Shrine of Challenge, and things are about to get *wild*.",
            "has taken the challenge at the Shrine. May the gods have mercy on them.",
            "is attempting the Shrine of Challenge. It's a one-way ticket to either fame or shame.",
            "has dared the Shrine of Challenge. Will they conquer, or be consumed by it?",
            "has embarked on the Shrine of Challenge. Expect an epic story of victory or disaster!"
        };

        // Generate a random index from the names vector
        int randomIndex = std::rand() % message.size();

        // Return the randomly selected name
        return message[randomIndex];
    }
};

