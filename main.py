#!/usr/bin/env python3
"""
Eternal Realms - Text-Based RPG Game
A complete role-playing game with character creation, combat, inventory, and exploration.
"""

import random
import json
import os
from typing import Dict, List, Optional, Any
from enum import Enum
from dataclasses import dataclass, field

class CharacterClass(Enum):
    WARRIOR = "Warrior"
    MAGE = "Mage"
    ROGUE = "Rogue"
    CLERIC = "Cleric"

class ItemType(Enum):
    WEAPON = "Weapon"
    ARMOR = "Armor"
    POTION = "Potion"
    MISC = "Misc"

@dataclass
class Item:
    name: str
    item_type: ItemType
    value: int
    stat_bonus: Dict[str, int] = field(default_factory=dict)
    description: str = ""

@dataclass
class Character:
    name: str
    char_class: CharacterClass
    level: int = 1
    hp: int = 100
    max_hp: int = 100
    mp: int = 50
    max_mp: int = 50
    attack: int = 10
    defense: int = 5
    magic: int = 8
    exp: int = 0
    exp_to_next: int = 100
    gold: int = 50
    inventory: List[Item] = field(default_factory=list)
    equipped: Dict[str, Optional[Item]] = field(default_factory=lambda: {"weapon": None, "armor": None})
    
    def take_damage(self, damage: int) -> int:
        actual_damage = max(1, damage - self.defense)
        self.hp -= actual_damage
        return actual_damage
    
    def heal(self, amount: int) -> None:
        self.hp = min(self.max_hp, self.hp + amount)
    
    def gain_exp(self, amount: int) -> bool:
        self.exp += amount
        if self.exp >= self.exp_to_next:
            self.level_up()
            return True
        return False
    
    def level_up(self) -> None:
        self.level += 1
        self.exp = 0
        self.exp_to_next = int(self.exp_to_next * 1.5)
        
        self.max_hp += 20
        self.hp = self.max_hp
        self.max_mp += 10
        self.mp = self.max_mp
        self.attack += 5
        self.defense += 3
        self.magic += 4

class Enemy:
    def __init__(self, name: str, level: int, hp: int, attack: int, defense: int, exp_reward: int, gold_reward: int):
        self.name = name
        self.level = level
        self.hp = hp
        self.max_hp = hp
        self.attack = attack
        self.defense = defense
        self.exp_reward = exp_reward
        self.gold_reward = gold_reward
    
    def take_damage(self, damage: int) -> int:
        actual_damage = max(1, damage - self.defense)
        self.hp -= actual_damage
        return actual_damage

class GameWorld:
    def __init__(self):
        self.locations = {
            "town": {
                "name": "Peaceful Town",
                "description": "A quiet town where adventurers rest and prepare.",
                "exits": {"north": "forest", "east": "shop"},
                "npcs": ["healer", "quest_giver"]
            },
            "forest": {
                "name": "Dark Forest",
                "description": "A mysterious forest filled with dangerous creatures.",
                "exits": {"south": "town", "north": "cave"},
                "enemies": ["goblin", "wolf"]
            },
            "cave": {
                "name": "Dragon's Cave",
                "description": "A dark cave where a powerful dragon resides.",
                "exits": {"south": "forest"},
                "enemies": ["dragon"]
            },
            "shop": {
                "name": "Item Shop",
                "description": "A shop selling weapons, armor, and potions.",
                "exits": {"west": "town"},
                "shopkeeper": True
            }
        }
        self.current_location = "town"
    
    def get_current_location(self) -> Dict[str, Any]:
        return self.locations[self.current_location]
    
    def move(self, direction: str) -> bool:
        current = self.get_current_location()
        if direction in current.get("exits", {}):
            self.current_location = current["exits"][direction]
            return True
        return False

class RPGGame:
    def __init__(self):
        self.player: Optional[Character] = None
        self.world = GameWorld()
        self.game_running = False
        self.enemies = {
            "goblin": Enemy("Goblin", 1, 30, 8, 2, 15, 10),
            "wolf": Enemy("Wolf", 2, 40, 12, 3, 25, 15),
            "dragon": Enemy("Ancient Dragon", 10, 200, 30, 15, 200, 500)
        }
        self.items = {
            "sword": Item("Iron Sword", ItemType.WEAPON, 50, {"attack": 8}, "A sturdy iron sword."),
            "staff": Item("Magic Staff", ItemType.WEAPON, 60, {"magic": 10}, "A wooden staff imbued with magic."),
            "dagger": Item("Sharp Dagger", ItemType.WEAPON, 40, {"attack": 6}, "A quick and deadly dagger."),
            "armor": Item("Leather Armor", ItemType.ARMOR, 80, {"defense": 5}, "Basic leather armor."),
            "potion": Item("Health Potion", ItemType.POTION, 20, {}, "Restores 50 HP.")
        }
    
    def create_character(self) -> None:
        print("\n=== CHARACTER CREATION ===")
        name = input("Enter your character's name: ").strip()
        
        print("\nChoose your class:")
        print("1. Warrior - High HP and attack, low magic")
        print("2. Mage - High magic, low HP")
        print("3. Rogue - Balanced stats, high attack")
        print("4. Cleric - Good magic and healing")
        
        while True:
            choice = input("\nEnter choice (1-4): ").strip()
            if choice == "1":
                char_class = CharacterClass.WARRIOR
                break
            elif choice == "2":
                char_class = CharacterClass.MAGE
                break
            elif choice == "3":
                char_class = CharacterClass.ROGUE
                break
            elif choice == "4":
                char_class = CharacterClass.CLERIC
                break
            else:
                print("Invalid choice. Try again.")
        
        self.player = Character(name, char_class)
        
        if char_class == CharacterClass.WARRIOR:
            self.player.hp = self.player.max_hp = 150
            self.player.attack = 15
            self.player.defense = 8
            self.player.magic = 3
        elif char_class == CharacterClass.MAGE:
            self.player.hp = self.player.max_hp = 70
            self.player.mp = self.player.max_mp = 100
            self.player.attack = 5
            self.player.defense = 3
            self.player.magic = 20
        elif char_class == CharacterClass.ROGUE:
            self.player.hp = self.player.max_hp = 90
            self.player.attack = 18
            self.player.defense = 4
            self.player.magic = 8
        elif char_class == CharacterClass.CLERIC:
            self.player.hp = self.player.max_hp = 100
            self.player.mp = self.player.max_mp = 80
            self.player.attack = 8
            self.player.defense = 6
            self.player.magic = 15
        
        self.player.inventory.append(self.items["potion"])
        print(f"\nWelcome, {name} the {char_class.value}!")
        print("Your adventure begins...")
    
    def display_status(self) -> None:
        if not self.player:
            return
        
        print(f"\n=== {self.player.name} - Level {self.player.level} {self.player.char_class.value} ===")
        print(f"HP: {self.player.hp}/{self.player.max_hp}")
        print(f"MP: {self.player.mp}/{self.player.max_mp}")
        print(f"ATK: {self.player.attack} | DEF: {self.player.defense} | MAG: {self.player.magic}")
        print(f"EXP: {self.player.exp}/{self.player.exp_to_next}")
        print(f"Gold: {self.player.gold}")
    
    def display_location(self) -> None:
        location = self.world.get_current_location()
        print(f"\n=== {location['name']} ===")
        print(location['description'])
        
        exits = location.get('exits', {})
        if exits:
            print(f"Exits: {', '.join(exits.keys())}")
        
        if 'enemies' in location:
            print("You sense dangerous creatures nearby...")
    
    def combat(self, enemy: Enemy) -> None:
        print(f"\n⚔️  COMBAT: {self.player.name} vs {enemy.name}!")
        
        while enemy.hp > 0 and self.player.hp > 0:
            print(f"\n{self.player.name}: {self.player.hp}/{self.player.max_hp} HP")
            print(f"{enemy.name}: {enemy.hp}/{enemy.max_hp} HP")
            
            print("\nCombat Options:")
            print("1. Attack")
            print("2. Magic Attack")
            print("3. Use Potion")
            print("4. Run")
            
            choice = input("Choose action: ").strip()
            
            if choice == "1":
                damage = self.player.attack + random.randint(-2, 2)
                actual_damage = enemy.take_damage(damage)
                print(f"You deal {actual_damage} damage!")
                
            elif choice == "2":
                if self.player.mp >= 10:
                    damage = self.player.magic + random.randint(-2, 2)
                    actual_damage = enemy.take_damage(damage)
                    self.player.mp -= 10
                    print(f"You cast a spell dealing {actual_damage} damage!")
                else:
                    print("Not enough MP!")
                    continue
                    
            elif choice == "3":
                potion = next((item for item in self.player.inventory if item.item_type == ItemType.POTION), None)
                if potion:
                    self.player.heal(50)
                    self.player.inventory.remove(potion)
                    print("You use a health potion and restore 50 HP!")
                else:
                    print("No potions available!")
                    continue
                    
            elif choice == "4":
                if random.random() < 0.5:
                    print("You successfully run away!")
                    return
                else:
                    print("You failed to escape!")
            
            if enemy.hp > 0:
                enemy_damage = enemy.attack + random.randint(-2, 2)
                actual_damage = self.player.take_damage(enemy_damage)
                print(f"{enemy.name} deals {actual_damage} damage to you!")
        
        if enemy.hp <= 0:
            print(f"\nVictory! You defeated {enemy.name}!")
            self.player.gain_exp(enemy.exp_reward)
            self.player.gold += enemy.gold_reward
            print(f"Gained {enemy.exp_reward} EXP and {enemy.gold_reward} gold!")
            
            if self.player.exp >= self.player.exp_to_next:
                print(f"🎉 LEVEL UP! You are now level {self.player.level}!")
        
        elif self.player.hp <= 0:
            print("\n💀 You have been defeated!")
            self.game_running = False
    
    def shop(self) -> None:
        print("\n=== ITEM SHOP ===")
        print("Welcome! What would you like to buy?")
        print("1. Iron Sword (50 gold)")
        print("2. Magic Staff (60 gold)")
        print("3. Sharp Dagger (40 gold)")
        print("4. Leather Armor (80 gold)")
        print("5. Health Potion (20 gold)")
        print("6. Exit shop")
        
        while True:
            choice = input("Enter choice: ").strip()
            
            if choice == "1":
                self.buy_item("sword", 50)
            elif choice == "2":
                self.buy_item("staff", 60)
            elif choice == "3":
                self.buy_item("dagger", 40)
            elif choice == "4":
                self.buy_item("armor", 80)
            elif choice == "5":
                self.buy_item("potion", 20)
            elif choice == "6":
                break
            else:
                print("Invalid choice!")
    
    def buy_item(self, item_name: str, cost: int) -> None:
        if self.player.gold >= cost:
            self.player.gold -= cost
            item = self.items[item_name]
            self.player.inventory.append(item)
            print(f"Purchased {item.name}!")
        else:
            print("Not enough gold!")
    
    def explore(self) -> None:
        location = self.world.get_current_location()
        
        if 'enemies' in location:
            if random.random() < 0.6:
                enemy_name = random.choice(location['enemies'])
                enemy = self.enemies[enemy_name]
                self.combat(enemy)
                return
        
        print("You explore the area but find nothing of interest.")
    
    def main_menu(self) -> None:
        print("\n=== MAIN MENU ===")
        print("1. Explore")
        print("2. Travel")
        print("3. Inventory")
        print("4. Status")
        print("5. Shop (if in town)")
        print("6. Save Game")
        print("7. Quit")
    
    def show_inventory(self) -> None:
        print("\n=== INVENTORY ===")
        if not self.player.inventory:
            print("Your inventory is empty.")
            return
        
        for i, item in enumerate(self.player.inventory, 1):
            print(f"{i}. {item.name} - {item.description}")
            if item.stat_bonus:
                stats = ", ".join([f"+{v} {k}" for k, v in item.stat_bonus.items()])
                print(f"   ({stats})")
    
    def travel(self) -> None:
        location = self.world.get_current_location()
        exits = location.get('exits', {})
        
        if not exits:
            print("No exits available from here.")
            return
        
        print(f"\nAvailable exits: {', '.join(exits.keys())}")
        direction = input("Enter direction to travel: ").strip().lower()
        
        if self.world.move(direction):
            print(f"You travel {direction}...")
            self.display_location()
        else:
            print("You can't go that way!")
    
    def save_game(self) -> None:
        save_data = {
            "player": {
                "name": self.player.name,
                "char_class": self.player.char_class.value,
                "level": self.player.level,
                "hp": self.player.hp,
                "max_hp": self.player.max_hp,
                "mp": self.player.mp,
                "max_mp": self.player.max_mp,
                "attack": self.player.attack,
                "defense": self.player.defense,
                "magic": self.player.magic,
                "exp": self.player.exp,
                "exp_to_next": self.player.exp_to_next,
                "gold": self.player.gold
            },
            "location": self.world.current_location
        }
        
        with open("rpg_save.json", "w") as f:
            json.dump(save_data, f, indent=2)
        print("Game saved!")
    
    def run(self) -> None:
        print("⚔️  ETERNAL REALMS - Text RPG ⚔️")
        print("=" * 40)
        
        self.create_character()
        self.game_running = True
        
        while self.game_running:
            self.display_location()
            self.main_menu()
            
            choice = input("\nEnter choice: ").strip()
            
            if choice == "1":
                self.explore()
            elif choice == "2":
                self.travel()
            elif choice == "3":
                self.show_inventory()
            elif choice == "4":
                self.display_status()
            elif choice == "5":
                if self.world.current_location == "shop":
                    self.shop()
                else:
                    print("You need to be in town to access the shop!")
            elif choice == "6":
                self.save_game()
            elif choice == "7":
                print("Thanks for playing!")
                self.game_running = False
            else:
                print("Invalid choice!")
            
            if self.player and self.player.hp <= 0:
                print("\n💀 GAME OVER 💀")
                self.game_running = False

if __name__ == "__main__":
    game = RPGGame()
    game.run()
