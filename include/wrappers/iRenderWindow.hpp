#ifndef I_RENDER_WINDOW_HPP
#define I_RENDER_WINDOW_HPP

#include <SFML/Graphics.hpp>

class IRenderWindow
{
public:
  virtual void clear() = 0;
  virtual void draw(const sf::Drawable &drawable) = 0;
  virtual void display() = 0;
};

#endif
