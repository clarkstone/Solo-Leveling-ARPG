# Solo Leveling: The System - Text-Based RPG

A complete text-based role-playing game inspired by the Solo Leveling manhwa, featuring Hunter ranks, Shadow Army mechanics, and the System interface.

## Features

🌑 **Hunter System**
- 6 unique Hunter classes: Fighter, Tanker, Ranger, Assassin, Healer, Mage
- Hunter ranking system from E-Rank to National Level
- Level progression with automatic rank promotions
- Double awakening mechanic for Shadow Monarch potential

⚔️ **Shadow Army System**
- Extract shadows from defeated enemies
- Command shadows with different ranks (Soldier to Monarch)
- Summon shadows in combat for assistance
- Build your army of extracted shadows

🎮 **System Interface**
- Daily quests with rewards
- System messages and notifications
- Quest tracking and completion
- Progress monitoring

🌍 **Game World**
- Hunter Association hub
- Dungeon instances with multiple difficulties
- Training grounds for stat improvement
- Hunter's shop for equipment

💾 **Advanced Features**
- Dungeon runs with scaling difficulty
- Save/load game functionality
- Inventory management
- Gold and experience systems

## Requirements

- Python 3.6 or higher
- No external dependencies (uses only Python standard library)

## Installation

1. Clone or download this repository
2. Navigate to the project directory
3. Run the game:

```bash
python main.py
```

## How to Play

### Hunter Awakening
1. Enter your name
2. Choose your Hunter class:
   - **Fighter**: Balanced combat specialist
   - **Tanker**: High defense and HP
   - **Ranger**: Ranged combat expert
   - **Assassin**: High attack, low defense
   - **Healer**: Support and recovery
   - **Mage**: Magical attacks

### Game Controls

**Main Menu Options:**
1. **Explore/Action** - Enter dungeons, train, or perform location-specific actions
2. **Travel** - Move between different locations
3. **Inventory** - View your items and equipment
4. **Status** - Check your Hunter stats and progress
5. **Shop** - Buy items (only available at shop)
6. **Shadow Army** - View your extracted shadows (Shadow Monarch only)
7. **Save Game** - Save your progress
8. **Quit** - Exit the game

**Combat Options:**
1. **Attack** - Physical attack using your attack stat
2. **Magic Attack** - Magical attack using MP
3. **Use Potion** - Heal 50 HP if you have potions
4. **Run** - Attempt to flee from combat (50% success rate)
5. **Summon Shadow** - Command a shadow to fight (Shadow Monarch only)

### Locations

- **Hunter Association**: Central hub for all hunters
- **Dungeon Gate**: Enter dungeons with various difficulty levels
- **Hunter's Shop**: Buy weapons, armor, and potions
- **Training Ground**: Improve your stats through training

### Hunter Ranks

Progress through ranks as you level up:
- **E-Rank**: Level 0+ (Starting rank)
- **D-Rank**: Level 10+
- **C-Rank**: Level 25+
- **B-Rank**: Level 50+
- **A-Rank**: Level 100+
- **S-Rank**: Level 200+
- **National Level**: Level 500+

### Shadow Monarch System

- 10% chance of double awakening during character creation
- Extract shadows from defeated enemies
- Shadow ranks: Soldier → Mage → Knight → General → Monarch
- Each shadow has unique abilities and stats
- Build your army to become the true Shadow Monarch

### Dungeon System

Choose your difficulty:
- **Easy**: Low risk, low rewards (Level 1-5)
- **Normal**: Balanced gameplay (Level 3-10)
- **Hard**: High risk, high rewards (Level 8-20)
- **Hell**: Extreme risk, extreme rewards (Level 15-50)

### Daily Quests

Complete daily quests for bonus rewards:
- Kill 10 Monsters
- Dungeon Clear
- Shadow Extraction
- Survival Test

## Game Tips

- Start with Easy dungeons to build experience
- Train at the Training Ground to boost stats
- Save gold for better equipment
- Shadow Monarchs should extract shadows whenever possible
- Higher rank dungeons give better rewards but are much harder
- Complete daily quests for bonus EXP and gold

## Example Gameplay

```
🌑 SOLO LEVELING: The System 🌑
==================================================

=== HUNTER AWAKENING ===
Enter your name: Jinwoo

Choose your Hunter class:
1. Fighter - Balanced combat specialist
2. Tanker - High defense and HP
3. Ranger - Ranged combat expert
4. Assassin - High attack, low defense
5. Healer - Support and recovery
6. Mage - Magical attacks

Enter choice (1-6): 1

🎯 Welcome, Jinwoo the Fighter!
📊 Initial Rank: E-Rank

[SYSTEM] Hunter awakening complete. System interface activating...
[SYSTEM] Daily quest generated. Check your status for details.
[SYSTEM] WARNING: Double awakening detected! Shadow extraction abilities unlocked.
🌑 You have awakened as a Shadow Monarch!
Your journey as a Hunter begins...

=== Hunter Association ===
The central hub for all hunters. Take on raids and get information.
Exits: north, east, west

=== MAIN MENU ===
1. Explore/Action
2. Travel
3. Inventory
4. Status
5. Shop (if available)
6. Shadow Army (if Shadow Monarch)
7. Save Game
8. Quit

Enter choice: 2

Available exits: north, east, west
Enter direction to travel: north
You travel north...

=== Dungeon Gate ===
Mysterious gates that lead to dungeons filled with monsters.
Exits: south

Enter choice: 1

Choose dungeon difficulty:
1. Easy (Low rewards, safe)
2. Normal (Balanced)
3. Hard (High rewards, dangerous)
4. Hell (Extreme risk, extreme rewards)
5. Cancel

Enter choice: 2

🌟 Entering NORMAL Dungeon (Level 7)

--- Enemy 1/5 ---
⚔️  COMBAT: Jinwoo vs Orc!

Jinwoo: 120/120 HP
Orc: 170/170 HP

Combat Options:
1. Attack
2. Magic Attack
3. Use Potion
4. Run
5. Summon Shadow
Choose action: 1
You deal 19 damage!

Victory! You defeated Orc!
Gained 40 EXP and 25 gold!
🌑 Shadow extracted: Shadow Orc (Shadow Knight)!

🎉 Daily Quest Complete: Kill 10 Monsters!
Rewards: 100 EXP, 50 Gold
```

## File Structure

```
Simple-App/
├── main.py                    # Main game application
├── requirements.txt           # Dependencies (none required)
├── README.md                 # This file
├── solo_leveling_save.json   # Save game file (created automatically)
└── .git/                    # Git repository
```

## Hunter Classes & Stats

### Hunter Classes
- **Fighter**: 120 HP, 50 MP, 12 ATK, 6 DEF, 5 MAG
- **Tanker**: 150 HP, 50 MP, 8 ATK, 10 DEF, 3 MAG
- **Ranger**: 100 HP, 50 MP, 14 ATK, 4 DEF, 6 MAG
- **Assassin**: 90 HP, 50 MP, 16 ATK, 3 DEF, 8 MAG
- **Healer**: 100 HP, 80 MP, 6 ATK, 5 DEF, 12 MAG
- **Mage**: 80 HP, 120 MP, 5 ATK, 3 DEF, 18 MAG

### Enemies
- **Goblin**: Level 1, 30 HP, weak but common
- **Orc**: Level 3, 60 HP, moderate threat
- **Wolf**: Level 2, 40 HP, fast attacker
- **Troll**: Level 5, 100 HP, high defense
- **Ancient Dragon**: Level 10, 200 HP, boss-level enemy
- **Stone Giant**: Level 15, 300 HP, ultimate challenge

### Items
- **Hunter's Dagger**: +6 Attack
- **Knight's Sword**: +12 Attack
- **Hunter's Bow**: +8 Attack
- **Mage Staff**: +15 Magic
- **Hunter's Armor**: +8 Defense
- **Health Potion**: Restores 50 HP
- **Mana Potion**: Restores 30 MP

## Contributing

Feel free to fork this project and submit pull requests with new features like:
- Additional Hunter classes and abilities
- More enemies and dungeon types
- Advanced shadow mechanics
- Equipment upgrade system
- Guild system
- PvP battles

## License

This project is open source and available under the MIT License.
