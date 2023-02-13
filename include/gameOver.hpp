#ifndef END_GAME_HPP
#define END_GAME_HPP

#include "./wrappers/iRenderWindow.hpp"
#include "./wrappers/iText.hpp"
#include "./models/iLaserCannon.hpp"
#include "./models/iLaser.hpp"

void displayGameOverScreen(IRenderWindow &window, IText &gameOverText, IText &playAgainText);

void playAgain(bool &isPlaying, bool &gameOver, ILaserCannon &cannon, ILaser &laser);

#endif
