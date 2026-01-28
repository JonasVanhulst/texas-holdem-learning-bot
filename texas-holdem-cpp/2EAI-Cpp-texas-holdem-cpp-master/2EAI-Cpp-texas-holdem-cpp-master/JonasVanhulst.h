#ifndef JONASVANHULST_H
#define JONASVANHULST_H

#include "player.h"

namespace PXL2023 {
class JonasVanhulst : public Player {
 public:
  JonasVanhulst(unsigned char instance = 0) : Player(instance) {}
  const char* getName(void) const;
  int willYouRaise(unsigned int totalBet);

 private:
  int myBet(unsigned char instance);
  bool checkInitialHandForPockets();
  int checkDealerDistance();
};
}  // namespace PXL2023

#endif  // JONASVANHULST_H
