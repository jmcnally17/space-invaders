#include "../../include/adaptors/SpriteAdaptor.hpp"

SpriteAdaptor::SpriteAdaptor(sf::Texture &texture) : texture_(texture)
{
  sprite_.setTexture(texture_);
}

sf::Vector2f SpriteAdaptor::getPosition() const
{
  return sprite_.getPosition();
}

void SpriteAdaptor::setPosition(const sf::Vector2f &position)
{
  sprite_.setPosition(position);
}

void SpriteAdaptor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(sprite_, states);
};

void SpriteAdaptor::move(const sf::Vector2f &offset)
{
  sprite_.move(offset);
}

sf::FloatRect SpriteAdaptor::getGlobalBounds() const
{
  return sprite_.getGlobalBounds();
}
