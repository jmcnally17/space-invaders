#include <vector>
#include "../../../include/models/iLaserCannon.hpp"
#include "../../../include/models/iLaser.hpp"
#include "../../../include/models/iInvader.hpp"

void playAgain(bool &isPlaying, bool &gameOver, ILaserCannon &cannon, ILaser &laser, const std::vector<std::vector<IInvader *>> &invaders)
{
  isPlaying = true;
  gameOver = false;
  cannon.reset();
  laser.reset();
  for (auto invaderRow : invaders)
  {
    for (auto invader : invaderRow)
    {
      invader->reset();
    }
  }
}
