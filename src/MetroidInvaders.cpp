#include "../include/MetroidInvaders.hpp"
#include "../include/Factory.hpp"
#include "../include/Title.hpp"
#include "../include/Game.hpp"
#include "../include/GameOver.hpp"
#include "../include/adaptors/RenderWindowAdaptor.hpp"
#include "../include/adaptors/ClockAdaptor.hpp"
#include "../include/interfaces/collisionInterface.hpp"

int main()
{
  // set up the game window
  RenderWindowAdaptor window(sf::VideoMode(1536, 1344), "Metroid Invaders");
  
  ClockAdaptor frameClock;
  
  // backgrounds
  std::unordered_map<std::string, ISprite*> backgrounds {Factory::makeBackgrounds()};
  
  // text objects
  std::unordered_map<std::string, IText*> textObjects {Factory::makeTextObjects()};
  
  // audio objects
  std::unordered_map<std::string, ISound*> themes {Factory::makeThemes()};
  
  // game objects
  std::array<IBunker*, 4> bunkers {Factory::makeBunkers()};
  GunshipLaser gunshipLaser {Factory::makeGunshipLaser()};
  Gunship gunship {Factory::makeGunship(gunshipLaser)};
  std::array<std::array<IMetroid*, 11>, 5> metroids {Factory::makeMetroids()};
  std::array<IMetroidLaser*, 3> metroidLasers {Factory::makeMetroidLasers()};
  Ridley ridley {Factory::makeRidley()};
  std::array<ISound*, 4> metroidSounds {Factory::makeMetroidSounds()};
  std::array<sf::RectangleShape, 2> rectangles {Factory::makeRectangles()};
  ClockAdaptor movementClock;
  Collision collisionInterface;
  
  // game variables
  std::unordered_map<std::string, int> variables {
    {"soundCounter", 0},
    {"interval", 665},
    {"step", 1},
    {"level", 1},
    {"score", 0},
    {"highScore", 0},
  };

  // final setup
  bool isPlaying {false};
  bool gameOver {false};
  pullHighScore(variables, *textObjects["highScore"]);
  themes["title"]->play();

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
      else if (event.type == sf::Event::Resized)
      {
        adjustView(window, event.size.width, event.size.height);
      }
    }

    if (frameClock.getElapsedTime().asMicroseconds() >= 6250)
    {
      if (isPlaying)
      {
        drawObjects(window, *backgrounds["game"], bunkers, gunship, gunshipLaser, metroids, metroidLasers, ridley, *textObjects["score"], *textObjects["highScore"], *textObjects["lives"], rectangles);
        monitorRidleyMovementSound(ridley);
        if (areMetroidsDead(metroids))
        {
          levelUp(variables, metroids, metroidLasers, ridley, movementClock);
        }
        evaluateGunshipLaserMetroidCollision(collisionInterface, gunshipLaser, metroids, variables, *textObjects["score"], *textObjects["highScore"]);
        evaluateGunshipLaserRidleyCollision(collisionInterface, gunshipLaser, ridley, variables, *textObjects["score"], *textObjects["highScore"]);
        evaluateGunshipLaserBunkerCollision(collisionInterface, gunshipLaser, bunkers);
        evaluateMetroidLaserBunkerCollision(collisionInterface, metroidLasers, bunkers);
        evaluateGunshipMetroidLaserCollision(collisionInterface, gunship, metroidLasers, gunshipLaser, *textObjects["lives"]);
        if (haveMetroidsInvaded(metroids) || gunship.getLives() == 0)
        {
          endGame(isPlaying, gameOver, ridley, *themes["battle"], *themes["credits"]);
          updateHighScore(variables, *textObjects["score"], *textObjects["highScore"]);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
          moveGunship(gunship, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
          moveGunship(gunship, -1);
        }
        moveGunshipLaser(gunshipLaser);
        moveMetroids(metroids, movementClock, variables, metroidSounds);
        moveMetroidLasers(metroidLasers);
        moveRidley(ridley);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
          fireGunshipLaser(gunship);
        }
        shootMetroidLaser(metroids, metroidLasers);
        spawnRidley(ridley);
      }
      else if (gameOver)
      {
        displayGameOverScreen(window, *textObjects["gameOver"], *textObjects["score"], *textObjects["playAgain"]);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
          resetObjects(gunship, gunshipLaser, metroids, metroidLasers, ridley, bunkers);
          resetValues(isPlaying, gameOver, variables);
          resetInformationObjects(*textObjects["score"], *textObjects["lives"], *themes["credits"], *themes["battle"], movementClock);
        }
      }
      else
      {
        displayTitleScreen(window, *backgrounds["title"], *textObjects["title"], *textObjects["instructions"]);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
          play(isPlaying, *themes["title"], *themes["battle"], movementClock);
        }
      }
      frameClock.restart();
    }
  }

  return 0;
}
