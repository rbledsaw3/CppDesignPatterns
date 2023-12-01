/* This Builder pattern creates NPCs with various attributes such as 'name',
 * 'health', 'armor', 'weapon', 'magic', etc. The 'Director' class
 * will handle the construction of these characters
 */

#include <iostream>
#include <memory>
#include <random>
#include <string>

struct DiceQty {
    int value;
};

struct DiceSides {
    int value;
};

int roll(DiceQty qty, DiceSides sides) {
  std::random_device rDev;
  std::uniform_int_distribution<int> dist(1, sides.value);

  int results = 0;
  for (int i = 0; i < qty.value; ++i) {
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
    virtual ~CharacterBuilder() = default;

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
      character->strength = roll(DiceQty { 1 }, DiceSides { 6 }) + 12;
      character->intelligence = roll(DiceQty { 1 }, DiceSides { 6 }) + 9;
      character->wisdom = roll(DiceQty { 1 }, DiceSides { 4 }) + 8;
      character->dexterity = roll(DiceQty { 1 }, DiceSides { 8 }) + 10;
      character->constitution = roll(DiceQty { 1 }, DiceSides { 8 }) + 10;
      character->charisma = roll(DiceQty { 1 }, DiceSides { 6 }) + 12;
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
      character->strength = roll(DiceQty { 1 }, DiceSides { 4 }) + 15;
      character->intelligence = roll(DiceQty { 1 }, DiceSides { 4 }) + 2;
      character->wisdom = roll(DiceQty { 1 }, DiceSides { 4 }) + 2;
      character->dexterity = roll(DiceQty { 3 }, DiceSides { 6 });
      character->constitution = roll(DiceQty { 1 }, DiceSides { 8 }) + 10;
      character->charisma = roll(DiceQty { 1 }, DiceSides { 4 }) + 2;
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
      character->strength = roll(DiceQty { 1 }, DiceSides { 6 }) + 8;
      character->intelligence = roll(DiceQty { 1 }, DiceSides { 6 }) + 12;
      character->wisdom = roll(DiceQty { 1 }, DiceSides { 4 }) + 14;
      character->dexterity = roll(DiceQty { 1 }, DiceSides { 6 }) + 12;
      character->constitution = roll(DiceQty { 2 }, DiceSides { 6 }) + 6;
      character->charisma = roll(DiceQty { 1 }, DiceSides { 4 }) + 14;
    }

    std::shared_ptr<Character> getCharacter() override {
      return character;
    }
};

class CharacterDirector {
  public:
    static void createHero(HeroBuilder& builder) {
      builder.buildCharacterAttributes();
    }

    static void createMonster(MonsterBuilder& builder) {
      builder.buildCharacterAttributes();
    }

    static void createNPC(NPCBuilder& builder) {
      builder.buildCharacterAttributes();
    }
};

int main() {
  HeroBuilder heroBuilder;
  MonsterBuilder monsterBuilder;
  NPCBuilder npcBuilder;

  CharacterDirector::createHero(heroBuilder);
  CharacterDirector::createMonster(monsterBuilder);
  CharacterDirector::createNPC(npcBuilder);

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
