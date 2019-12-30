#ifndef DEF_GAME
#define DEF_GAME

#include <sfml/graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "CharacterFactory.h"
#include "VersionsManager.h"
#include "Settings.h"
#include "AAttackDefinition.h"
#include "FilesManager.h"

class Character;

class Game
{
   friend class Character;
public:
   Game();
   ~Game();
   void init();
   void launch();

private:
   void _play();

   void _playerAttack();
   void _aiAttack();
   void _attack(Character * const user, Character * const target, std::shared_ptr<AAttackDefinition> attack_definition);

   void _updateEffects(Character * const target);
   void _updateMana();

   void _playerDead();
   void _aiDead();

   std::string getFilesPath() const;
   std::wstring stringToWstring(const std::string& s) const;

   sf::RenderWindow _window;
   Settings _settings;
   std::unique_ptr<VersionsManager> _version;
   FilesManager _files_manager;

   bool _is_game_closed;

   CharacterFactory _character_factory;

   Character*_player,
	  *_ai;
};

#endif