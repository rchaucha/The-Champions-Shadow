#ifndef DEF_PICVERSION
#define DEF_PICVERSION

#include <string>
#include <memory>
#include "SFML\graphics.hpp"
#include "CharacterFactory.h"
#include "AbstractVersion.h"
#include "LangManager.h"
#include "Settings.h"
#include "2DEntity.h"

class Character;
class Thread;
class Mutex;

class PicVersion : public AbstractVersion
{
public:
  PicVersion(Settings::Lang lang);
  ~PicVersion();

  AbstractVersion::MenuChoice displayMenu() override;
  CharacterFactory::CharacterType chooseCharacter() override;
  std::string choosePseudo() override;
  void displayPlayersPresentation(Character * const player, Character * const enemy) override;
  void lifeDisplay(Character * const player, Character * const enemy) override;
  void manaDisplay(Character * const player) override;
  unsigned short attackChoice(Character * const player, bool is_enemy_attainable) override;
  void turnMissed(Character * const player, Character * const target) override;

  void renderLastAttack(std::vector<AttackSpecificity*> attack_definition) override;
  void death(Character * const player) override;
  void win() override;
  void lose() override;
  void cantAttackRender(Character * const player) override;

private:
  enum _CursorType { Standard, Hand };
  bool _isMouseOver(sf::Text const & text) const;
  bool _isMouseOver(sf::Sprite const &  sprite) const;
  void _changeCursor(_CursorType type) const;

  void _animationsCleaner();
  void _animationsLauncher();

  void _versusAnim(Character * const player, Character * const enemy);
  void _initScene(Character * const player, Character * const enemy);

  void _draw();

  class _AnimationLauncher : public sf::Thread
  {
  public:
    _AnimationLauncher(PicVersion& pic_version, TwoDEntity &entity, bool is_endlessly_looping = false, int fps = 7);

    void stopLooping() { _is_endlessly_looping = false; }
    std::string getId() const { return _id; }

  private:
    void _animationLaunch();
    PicVersion *_pic_version;
    TwoDEntity _entity;
    bool _is_endlessly_looping;
    const std::string _id;
    int _fps;
    static unsigned int _counter;
  };
  std::vector<std::shared_ptr<_AnimationLauncher>> _animations_vect;

  void _printToTextBox(std::string str);

  int _getAttackId(const sf::Text& t);
  void _switchBoxDialog();

  bool _pollEvent(sf::Event& event);

  template<typename ... Args>
  std::string _strFormat(const std::string& format, Args ... args);

  const TwoDEntity *_warrior_entity, *_cleric_entity;
  TwoDEntity *_player_entity, *_enemy_entity;

  std::map<std::string, sf::Texture> _textures_buffer;
  std::map<std::string, sf::Font> _fonts_buffer;
  std::map<std::string, sf::Sprite> _sprites_to_draw;
  std::map<std::string, sf::Text> _texts_to_draw;

  std::string const _pictures_file_path;
  sf::RenderWindow* _window;
  sf::VideoMode _screen_size;

  int _window_width;
  int _window_height;

  sf::Sprite _background;

  sf::Thread* _draw_thread;
  sf::Mutex* _mutex;
};

#endif