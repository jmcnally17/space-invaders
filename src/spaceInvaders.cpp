#include "../include/spaceInvaders.hpp"
#include "../include/game.hpp"
#include "../include/gameOver.hpp"
#include "../include/wrappers/renderWindowWrapper.hpp"
#include "../include/wrappers/spriteWrapper.hpp"
#include "../include/wrappers/soundWrapper.hpp"
#include "../include/wrappers/clockWrapper.hpp"
#include "../include/wrappers/textWrapper.hpp"
#include "../include/models/laser.hpp"
#include "../include/models/laserCannon.hpp"
#include "../include/models/squid.hpp"
#include "../include/models/crab.hpp"
#include "../include/models/octopus.hpp"
#include "../include/interfaces/collisionInterface.hpp"

int main()
{
  RenderWindowWrapper window(sf::VideoMode(1536, 1344), "Space Invaders");

  Laser laser = makeLaser();
  LaserCannon cannon = makeCannon(laser);
  std::vector<std::vector<IInvader *>> invaders = makeInvaders();

  ClockWrapper clock;
  int interval = 665;
  int step = 1;

  std::vector<ISound *> invaderSounds = makeInvaderSounds();
  int soundCounter = 0;

  Collision collisionInterface;

  int level = 1;
  int score = 0;

  sf::Font m56;
  m56.loadFromFile("public/fonts/MicroN56.ttf");
  TextWrapper scoreText = makeScoreText(m56);
  TextWrapper gameOverText = makeGameOverText(m56);
  TextWrapper playAgainText = makePlayAgainText(m56);

  bool isPlaying = true;
  bool gameOver = false;

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

    if (isPlaying)
    {
      drawObjects(window, cannon, laser, invaders, scoreText);
      evaluateLaserInvaderCollision(collisionInterface, laser, invaders, score, scoreText);
      if (invadersHaveInvaded(invaders))
      {
        endGame(isPlaying, gameOver);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        moveLaserCannon(cannon, 0.25);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        moveLaserCannon(cannon, -0.25);
      }
      moveLaser(laser);
      moveInvaders(invaders, clock, interval, step, invaderSounds, soundCounter);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        fireLaser(cannon);
      }
    }
    else if (gameOver)
    {
      displayGameOverScreen(window, gameOverText, playAgainText);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
      {
        playAgain(isPlaying, gameOver, cannon, laser, invaders, interval, step, soundCounter, level, score, clock);
      }
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

  sf::SoundBuffer deathBuffer;
  deathBuffer.loadFromFile("public/audio/invaderDeath.wav");
  SoundWrapper *deathSoundWrapper = new SoundWrapper(deathBuffer);
  SoundWrapper &rSoundWrapper = *deathSoundWrapper;

  Laser laser(rSpriteWrapper, rSoundWrapper);
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
  float extraSquidXOffset = 12;

  for (int i = 0; i < 5; i++)
  {
    std::vector<IInvader *> invaderRow(11);
    for (int j = 0; j < 11; j++)
    {
      if (i == 0)
      {
        SpriteWrapper *squidSpriteWrapper = new SpriteWrapper(squidTexture);
        SpriteWrapper &rSpriteWrapper = *squidSpriteWrapper;
        Squid *squid = new Squid(j * 90 + xOffset + extraSquidXOffset, i * 90 + yOffset, rSpriteWrapper);
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

std::vector<ISound *> makeInvaderSounds()
{
  sf::SoundBuffer sound0Buffer;
  sound0Buffer.loadFromFile("public/audio/invader0.wav");
  SoundWrapper *sound0Wrapper = new SoundWrapper(sound0Buffer);

  sf::SoundBuffer sound1Buffer;
  sound1Buffer.loadFromFile("public/audio/invader1.wav");
  SoundWrapper *sound1Wrapper = new SoundWrapper(sound1Buffer);

  sf::SoundBuffer sound2Buffer;
  sound2Buffer.loadFromFile("public/audio/invader2.wav");
  SoundWrapper *sound2Wrapper = new SoundWrapper(sound2Buffer);

  sf::SoundBuffer sound3Buffer;
  sound3Buffer.loadFromFile("public/audio/invader3.wav");
  SoundWrapper *sound3Wrapper = new SoundWrapper(sound3Buffer);

  std::vector<ISound *> invaderSounds = {sound0Wrapper, sound1Wrapper, sound2Wrapper, sound3Wrapper};
  return invaderSounds;
}

TextWrapper makeScoreText(const sf::Font &font)
{
  std::string scoreString = "Score: 0";
  TextWrapper scoreText(scoreString, font);
  scoreText.setPosition(sf::Vector2f(20, 0));
  scoreText.setCharacterSize(50);
  return scoreText;
}

TextWrapper makeGameOverText(const sf::Font &font)
{
  std::string gameOverString = "Game Over";
  TextWrapper gameOverText(gameOverString, font);
  gameOverText.setPosition(sf::Vector2f(192, 200));
  gameOverText.setCharacterSize(153);
  return gameOverText;
}

TextWrapper makePlayAgainText(const sf::Font &font)
{
  std::string playAgainString = "Press p to play again";
  TextWrapper playAgainText(playAgainString, font);
  playAgainText.setPosition(sf::Vector2f(384, 1000));
  playAgainText.setCharacterSize(48);
  return playAgainText;
}
