#ifndef JONAS_H
#define JONAS_H

#include "player.h"

namespace PXL2023 {
class Jonas : public Player  // Jonas is Player
{
 public:
  Jonas(unsigned char instance = 0) : Player(instance) {}
  const char* getName(void) const;

 protected:
  int willYouRaise(unsigned int totalBet);

 private:
  bool bluff();
  int betSafely(int amount);
  bool stopRaising = false;
  static int amountOfWin;
};
}  // namespace PXL2023
#endif  // JONAS_H
