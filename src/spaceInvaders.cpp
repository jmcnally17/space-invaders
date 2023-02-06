#include "../include/wrappers/renderWindowWrapper.hpp"
#include "../include/wrappers/spriteWrapper.hpp"
#include "../include/models/laser.hpp"
#include "../include/wrappers/soundWrapper.hpp"
#include "../include/models/laserCannon.hpp"
#include "../include/models/squid.hpp"
#include "../include/models/crab.hpp"
#include "../include/models/octopus.hpp"
#include "../include/spaceInvaders.hpp"

int main()
{
  RenderWindowWrapper window(sf::VideoMode(1536, 1344), "Space Invaders");

  Laser laser = makeLaser();
  LaserCannon cannon = makeCannon(laser);
  std::vector<std::vector<IInvader *>> invaders = makeInvaders();

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
    }

    drawObjects(window, cannon, laser, invaders);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      moveLaserCannon(cannon, 0.25);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      moveLaserCannon(cannon, -0.25);
    }
    moveLaser(laser);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      fireLaser(cannon);
    }
  }

  return 0;
}

Laser makeLaser()
{
  sf::Texture laserTexture;
  laserTexture.loadFromFile("public/images/newSprites/laser.png");
  SpriteWrapper *laserSpriteWrapper = new SpriteWrapper(laserTexture);
  SpriteWrapper &rSpriteWrapper = *laserSpriteWrapper;

  Laser laser(rSpriteWrapper);
  return laser;
}

LaserCannon makeCannon(Laser &laser)
{
  sf::Texture cannonTexture;
  cannonTexture.loadFromFile("public/images/newSprites/laserCannon.png");
  SpriteWrapper *cannonSpriteWrapper = new SpriteWrapper(cannonTexture);
  SpriteWrapper &rSpriteWrapper = *cannonSpriteWrapper;

  sf::SoundBuffer fireSoundBuffer;
  fireSoundBuffer.loadFromFile("public/audio/shoot.wav");
  SoundWrapper *fireSoundWrapper = new SoundWrapper(fireSoundBuffer);
  SoundWrapper &rSoundWrapper = *fireSoundWrapper;

  LaserCannon cannon(rSpriteWrapper, laser, rSoundWrapper);
  return cannon;
}

std::vector<std::vector<IInvader *>> makeInvaders()
{
  sf::Texture squidTexture;
  squidTexture.loadFromFile("public/images/newSprites/squid.png");
  sf::Texture crabTexture;
  crabTexture.loadFromFile("public/images/newSprites/crab.png");
  sf::Texture octopusTexture;
  octopusTexture.loadFromFile("public/images/newSprites/octopus.png");
  std::vector<std::vector<IInvader *>> invaders(5);

  float xOffset = 282;
  float yOffset = 348;

  for (int i = 0; i < 5; i++)
  {
    std::vector<IInvader *> invaderRow(11);
    for (int j = 0; j < 11; j++)
    {
      if (i == 0)
      {
        SpriteWrapper *squidSpriteWrapper = new SpriteWrapper(squidTexture);
        SpriteWrapper &rSpriteWrapper = *squidSpriteWrapper;
        Squid *squid = new Squid(j * 90 + xOffset, i * 90 + yOffset, rSpriteWrapper);
        invaderRow[j] = squid;
      }
      else if (i < 3)
      {
        SpriteWrapper *crabSpriteWrapper = new SpriteWrapper(crabTexture);
        SpriteWrapper &rSpriteWrapper = *crabSpriteWrapper;
        Crab *crab = new Crab(j * 90 + xOffset, i * 90 + yOffset, rSpriteWrapper);
        invaderRow[j] = crab;
      }
      else
      {
        SpriteWrapper *octopusSpriteWrapper = new SpriteWrapper(octopusTexture);
        SpriteWrapper &rSpriteWrapper = *octopusSpriteWrapper;
        Octopus *octopus = new Octopus(j * 90 + xOffset, i * 90 + yOffset, rSpriteWrapper);
        invaderRow[j] = octopus;
      }
    }
    invaders[i] = invaderRow;
  }

  return invaders;
}
