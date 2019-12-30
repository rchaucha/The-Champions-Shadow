#include "2DEntity.h"

using namespace sf;
using namespace std;

TwoDEntity::TwoDEntity() :
	_sprite(Sprite()),
	_sprite_dimensions({ 0,0,0,0 }),
  _relative_coordinates_vect(std::vector<std::pair<int, int>>())
{}

TwoDEntity::TwoDEntity(sf::Sprite sprite, SpriteDimensions sprite_dimensions, std::vector<std::pair<int, int>> relative_coordinates_vect):
	_sprite(sprite),
	_sprite_dimensions(sprite_dimensions),
  _relative_coordinates_vect(relative_coordinates_vect)
{}