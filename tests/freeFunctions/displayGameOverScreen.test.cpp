#include "../../include/spaceInvaders.hpp"
#include "../mockModels/mockRenderWindow.hpp"
#include "../mockModels/mockText.hpp"

using ::testing::NiceMock;

TEST(displayGameOverScreen, callsClearOnTheWindow)
{
  NiceMock<MockRenderWindow> window;
  MockText gameOverText;

  EXPECT_CALL(window, clear())
      .Times(1);
  displayGameOverScreen(window, gameOverText);
}

TEST(displayGameOverScreen, drawsTheGameOverText)
{
  NiceMock<MockRenderWindow> window;
  MockText gameOverText;

  EXPECT_CALL(window, draw(testing::Truly([](const sf::Drawable &drawable)
                                          { return true; })))
      .Times(1);
  displayGameOverScreen(window, gameOverText);
}

TEST(displayGameOverScreen, callsDisplayOnTheWindow)
{
  NiceMock<MockRenderWindow> window;
  MockText gameOverText;

  EXPECT_CALL(window, display())
      .Times(1);
  displayGameOverScreen(window, gameOverText);
}
