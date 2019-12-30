#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "AAttackDefinition.h"

class LangManager;
class Effect;

class Character
{
	friend class Game;

public:
	Character(std::string name, int strenght, int defense, int precision, int evade, unsigned int life = 50, unsigned short mana = 100);
	virtual ~Character() {}
	unsigned int takeDamage(unsigned int amout);
	unsigned int heal(unsigned int amout);
	bool subtractMana(unsigned short amout);
	void addMana(unsigned short amout);

	std::shared_ptr<AAttackDefinition> getAttackById(unsigned short id) const { return _attacks_list[id]; }

	unsigned int getAttacksListSize() { return _attacks_list.size(); }
	std::vector<std::string> getAttacksNameList(LangManager const *lang_manager);
	std::map<std::string, std::string> getAttacksDescription(LangManager const *lang_manager);

	const std::string getName() const { return _name; }
	unsigned int getLife() const { return _life; }
	unsigned int getMaxLife() const { return _max_life; }
	unsigned short getMana() const { return _mana; }
	unsigned short getMaxMana() const { return _max_mana; }
	int getStrenght() const { return _strenght; }
	int getDefense() const { return _defense; }
	int getPrecision() const { return _precision; }
	int getEvade() const { return _evade; }
	bool canBeAttacked() const { return (_unable_to_be_attacked_counter == 0) ? true : false; }
	bool canAttack() const { return (_unable_to_attack_counter == 0) ? true : false; }

	void setIsAttackable(bool new_state) { (new_state) ? _unable_to_be_attacked_counter-- : _unable_to_be_attacked_counter++; }
	void setIsAbleToAttack(bool new_state) { (new_state) ? _unable_to_attack_counter-- : _unable_to_attack_counter++; }
	void addStrenght(unsigned int addition) { _strenght += addition; }
	void addDefense(unsigned int addition) { _defense += addition; }
	void addPrecision(unsigned int addition) { _precision += addition; }
	void addEvade(unsigned int addition) { _evade += addition; }
	void subtractStrenght(unsigned int subtraction) { _strenght -= subtraction; }
	void subtractDefense(unsigned int subtraction) { _defense -= subtraction; }
	void subtractPrecision(unsigned int subtraction) { _precision -= subtraction; }
	void subtractEvade(unsigned int subtraction) { _evade -= subtraction; }

	void addEffect(Effect* effect);

	void updateEffects();

	virtual const std::string getClassNameStr(LangManager const *lang_manager) const = 0;
	virtual std::shared_ptr<AAttackDefinition> aiAction(Character const &enemy) const = 0;

protected:
	unsigned int _getNumberOfAttacks() { return _attacks_list.size(); }
	std::vector<unsigned int> _getUsableAttacks(Character const &enemy) const;

	unsigned int _life;
	unsigned int const _max_life;
	unsigned short _mana;
	unsigned short const _max_mana;

	int _strenght;	//force
	int _defense;	//defense
	int _precision;	//precision
	int _evade;		//esquive

	std::string const _name;

	std::vector<Effect*> _effects;

	std::vector<std::shared_ptr<AAttackDefinition>>_attacks_list;

private:
	unsigned int _unable_to_attack_counter;      //compteur de fois où le perso prend un effet le rendant intouchable
	unsigned int _unable_to_be_attacked_counter; //compteur de fois où le perso est stun, epuisé, ...
};

#endif