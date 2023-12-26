#include "../../include/models/Metroid.hpp"
#include "../mockModels/MockMetroidLaser.hpp"
#include "../mockModels/MockRenderWindow.hpp"
#include "../mockModels/MockSound.hpp"
#include "../mockModels/MockSprite.hpp"

using ::testing::NiceMock;
using ::testing::Return;

class MetroidTest : public testing::Test
{
protected:
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite {&sprite};
  NiceMock<MockSound> deathSound;
  MockSound *pDeathSound {&deathSound};
  Metroid metroid {Metroid(300, 320, pSprite, 50, pDeathSound)};
  MockRenderWindow window;
  NiceMock<MockMetroidLaser> metroidLaser1;
  MockMetroidLaser *pMetroidLaser1 {&metroidLaser1};
  NiceMock<MockMetroidLaser> metroidLaser2;
  MockMetroidLaser *pMetroidLaser2 {&metroidLaser2};
  NiceMock<MockMetroidLaser> metroidLaser3;
  MockMetroidLaser *pMetroidLaser3 {&metroidLaser3};
  std::array<IMetroidLaser*, 3> metroidLasers {pMetroidLaser1, pMetroidLaser2, pMetroidLaser3};
  sf::FloatRect spriteBounds {sf::FloatRect(sf::Vector2f(200, 320), sf::Vector2f(66, 48))};
};

TEST_F(MetroidTest, setsDirectionUponInstantiation)
{
  EXPECT_EQ(metroid.getDirection(), 1);
}

TEST_F(MetroidTest, setsAliveUponInstantiation)
{
  EXPECT_TRUE(metroid.isAlive());
}

TEST_F(MetroidTest, setsJustMovedDownUponInstantiation)
{
  EXPECT_FALSE(metroid.hasJustMovedDown());
}

TEST_F(MetroidTest, drawCallsDrawOnSpriteWhenAlive)
{
  EXPECT_CALL(window, draw(testing::Truly([](const sf::Drawable &drawable)
                                          { return true; })))
    .Times(1);
  metroid.draw(window);
}

TEST_F(MetroidTest, dieChangesAliveToFalse)
{
  metroid.die();
  EXPECT_FALSE(metroid.isAlive());
}

TEST_F(MetroidTest, diePlaysDeathSound)
{
  EXPECT_CALL(deathSound, play())
    .Times(1);
  metroid.die();
}

TEST_F(MetroidTest, drawDoesNotCallDrawOnSpriteWhenNotAlive)
{
  metroid.die(); // set alive_ to false
  
  EXPECT_CALL(window, draw)
    .Times(0);
  metroid.draw(window);
}

TEST_F(MetroidTest, moveMovesSpriteToTheRightWhenDirectionIsOneAndNotAtSideBoundary)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));

  EXPECT_CALL(sprite, move(sf::Vector2f(14.1, 0)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveMovesSpriteToTheLeftWhenDirectionIsMinusOneAndNotAtSideBoundary)
{
  metroid.changeDirection(); // set direction_ to -1
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));

  EXPECT_CALL(sprite, move(sf::Vector2f(-14.1, 0)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveMovesSpriteToTheRightWhenAtLeftBoundaryAndJustMovedDownIsTrue)
{
  metroid.changeDirection(); // set direction_ to -1
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(18, 320)));
  metroid.move();            // call to move metroid down which sets justMovedDown_ to true and direction back to 1

  EXPECT_CALL(sprite, move(sf::Vector2f(14.1, 0)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveMovesSpriteToTheLeftWhenAtRightBoundaryAndJustMovedDownIsTrue)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(582, 320)));
  metroid.move(); // call to move metroid down which sets justMovedDown_ to true

  EXPECT_CALL(sprite, move(sf::Vector2f(-14.1, 0)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveSetsJustMovedDownToFalseWhenAtLeftBoundaryAndJustMovedDownIsTrue)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(18, 320)));
  metroid.move(); // call to move metroid down which sets justMovedDown_ to true

  metroid.move();
  EXPECT_FALSE(metroid.hasJustMovedDown());
}

TEST_F(MetroidTest, moveSetsJustMovedDownToFalseWhenAtRightBoundaryAndJustMovedDownIsTrue)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(582, 320)));
  metroid.move(); // call to move metroid down which sets justMovedDown_ to true

  metroid.move();
  EXPECT_FALSE(metroid.hasJustMovedDown());
}

TEST_F(MetroidTest, moveMovesSpriteDownWhenAtRightBoundaryAndJustMovedDownIsFalse)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(582, 320)));

  EXPECT_CALL(sprite, move(sf::Vector2f(0, 42)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveChangesDirectionWhenAtRightBoundaryAndJustMovedDownIsFalse)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(582, 320)));

  metroid.move();
  EXPECT_EQ(metroid.getDirection(), -1);
}

TEST_F(MetroidTest, moveSetsJustMovedDownToTrueWhenAtRightBoundaryAndJustMovedDownIsFalse)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(582, 320)));

  metroid.move();
  EXPECT_TRUE(metroid.hasJustMovedDown());
}

TEST_F(MetroidTest, moveMovesSpriteDownWhenAtLeftBoundaryAndJustMovedDownIsFalse)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(18, 320)));

  EXPECT_CALL(sprite, move(sf::Vector2f(0, 42)))
    .Times(1);
  metroid.move();
}

TEST_F(MetroidTest, moveChangesDirectionWhenAtLeftBoundaryAndJustMovedDownIsFalse)
{
  metroid.changeDirection(); // set direction_ to -1
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(18, 320)));

  metroid.move();
  EXPECT_EQ(metroid.getDirection(), 1);
}

TEST_F(MetroidTest, moveSetsJustMovedDownToTrueWhenAtLeftBoundaryAndJustMovedDownIsFalse)
{
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(18, 320)));

  metroid.move();
  EXPECT_TRUE(metroid.hasJustMovedDown());
}

TEST_F(MetroidTest, resurrectSetsAliveBackToTrue)
{
  metroid.die(); // set alive_ to false

  metroid.resurrect();
  EXPECT_TRUE(metroid.isAlive());
}

TEST_F(MetroidTest, resetSetsSpritePositionBackToOriginalPosition)
{
  EXPECT_CALL(sprite, setPosition(sf::Vector2f(300, 320)))
    .Times(1);
  metroid.reset();
}

TEST_F(MetroidTest, resetSetsAliveBackToTrue)
{
  metroid.die(); // set alive_ to false

  metroid.reset();
  EXPECT_TRUE(metroid.isAlive());
}

TEST_F(MetroidTest, resetSetsDirectionBackToOne)
{
  metroid.changeDirection(); // set direction to -1

  metroid.reset();
  EXPECT_EQ(metroid.getDirection(), 1);
}

TEST_F(MetroidTest, shootSetsPositionOfFirstMetroidLaserIfBelowBoard)
{
  ON_CALL(sprite, getGlobalBounds())
    .WillByDefault(Return(sf::FloatRect(sf::Vector2f(300, 320), sf::Vector2f(66, 48))));
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));
  ON_CALL(metroidLaser1, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));

  EXPECT_CALL(metroidLaser1, setPosition(sf::Vector2f(324, 368)))
    .Times(1);
  metroid.shoot(metroidLasers, 0);
}

TEST_F(MetroidTest, shootSetsPositionOfSecondMetroidLaserIfBelowBoardAndFirstMetroidLaserIsOnBoard)
{
  ON_CALL(sprite, getGlobalBounds())
    .WillByDefault(Return(sf::FloatRect(sf::Vector2f(300, 320), sf::Vector2f(66, 48))));
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));
  ON_CALL(metroidLaser1, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 900)));
  ON_CALL(metroidLaser2, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));

  EXPECT_CALL(metroidLaser2, setPosition(sf::Vector2f(324, 368)))
    .Times(1);
  metroid.shoot(metroidLasers, 0);
}

TEST_F(MetroidTest, shootSetsPositionOfThirdMetroidLaserIfBelowBoardAndFirstAndSecondMetroidLasersAreOnBoard)
{
  ON_CALL(sprite, getGlobalBounds())
    .WillByDefault(Return(sf::FloatRect(sf::Vector2f(300, 320), sf::Vector2f(66, 48))));
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));
  ON_CALL(metroidLaser1, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 900)));
  ON_CALL(metroidLaser2, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 600)));
  ON_CALL(metroidLaser3, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));

  EXPECT_CALL(metroidLaser3, setPosition(sf::Vector2f(324, 368)))
    .Times(1);
  metroid.shoot(metroidLasers, 0);
}

TEST_F(MetroidTest, shootDoesNotSetPositionOfAnyMetroidLaserIfTheyAreAllOnBoard)
{
  ON_CALL(sprite, getGlobalBounds())
    .WillByDefault(Return(sf::FloatRect(sf::Vector2f(300, 320), sf::Vector2f(66, 48))));
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));
  ON_CALL(metroidLaser1, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 900)));
  ON_CALL(metroidLaser2, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 600)));
  ON_CALL(metroidLaser3, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 300)));

  EXPECT_CALL(metroidLaser1, setPosition)
    .Times(0);
  EXPECT_CALL(metroidLaser2, setPosition)
    .Times(0);
  EXPECT_CALL(metroidLaser3, setPosition)
    .Times(0);
  metroid.shoot(metroidLasers, 0);
}

TEST_F(MetroidTest, shootDoesNotSetPositionOfAnyMetroidLaserIfRandomNumberIsNot0)
{
  ON_CALL(sprite, getGlobalBounds())
    .WillByDefault(Return(sf::FloatRect(sf::Vector2f(300, 320), sf::Vector2f(66, 48))));
  ON_CALL(sprite, getPosition())
    .WillByDefault(Return(sf::Vector2f(300, 320)));
  ON_CALL(metroidLaser1, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));
  ON_CALL(metroidLaser2, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));
  ON_CALL(metroidLaser3, getPosition())
    .WillByDefault(Return(sf::Vector2f(120, 1344)));

  EXPECT_CALL(metroidLaser1, setPosition)
    .Times(0);
  EXPECT_CALL(metroidLaser2, setPosition)
    .Times(0);
  EXPECT_CALL(metroidLaser3, setPosition)
    .Times(0);
  metroid.shoot(metroidLasers, 50);
}
