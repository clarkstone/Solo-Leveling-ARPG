# Solo Leveling-Inspired ARPG Vertical Slice Roadmap

## Overview

This roadmap outlines the development of a vertical slice demonstrating the core gameplay loop from F-rank hunter to E-rank hero. The slice will showcase combat, exploration, progression, and a climactic boss battle in a 15-30 minute experience.

## 🎯 Vertical Slice Content Plan

### Story & Progression Loop

**Objective:** Demonstrate core gameplay loop: fight enemies → gain loot/XP → improve skills → face stronger challenge → rank up from F to E.

**Key Elements:**
- **Starting Point:** F-rank hunter at Guild Hall hub
- **Main Quest:** Investigate dangerous anomaly (gate) unleashing monsters
- **Progression:** XP system with rank-up at completion
- **Duration:** 15-30 minutes complete experience
- **Scope:** Single region, one quest arc, focused content

### World Region & Dungeons

**Playable Area:** 0.5 x 0.5 km micro-open-world with dark enchanted forest theme

**Hub Area:**
- Small Guild Hall village
- NPC guild master for quest acceptance
- Basic services (training dummy, vendor)
- Safe starting point

**Dungeon 1: Side Dungeon (Optional)**
- Small cave or crypt
- Handful of mobs + mini-boss
- Rewards: Unique weapon or spell scroll
- Demonstrates multi-class potential

**Dungeon 2: Main Dungeon (Critical Path)**
- Ancient temple of shadows/demonic castle
- Distinct sections: antechamber → gauntlet → boss arena
- Environmental hazards and puzzles
- Linear with hidden alcoves for extra loot

### Core Enemies & Boss

**Enemy Types:**
- **Lesser Fiends:** Common trash mobs (goblin-like/undead)
- **Elite Enemy:** Mid-tier mini-boss (Orc Brute/Lesser Demon Knight)
- **Dungeon Mini-Boss:** Guardian statue or sub-boss monster

**Major Boss: Shadow Monarch's Avatar**
- **Phase 1:** Basic attacks and patterns (0-66% HP)
- **Phase 2:** Evolved form with new hazards (66-33% HP)
- **Phase 3:** Frenzy mode with ultimate attack (33-0% HP)
- Three-phase design testing player mastery

## 🛠️ System Feature Scope

### Combat & Core Gameplay Loop

**Combat System:**
- Real-time third-person action
- Weighty Souls-like combat feel
- Light/heavy attacks + dodge roll
- Lock-on targeting system
- Minimal stamina management
- Responsive, impactful combat

**Technical Implementation:**
- Unreal Engine 5.3+ Gameplay Ability System (GAS)
- Animation montages for combos
- Behavior Trees for AI
- Root motion animations
- Network-safe for future co-op

**Enemy AI:**
- Simple states: patrol → chase → attack → recover
- AI Perception for sight radius
- Telegraphed moves with clear tells
- Boss AI with phase-based selectors

### Skill Acquisition & Powers Progression

**Progression Systems:**
- XP system tied to combat/quests
- Rank-up from F to E at completion
- Tangible improvements: stat increase + new skill
- Milestone-based unlocks (not full skill tree)

**Skill Implementation:**
- Start: 1 basic skill (sword combo + dodge)
- Midway: 1 new ability (Fireball spell or similar)
- Boss fight: 2+ active skills + utility
- GAS-based ability system
- Linear unlock approach for slice scope

**Demonstrated Powers:**
- **Fighter:** Sword combos, heavy strikes
- **Mage:** Ranged magic projectile
- **Ranger/Assassin:** Bow or stealth mechanic (if resources allow)

### Character Customization

**Cosmetic Customization:**
- Equip different gear pieces with visual changes
- Modular character parts or pre-made armor sets
- Choose from 2-3 starting appearances
- Visual upgrades through loot
- High-quality player models (Metahuman/Paragon)

**Mechanical Customization:**
- Simple talent choice on level-up
- Guild reputation spending choices
- Easy weapon swapping mid-game
- Basic inventory UI for equipment
- Data-driven weapon stats

### Loot, Inventory & Progression

**Item Types:**
- **Weapons:** Iron Sword → Knight's Longsword → Bow/Staff
- **Armor:** Shadow Hunter Coat (boss drop)
- **Consumables:** Healing potions
- **Miscellaneous:** Gold/Mana crystals

**Inventory System:**
- Basic UI with icons and stats
- Equipment slots (weapon, armor, accessory)
- Item use effects (healing, stat boosts)
- 10-item cap for slice simplicity

**Progression Tracking:**
- XP bar with level-up notification
- Guild reputation counter
- NPC dialogue changes based on rank
- Save system for boss checkpoint

## 📅 Development Roadmap (5 Phases)

### Phase 1: Core Setup and Grayboxing (2-3 weeks)

**Objectives:**
- Establish UE5 project foundation
- Create basic player controller
- Prototype combat mechanics
- Graybox environments
- Basic enemy placeholder

**Key Deliverables:**
- ✅ Project initialization with source control
- ✅ Character controller with ALS integration
- ✅ Combat gym with melee attack + dodge
- ✅ Grayboxed hub, overworld, dungeon layouts
- ✅ Basic AI enemy (cylinder/mannequin)
- ✅ First playable prototype

**Tools & Assets:**
- Advanced Locomotion System (free)
- UE5 mannequin assets
- Basic landscape tools
- Simple collision shapes

### Phase 2: Combat Systems & Player Abilities (3-4 weeks)

**Objectives:**
- Implement Gameplay Ability System
- Create real combat animations
- Add special skills
- Upgrade enemy AI
- Build damage/stats system
- Create basic HUD

**Key Deliverables:**
- ✅ GAS integration with ability components
- ✅ Light attack combo (3-chain) + heavy attack
- ✅ Special abilities (Fireball, Power Strike)
- ✅ Enemy AI with Behavior Trees
- ✅ Elite enemy variant
- ✅ Player/Enemy stats system
- ✅ Basic HUD (health, XP, ability icons)

**Tools & Assets:**
- Animation Starter Pack
- Paragon character animations
- Infinity Blade sound effects
- GAS documentation

### Phase 3: World Building & Content Integration (4-5 weeks)

**Objectives:**
- Create actual environments
- Add lighting and atmosphere
- Populate with enemies and loot
- Implement NPCs and hub
- Script quest logic
- Create boss prototype

**Key Deliverables:**
- ✅ High-quality environment art (Megascans/Infinity Blade)
- ✅ Atmospheric lighting (dusk theme, fog)
- ✅ Enemy spawn points and encounters
- ✅ Side dungeon with mini-boss
- ✅ Main dungeon with boss arena
- ✅ Hub NPCs (Guild Master, vendor)
- ✅ Main quest scripting
- ✅ Boss Phase 1 implementation
- ✅ Basic audio integration

**Tools & Assets:**
- Quixel Megascans (free)
- Infinity Blade environment packs
- Paragon character models
- Free sound packs
- UE5 lighting tools

### Phase 4: Progression & Refinement (3-4 weeks)

**Objectives:**
- Finalize XP and leveling
- Implement skill unlocks
- Polish inventory UI
- Add economy/vendor
- Balance gameplay
- Bug fixing
- Visual improvements

**Key Deliverables:**
- ✅ XP bar with rank-up to E
- ✅ Skill choice UI (2 options)
- ✅ Inventory with icons and stats
- ✅ Vendor with currency system
- ✅ Guild reputation effects
- ✅ Balanced combat (2-3 hits for grunts, 5 hits player HP)
- ✅ Boss tuning (3 mistakes allowed)
- ✅ Particle effects for spells
- ✅ Performance optimization

**Tools & Assets:**
- Infinity Blade Effects pack
- Free RPG icon sets
- UE5 Profiler tools
- Community inventory plugins

### Phase 5: Final Polishing and Testable Build (2-3 weeks)

**Objectives:**
- Fine-tune animations
- Polish UI design
- Performance optimization
- Playtesting and feedback
- Package final build
- Create title screen

**Key Deliverables:**
- ✅ Polished animation blending
- ✅ Dark fantasy UI theme
- ✅ Stable 60+ FPS performance
- ✅ Playtested with external feedback
- ✅ Packaged Windows build
- ✅ Title screen and menu
- ✅ Final boss all phases
- ✅ Complete 15-30 minute experience

**Tools & Assets:**
- UE5 packaging tools
- Performance profilers
- External testing feedback
- Final audio mixing

## 🛠️ Recommended Tools & Plugins

### Essential Free Resources:
- **Unreal Marketplace Samples:** Action RPG Sample, Lyra Starter Game
- **Advanced Locomotion System (ALSv4):** Professional character controller
- **Paragon Characters:** 39 AAA-quality character models
- **Infinity Blade Assets:** Environment pieces, weapons, effects
- **Gameplay Ability System:** Built-in UE5 RPG framework

### Time-Saving Plugins:
- **Inventory Systems:** Community RPG inventory ($30)
- **Dialogue Systems:** Quest Manager plugins
- **Visual Effects:** Infinity Blade Effects pack
- **Audio:** Free sound libraries + music packs

### Development Tools:
- **Source Control:** Git with LFS for assets
- **Project Management:** Trello/GitHub Projects
- **Profiling:** UE5 Stat Unit, Profiler
- **Communication:** Unreal Slackers Discord

## 🎯 Production Tips for Solo Development

### Prioritization Strategy:
1. **Core Gameplay First:** Combat feel, basic progression, boss fight
2. **Vertical Not Horizontal:** Complete end-to-end experience
3. **Graybox Generously:** Test gameplay before art assets
4. **Fake Complex Systems:** Script instead of full implementation
5. **Time Management:** Micro-deadlines with playable builds

### Development Best Practices:
- **Test Early, Test Often:** Get feedback as soon as playable
- **Progressive Polish:** Bring everything to 70% then 90%
- **Leverage Community:** Use forums and existing assets
- **Maintainable Code:** Document Blueprints and use naming conventions
- **Scope Control:** Resist feature creep, focus on slice goals

### Polish Priorities:
1. **Combat Visuals:** Animation smoothing, hit feedback
2. **Key Moments:** First combat, skill unlock, boss fight
3. **UI Clarity:** Minimalist, functional interface
4. **Performance:** Stable frame rate optimization
5. **Audio:** Impact sounds, atmospheric music

## 📊 Success Metrics

### Completion Criteria:
- ✅ 15-30 minute complete playthrough
- ✅ F to E rank progression demonstrated
- ✅ All major systems working together
- ✅ Boss fight winnable with current mechanics
- ✅ No crashes or softlocks
- ✅ Stable 60+ FPS performance

### Quality Targets:
- **Combat:** Responsive, impactful, fair difficulty
- **Progression:** Clear advancement, meaningful choices
- **Exploration:** Rewarding but not mandatory side content
- **Presentation:** Polished key moments, cohesive art style
- **Technical:** Stable build, good performance

## 🚀 Expected Outcome

The completed vertical slice will demonstrate:
- **Fluid Combat:** Souls-inspired action with multiple abilities
- **Open World Feel:** Small but immersive region with exploration
- **Character Growth:** Satisfying progression from F to E rank
- **Epic Climax:** Three-phase boss battle testing player mastery
- **Professional Quality:** AAA-level presentation using marketplace assets

This slice serves as both a playable demo and a strong foundation for full game development, proving the concept's viability and providing a polished showcase of the Solo Leveling ARPG vision.
