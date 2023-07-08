/* This Builder pattern creates NPCs with various attributes such as 'name',
 * 'health', 'armor', 'weapon', 'magic', 'disposition'. The 'Director' class 
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

class NPC {
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

class NPCBuilder {
    public:
        virtual ~NPCBuilder() = default;

        virtual void set_name(const std::string& name) = 0;
        virtual void set_health(int health) = 0;
        virtual void set_armor(const std::string& armor) = 0;
        virtual void set_weapon(const std::string& weapon) = 0;
        virtual void set_magic(const std::string& magic) = 0;
        virtual void set_strength(int strength) = 0;
        virtual void set_intelligence(int intelligence) = 0;
        virtual void set_wisdom(int wisdom) = 0;
        virtual void set_dexterity(int dexterity) = 0;
        virtual void set_constitution(int constitution) = 0;
        virtual void set_charisma(int charisma) = 0;

        virtual std::unique_ptr<NPC> get_npc() = 0;

};

class HeroBuilder : public NPCBuilder {
    std::unique_ptr<NPC> m_npc;
    public:
        HeroBuilder(): m_npc(std::make_unique<NPC>()) {}


         void set_name(const std::string& name) override { m_npc->name = name; }
         void set_health(int health) override { m_npc->health = health; }
         void set_armor(const std::string& armor) override { m_npc->armor = armor; }
         void set_weapon(const std::string& weapon) override { m_npc->weapon = weapon; }
         void set_magic(const std::string& magic) override { m_npc->magic = magic; }
         void set_strength(int strength) override { m_npc->strength = strength; }
         void set_intelligence(int intelligence) override { m_npc->intelligence = intelligence; }
         void set_wisdom(int wisdom) override { m_npc->wisdom = wisdom; }
         void set_dexterity(int dexterity) override { m_npc->dexterity = dexterity; }
         void set_constitution(int constitution) override { m_npc->constitution = constitution; }
         void set_charisma(int charisma) override { m_npc->charisma = charisma; }

         std::unique_ptr<NPC> get_npc() override { return std::move(m_npc); }

};

class NPCDirector {
    public:
        void create_hero(NPCBuilder& builder) {
            builder.set_name("Link");
            builder.set_health(3);
            builder.set_armor("Green Tunic");
            builder.set_weapon("Fighter Sword");
            builder.set_magic("Latern");
            builder.set_strength(roll(9,2));
            builder.set_intelligence(roll(6,3));
            builder.set_wisdom(roll(3,6));
            builder.set_dexterity(roll(9,2));
            builder.set_constitution(roll(9,2));
            builder.set_charisma(roll(3,6));
        }
};


int main() {
    NPCDirector director;
    HeroBuilder builder;

    director.create_hero(builder);
    std::unique_ptr<NPC> hero = builder.get_npc();

    hero->info();

    return 0;
}
