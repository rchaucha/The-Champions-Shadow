#pragma once

#include <string>
#include <vector>
#include "SFML\graphics.hpp"

class TwoDEntity
{
public:
  struct SpriteDimensions { unsigned short _unit_width, _unit_height, _total_width, _total_height; };

  TwoDEntity();
  TwoDEntity(sf::Sprite sprite, SpriteDimensions sprite_dimensions, std::vector<std::pair<int, int>> relative_coordinates_vect);

  sf::Sprite& getSprite() { return _sprite; }
  const SpriteDimensions getSpriteDimensions() const { return _sprite_dimensions; }
  const std::vector<std::pair<int, int>>& getRelativeCoordinatesVect() const { return _relative_coordinates_vect; }

private:
  sf::Sprite _sprite;

  SpriteDimensions const _sprite_dimensions;
  std::vector<std::pair<int, int>> const _relative_coordinates_vect;
};
