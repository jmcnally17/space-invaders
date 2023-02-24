#include "../../../include/game.hpp"
#include "../../mockModels/mockRenderWindow.hpp"
#include "../../mockModels/mockLaserCannon.hpp"
#include "../../mockModels/mockLaser.hpp"
#include "../../mockModels/mockInvader.hpp"
#include "../../mockModels/mockText.hpp"

using ::testing::NiceMock;
using ::testing::Return;

TEST(drawObjects, callsClearOnTheWindow)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  std::vector<std::vector<IInvader *>> invaders;
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(window, clear())
      .Times(1);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, callsDrawOnTheLaserCannon)
{
  NiceMock<MockRenderWindow> window;
  MockLaserCannon cannon;
  NiceMock<MockLaser> laser;
  std::vector<std::vector<IInvader *>> invaders;
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(cannon, draw)
      .Times(1);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, callsDrawOnTheLaser)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  MockLaser laser;
  std::vector<std::vector<IInvader *>> invaders;
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(laser, draw)
      .Times(1);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, callsDrawOnAllTheInvadersIfTheyAreAlive)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  NiceMock<MockInvader> invader;
  MockInvader *pInvader = &invader;
  std::vector<std::vector<IInvader *>> invaders(5);
  for (int i = 0; i < 5; i++)
  {
    std::vector<IInvader *> invaderRow(11);
    for (int j = 0; j < 11; j++)
    {
      invaderRow[j] = pInvader;
    }
    invaders[i] = invaderRow;
  }
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  ON_CALL(invader, isAlive())
      .WillByDefault(Return(true));

  EXPECT_CALL(invader, draw)
      .Times(55);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, doesNotCallDrawOnAllTheInvadersIfTheyAreDead)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  NiceMock<MockInvader> invader;
  MockInvader *pInvader = &invader;
  std::vector<std::vector<IInvader *>> invaders(5);
  for (int i = 0; i < 5; i++)
  {
    std::vector<IInvader *> invaderRow(11);
    for (int j = 0; j < 11; j++)
    {
      invaderRow[j] = pInvader;
    }
    invaders[i] = invaderRow;
  }
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  ON_CALL(invader, isAlive())
      .WillByDefault(Return(false));

  EXPECT_CALL(invader, draw)
      .Times(0);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, drawsTheInvaderLasers)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  std::vector<std::vector<IInvader *>> invaders;
  MockLaser invaderLaser;
  MockLaser *pInvaderLaser = &invaderLaser;
  std::vector<ILaser *> invaderLasers(3);
  for (int i = 0; i < 3; i++)
  {
    invaderLasers[i] = pInvaderLaser;
  }
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(invaderLaser, draw)
      .Times(3);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, drawsTheScoreAndLivesText)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  std::vector<std::vector<IInvader *>> invaders;
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(window, draw(testing::Truly([](const sf::Drawable &drawable)
                                          { return true; })))
      .Times(2);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}

TEST(drawObjects, callsDisplayOnTheWindow)
{
  NiceMock<MockRenderWindow> window;
  NiceMock<MockLaserCannon> cannon;
  NiceMock<MockLaser> laser;
  std::vector<std::vector<IInvader *>> invaders;
  std::vector<ILaser *> invaderLasers;
  MockText scoreText;
  MockText livesText;

  EXPECT_CALL(window, display())
      .Times(1);
  drawObjects(window, cannon, laser, invaders, invaderLasers, scoreText, livesText);
}
