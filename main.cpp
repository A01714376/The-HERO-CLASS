#include <iostream>
#include <string>

class Potion {
public:
    std::string name;
    Potion(std::string n) : name(n) {}
    void consume() {
        std::cout << "[-] Potion '" << name << "' consumed and vanished.\n";
    }
};


class Guild {
public:
    std::string name;
    Guild(std::string n) : name(n) {
        std::cout << "[+] Guild '" << name << "' created.\n";
    }
    ~Guild() {
        std::cout << "[-] Guild '" << name << "' destroyed.\n";
    }
    void printStatus() {
        std::cout << "[INFO] Guild '" << name << "' is still active and waiting for new members.\n";
    }
};

class Weapon {
public:
    std::string name;
    int baseDamage;

    Weapon(std::string n, int dmg) : name(n), baseDamage(dmg) {
        std::cout << "[+] Weapon base '" << name << "' created.\n";
    }
    virtual ~Weapon() {
        std::cout << "[-] Weapon '" << name << "' destroyed.\n";
    }

    virtual void attack() {
        std::cout << "[ACTION] Attacking with " << name << " for " << baseDamage << " damage\n";
    }
};

class Sword : public Weapon {
public:
    int sharpness;

    Sword(std::string n, int dmg, int sharp) : Weapon(n, dmg), sharpness(sharp) {}

    void attack() override {
        std::cout << "[ACTION] Slashing with sword '" << name
                  << "' for " << (baseDamage + sharpness) << " damage (Includes sharpness bonus)\n";
    }
};


class GameObject {
public:
    GameObject() { std::cout << "[+] GameObject initialized.\n"; }
    virtual ~GameObject() { std::cout << "[-] GameObject destroyed.\n"; }
};

class Stats {
public:
    int health;
    int mana;
    Stats(int h, int m) : health(h), mana(m) {
        std::cout << "Stats (Internal) created.\n";
    }
    ~Stats() {
        std::cout << "Stats (Internal) deleted. No memory leaks\n";
    }
};

class SoulMark {
public:
    std::string markName;
    SoulMark(std::string m) : markName(m) {
        std::cout << "SoulMark '" << markName << "' (Internal) bound to body.\n";
    }
    ~SoulMark() {
        std::cout << "SoulMark '" << markName << "' (Internal) faded away.\n";
    }
};

class Hero : public GameObject {
private:
    Stats stats;
    SoulMark soulMark;
    Guild* guild;
    Weapon* weapon;

public:
    Hero() : GameObject(), stats(100, 50), soulMark("Darksign"), guild(nullptr), weapon(nullptr) {
        std::cout << "[+] Hero has spawned into the world.\n";
    }

    ~Hero() override {
        std::cout << "\n[!] HERO IS DYING... Running destructor:\n";
    }

    void joinGuild(Guild* g) {
        guild = g;
        std::cout << "[EVENT] Hero joined guild: " << guild->name << "\n";
    }

    void equipWeapon(Weapon* w) {
        weapon = w;
        std::cout << "[EVENT] Hero equipped: " << weapon->name << "\n";
    }


    void usePotion(Potion* p) {
        if (p) {
            std::cout << "[ACTION] Hero uses a potion...\n";
            p->consume();
        }
    }

    void performAttack() {
        if (weapon) {
            weapon->attack();
        } else {
            std::cout << "[ACTION] Hero punches with bare hands\n";
        }
    }
};

int main() {
    std::cout << "Starting Simulation\n";


    Guild* serverGuild = new Guild("Knights");
    Weapon* rareSword = new Sword("Great Sword", 50, 15);


    Potion healthPotion("Major Health Potion");

    std::cout << "\nCreating Hero\n";
    Hero* protagonist = new Hero();

    std::cout << "\nRelationships\n";
    protagonist->joinGuild(serverGuild);
    protagonist->equipWeapon(rareSword);

    std::cout << "\nAction Sequence\n";
    protagonist->usePotion(&healthPotion);
    protagonist->performAttack();

    std::cout << "\nSimulating Hero Death\n";
    delete protagonist;

    std::cout << "\nPost death verification\n";

    serverGuild->printStatus();
    std::cout << "[INFO] The weapon '" << rareSword->name << "' dropped to the ground and still exists.\n";

    std::cout << "\nShutdown\n";
    delete serverGuild;
    delete rareSword;

    return 0;
}
