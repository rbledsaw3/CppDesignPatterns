/* This Builder pattern creates NPCs with various attributes such as 'name',
 * 'health', 'armor', 'weapon', 'magic', etc. The 'Director' class 
 * will handle the construction of these characters
 */

#include <iostream>
#include <memory>
#include <string>
#include <random>

int roll(int diceQty, int diceSides) {
    std::random_device rDev;
    std::uniform_int_distribution<int> dist(1, diceSides);

    int results = 0;
    for(int i = 0; i < diceQty; ++i) {
        results += dist(rDev);
    }

    return results;
}

class Character {
    public:
        std::string name;
        int health;
        std::string armor;
        std::string weapon;
        std::string magic;
        int strength;
        int intelligence;
        int wisdom;
        int dexterity;
        int constitution;
        int charisma;

        void info() const {
            std::cout << "NPC " << name << ":\n";
            
            std::cout << "Health: " << health << "\n";
            std::cout << "Armor: " << armor << "\n";
            std::cout << "Weapon: " << weapon << "\n";
            std::cout << "Magic: " << magic << "\n";
            std::cout << "STR: " << strength << "\n";
            std::cout << "INT: " << intelligence << "\n";
            std::cout << "WIS: " << wisdom << "\n";
            std::cout << "DEX: " << dexterity << "\n";
            std::cout << "CON: " << constitution << "\n";
            std::cout << "CHA: " << charisma << "\n";
        }
};

class CharacterBuilder {
    public:
        virtual ~CharacterBuilder() {}
        virtual void buildCharacterAttributes() = 0;
        virtual std::shared_ptr<Character> getCharacter() = 0;
};

class HeroBuilder : public CharacterBuilder {
    public:
        std::shared_ptr<Character> character;

        HeroBuilder() { 
            this->reset(); 
        }

        void reset() {
            character = std::make_shared<Character>();
        }

        void buildCharacterAttributes() override {
            character->name = "Link";
            character->health = 3;
            character->armor = "Green Tunic";
            character->weapon = "Fighter Sword";
            character->magic = "Latern";
            character->strength = roll(1,6)+12;
            character->intelligence = roll(1,6)+9;
            character->wisdom = roll(1,4)+8;
            character->dexterity = roll(1,8)+10;
            character->constitution = roll(1,8)+10;
            character->charisma = roll(1,6)+12;
        }

        std::shared_ptr<Character> getCharacter() override {
            return character;
        }
};


class MonsterBuilder : public CharacterBuilder {
    public:
        std::shared_ptr<Character> character;

        MonsterBuilder() { 
            this->reset(); 
        }

        void reset() {
            character = std::make_shared<Character>();
        }

        void buildCharacterAttributes() override {
            character->name = "Moblin";
            character->health = 2;
            character->armor = "None";
            character->weapon = "Spear";
            character->magic = "None";
            character->strength = roll(1,4)+15;
            character->intelligence = roll(1,4)+2;
            character->wisdom = roll(1,4)+2;
            character->dexterity = roll(3,6);
            character->constitution = roll(1,8)+10;
            character->charisma = roll(1,4)+2;
        }

        std::shared_ptr<Character> getCharacter() override {
            return character;
        }
};

class NPCBuilder : public CharacterBuilder {
    public:
        std::shared_ptr<Character> character;

        NPCBuilder() { 
            this->reset(); 
        }

        void reset() {
            character = std::make_shared<Character>();
        }

        void buildCharacterAttributes() override {
            character->name = "Pricess Zelda";
            character->health = 12;
            character->armor = "Sheika Robes";
            character->weapon = "Gleaming Rapier";
            character->magic = "Teleport";
            character->strength = roll(1,6)+8;
            character->intelligence = roll(1,6)+12;
            character->wisdom = roll(1,4)+14;
            character->dexterity = roll(1,6)+12;
            character->constitution = roll(2,6)+6;
            character->charisma = roll(1,4)+14;
        }

        std::shared_ptr<Character> getCharacter() override {
            return character;
        }
};

class CharacterDirector {
    public:
        void createHero(HeroBuilder& builder) {
            builder.buildCharacterAttributes();
        }
        
        void createMonster(MonsterBuilder& builder) {
            builder.buildCharacterAttributes();
        }

        void createNPC(NPCBuilder& builder) {
            builder.buildCharacterAttributes();
        }
};


int main() {
    CharacterDirector director;
    HeroBuilder heroBuilder;
    MonsterBuilder monsterBuilder;
    NPCBuilder npcBuilder;
    
    director.createHero(heroBuilder);
    director.createMonster(monsterBuilder);
    director.createNPC(npcBuilder);

    std::shared_ptr<Character> hero = heroBuilder.getCharacter();
    std::shared_ptr<Character> monster = monsterBuilder.getCharacter();
    std::shared_ptr<Character> npc = npcBuilder.getCharacter();
    
    hero->info();
    std::cout << "\n";
    monster->info();
    std::cout << "\n";
    npc->info();

    return 0;
}
