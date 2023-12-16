#include "../../../include/interfaces/collisionInterface.hpp"
#include "../../../include/models/iLaser.hpp"
#include "../../../include/models/iMetroid.hpp"
#include "../../../include/models/iRidley.hpp"
#include "../../../include/models/iBunker.hpp"
#include "../../../include/models/iGunship.hpp"
#include "../../../include/wrappers/iText.hpp"

void evaluateGunshipLaserMetroidCollision(const CollisionInterface &collision,
                                          ILaser &gunshipLaser,
                                          const std::array<std::array<IMetroid*, 11>, 5> &metroids,
                                          std::unordered_map<std::string, int> &variables,
                                          IText &scoreText,
                                          IText &highScoreText)
{
  for (auto row : metroids)
  {
    for (auto metroid : row)
    {
      if (metroid->isAlive() && collision.haveCollided(gunshipLaser, *metroid))
      {
        metroid->die();
        variables["score"] += metroid->getPoints();
        scoreText.setString("Score: " + std::to_string(variables["score"]));
        if (variables["score"] > variables["highScore"])
        {
          highScoreText.setString("High Score: " + std::to_string(variables["score"]));
        }
        gunshipLaser.playMetroidDeath();
        gunshipLaser.reset();
        return;
      }
    }
  }
}

void evaluateGunshipLaserRidleyCollision(const CollisionInterface &collision,
                                         ILaser &gunshipLaser,
                                         IRidley &ridley,
                                         std::unordered_map<std::string, int> &variables,
                                         IText &scoreText,
                                         IText &highScoreText)
{
  if (collision.haveCollided(gunshipLaser, ridley))
  {
    ridley.die();
    variables["score"] += ridley.getPoints();
    scoreText.setString("Score: " + std::to_string(variables["score"]));
    if (variables["score"] > variables["highScore"])
    {
      highScoreText.setString("High Score: " + std::to_string(variables["score"]));
    }
    gunshipLaser.reset();
  }
}

void evaluateGunshipLaserBunkerCollision(const CollisionInterface &collision, ILaser &gunshipLaser, std::array<IBunker*, 4> &bunkers)
{
  for (auto bunker : bunkers)
  {
    if (bunker->getHealth() > 0 && collision.haveCollided(gunshipLaser, *bunker))
    {
      bunker->decreaseHealth();
      gunshipLaser.reset();
      return;
    }
  }
}

void evaluateMetroidLaserBunkerCollision(const CollisionInterface &collision, const std::array<ILaser*, 3> &metroidLasers, std::array<IBunker*, 4> &bunkers)
{
  for (auto metroidLaser : metroidLasers)
  {
    int count = 0;
    while (count < 4)
    {
      IBunker *bunker = bunkers[count];
      if (bunker->getHealth() > 0 && collision.haveCollided(*metroidLaser, *bunker))
      {
        bunker->decreaseHealth();
        metroidLaser->reset();
        count = 4;
      }
      else
      {
        count++;
      }
    }
  }
}

void evaluateGunshipMetroidLaserCollision(const CollisionInterface &collision,
                                          IGunship &gunship,
                                          const std::array<ILaser*, 3> &metroidLasers,
                                          ILaser &gunshipLaser,
                                          IText &livesText)
{
  for (auto metroidLaser : metroidLasers)
  {
    if (collision.haveCollided(gunship, *metroidLaser))
    {
      gunship.loseLife();
      gunship.resetPosition();
      gunshipLaser.reset();
      for (auto metroidLaser : metroidLasers)
      {
        metroidLaser->reset();
      }
      livesText.setString("Lives: " + std::to_string(gunship.getLives()));
      return;
    }
  }
}
