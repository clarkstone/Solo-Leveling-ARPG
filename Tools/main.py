#!/usr/bin/env python3
"""
Solo Leveling: The System - Text-Based RPG Game
A complete role-playing game based on the Solo Leveling manhwa with Hunter ranks, Shadow Army, and System interface.
"""

import random
import json
import os
import time
from typing import Dict, List, Optional, Any
from enum import Enum
from dataclasses import dataclass, field

class HunterRank(Enum):
    E = "E-Rank"
    D = "D-Rank"
    C = "C-Rank"
    B = "B-Rank"
    A = "A-Rank"
    S = "S-Rank"
    NATIONAL = "National Level"

class HunterClass(Enum):
    FIGHTER = "Fighter"
    TANKER = "Tanker"
    RANGER = "Ranger"
    ASSASSIN = "Assassin"
    HEALER = "Healer"
    MAGE = "Mage"

class ItemType(Enum):
    WEAPON = "Weapon"
    ARMOR = "Armor"
    POTION = "Potion"
    SHADOW = "Shadow"
    MISC = "Misc"

class ShadowRank(Enum):
    SOLDIER = "Shadow Soldier"
    MAGE = "Shadow Mage"
    KNIGHT = "Shadow Knight"
    GENERAL = "Shadow General"
    MONARCH = "Shadow Monarch"

@dataclass
class Item:
    name: str
    item_type: ItemType
    value: int
    stat_bonus: Dict[str, int] = field(default_factory=dict)
    description: str = ""

@dataclass
class Shadow:
    name: str
    rank: ShadowRank
    hp: int
    attack: int
    defense: int
    special_ability: str = ""
    
    def take_damage(self, damage: int) -> int:
        actual_damage = max(1, damage - self.defense)
        self.hp -= actual_damage
        return actual_damage

@dataclass
class Hunter:
    name: str
    hunter_class: HunterClass
    hunter_rank: HunterRank = HunterRank.E
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
    shadow_army: List[Shadow] = field(default_factory=list)
    is_shadow_monarch: bool = False
    system_level: int = 1
    daily_quests_completed: int = 0
    last_quest_date: str = ""
    
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
        
        self.check_rank_up()
    
    def check_rank_up(self) -> None:
        rank_requirements = {
            HunterRank.E: 0,
            HunterRank.D: 10,
            HunterRank.C: 25,
            HunterRank.B: 50,
            HunterRank.A: 100,
            HunterRank.S: 200,
            HunterRank.NATIONAL: 500
        }
        
        for rank, req_level in rank_requirements.items():
            if self.level >= req_level and self.get_rank_value(rank) > self.get_rank_value(self.hunter_rank):
                self.hunter_rank = rank
                print(f"🎉 RANK UP! You are now {rank.value}!")
                break
    
    def get_rank_value(self, rank: HunterRank) -> int:
        rank_values = {
            HunterRank.E: 1,
            HunterRank.D: 2,
            HunterRank.C: 3,
            HunterRank.B: 4,
            HunterRank.A: 5,
            HunterRank.S: 6,
            HunterRank.NATIONAL: 7
        }
        return rank_values[rank]
    
    def extract_shadow(self, enemy_name: str, enemy_level: int) -> Optional[Shadow]:
        if not self.is_shadow_monarch:
            return None
        
        shadow_ranks = [
            (ShadowRank.SOLDIER, 50, 15, 5),
            (ShadowRank.MAGE, 40, 20, 3),
            (ShadowRank.KNIGHT, 30, 25, 8),
            (ShadowRank.GENERAL, 10, 35, 12),
            (ShadowRank.MONARCH, 5, 50, 20)
        ]
        
        for rank, chance, attack_bonus, defense_bonus in shadow_ranks:
            if random.randint(1, 100) <= chance:
                shadow = Shadow(
                    name=f"Shadow {enemy_name}",
                    rank=rank,
                    hp=50 + enemy_level * 10,
                    attack=self.attack + attack_bonus,
                    defense=self.defense + defense_bonus,
                    special_ability=self.get_shadow_ability(rank)
                )
                self.shadow_army.append(shadow)
                return shadow
        return None
    
    def get_shadow_ability(self, rank: ShadowRank) -> str:
        abilities = {
            ShadowRank.SOLDIER: "Basic Attack",
            ShadowRank.MAGE: "Shadow Bolt",
            ShadowRank.KNIGHT: "Shield Bash",
            ShadowRank.GENERAL: "Command Aura",
            ShadowRank.MONARCH: "Dominion"
        }
        return abilities[rank]

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

class SystemInterface:
    def __init__(self):
        self.quests = [
            {"name": "Kill 10 Monsters", "description": "Defeat 10 enemies", "target": 10, "type": "kill", "reward_exp": 100, "reward_gold": 50},
            {"name": "Dungeon Clear", "description": "Complete a dungeon run", "target": 1, "type": "dungeon", "reward_exp": 200, "reward_gold": 100},
            {"name": "Shadow Extraction", "description": "Extract 3 shadows", "target": 3, "type": "shadow", "reward_exp": 150, "reward_gold": 75},
            {"name": "Survival Test", "description": "Survive 5 battles without healing", "target": 5, "type": "survival", "reward_exp": 300, "reward_gold": 150}
        ]
        self.active_quests = []
        self.daily_quest = None
    
    def generate_daily_quest(self) -> Dict[str, Any]:
        self.daily_quest = random.choice(self.quests).copy()
        self.daily_quest["progress"] = 0
        return self.daily_quest
    
    def update_quest_progress(self, quest_type: str, amount: int = 1) -> bool:
        if self.daily_quest and self.daily_quest["type"] == quest_type:
            self.daily_quest["progress"] += amount
            if self.daily_quest["progress"] >= self.daily_quest["target"]:
                return True
        return False
    
    def show_system_message(self, message: str, delay: float = 1.0) -> None:
        print(f"\n[SYSTEM] {message}")
        time.sleep(delay)

class GameWorld:
    def __init__(self):
        self.locations = {
            "hunter_association": {
                "name": "Hunter Association",
                "description": "The central hub for all hunters. Take on raids and get information.",
                "exits": {"north": "dungeon_gate", "east": "shop", "west": "training_ground"},
                "npcs": ["receptionist", "guild_master"]
            },
            "dungeon_gate": {
                "name": "Dungeon Gate",
                "description": "Mysterious gates that lead to dungeons filled with monsters.",
                "exits": {"south": "hunter_association"},
                "dungeon": True
            },
            "shop": {
                "name": "Hunter's Shop",
                "description": "A shop selling weapons, armor, and magical items for hunters.",
                "exits": {"west": "hunter_association"},
                "shopkeeper": True
            },
            "training_ground": {
                "name": "Training Ground",
                "description": "Practice your skills and improve your abilities.",
                "exits": {"east": "hunter_association"},
                "training": True
            }
        }
        self.current_location = "hunter_association"
        self.dungeon_active = False
        self.dungeon_level = 1
    
    def get_current_location(self) -> Dict[str, Any]:
        return self.locations[self.current_location]
    
    def move(self, direction: str) -> bool:
        current = self.get_current_location()
        if direction in current.get("exits", {}):
            self.current_location = current["exits"][direction]
            return True
        return False
    
    def enter_dungeon(self, difficulty: str = "normal") -> Dict[str, Any]:
        dungeon_difficulties = {
            "easy": {"level_range": (1, 5), "enemies": 3, "boss_chance": 0.1},
            "normal": {"level_range": (3, 10), "enemies": 5, "boss_chance": 0.2},
            "hard": {"level_range": (8, 20), "enemies": 8, "boss_chance": 0.3},
            "hell": {"level_range": (15, 50), "enemies": 12, "boss_chance": 0.5}
        }
        
        diff = dungeon_difficulties.get(difficulty, dungeon_difficulties["normal"])
        self.dungeon_active = True
        self.dungeon_level = random.randint(*diff["level_range"])
        
        return {
            "level": self.dungeon_level,
            "enemies": diff["enemies"],
            "boss_chance": diff["boss_chance"],
            "difficulty": difficulty
        }

class SoloLevelingGame:
    def __init__(self):
        self.player: Optional[Hunter] = None
        self.world = GameWorld()
        self.system = SystemInterface()
        self.game_running = False
        self.enemies = {
            "goblin": Enemy("Goblin", 1, 30, 8, 2, 15, 10),
            "orc": Enemy("Orc", 3, 60, 15, 5, 40, 25),
            "wolf": Enemy("Wolf", 2, 40, 12, 3, 25, 15),
            "troll": Enemy("Troll", 5, 100, 20, 8, 80, 50),
            "dragon": Enemy("Ancient Dragon", 10, 200, 30, 15, 200, 500),
            "giant": Enemy("Stone Giant", 15, 300, 40, 20, 300, 800)
        }
        self.items = {
            "dagger": Item("Hunter's Dagger", ItemType.WEAPON, 40, {"attack": 6}, "A dagger favored by hunters."),
            "sword": Item("Knight's Sword", ItemType.WEAPON, 80, {"attack": 12}, "A well-crafted sword."),
            "bow": Item("Hunter's Bow", ItemType.WEAPON, 60, {"attack": 8}, "A reliable bow for ranged combat."),
            "staff": Item("Mage Staff", ItemType.WEAPON, 100, {"magic": 15}, "A staff that amplifies magical power."),
            "armor": Item("Hunter's Armor", ItemType.ARMOR, 120, {"defense": 8}, "Armor designed for hunters."),
            "potion": Item("Health Potion", ItemType.POTION, 20, {}, "Restores 50 HP."),
            "mana_potion": Item("Mana Potion", ItemType.POTION, 25, {}, "Restores 30 MP."),
            "shadow_extract": Item("Shadow Extract", ItemType.SHADOW, 0, {}, "A mysterious shadow essence.")
        }
    
    def create_character(self) -> None:
        print("\n=== HUNTER AWAKENING ===")
        name = input("Enter your name: ").strip()
        
        print("\nChoose your Hunter class:")
        print("1. Fighter - Balanced combat specialist")
        print("2. Tanker - High defense and HP")
        print("3. Ranger - Ranged combat expert")
        print("4. Assassin - High attack, low defense")
        print("5. Healer - Support and recovery")
        print("6. Mage - Magical attacks")
        
        while True:
            choice = input("\nEnter choice (1-6): ").strip()
            if choice == "1":
                hunter_class = HunterClass.FIGHTER
                break
            elif choice == "2":
                hunter_class = HunterClass.TANKER
                break
            elif choice == "3":
                hunter_class = HunterClass.RANGER
                break
            elif choice == "4":
                hunter_class = HunterClass.ASSASSIN
                break
            elif choice == "5":
                hunter_class = HunterClass.HEALER
                break
            elif choice == "6":
                hunter_class = HunterClass.MAGE
                break
            else:
                print("Invalid choice. Try again.")
        
        self.player = Hunter(name, hunter_class)
        
        if hunter_class == HunterClass.FIGHTER:
            self.player.hp = self.player.max_hp = 120
            self.player.attack = 12
            self.player.defense = 6
            self.player.magic = 5
        elif hunter_class == HunterClass.TANKER:
            self.player.hp = self.player.max_hp = 150
            self.player.attack = 8
            self.player.defense = 10
            self.player.magic = 3
        elif hunter_class == HunterClass.RANGER:
            self.player.hp = self.player.max_hp = 100
            self.player.attack = 14
            self.player.defense = 4
            self.player.magic = 6
        elif hunter_class == HunterClass.ASSASSIN:
            self.player.hp = self.player.max_hp = 90
            self.player.attack = 16
            self.player.defense = 3
            self.player.magic = 8
        elif hunter_class == HunterClass.HEALER:
            self.player.hp = self.player.max_hp = 100
            self.player.mp = self.player.max_mp = 80
            self.player.attack = 6
            self.player.defense = 5
            self.player.magic = 12
        elif hunter_class == HunterClass.MAGE:
            self.player.hp = self.player.max_hp = 80
            self.player.mp = self.player.max_mp = 120
            self.player.attack = 5
            self.player.defense = 3
            self.player.magic = 18
        
        self.player.inventory.append(self.items["potion"])
        self.player.inventory.append(self.items["potion"])
        
        print(f"\n🎯 Welcome, {name} the {hunter_class.value}!")
        print(f"📊 Initial Rank: {self.player.hunter_rank.value}")
        
        self.system.show_system_message("Hunter awakening complete. System interface activating...")
        time.sleep(1)
        self.system.show_system_message("Daily quest generated. Check your status for details.")
        
        if random.random() < 0.1:
            self.system.show_system_message("WARNING: Double awakening detected! Shadow extraction abilities unlocked.", 2)
            self.player.is_shadow_monarch = True
            print("🌑 You have awakened as a Shadow Monarch!")
        
        print("Your journey as a Hunter begins...")
    
    def display_status(self) -> None:
        if not self.player:
            return
        
        print(f"\n=== {self.player.name} - Level {self.player.level} ===")
        print(f"🎯 Rank: {self.player.hunter_rank.value}")
        print(f"⚔️  Class: {self.player.hunter_class.value}")
        print(f"❤️  HP: {self.player.hp}/{self.player.max_hp}")
        print(f"💙 MP: {self.player.mp}/{self.player.max_mp}")
        print(f"⚔️  ATK: {self.player.attack} | 🛡️ DEF: {self.player.defense} | ✨ MAG: {self.player.magic}")
        print(f"⭐ EXP: {self.player.exp}/{self.player.exp_to_next}")
        print(f"💰 Gold: {self.player.gold}")
        
        if self.player.is_shadow_monarch:
            print(f"🌑 Shadow Army: {len(self.player.shadow_army)} shadows")
        
        if self.system.daily_quest:
            quest = self.system.daily_quest
            print(f"\n📋 Daily Quest: {quest['name']}")
            print(f"   Progress: {quest['progress']}/{quest['target']}")
            print(f"   Reward: {quest['reward_exp']} EXP, {quest['reward_gold']} Gold")
    
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
            if self.player.is_shadow_monarch and self.player.shadow_army:
                print("5. Summon Shadow")
            
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
            
            elif choice == "5" and self.player.is_shadow_monarch and self.player.shadow_army:
                shadow = random.choice(self.player.shadow_army)
                shadow_damage = shadow.attack + random.randint(-2, 2)
                actual_damage = enemy.take_damage(shadow_damage)
                print(f"{shadow.name} attacks dealing {actual_damage} damage!")
            
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
            
            if self.player.is_shadow_monarch:
                shadow = self.player.extract_shadow(enemy.name, enemy.level)
                if shadow:
                    print(f"🌑 Shadow extracted: {shadow.name} ({shadow.rank.value})!")
                
                if self.system.update_quest_progress("shadow", 1):
                    self.complete_daily_quest()
            
            if self.system.update_quest_progress("kill", 1):
                self.complete_daily_quest()
        
        elif self.player.hp <= 0:
            print("\n💀 You have been defeated!")
            self.game_running = False
    
    def complete_daily_quest(self) -> None:
        if not self.system.daily_quest:
            return
        
        quest = self.system.daily_quest
        print(f"\n🎉 Daily Quest Complete: {quest['name']}!")
        print(f"Rewards: {quest['reward_exp']} EXP, {quest['reward_gold']} Gold")
        
        self.player.gain_exp(quest['reward_exp'])
        self.player.gold += quest['reward_gold']
        self.system.daily_quest = None
        
        self.system.show_system_message("New daily quest will be available tomorrow.")
    
    def dungeon_run(self, difficulty: str = "normal") -> None:
        dungeon_info = self.world.enter_dungeon(difficulty)
        print(f"\n🌟 Entering {difficulty.upper()} Dungeon (Level {dungeon_info['level']})")
        
        enemies_defeated = 0
        for i in range(dungeon_info['enemies']):
            enemy_types = ["goblin", "orc", "wolf", "troll"]
            if i == dungeon_info['enemies'] - 1 and random.random() < dungeon_info['boss_chance']:
                enemy_types = ["dragon", "giant"]
            
            enemy_name = random.choice(enemy_types)
            enemy = self.enemies[enemy_name]
            enemy.level = dungeon_info['level']
            enemy.hp = enemy.max_hp = 30 + dungeon_info['level'] * 20
            enemy.attack = 8 + dungeon_info['level'] * 2
            enemy.defense = 2 + dungeon_info['level']
            
            print(f"\n--- Enemy {i+1}/{dungeon_info['enemies']} ---")
            self.combat(enemy)
            
            if self.player.hp <= 0:
                print("💀 Dungeon run failed!")
                return
            
            enemies_defeated += 1
        
        print(f"\n🎉 Dungeon Clear! Defeated {enemies_defeated} enemies!")
        bonus_gold = dungeon_info['level'] * 50
        bonus_exp = dungeon_info['level'] * 30
        self.player.gold += bonus_gold
        self.player.gain_exp(bonus_exp)
        print(f"Dungeon Rewards: {bonus_exp} EXP, {bonus_gold} Gold")
        
        self.world.dungeon_active = False
        
        if self.system.update_quest_progress("dungeon", 1):
            self.complete_daily_quest()
    
    def shop(self) -> None:
        print("\n=== HUNTER'S SHOP ===")
        print("Welcome! What would you like to buy?")
        print("1. Hunter's Dagger (40 gold)")
        print("2. Knight's Sword (80 gold)")
        print("3. Hunter's Bow (60 gold)")
        print("4. Mage Staff (100 gold)")
        print("5. Hunter's Armor (120 gold)")
        print("6. Health Potion (20 gold)")
        print("7. Mana Potion (25 gold)")
        print("8. Exit shop")
        
        while True:
            choice = input("Enter choice: ").strip()
            
            if choice == "1":
                self.buy_item("dagger", 40)
            elif choice == "2":
                self.buy_item("sword", 80)
            elif choice == "3":
                self.buy_item("bow", 60)
            elif choice == "4":
                self.buy_item("staff", 100)
            elif choice == "5":
                self.buy_item("armor", 120)
            elif choice == "6":
                self.buy_item("potion", 20)
            elif choice == "7":
                self.buy_item("mana_potion", 25)
            elif choice == "8":
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
        
        if location.get("dungeon"):
            print("\nChoose dungeon difficulty:")
            print("1. Easy (Low rewards, safe)")
            print("2. Normal (Balanced)")
            print("3. Hard (High rewards, dangerous)")
            print("4. Hell (Extreme risk, extreme rewards)")
            print("5. Cancel")
            
            choice = input("Enter choice: ").strip()
            difficulties = {"1": "easy", "2": "normal", "3": "hard", "4": "hell"}
            
            if choice in difficulties:
                self.dungeon_run(difficulties[choice])
            return
        
        elif location.get("training"):
            print("\n=== TRAINING GROUND ===")
            print("1. Physical Training (+5 HP)")
            print("2. Magic Training (+5 MP)")
            print("3. Combat Practice (+2 Attack)")
            print("4. Defense Training (+2 Defense)")
            print("5. Cancel")
            
            choice = input("Enter choice: ").strip()
            if choice == "1":
                self.player.max_hp += 5
                self.player.hp += 5
                print("HP increased by 5!")
            elif choice == "2":
                self.player.max_mp += 5
                self.player.mp += 5
                print("MP increased by 5!")
            elif choice == "3":
                self.player.attack += 2
                print("Attack increased by 2!")
            elif choice == "4":
                self.player.defense += 2
                print("Defense increased by 2!")
            return
        
        print("You explore the area but find nothing of interest.")
    
    def main_menu(self) -> None:
        print("\n=== MAIN MENU ===")
        print("1. Explore/Action")
        print("2. Travel")
        print("3. Inventory")
        print("4. Status")
        print("5. Shop (if available)")
        print("6. Shadow Army (if Shadow Monarch)")
        print("7. Save Game")
        print("8. Quit")
    
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
    
    def show_shadow_army(self) -> None:
        if not self.player.is_shadow_monarch:
            print("You are not a Shadow Monarch.")
            return
        
        print(f"\n=== SHADOW ARMY ({len(self.player.shadow_army)} shadows) ===")
        if not self.player.shadow_army:
            print("No shadows in your army yet.")
            return
        
        rank_counts = {}
        for shadow in self.player.shadow_army:
            rank = shadow.rank.value
            rank_counts[rank] = rank_counts.get(rank, 0) + 1
        
        for rank, count in rank_counts.items():
            print(f"{rank}: {count}")
        
        print("\nShadow Details:")
        for i, shadow in enumerate(self.player.shadow_army[:10], 1):
            print(f"{i}. {shadow.name} ({shadow.rank.value})")
            print(f"   HP: {shadow.hp} | ATK: {shadow.attack} | DEF: {shadow.defense}")
            print(f"   Ability: {shadow.special_ability}")
        
        if len(self.player.shadow_army) > 10:
            print(f"... and {len(self.player.shadow_army) - 10} more shadows")
    
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
                "hunter_class": self.player.hunter_class.value,
                "hunter_rank": self.player.hunter_rank.value,
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
                "gold": self.player.gold,
                "is_shadow_monarch": self.player.is_shadow_monarch,
                "shadow_army_size": len(self.player.shadow_army)
            },
            "location": self.world.current_location,
            "daily_quest": self.system.daily_quest
        }
        
        with open("solo_leveling_save.json", "w") as f:
            json.dump(save_data, f, indent=2)
        print("Game saved!")
    
    def run(self) -> None:
        print("🌑 SOLO LEVELING: The System 🌑")
        print("=" * 50)
        
        self.create_character()
        self.game_running = True
        
        if not self.system.daily_quest:
            self.system.generate_daily_quest()
        
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
                    print("Shop not available at this location!")
            elif choice == "6":
                self.show_shadow_army()
            elif choice == "7":
                self.save_game()
            elif choice == "8":
                print("Thanks for playing Solo Leveling!")
                self.game_running = False
            else:
                print("Invalid choice!")
            
            if self.player and self.player.hp <= 0:
                print("\n💀 GAME OVER 💀")
                print("You have fallen in battle...")
                self.game_running = False

if __name__ == "__main__":
    game = SoloLevelingGame()
    game.run()
