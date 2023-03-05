#include "../../include/models/ridley.hpp"
#include "../mockModels/mockSprite.hpp"
#include "../mockModels/mockSound.hpp"
#include "../mockModels/mockRenderWindow.hpp"

using ::testing::NiceMock;
using ::testing::Return;

TEST(Ridley, hasAWidthClassMemberOf96)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_EQ(ridley.getWidth(), 96);
}

TEST(Ridley, hasAHeightClassMemberOf42)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_EQ(ridley.getHeight(), 42);
}

TEST(Ridley, setsItsOwnPositionMember)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-96, 200));
}

TEST(Ridley, setsPositionOnSpriteClassMember)
{
  MockSprite sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;

  EXPECT_CALL(sprite, setPosition(sf::Vector2f(-96, 200)))
      .Times(1);
  Ridley ridley(pSprite, pMovementSound, deathSound);
}

TEST(Ridley, hasAPointsMemberOf150)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_EQ(ridley.getPoints(), 150);
}

TEST(Ridley, hasADirectionMemberInitiallySetToMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_EQ(ridley.getDirection(), -1);
}

TEST(Ridley, setsLoopOnMovementSoundToTrue)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  MockSound movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;

  EXPECT_CALL(movementSound, setLoop(true))
      .Times(1);
  Ridley ridley(pSprite, pMovementSound, deathSound);
}

TEST(Ridley, setPositionChangesPosition)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 920));
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(500, 920));
}

TEST(Ridley, setPositionUpdatesSpritePosition)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_CALL(sprite, setPosition(sf::Vector2f(500, 920)));
  ridley.setPosition(sf::Vector2f(500, 920));
}

TEST(Ridley, drawCallsDrawOnTheSpriteClassMemberWhenOnTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);
  MockRenderWindow window;

  ridley.setPosition(sf::Vector2f(500, 200));

  EXPECT_CALL(window, draw(testing::Truly([](const sf::Drawable &drawable)
                                          { return true; })))
      .Times(1);
  ridley.draw(window);
}

TEST(Ridley, drawDoesNotCallDrawOnTheSpriteClassMemberWhenLeftOfTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);
  MockRenderWindow window;

  EXPECT_CALL(window, draw)
      .Times(0);
  ridley.draw(window);
}

TEST(Ridley, drawDoesNotCallDrawOnTheSpriteClassMemberWhenRightOfTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);
  MockRenderWindow window;

  ridley.setPosition(sf::Vector2f(1536, 200));

  EXPECT_CALL(window, draw)
      .Times(0);
  ridley.draw(window);
}

TEST(Ridley, changeDirectionSwitchesDirectionTo1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.changeDirection();
  EXPECT_EQ(ridley.getDirection(), 1);
}

TEST(Ridley, changeDirectionSwitchesDirectionBackToMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.changeDirection(); // Set direction to 1

  ridley.changeDirection();
  EXPECT_EQ(ridley.getDirection(), -1);
}

TEST(Ridley, resetSetsPositionBackToOriginalPosition)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(900, 1100));

  ridley.reset();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-96, 200));
}

TEST(Ridley, resetSetsSpritePositionBackToOriginalPosition)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(900, 1100));

  EXPECT_CALL(sprite, setPosition(sf::Vector2f(-96, 200)))
      .Times(1);
  ridley.reset();
}

TEST(Ridley, resetSetsDirectionBackToMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.changeDirection(); // Set direction to 1

  ridley.reset();
  EXPECT_EQ(ridley.getDirection(), -1);
}

TEST(Ridley, moveAdds0Point125ToXPositionWhenDirectionIs1AndIsOnTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 200)); // Put Ridley on the board
  ridley.changeDirection();                   // Set direction to 1

  ridley.move();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(500.125, 200));
}

TEST(Ridley, moveTakesAway0Point125ToXPositionWhenDirectionIsMinus1AndIsOnTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 200)); // Put Ridley on the board

  ridley.move();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(499.875, 200));
}

TEST(Ridley, moveDoesNotChangePositionWhenRidleyIsLeftOfTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.move();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-96, 200));
}

TEST(Ridley, moveDoesNotChangePositionWhenRidleyIsRightOfTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(1536, 200)); // Put Ridley off the window to the right

  ridley.move();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(1536, 200));
}

TEST(Ridley, moveUpdatesSpritePositionWhenOnTheBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 200)); // Put Ridley on the board

  EXPECT_CALL(sprite, setPosition(sf::Vector2f(499.875, 200)))
      .Times(1);
  ridley.move();
}

TEST(Ridley, spawnChangesDirectionTo1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.spawn(0);
  EXPECT_EQ(ridley.getDirection(), 1);
}

TEST(Ridley, spawnChangesDirectionToMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.changeDirection(); // Set direction to 1

  ridley.spawn(0);
  EXPECT_EQ(ridley.getDirection(), -1);
}

TEST(Ridley, spawnSetsSpriteScaleWithXOf1WhenDirectionStartsAtMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_CALL(sprite, setScale(1, 1));
  ridley.spawn(0);
}

TEST(Ridley, spawnAdds0Point125ToXPositionWhenRidleyIsLeftOfBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.spawn(0);
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-95.875, 200));
}

TEST(Ridley, spawnTakesAway0Point125FromXPositionWhenRidleyIsRightOfBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(1536, 200)); // Put Ridley off the window to the right
  ridley.changeDirection();                    // Set direction to 1

  ridley.spawn(0);
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(1535.875, 200));
}

TEST(Ridley, spawnPlaysTheMovementSound)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_CALL(movementSound, play())
      .Times(1);
  ridley.spawn(0);
}

TEST(Ridley, spawnDoesNotSpawnRidleyWhenNotAtLeftOrRightEdgeOfBoard)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 200));

  EXPECT_CALL(movementSound, play())
      .Times(0);
  ridley.spawn(0);
  EXPECT_EQ(ridley.getDirection(), -1);
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(500, 200));
}

TEST(Ridley, spawnDoesNotSpawnRidleyWhenRandomNumberIsNot0)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  EXPECT_CALL(movementSound, play())
      .Times(0);
  ridley.spawn(50);
  EXPECT_EQ(ridley.getDirection(), -1);
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-96, 200));
}

TEST(Ridley, stopMovementSoundIfPlayingStopsMovementSoundIfItIsPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Playing));

  EXPECT_CALL(movementSound, stop())
      .Times(1);
  ridley.stopMovementSoundIfPlaying();
}

TEST(Ridley, stopMovementSoundIfPlayingDoesNotStopMovementSoundIfItIsNotPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Stopped));

  EXPECT_CALL(movementSound, stop())
      .Times(0);
  ridley.stopMovementSoundIfPlaying();
}

TEST(Ridley, stopMovementSoundIfAtSideOfWindowStopsMovementSoundIfAtLeftSideAndPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Playing));

  EXPECT_CALL(movementSound, stop())
      .Times(1);
  ridley.stopMovementSoundIfAtSideOfWindow();
}

TEST(Ridley, stopMovementSoundIfAtSideOfWindowStopsMovementSoundIfAtRightSideAndPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(1536, 200));
  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Playing));

  EXPECT_CALL(movementSound, stop())
      .Times(1);
  ridley.stopMovementSoundIfAtSideOfWindow();
}

TEST(Ridley, stopMovementSoundIfAtSideOfWindowDoesNotStopMovementSoundIfInTheWindowAndPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ridley.setPosition(sf::Vector2f(500, 200));
  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Playing));

  EXPECT_CALL(movementSound, stop())
      .Times(0);
  ridley.stopMovementSoundIfAtSideOfWindow();
}

TEST(Ridley, stopMovementSoundIfAtSideOfWindowDoesNotStopMovementSoundIfNotPlaying)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound *deathSound;
  Ridley ridley(pSprite, pMovementSound, deathSound);

  ON_CALL(movementSound, getStatus())
      .WillByDefault(Return(sf::Sound::Stopped));

  EXPECT_CALL(movementSound, stop())
      .Times(0);
  ridley.stopMovementSoundIfAtSideOfWindow();
}

TEST(Ridley, dieSetsPositionToRightOfWindowWhenDirectionIs1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  NiceMock<MockSound> deathSound;
  MockSound *pDeathSound = &deathSound;
  Ridley ridley(pSprite, pMovementSound, pDeathSound);

  ridley.setPosition(sf::Vector2f(500, 200));
  ridley.changeDirection(); // Set direction to 1

  ridley.die();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(1536, 200));
}

TEST(Ridley, dieSetsPositionToLeftOfWindowWhenDirectionIsMinus1)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  NiceMock<MockSound> deathSound;
  MockSound *pDeathSound = &deathSound;
  Ridley ridley(pSprite, pMovementSound, pDeathSound);

  ridley.setPosition(sf::Vector2f(500, 200));

  ridley.die();
  EXPECT_EQ(ridley.getPosition(), sf::Vector2f(-96, 200));
}

TEST(Ridley, dieUpdatesTheSpritePosition)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  NiceMock<MockSound> deathSound;
  MockSound *pDeathSound = &deathSound;
  Ridley ridley(pSprite, pMovementSound, pDeathSound);

  ridley.setPosition(sf::Vector2f(500, 200));

  EXPECT_CALL(sprite, setPosition(sf::Vector2f(-96, 200)))
      .Times(1);
  ridley.die();
}

TEST(Ridley, dieStopsTheMovementSound)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  NiceMock<MockSound> deathSound;
  MockSound *pDeathSound = &deathSound;
  Ridley ridley(pSprite, pMovementSound, pDeathSound);

  EXPECT_CALL(movementSound, stop())
      .Times(1);
  ridley.die();
}

TEST(Ridley, diePlaysTheDeathSound)
{
  NiceMock<MockSprite> sprite;
  MockSprite *pSprite = &sprite;
  NiceMock<MockSound> movementSound;
  MockSound *pMovementSound = &movementSound;
  MockSound deathSound;
  MockSound *pDeathSound = &deathSound;
  Ridley ridley(pSprite, pMovementSound, pDeathSound);

  EXPECT_CALL(deathSound, play())
      .Times(1);
  ridley.die();
}
