#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include "team.h"
#include "random.h"
//#include "level.h"

class Mob : public Entity {

public:
	using Entity::Entity;

	Mob();

	~Mob() = default ;

	Mob(double maxHealth, double x, double y);

	double getHealth() const;

	void setHealth(double x);

	double getMaxHp() const;

	static int getCount();

	void damage(double damage);

	void heal(double amt);

	void checkHp();

	bool isAlive() const {return _isAlive;}
	void healthRegen(); //Any sort of health regeneration that needs to be called
	void manaRegen();// Any sort of mana regeneration that needs to be called


	// update function needs to have the same parameters as the update function it inherits/overrides
	void update() override;

	virtual void drawSelf(Example& gfx) const override;

	virtual void die();
	virtual void revive();

//	bool inRange(const Mob & target) // Has levelRef and members to determine location
//	{
//		target.getXPos()...something here
//	}

	//each type of mob will have a different attack type & it is up to them to implement this
	virtual void attack(Mob* target);

	Team& getTeam();

//	double getSpeed() const;
//	void setSpeed(double);
    int counter = 0;
private:
	// Personal State
	bool _isAlive = true;

	// Health
	double _health;
	double _maxHealth;
	double _hpPerFrame;

			//void setHealth(double hp);
	void addToHealth(double hpPlus); // Increase Hp by hpPlus
	void setMaxHealth(double hpMax); // Set Maximum health
	void setHpPerFrame(double hpRegen); // Set the Hp regenerated each frame
	void addToHpPerFrame(double hpRegenPlus); // Increase the amount of health regenerated each frame

			//auto getHealth();
	auto getMaxHealth();
	auto getHpPerFrame();

	// Mana
	double _mana;
	double _maxMana;
	double _mpPerFrame;

	void setMana(double mp);
	void addToMana(double mpPlus); // Increase Mp by mpPlus
	void setMaxMana(double mpMax); // Set Maximum mana
	void setMpPerFrame(double mpRegen); // Set the Mp regenerated each frame
	void addToMpPerFrame(double mpRegenPlus); // Increase the amount of mana regenerated each frame

	auto getMana();
	auto getMaxMana();
	auto getMpPerFrame();

	// Offense
	double _attackDmg;
	double _critModifier;
	double _critChance;
	double _attackRange;
	double _distFromTarget;

	auto getAttackDmg(); // Get the amount of damage dealt by this mob
	auto getCritModifier(); // Get the critical damage modifier for this mob
	auto getCritChance(); // Get the critical chance for this mob's attacks
	auto getAttackRange(); // Get the range of attack for this mob
	auto getDistFromTarget(); // Get the distance between this mob and its target  - > // Prabably more of a level function


	void setAttackDmg(double attackDmg); // Set the amount of damage dealt by this mob
			//void addToAttackDmg(); // Increase the amount of damage dealt by this mob
	void setCritModifier(double critModifier); // Get the critical damage modifier for this mob
			//void addToCritModifier(); // Increase the critical damage modifier for this mob
	void setCritChance(double critChance); // Get the critical chance for this mob's attacks
	void setAttackRange(double attackRange); // Get the range of attack for this mob



//	double _speed;

	Team _team;

	//Keeps track of the number of current constructed mobs in existence.
	//if you want a counter to keep mob counts within a range in the level,
	//it needs to be done differently.
	static int _mobPop;
};

class ChaserMob: public Mob {
private:

public:
    ChaserMob ();
    ChaserMob (double x, double y);
    virtual void update() override;
    virtual void drawSelf(Example& gfx) const override;
};


class ScatterMob: public Mob {
private:
//    Random random1;
//    std::mt19937 generator;
public:
    ScatterMob(double x, double y);

    virtual void update() override;
};
#endif

/*
 * make a pure virtual function attack()
 * pass update() & drawSelf() onto the derived classes
 * create derived classes: anActualTank, gunThrower, spellCaster, tank, summoner, summonedMob
 */
