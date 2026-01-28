# Eternal Realms - Text-Based RPG

A complete text-based role-playing game built in Python with character creation, combat, inventory management, and world exploration.

## Features

⚔️ **Character System**
- 4 unique classes: Warrior, Mage, Rogue, Cleric
- Level progression with stat growth
- HP, MP, Attack, Defense, and Magic stats

🎮 **Gameplay**
- Turn-based combat system with multiple attack options
- Exploration of different locations
- Random enemy encounters
- Item shop with weapons, armor, and potions

🌍 **Game World**
- Multiple interconnected locations
- Town, Forest, Dragon's Cave, and Shop
- Each area with unique enemies and challenges

💾 **Features**
- Save/load game functionality
- Inventory management
- Gold and experience system
- Persistent game state

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

### Character Creation
1. Enter your character's name
2. Choose your class:
   - **Warrior**: High HP and attack, low magic
   - **Mage**: High magic, low HP
   - **Rogue**: Balanced stats, high attack
   - **Cleric**: Good magic and healing

### Game Controls

**Main Menu Options:**
1. **Explore** - Search the current area for enemies and treasure
2. **Travel** - Move to different locations
3. **Inventory** - View your items and equipment
4. **Status** - Check your character's stats and progress
5. **Shop** - Buy items (only available in town)
6. **Save Game** - Save your progress
7. **Quit** - Exit the game

**Combat Options:**
1. **Attack** - Physical attack using your attack stat
2. **Magic Attack** - Magical attack using MP
3. **Use Potion** - Heal 50 HP if you have potions
4. **Run** - Attempt to flee from combat (50% success rate)

### Locations

- **Peaceful Town**: Starting area with shop access
- **Dark Forest**: Dangerous area with goblins and wolves
- **Dragon's Cave**: High-level area with powerful dragons
- **Item Shop**: Buy weapons, armor, and potions

### Progression

- Gain experience and gold by defeating enemies
- Level up to increase your stats
- Buy better equipment from the shop
- Explore more dangerous areas as you grow stronger

## Game Tips

- Start by exploring the forest to gain experience
- Save your gold for better weapons and armor
- Keep potions handy for tough battles
- The dragon is very powerful - prepare before facing it
- Magic attacks use MP, so manage your resources carefully

## Example Gameplay

```
⚔️  ETERNAL REALMS - Text RPG ⚔️
========================================

=== CHARACTER CREATION ===
Enter your character's name: Aragorn

Choose your class:
1. Warrior - High HP and attack, low magic
2. Mage - High magic, low HP
3. Rogue - Balanced stats, high attack
4. Cleric - Good magic and healing

Enter choice (1-4): 1

Welcome, Aragorn the Warrior!
Your adventure begins...

=== Peaceful Town ===
A quiet town where adventurers rest and prepare.
Exits: north, east

=== MAIN MENU ===
1. Explore
2. Travel
3. Inventory
4. Status
5. Shop (if in town)
6. Save Game
7. Quit

Enter choice: 2

Available exits: north, east
Enter direction to travel: north
You travel north...

=== Dark Forest ===
A mysterious forest filled with dangerous creatures.
Exits: south, north
You sense dangerous creatures nearby...

Enter choice: 1

⚔️  COMBAT: Aragorn vs Goblin!

Aragorn: 150/150 HP
Goblin: 30/30 HP

Combat Options:
1. Attack
2. Magic Attack
3. Use Potion
4. Run
Choose action: 1
You deal 17 damage!

Victory! You defeated Goblin!
Gained 15 EXP and 10 gold!
```

## File Structure

```
Simple-App/
├── main.py              # Main game application
├── requirements.txt     # Dependencies (none required)
├── README.md           # This file
├── rpg_save.json      # Save game file (created automatically)
└── .git/              # Git repository
```

## Game Classes & Stats

### Character Classes
- **Warrior**: 150 HP, 50 MP, 15 ATK, 8 DEF, 3 MAG
- **Mage**: 70 HP, 100 MP, 5 ATK, 3 DEF, 20 MAG
- **Rogue**: 90 HP, 50 MP, 18 ATK, 4 DEF, 8 MAG
- **Cleric**: 100 HP, 80 MP, 8 ATK, 6 DEF, 15 MAG

### Enemies
- **Goblin**: Level 1, 30 HP, weak but common
- **Wolf**: Level 2, 40 HP, moderate threat
- **Ancient Dragon**: Level 10, 200 HP, boss-level enemy

### Items
- **Iron Sword**: +8 Attack
- **Magic Staff**: +10 Magic
- **Sharp Dagger**: +6 Attack
- **Leather Armor**: +5 Defense
- **Health Potion**: Restores 50 HP

## Contributing

Feel free to fork this project and submit pull requests with new features like:
- Additional character classes
- More enemies and locations
- Quest system
- Equipment durability
- Magic spells system

## License

This project is open source and available under the MIT License.
