#include <JonasVanhulst.h>
#include <game.h>

namespace PXL2023 {

const char* JonasVanhulst::getName() const { return "SecretsOfThePeakyJonas"; }

int JonasVanhulst::myBet(unsigned char instance) {
  srand(time(NULL));

  switch (instance) {
    case 1:
      return rand() % 20 + 1 + instance;
      break;
    case 2:
      return rand() % 23 + 5 * instance;
      break;
    default:
      return rand() % 40 + 1;
      break;
  }
}

bool JonasVanhulst::checkInitialHandForPockets() {
  Card::RANK firstCardValue = getHand().getFirstCard()->getRank();
  Card::RANK secondCardValue = getHand().getSecondCard()->getRank();

  for (int i = 1; i <= 14; i++) {
    // Pockets
    if (firstCardValue == i && secondCardValue == i) return true;
  }
  // AK or KA
  if ((firstCardValue == 14 || firstCardValue == 13) &&
      (secondCardValue == 13 || secondCardValue == 14))
    return true;
  // AQ or QA
  else if ((firstCardValue == 14 || firstCardValue == 12) &&
           (secondCardValue == 12 || secondCardValue == 14))
    return true;
  // AJ or JA
  else if ((firstCardValue == 14 || firstCardValue == 11) &&
           (secondCardValue == 11 || secondCardValue == 14))
    return true;
  // AT or TA
  else if ((firstCardValue == 14 || firstCardValue == 10) &&
           (secondCardValue == 10 || secondCardValue == 14))
    return true;
  // KQ or QK
  else if ((firstCardValue == 13 || firstCardValue == 12) &&
           (secondCardValue == 12 || secondCardValue == 13))
    return true;
  // KJ or JK
  else if ((firstCardValue == 13 || firstCardValue == 11) &&
           (secondCardValue == 11 || secondCardValue == 13))
    return true;
  // QJ or JQ
  else if ((firstCardValue == 12 || firstCardValue == 11) &&
           (secondCardValue == 11 || secondCardValue == 12))
    return true;
  // QJ or JQ
  else if ((firstCardValue == 11 || firstCardValue == 10) &&
           (secondCardValue == 10 || secondCardValue == 11))
    return true;

  // No Valid Combinations -> fold
  else
    return false;
}

int JonasVanhulst::checkDealerDistance() {
  if (getGame()->getDistanceToDealer(this) == 1)
    return (200 * instance + getGame()->getBlind());
  else
    return 200;
}

int JonasVanhulst::willYouRaise(unsigned int totalBet) {
  int maxBetEver[MAX_PLAYER_ID];
  int getAmountOfPlayers = getGame()->getAmountHands();

  PokerRank myHandRank = getRank();

  if (getTable()->isPreFlop()) {
    if (checkInitialHandForPockets() == true) {
      return (300 - totalBet);
    } else {
      for (int i = 0; i < getGame()->getPlayers().size(); i++) {
        if ((getID() != PXL_2023_JONAS) && hasHand()) {
          return (maxBetEver[getID()] = totalBet + 1);
        }
      }
    }
  }

  if (getGame()->getPlays() > 10 && getTable()->isFlop()) {
    if (myHandRank.getCategory() >= FULL_HOUSE ||
        myHandRank.getCategory() >= FOUR_OF_A_KIND) {
      return (100 - totalBet);
    }
  }

  if (getGame()->getPlays() > 10 && getTable()->isTurn()) {
    if (myHandRank.getCategory() >= THREE_OF_A_KIND ||
        myHandRank.getCategory() >= TWO_PAIR) {
      return getChips();
    }
  }

  switch (instance) {
    case 0:
      if (getGame()->getPlays() < 60 && getTable()->isRiver()) {
        if ((myHandRank.getCategory() >= STRAIGHT_FLUSH ||
             myHandRank.getCategory() >= FLUSH) &&
            getAmountOfPlayers <= 3) {
          if (getGame()->getHighestBet() >= 400) {
            return (getGame()->getHighestBet() + checkDealerDistance());
          } else
            return getGame()->getHighestBet();
        }
      }
      break;

    case 1:
      if (getGame()->getPlays() > 10 && getTable()->isRiver()) {
        if ((myHandRank.getCategory() >= STRAIGHT_FLUSH ||
             myHandRank.getCategory() >= FLUSH) &&
            getAmountOfPlayers <= 4) {
          if (getGame()->getHighestBet() > 300) {
            return (getGame()->getHighestBet() + checkDealerDistance());
          } else if (totalBet > getGame()->getBlind() * 5) {
            return getChips();
          } else
            return myBet(instance);
        }
      }
      break;

    case 2:
      if (getGame()->getPlays() > 10 && getTable()->isRiver()) {
        if ((myHandRank.getCategory() >= STRAIGHT_FLUSH ||
             myHandRank.getCategory() >= FLUSH) &&
            getAmountOfPlayers <= 3) {
          if (getGame()->getHighestBet() > 300) {
            return myBet(instance);
          } else
            return getGame()->getHighestBet() + 1;
        }
      }
      break;
    default:
      break;
  }

  return 0;
}

}  // namespace PXL2023
