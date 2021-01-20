#include "PicVersion.h"

#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <algorithm>
#include <math.h>
#include <Windows.h>
#include <SFML\Window\Mouse.hpp>
#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Thread.hpp"

using namespace std;
using namespace sf;

PicVersion::PicVersion(Settings::Lang lang) : AbstractVersion(lang),
_screen_size(VideoMode::getDesktopMode()),
_pictures_file_path("../../files/pictures/"),
_draw_thread(new sf::Thread(&PicVersion::_draw, this))
{
   _window = new RenderWindow(VideoMode::getDesktopMode(), "The Champion's Shadow", Style::Fullscreen);
   _window->setVerticalSyncEnabled(true);

   _window_width = _window->getSize().x;
   _window_height = _window->getSize().y;

   vector<pair<int, int>> relative_coordinates_vect;
   relative_coordinates_vect.push_back(pair<int, int>(0, 0));

   _warrior_entity = new TwoDEntity(Sprite(_textures_buffer["warrior_idle"], IntRect(0, 0, 500, 600)), TwoDEntity::SpriteDimensions{ 500,600,500,3000 }, relative_coordinates_vect);
   _cleric_entity = new TwoDEntity(Sprite(_textures_buffer["cleric_idle"], IntRect(0, 0, 450, 600)), TwoDEntity::SpriteDimensions{ 450,600,450,3000 }, relative_coordinates_vect);

   map<string, string> fonts_list, textures_list;
   fonts_list["HamletOrNot"] = "../../files/fonts/HamletOrNot.ttf";
   fonts_list["kingthings"] = "../../files/fonts/kingthings.ttf";
   fonts_list["vinque"] = "../../files/fonts/vinque.ttf";
   fonts_list["LatoBlack"] = "../../files/fonts/LatoBlack.ttf";

   textures_list["menu_background"] = _pictures_file_path + "menu_background.jpg";
   textures_list["character_menu_background"] = _pictures_file_path + "character_menu_background.jpg";
   char i = rand() % 3;
   textures_list["fight_background"] = _pictures_file_path + "backgrounds/" + to_string(i) + ".jpg";
   textures_list["warrior_idle"] = _pictures_file_path + "warrior/idle.png";
   textures_list["cleric_idle"] = _pictures_file_path + "cleric/idle.png";
   textures_list["health_bar"] = _pictures_file_path + "statusbars/health.png";
   textures_list["mana_bar"] = _pictures_file_path + "statusbars/mana.png";
   textures_list["gui"] = _pictures_file_path + "gui.png";
   textures_list["empty_bar"] = _pictures_file_path + "statusbars/empty.png";

   for (auto const& x : fonts_list)
      if (!(_fonts_buffer[x.first].loadFromFile(x.second)))
         cout << "Impossible de charger la police de caractere:" << x.first << endl;

   for (auto const& x : textures_list)
      if (!(_textures_buffer[x.first].loadFromFile(x.second)))
         cout << "Impossible de charger la texture:" << x.first << endl;

   _window->setActive(false);

   _draw_thread->launch();
}

PicVersion::~PicVersion()
{
   _animationsCleaner();

   _window->close();

   _draw_thread->wait();
   delete _draw_thread;
   _draw_thread = nullptr;

   delete _window;
   _window = nullptr;

   delete _warrior_entity;
   _warrior_entity = nullptr;

   delete _cleric_entity;
   _cleric_entity = nullptr;

   delete _player_entity;
   _player_entity = nullptr;

   delete _enemy_entity;
   _enemy_entity = nullptr;
}

AbstractVersion::MenuChoice PicVersion::displayMenu()
{
   int _window_width = _window->getSize().x,
      _window_height = _window->getSize().y;
   {
      Text play_text;
      Text settings_text;
      Text quit_text;

      Sprite background_sprite;
      background_sprite.setTexture(_textures_buffer["menu_background"]);
      background_sprite.setScale(_window_width / background_sprite.getLocalBounds().width, _window_height / background_sprite.getLocalBounds().height);

      play_text.setCharacterSize(120);
      play_text.setString("Jouer");
      play_text.setFont(_fonts_buffer["kingthings"]);
      play_text.setFillColor(Color::White);
      play_text.setOutlineColor(Color::White);
      play_text.setStyle(Text::Bold);
      play_text.setPosition((_window_width - play_text.getGlobalBounds().width) / 2, (_window_height - play_text.getGlobalBounds().height) * 0.45f);

      settings_text.setCharacterSize(120);
      settings_text.setString("Parametres");
      settings_text.setFont(_fonts_buffer["kingthings"]);
      settings_text.setFillColor(Color::White);
      settings_text.setOutlineColor(Color::White);
      settings_text.setStyle(Text::Bold);
      settings_text.setPosition((_window_width - settings_text.getGlobalBounds().width) / 2, (_window_height - settings_text.getGlobalBounds().height) * 0.57f);

      quit_text.setCharacterSize(120);
      quit_text.setString("Quitter");
      quit_text.setFont(_fonts_buffer["kingthings"]);
      quit_text.setFillColor(Color::White);
      quit_text.setOutlineColor(Color::White);
      quit_text.setStyle(Text::Bold);
      quit_text.setPosition((_window_width - quit_text.getGlobalBounds().width) / 2, (_window_height - quit_text.getGlobalBounds().height) * 0.73f);

      _sprites_to_draw.set("background", background_sprite);
      _texts_to_draw.set("play", play_text);
      _texts_to_draw.set("settings", settings_text);
      _texts_to_draw.set("quit", quit_text);
   }

   Event event;

   while (_window->isOpen())
   {
      Color play_color = Color::White,
         settings_color = Color::White,
         quit_color = Color::White;


      if (_isMouseOver(_texts_to_draw.get("play")) || _isMouseOver(_texts_to_draw.get("settings")) || _isMouseOver(_texts_to_draw.get("quit")))
      {
         _changeCursor(_CursorType::Hand);

         if (_isMouseOver(_texts_to_draw.get("play")))
            play_color = Color(255, 128, 0);

         else if (_isMouseOver(_texts_to_draw.get("settings")))
            settings_color = Color(255, 128, 0);

         else if (_isMouseOver(_texts_to_draw.get("quit")))
            quit_color = Color(255, 128, 0);
      }
      else
         _changeCursor(_CursorType::Standard);

      _texts_to_draw.lock();
      _texts_to_draw.getWhenLocked("play").setFillColor(play_color);
      _texts_to_draw.getWhenLocked("settings").setFillColor(settings_color);
      _texts_to_draw.getWhenLocked("quit").setFillColor(quit_color);
      _texts_to_draw.unlock();

      while (_pollEvent(event))
      {
         switch (event.type)
         {
         case Event::Closed:
            _window->close(); break;

         case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left)
            {
               _changeCursor(_CursorType::Standard);
               if (_isMouseOver(_texts_to_draw.get("play")))
                  return MenuChoice::Play;

               if (_isMouseOver(_texts_to_draw.get("settings")))
                  return MenuChoice::Settings;

               if (_isMouseOver(_texts_to_draw.get("quit")))
                  return MenuChoice::Quit;

            }break;

         default:
            break;
         }
      }
   }
   return MenuChoice::Quit;
}

CharacterFactory::CharacterType PicVersion::chooseCharacter()
{
   _texts_to_draw.clear();

   TwoDEntity warrior = *_warrior_entity,
      cleric = *_cleric_entity;

   Sprite warrior_sprite, cleric_sprite;

   warrior.getSprite().setScale(0.8f, 0.8f);
   warrior.getSprite().setPosition((_window_width - warrior.getSprite().getGlobalBounds().width) * 0.37f, (_window_height - warrior.getSprite().getGlobalBounds().height) * 0.43f);
   warrior_sprite = warrior.getSprite();

   cleric.getSprite().setScale(0.8f, 0.8f);
   cleric.getSprite().setPosition((_window_width - cleric.getSprite().getGlobalBounds().width) * 0.69f, (_window_height - cleric.getSprite().getGlobalBounds().height) * 0.43f);
   cleric_sprite = cleric.getSprite();

   {
      Sprite background_sprite;
      background_sprite.setTexture(_textures_buffer["character_menu_background"]);
      background_sprite.setScale(_window_width / background_sprite.getLocalBounds().width, _window_height / background_sprite.getLocalBounds().height);

      Text warrior_text;
      warrior_text.setCharacterSize(120);
      warrior_text.setString("Guerrier");
      warrior_text.setFont(_fonts_buffer["kingthings"]);
      warrior_text.setFillColor(Color::White);
      warrior_text.setStyle(Text::Bold);
      warrior_text.setPosition((_window_width - warrior_text.getGlobalBounds().width) * 0.35f, (_window_height - warrior_text.getGlobalBounds().height) * 0.72f);

      Text cleric_text;
      cleric_text.setCharacterSize(120);
      cleric_text.setString("Pretre");
      cleric_text.setFont(_fonts_buffer["kingthings"]);
      cleric_text.setFillColor(Color::White);
      cleric_text.setStyle(Text::Bold);
      cleric_text.setPosition((_window_width - cleric_text.getGlobalBounds().width) * 0.65f, (_window_height - cleric_text.getGlobalBounds().height) * 0.70f);

      _sprites_to_draw.set("background", background_sprite);
      _texts_to_draw.set("warrior", warrior_text);
      _texts_to_draw.set("cleric", cleric_text);
   }

   _animations_vect.push_back(shared_ptr<_AnimationLauncher>(new _AnimationLauncher(*this, warrior, true)));
   _animations_vect.push_back(shared_ptr<_AnimationLauncher>(new _AnimationLauncher(*this, cleric, true)));

   _animationsLauncher();

   Event event;
   while (_window->isOpen())
   {
      Color warrior_color = Color::White,
         cleric_color = Color::White;

      if (_isMouseOver(_texts_to_draw.get("warrior")) || _isMouseOver(_texts_to_draw.get("cleric")) || _isMouseOver(warrior_sprite) || _isMouseOver(cleric_sprite))
      {
         _changeCursor(_CursorType::Hand);

         if (_isMouseOver(_texts_to_draw.get("warrior")) || _isMouseOver(warrior_sprite))
            warrior_color = Color(255, 128, 0);

         else if (_isMouseOver(_texts_to_draw.get("cleric")) || _isMouseOver(cleric_sprite))
            cleric_color = Color(255, 128, 0);
      }
      else
         _changeCursor(_CursorType::Standard);

      _texts_to_draw.lock();
      _texts_to_draw.getWhenLocked("warrior").setFillColor(warrior_color);
      _texts_to_draw.getWhenLocked("cleric").setFillColor(cleric_color);
      _texts_to_draw.unlock();

      while (_pollEvent(event))
      {
         switch (event.type)
         {
         case Event::Closed:
            _window->close(); break;

         case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left)
            {
               _changeCursor(_CursorType::Standard);
               if (_isMouseOver(_texts_to_draw.get("warrior")) || _isMouseOver(warrior_sprite))
                  return CharacterFactory::CharacterType::WarriorType;

               if (_isMouseOver(_texts_to_draw.get("cleric")) || _isMouseOver(cleric_sprite))
                  return CharacterFactory::CharacterType::ClericType;
            }break;

         default:
            break;
         }
      }
   }
   return CharacterFactory::CharacterType::UndefinedType;
}

string PicVersion::choosePseudo()
{
   _animationsCleaner();
   _texts_to_draw.clear();
   _sprites_to_draw.erase("warrior");
   _sprites_to_draw.erase("cleric");

   string pseudo = "";

   const int _window_width = _window->getSize().x,
      _window_height = _window->getSize().y;

   {
      Sprite text_box_sprite;
      text_box_sprite.setTexture(_textures_buffer["gui"]);
      text_box_sprite.setTextureRect(IntRect(0, 49, 190, 45));
      text_box_sprite.setScale(5.6f, 9.5f);
      text_box_sprite.setPosition((_window_width - text_box_sprite.getGlobalBounds().width) * 0.5f, (_window_height - text_box_sprite.getGlobalBounds().height) * 0.48f);

      Text box_text;
      box_text.setCharacterSize(42);
      box_text.setString("Quel sera votre nom?\n(Ne tapez rien si vous vous voulez un nom aléatoire)");
      box_text.setFont(_fonts_buffer["HamletOrNot"]);
      box_text.setFillColor(Color::White);
      box_text.setStyle(Text::Bold);
      box_text.setPosition((_window_width - box_text.getGlobalBounds().width) * 0.5f, (_window_height - box_text.getGlobalBounds().height) * 0.38f);

      Text pseudo_text;
      pseudo_text.setCharacterSize(50);
      pseudo_text.setFont(_fonts_buffer["HamletOrNot"]);
      pseudo_text.setFillColor(Color::Yellow);
      pseudo_text.setStyle(Text::Bold);
      pseudo_text.setPosition((_window_width - box_text.getGlobalBounds().width) * 0.5f, (_window_height - box_text.getGlobalBounds().height) * 0.58f);

      Text ok_text;
      ok_text.setCharacterSize(45);
      ok_text.setString("Valider");
      ok_text.setFont(_fonts_buffer["HamletOrNot"]);
      ok_text.setFillColor(Color::White);
      ok_text.setStyle(Text::Bold);
      ok_text.setPosition((_window_width - ok_text.getGlobalBounds().width) * 0.75f, (_window_height - ok_text.getGlobalBounds().height) * 0.62f);

      _texts_to_draw.set("box", box_text);
      _texts_to_draw.set("ok", ok_text);
      _texts_to_draw.set("pseudo", pseudo_text);
      _sprites_to_draw.set("text_box", text_box_sprite);
   }

   Event event;

   while (_window->isOpen())
   {
      Color couleur_ok = Color::White;

      if (_isMouseOver(_texts_to_draw.get("ok")))
      {
         _changeCursor(_CursorType::Hand);
         couleur_ok = Color(255, 128, 0);
      }
      else
         _changeCursor(_CursorType::Standard);

      _texts_to_draw.lock();
      _texts_to_draw.getWhenLocked("ok").setFillColor(couleur_ok);
      _texts_to_draw.unlock();

      while (_pollEvent(event))
      {
         switch (event.type)
         {
         case Event::Closed:
            _window->close();
            break;
         case Event::TextEntered:
         {
            if ((event.text.unicode == 8) && (!pseudo.empty())) //Backspace
               pseudo.pop_back();
            else if (event.text.unicode == 13) //Retour à la ligne 
               return pseudo;
            else if ((event.text.unicode > 32) && (pseudo.length() < 20))
               pseudo += event.text.unicode;

            _texts_to_draw.lock();
            _texts_to_draw.getWhenLocked("pseudo").setString(pseudo);
            _texts_to_draw.unlock();
            break;
         }
         case Event::MouseButtonReleased:
            _changeCursor(_CursorType::Standard);
            if (event.mouseButton.button == Mouse::Left && _isMouseOver(_texts_to_draw.get("ok")))
               return pseudo;
            break;
         default:
            break;
         }
      }
   }

   return "";
}

void PicVersion::displayPlayersPresentation(Character* const player, Character* const enemy)
{
   _versusAnim(player, enemy);
   _initScene(player, enemy);
}

void PicVersion::_versusAnim(Character* const player, Character* const enemy)
{
   _animationsCleaner();
   _texts_to_draw.clear();
   _sprites_to_draw.erase("text_box");

   Texture vs_texture;
   {
      int _window_width = _window->getSize().x,
         _window_height = _window->getSize().y;

      Sprite background_sprite;
      background_sprite.setTexture(_textures_buffer["fight_background"]);
      background_sprite.setScale(_window_width / background_sprite.getLocalBounds().width, _window_height / background_sprite.getLocalBounds().height);

      Sprite vs;
      if (vs_texture.loadFromFile(_pictures_file_path + "vs.png"))
      {
         vs.setTexture(vs_texture);
         vs.setScale(0.01f, 0.01f);
         vs.setPosition((_window_width - vs.getGlobalBounds().width) * 0.5f, (_window_height - vs.getGlobalBounds().height) * 0.5f);

         _sprites_to_draw.set("vs", vs);
      }

      TwoDEntity warrior = *_warrior_entity,
         cleric = *_cleric_entity;

      warrior.getSprite().setScale(0.8f, 0.8f);
      cleric.getSprite().setScale(0.8f, 0.8f);

      string player_class = player->getClassNameStr(&_lang_manager),
         enemy_class = enemy->getClassNameStr(&_lang_manager);

      if (player_class == "le Guerrier\n")
         _player_entity = new TwoDEntity(warrior);
      else if (player_class == "le Pretre\n")
         _player_entity = new TwoDEntity(cleric);

      if (enemy_class == "le Guerrier\n")
         _enemy_entity = new TwoDEntity(warrior);
      else if (enemy_class == "le Pretre\n")
         _enemy_entity = new TwoDEntity(cleric);

      _player_entity->getSprite().setPosition((_window_width - _player_entity->getSprite().getGlobalBounds().width) * 0.22f, (_window_height - _player_entity->getSprite().getGlobalBounds().height) * 0.43f);

      _enemy_entity->getSprite().scale(-1, 1);
      _enemy_entity->getSprite().setPosition((_window_width - _enemy_entity->getSprite().getGlobalBounds().width) * 0.79f + _enemy_entity->getSprite().getGlobalBounds().width * 0.8f,
         (_window_height - _enemy_entity->getSprite().getGlobalBounds().height) * 0.43f);

      _animations_vect.push_back(shared_ptr<_AnimationLauncher>(new _AnimationLauncher(*this, *_player_entity, true)));
      _animations_vect.push_back(shared_ptr<_AnimationLauncher>(new _AnimationLauncher(*this, *_enemy_entity, true)));

      _animationsLauncher();

      Text player_name;
      player_name.setCharacterSize(80);
      player_name.setString(player->getName() + " (You)");
      player_name.setFont(_fonts_buffer["HamletOrNot"]);
      player_name.setFillColor(Color(255, 65, 65));
      player_name.setStyle(Text::Bold);
      player_name.setPosition((_window_width - player_name.getGlobalBounds().width) * 0.20f, (_window_height - player_name.getGlobalBounds().height) * 0.76f);

      Text enemy_name;
      enemy_name.setCharacterSize(80);
      enemy_name.setString(enemy->getName());
      enemy_name.setFont(_fonts_buffer["HamletOrNot"]);
      enemy_name.setFillColor(Color(255, 65, 65));
      enemy_name.setStyle(Text::Bold);
      enemy_name.setPosition((_window_width - enemy_name.getGlobalBounds().width) * 0.76f, (_window_height - enemy_name.getGlobalBounds().height) * 0.76f);

      _texts_to_draw.set("player_name", player_name);
      _texts_to_draw.set("enemy_name", enemy_name);
      _sprites_to_draw.set("background", background_sprite);
   }

   Clock clock_vs;
   
   _sprites_to_draw.lock();
   Sprite& vs = _sprites_to_draw.getWhenLocked("vs");
   _sprites_to_draw.unlock(); // Autorisation spéciale, pour une animation on se moque des conflits

   while (vs.getScale().x < 0.8f)
   {
      if (clock_vs.getElapsedTime().asMilliseconds() > 2)
      {
         vs.setScale(vs.getScale().x + 0.005f, vs.getScale().y + 0.005f);
         vs.setPosition((_window_width - vs.getGlobalBounds().width) * 0.5f, (_window_height - vs.getGlobalBounds().height) * 0.5f);

         clock_vs.restart();
      }
   }

   Event event;

   bool is_presentation_done = false;
   while (!is_presentation_done)
   {
      while (_pollEvent(event))
      {
         switch (event.type)
         {
         case Event::Closed:
            _window->close(); break;
         case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left)
               is_presentation_done = true;
            break;
         default:
            break;
         }
      }
   }
   _sprites_to_draw.erase("vs");
}

void PicVersion::_initScene(Character* const player, Character* const enemy)
{
   _player_entity->getSprite().setPosition((_window_width - _player_entity->getSprite().getGlobalBounds().width) * 0.15f,
      (_window_height - _player_entity->getSprite().getGlobalBounds().height) * 0.6f);
   _enemy_entity->getSprite().setPosition((_window_width - _enemy_entity->getSprite().getGlobalBounds().width) * 0.85f + _enemy_entity->getSprite().getGlobalBounds().width,
      (_window_height - _enemy_entity->getSprite().getGlobalBounds().height) * 0.6f);

   Sprite health_bar1;
   health_bar1.setTexture(_textures_buffer["health_bar"]);
   health_bar1.setTextureRect(IntRect(8, 0, int(health_bar1.getGlobalBounds().width) - 7, health_bar1.getTextureRect().height));
   health_bar1.setPosition((_window_width - health_bar1.getGlobalBounds().width) * 0.15f + 8, _window_height * 0.1f);

   Sprite health_bar2;
   health_bar2.setTexture(_textures_buffer["health_bar"]);
   health_bar2.setTextureRect(IntRect(8, 0, int(health_bar2.getGlobalBounds().width) - 7, health_bar2.getTextureRect().height));
   health_bar2.setPosition((_window_width - health_bar2.getGlobalBounds().width) * 0.85f + 8, _window_height * 0.1f);

   Sprite mana_bar;
   mana_bar.setTexture(_textures_buffer["mana_bar"]);
   mana_bar.setTextureRect(IntRect(8, 0, int(mana_bar.getGlobalBounds().width) - 7, mana_bar.getTextureRect().height));
   mana_bar.setPosition((_window_width - mana_bar.getGlobalBounds().width) * 0.15f + 8, _window_height * 0.14f);

   Sprite empty_bar1;
   empty_bar1.setTexture(_textures_buffer["empty_bar"]);
   empty_bar1.setPosition(health_bar1.getPosition().x - 8, health_bar1.getPosition().y);

   Sprite empty_bar2;
   empty_bar2.setTexture(_textures_buffer["empty_bar"]);
   empty_bar2.setPosition(health_bar2.getPosition().x - 8, health_bar2.getPosition().y);

   Sprite empty_bar3;
   empty_bar3.setTexture(_textures_buffer["empty_bar"]);
   empty_bar3.setPosition(mana_bar.getPosition().x - 8, mana_bar.getPosition().y);

   Text player_life;
   player_life.setCharacterSize(28);
   player_life.setString(to_string(player->getLife()) + "/" + to_string(player->getMaxLife()));
   player_life.setFont(_fonts_buffer["LatoBlack"]);
   player_life.setFillColor(Color::White);
   player_life.setStyle(Text::Bold);
   player_life.setPosition(health_bar1.getPosition().x - 90, health_bar1.getPosition().y - 7);

   Text enemy_life;
   enemy_life.setCharacterSize(28);
   enemy_life.setString(to_string(enemy->getLife()) + "/" + to_string(enemy->getMaxLife()));
   enemy_life.setFont(_fonts_buffer["LatoBlack"]);
   enemy_life.setFillColor(Color::White);
   enemy_life.setStyle(Text::Bold);
   enemy_life.setPosition(health_bar2.getPosition().x + health_bar2.getGlobalBounds().width + 10, health_bar2.getPosition().y - 7);

   Text player_mana;
   player_mana.setCharacterSize(28);
   player_mana.setString(to_string(enemy->getMana()) + "/" + to_string(enemy->getMaxMana()));
   player_mana.setFont(_fonts_buffer["LatoBlack"]);
   player_mana.setFillColor(Color::White);
   player_mana.setStyle(Text::Bold);
   player_mana.setPosition(mana_bar.getPosition().x - 124, mana_bar.getPosition().y - 7);

   Sprite text_box_sprite;
   text_box_sprite.setTexture(_textures_buffer["gui"]);
   text_box_sprite.setTextureRect(IntRect(0, 49, 190, 45));
   text_box_sprite.setScale(5.7f, 4.7f);
   text_box_sprite.setOrigin(float(text_box_sprite.getTextureRect().width) / 2.f, float(text_box_sprite.getTextureRect().height) / 2.f);
   text_box_sprite.setPosition(_window_width * 0.5f, _window_height * 0.9f);

   Text text_box_txt;
   text_box_txt.setCharacterSize(31);
   text_box_txt.setFont(_fonts_buffer["vinque"]);
   text_box_txt.setFillColor(Color::White);
   text_box_txt.setStyle(Text::Bold);
   text_box_txt.setPosition(text_box_sprite.getPosition().x - text_box_sprite.getGlobalBounds().width / 2 + 35,
      text_box_sprite.getPosition().y - text_box_sprite.getGlobalBounds().height / 2 + 28);

   Sprite next_arrow;
   next_arrow.setTexture(_textures_buffer["gui"]);
   next_arrow.setTextureRect(IntRect(171, 487, 23, int(next_arrow.getGlobalBounds().height)));
   next_arrow.setPosition(_window_width * 0.803f, _window_height * 0.945f);
   next_arrow.scale(1.6f, 1.6f);
   next_arrow.rotate(90);

   Sprite attack_selector;
   attack_selector.setTexture(_textures_buffer["gui"]);
   attack_selector.setTextureRect(IntRect(336, 152, 32, 34));
   attack_selector.setScale(0, 0);
   attack_selector.scale(1.f, 1.f);
   attack_selector.rotate(90);

   _texts_to_draw.set("player_life", player_life);
   _texts_to_draw.set("enemy_life", enemy_life);
   _texts_to_draw.set("player_mana", player_mana);
   _texts_to_draw.set("text_box", text_box_txt);

   _texts_to_draw.lock();
   _texts_to_draw.getWhenLocked("player_name").setPosition(health_bar1.getPosition().x + 3, _window_height * 0.05f);
   _texts_to_draw.getWhenLocked("enemy_name").setPosition(health_bar2.getPosition().x + 3, _window_height * 0.05f);
   _texts_to_draw.getWhenLocked("player_name").setCharacterSize(35);
   _texts_to_draw.getWhenLocked("enemy_name").setCharacterSize(35);
   _texts_to_draw.unlock();

   _sprites_to_draw.set("health_bar1", health_bar1);
   _sprites_to_draw.set("health_bar2", health_bar2);
   _sprites_to_draw.set("mana_bar", mana_bar);
   _sprites_to_draw.set("empty_bar1", empty_bar1);
   _sprites_to_draw.set("empty_bar2", empty_bar2);
   _sprites_to_draw.set("empty_bar3", empty_bar3);
   _sprites_to_draw.set("text_box", text_box_sprite);
   _sprites_to_draw.set("z_next_arrow", next_arrow);
   _sprites_to_draw.set("z_attack_selector", attack_selector);
}

void PicVersion::lifeDisplay(Character* const player, Character* const enemy)
{
   float ratio_player = float(player->getLife()) / float(player->getMaxLife()),
      ratio_enemy = float(enemy->getLife()) / float(enemy->getMaxLife());

   _texts_to_draw.lock();
   _texts_to_draw.getWhenLocked("player_life").setString(to_string(player->getLife()) + "/" + to_string(player->getMaxLife()));
   _texts_to_draw.getWhenLocked("enemy_life").setString(to_string(enemy->getLife()) + "/" + to_string(enemy->getMaxLife()));
   _texts_to_draw.unlock();

   _sprites_to_draw.lock();
   _sprites_to_draw.getWhenLocked("health_bar1").setTextureRect(IntRect(8, 0, int(_sprites_to_draw.get("empty_bar1").getTextureRect().width * ratio_player), _sprites_to_draw.get("empty_bar1").getTextureRect().height));
   _sprites_to_draw.getWhenLocked("health_bar2").setTextureRect(IntRect(8, 0, int(_sprites_to_draw.get("empty_bar1").getTextureRect().width * ratio_enemy), _sprites_to_draw.get("empty_bar1").getTextureRect().height));
   _sprites_to_draw.unlock();
}

void PicVersion::manaDisplay(Character* const player)
{
   float ratio = float(player->getMana()) / float(player->getMaxMana());

   _sprites_to_draw.lock();
   _sprites_to_draw.getWhenLocked("mana_bar").setTextureRect(IntRect(8, 0, int(_sprites_to_draw.get("empty_bar1").getTextureRect().width * ratio), _sprites_to_draw.get("empty_bar1").getTextureRect().height));
   _sprites_to_draw.unlock();

   _texts_to_draw.lock();
   _texts_to_draw.getWhenLocked("player_mana").setString(to_string(player->getMana()) + "/" + to_string(player->getMaxMana()));
   _texts_to_draw.unlock();
}

unsigned short PicVersion::attackChoice(Character* const player, bool is_enemy_attainable)
{
   _printToTextBox(_lang_manager.getStrById("choose_attack", 0).c_str());

   _switchBoxDialog();

   vector<string> attacks_list = player->getAttacksNameList(&_lang_manager);
   map<string, string> attack_description_map = player->getAttacksDescription(&_lang_manager);

   vector<Text> attacks, unusable_attacks;
   string usable = "";
   shared_ptr<AAttackDefinition> current_attack;

   Text temp_text;

   unsigned short i = 0;
   for (string const& attack_name : attacks_list)
   {
      temp_text = _texts_to_draw.get("text_box");

      temp_text.setPosition(temp_text.getPosition().x + 30, temp_text.getPosition().y + 32 * i);

      usable = "";

      current_attack = player->getAttackById(i);

      unsigned short mana_consumption = current_attack->getManaConsumption();

      if ((!is_enemy_attainable && !current_attack->is_user_targeted_only()) || (player->getMana() < current_attack->getManaConsumption())) //si l'ennemi n'est pas accessible (4e dimension par ex) et que l'attaque le vise OU pas assez de mana => on la met dans la liste des interdites
      {
         temp_text.setFillColor(Color(70, 70, 70));
         usable = _lang_manager.getStrById("attack_unusable", 0) + " ";
         temp_text.setString(to_string(mana_consumption) + " :" + usable + attack_name);
      }
      else
      {
         temp_text.setString(to_string(mana_consumption) + " :" + usable + attack_name);
         attacks.push_back(temp_text);
      }
      
      _texts_to_draw.set("attack" + to_string(i), temp_text);

      i++;
   }

   temp_text = _texts_to_draw.get("text_box");

   temp_text.setPosition(temp_text.getPosition().x + 30, temp_text.getPosition().y + 32 * i);
   temp_text.setString("00 :" + _lang_manager.getStrById("miss_turn", 0));
   attacks.push_back(temp_text);

   _texts_to_draw.set("attack" + to_string(i), temp_text);


   Event event;

   while (_window->isOpen())
   {
      _sprites_to_draw.lock();
      Sprite& attack_selector = _sprites_to_draw.getWhenLocked("z_attack_selector");

      bool is_mouse_over_attack = false;
      for (Text const& t : attacks)
      {
         if (_isMouseOver(t))
         {
            _changeCursor(_CursorType::Hand);
            attack_selector.setPosition(t.getPosition().x - 5, t.getPosition().y + 5);
            attack_selector.setScale(1, 1);
            is_mouse_over_attack = true;
            break;
         }
      }
      if (!is_mouse_over_attack)
      {
         _changeCursor(_CursorType::Standard);
         attack_selector.setScale(0, 0);
      }
      _sprites_to_draw.unlock();

      while (_pollEvent(event))
      {
         switch (event.type)
         {
         case Event::Closed:
            _window->close(); break;

         case Event::MouseButtonReleased:
            if (event.mouseButton.button == Mouse::Left)
            {
               for (Text const& t : attacks)
               {
                  if (_isMouseOver(t))
                  {
                     _changeCursor(_CursorType::Standard);

                     _sprites_to_draw.lock();
                     attack_selector.setScale(0, 0);
                     _sprites_to_draw.unlock();

                     for (unsigned int i = 0; i < attacks_list.size() + 1; i++)
                        _texts_to_draw.erase("attack" + to_string(i));

                     _switchBoxDialog();

                     return _getAttackId(t);
                  }
               }
            }break;

         default:
            break;
         }
      }
   }

   return 0;
}

void PicVersion::turnMissed(Character* const player, Character* const target)
{
}

void PicVersion::renderLastAttack(std::vector<AttackSpecificity*> attack_specificity_vct)
{
   vector<string> attacks_already_rendered_list;
   bool is_already_rendered = false;

   string render_str = "";

   for (AttackSpecificity* attack_specify_ptr : attack_specificity_vct)
   {
      string attack_id = attack_specify_ptr->getAttackNameId();

      is_already_rendered = false;

      for (string const& attack_already_rendered : attacks_already_rendered_list)
      {
         if (attack_id == attack_already_rendered) //si l'attaque était déjà affichée
            is_already_rendered = true;
      }

      if (!is_already_rendered) //si elle n'a pas encore été affichée, on l'affiche et on l'ajoute à la liste des affichées
      {
         attacks_already_rendered_list.push_back(attack_id);
         render_str += _strFormat(_lang_manager.getStrById("attack_action_render").c_str(), attack_specify_ptr->getUser()->getName().c_str(), _lang_manager.getStrById(attack_id, 0).c_str()) + '\n';
      }

      switch (attack_specify_ptr->getSkillType())
      {
      case AttackSpecificity::SkillType::DamageAttack:
         //_renderDamageAttack(attack_specify_ptr);
         break;
      case AttackSpecificity::SkillType::EffectAttack:
      {
         unsigned int effect_level = attack_specify_ptr->getEffet()->getLevel();

         render_str += _strFormat(attack_specify_ptr->getEffet()->getDescription(&_lang_manager).c_str(), attack_specify_ptr->getTarget()->getName().c_str()) + '\n';

         break;
      }
      default: break;
      }
   }

   _printToTextBox(render_str);
}

void PicVersion::death(Character* const player)
{

}

void PicVersion::win()
{

}

void PicVersion::lose()
{

}

void PicVersion::cantAttackRender(Character* const player)
{
}

bool PicVersion::_isMouseOver(Text const& text) const
{
   Vector2i mouse_pos = Mouse::getPosition();

   return (mouse_pos.x >= text.getGlobalBounds().left
      && mouse_pos.x <= text.getGlobalBounds().left + text.getGlobalBounds().width
      && mouse_pos.y >= text.getGlobalBounds().top
      && mouse_pos.y <= text.getGlobalBounds().top + text.getGlobalBounds().height);
}

bool PicVersion::_isMouseOver(Sprite const& sprite) const
{
   Vector2i mouse_pos = Mouse::getPosition();

   return (mouse_pos.x >= sprite.getGlobalBounds().left
      && mouse_pos.x <= sprite.getGlobalBounds().left + sprite.getGlobalBounds().width
      && mouse_pos.y >= sprite.getGlobalBounds().top
      && mouse_pos.y <= sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
}

void PicVersion::_changeCursor(_CursorType type) const
{
   LPCTSTR cursor;
   switch (type)
   {
   case Standard:
      cursor = IDC_ARROW; break;
   case Hand:
      cursor = IDC_HAND; break;
   default:
      cursor = IDC_ARROW; break;
   }

   WindowHandle wHandle;
   wHandle = _window->getSystemHandle();
   HCURSOR Cursor = LoadCursor(NULL, cursor);

   SetCursor(Cursor);
   SetClassLongPtr(wHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}

void PicVersion::_animationsCleaner()
{
   for (auto& animation : _animations_vect)
   {
      animation->stopLooping();
      _sprites_to_draw.erase(animation->getId());
   }
   for (auto& animation : _animations_vect)
      animation->wait();

   _animations_vect.clear();
}

void PicVersion::_animationsLauncher()
{
   for (auto& animation : _animations_vect)
      animation->launch();
}

void PicVersion::_draw()
{
   while (_window->isOpen())
   {
      _window->clear();

      if (!_sprites_to_draw.empty())
      {
         _sprites_to_draw.lock();
         for (auto const& x : _sprites_to_draw.getMapWhenLocked())
            _window->draw(x.second);
         _sprites_to_draw.unlock();
      }

      if (!_texts_to_draw.empty())
      {
         _texts_to_draw.lock();
         for (auto const& x : _texts_to_draw.getMapWhenLocked())
            _window->draw(x.second);
         _texts_to_draw.unlock();
      }

      _window->display();
   }
}

PicVersion::_AnimationLauncher::_AnimationLauncher(PicVersion& pic_version, TwoDEntity& entity, bool is_endlessly_looping, int fps) : Thread(&PicVersion::_AnimationLauncher::_animationLaunch, this),
_pic_version(&pic_version),
_entity(entity),
_is_endlessly_looping(is_endlessly_looping),
_fps(fps),
_id("zzzzzzzzzzzzzzz" + std::to_string(_counter++))
{
}

unsigned int PicVersion::_AnimationLauncher::_counter = 0;

/*string PicVersion::_AnimationLauncher::idGenerator()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<unsigned long long> dis(0, unsigned long long(pow(2, 64) - 1));
  return to_string(dis(gen));
}*/

void PicVersion::_AnimationLauncher::_animationLaunch()
{
   Clock clock;

   _pic_version->_sprites_to_draw.set(_id, _entity.getSprite());

   do
   {
      if (!_entity.getRelativeCoordinatesVect().empty())
      {
         for (const auto& x : _entity.getRelativeCoordinatesVect())
         {
            while (clock.getElapsedTime().asMilliseconds() < int(1000 / _fps)) {}

            IntRect rect = _pic_version->_sprites_to_draw.get(_id).getTextureRect();
            TwoDEntity::SpriteDimensions dimensions = _entity.getSpriteDimensions();

            if (rect.left >= dimensions._total_width)
            {
               rect.left = 0;
               rect.top += dimensions._unit_height;
            }
            else
               rect.left += dimensions._unit_width;

            if (rect.top >= dimensions._total_height)
               rect.top = 0;

            _pic_version->_sprites_to_draw.lock();
            Sprite& entity_sprite = _pic_version->_sprites_to_draw.getWhenLocked(_id);

            entity_sprite.setTextureRect(rect);
            entity_sprite.setPosition(entity_sprite.getPosition().x + x.first, entity_sprite.getPosition().y + x.second);
            _pic_version->_sprites_to_draw.unlock();

            clock.restart();
         }
      }
      else
         break;

   } while (_is_endlessly_looping);
}

void PicVersion::_printToTextBox(string str)
{
   size_t pos = str.find("\n\n");
   while (pos != string::npos)
   {
      str.replace(pos, 2, "\n");
      pos = str.find("\n\n");
   }

   vector<string> groups_to_display;

   _texts_to_draw.lock();
   _texts_to_draw.getWhenLocked("text_box").setString(str);
   _texts_to_draw.unlock();

   _texts_to_draw.lock();
   auto text_box_bounds = _texts_to_draw.getWhenLocked("text_box").getGlobalBounds();
   _texts_to_draw.unlock();

   float text_left_pos = text_box_bounds.left,
      text_width = text_box_bounds.width,
      box_left_pos = text_box_bounds.left,
      box_width = text_box_bounds.width;

   float ratio = (box_width - (text_left_pos - box_left_pos) - 100) / text_width;

   string temp_str = "";
   const size_t str_lenght = str.length();

   short lines_nbr = 0;
   if (ratio < 1) //si le texte dépasse de la box
   {
      for (int i = 0; i < ceil(1 / ratio); i++)
      {
         lines_nbr++;
         if (lines_nbr < 4)
         {
            temp_str += str.substr(0, int(floor(ratio * str_lenght))) + '\n';
            str.erase(0, int(floor(ratio * str_lenght)));
         }
         else
         {
            groups_to_display.push_back(temp_str);
            temp_str = "";
            lines_nbr = 0;
            i--;
         }
      }
   }
   else
      temp_str = str;

   if (!temp_str.empty())
      groups_to_display.push_back(temp_str);

   for (string const& str : groups_to_display)
   {
      _texts_to_draw.lock();
      _texts_to_draw.getWhenLocked("text_box").setString(str);
      _texts_to_draw.unlock();

      Event event;

      bool is_next_pressed = false;
      while (!is_next_pressed)
      {
         IntRect texture;
         if (_isMouseOver(_sprites_to_draw.get("z_next_arrow")))
         {
            _changeCursor(_CursorType::Hand);
            texture = IntRect(215, 487, 23, int(_sprites_to_draw.get("z_next_arrow").getGlobalBounds().height));
         }
         else
         {
            _changeCursor(_CursorType::Standard);
            texture = IntRect(171, 487, 23, int(_sprites_to_draw.get("z_next_arrow").getGlobalBounds().height));
         }

         _sprites_to_draw.lock();
         _sprites_to_draw.getWhenLocked("z_next_arrow").setTextureRect(texture);
         _sprites_to_draw.unlock();

         while (_pollEvent(event))
         {
            if (event.type == Event::Closed)
               _window->close();

            if ((event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && _isMouseOver(_sprites_to_draw.get("z_next_arrow")))
               || (event.type == Event::KeyReleased && (event.key.code == Keyboard::Return || event.key.code == Keyboard::Down)))
            {
               is_next_pressed = true;
            }
         }
      }
   }

   _texts_to_draw.lock();
   _texts_to_draw.getWhenLocked("text_box").setString("");
   _texts_to_draw.unlock();
}

int PicVersion::_getAttackId(const Text& t)
{
   int i = int((t.getPosition().y - _texts_to_draw.get("text_box").getPosition().y) / 32);
   return i;
}

void PicVersion::_switchBoxDialog()
{
   _sprites_to_draw.lock();
   Sprite& text_box = _sprites_to_draw.getWhenLocked("text_box");
   _sprites_to_draw.unlock(); // Autorisation spéciale, pour une animation on se moque des conflits

   int top = (text_box.getTextureRect().top == 144) ? 49 : 144;

   while (text_box.getScale().y > 0.3f)
   {
      text_box.setScale(text_box.getScale().x, text_box.getScale().y - 0.4f);
      Sleep(20);
   }

   text_box.setTextureRect(IntRect(0, top, 190, 45));

   while (text_box.getScale().y < 4.7f)
   {
      text_box.setScale(text_box.getScale().x, text_box.getScale().y + 0.4f);
      Sleep(20);
   }
}

bool PicVersion::_pollEvent(Event& event)
{
   return _window->pollEvent(event);
}

template<typename ... Args>
string PicVersion::_strFormat(const std::string& format, Args ... args)
{
   size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
   unique_ptr<char[]> buf(new char[size]);
   snprintf(buf.get(), size, format.c_str(), args ...);
   return string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
