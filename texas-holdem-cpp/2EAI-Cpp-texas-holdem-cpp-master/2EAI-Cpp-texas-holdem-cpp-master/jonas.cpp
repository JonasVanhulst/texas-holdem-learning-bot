#include "jonas.h"

#include "game.h"

namespace PXL2023 {

const char* Jonas::getName() const { return "JonasVHTPOWER"; }

int Jonas::willYouRaise(unsigned int totalBet) {
  int i = 0;
  int maxBet[30];
  for (Player* player : getGame()->getPlayers()) {
    if (maxBet[i] <= player->getBet()) maxBet[i] = player->getBet();
  }
  if (getRank().getCategory() >= FULL_HOUSE) {
    return getChips();
  }

  PokerRank mijnHandRank = getRank();
  if (getTable()->isPreFlop())  // Pre flop
  {
    if (getHand().getFirstCard()->getSuit() ==
        getHand().getSecondCard()->getSuit()) {  // suited hands
      int diffBetweenOrderedCards =
          mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
      if (diffBetweenOrderedCards == 1 ||
          diffBetweenOrderedCards == 13) {  // suited connected
        return (getGame()->getBlind() * 10) -
               totalBet;  // max 7x blind and fold otherwise
      }
      return (getGame()->getBlind() * 8) -
             totalBet;  // max 3x blind and fold otherwise
    }
    if (getHand().getFirstCard()->getRank() ==
        getHand().getSecondCard()->getRank()) {  // 1 pair to start
      return (getGame()->getBlind() * 5) -
             totalBet;  // max 5x blind and fold otherwise
    }
    int diffBetweenOrderedCards =
        mijnHandRank.getHand().at(0) - mijnHandRank.getHand().at(1);
    if (diffBetweenOrderedCards == 1 ||
        diffBetweenOrderedCards == 13) {  // unsuited connected
      return (getGame()->getBlind() * 6) -
             totalBet;  // max 3x blind and fold otherwise
    }
    if (totalBet > getGame()->getBlind() * 2) {
      return -1;
    }
    return 0;
  } else if (getTable()->isFlop()) {  // on flop
    return 0;
  } else if (getTable()->isTurn()) {  // on turn
    return 0;
  } else {  // on river
    return 0;
  }
}

// voorbeeld instance dus => return((rand()%1+100*instance*instance)) == 0);

}  // namespace PXL2023
