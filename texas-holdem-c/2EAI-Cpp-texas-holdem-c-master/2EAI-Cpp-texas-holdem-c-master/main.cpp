#include <string.h>

#include <iostream>
#define DEBUG_PRINT
#include "texasholdem.h"

enum spelerIDs {
  IK,
  JIJ,
  Jonas,
  ZIJ,
  STUDENT_2022,
  STUDENT_2023,
  MAX_PLAYER_ID
};

bool init = false;
int maxBetEver[MAX_PLAYER_ID];

bool checkInitialHandForPockets(struct Hand* hand) {
  RANK firstCardValue = hand->cards[0]->rank;
  RANK secondCardValue = hand->cards[1]->rank;

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

int willYouRaise(struct Game* game, struct Player* player,
                 unsigned int totalBet) {
  if (!init) {
    init = true;
    for (int i = 0; i < MAX_PLAYER_ID; i++) {
      maxBetEver[i] = 0;
    }
  }
  switch (player->ID) {
    case IK: {
      if (getMyHandRank(player->hand).category == STRAIGHT_FLUSH) {
        return 10000;
      }
      if (game->plays > 10 && table[4] != nullptr)  // Play on river
      {
        PokerRank mijnHandRank = getMyHandRank(player->hand);
        PokerRank tafelRank = getMyHandRank(nullptr);
        if (mijnHandRank.category >= TWO_PAIR &&
            mijnHandRank.category > tafelRank.category) {
          return (20 - totalBet);
        }
      }
      if (totalBet > game->blind * 5) {
        return (-1);
      }
      return (0);
      break;
    }
    case JIJ:
      for (int i = 0; i < game->playersSize; i++) {
        if (game->players[i]->bet > maxBetEver[game->players[i]->ID]) {
          maxBetEver[game->players[i]->ID] = game->players[i]->bet;
        }
      }
      if (game->amountHands > 2) {
        return (-1);
      }
      for (int i = 0; i < game->playersSize; i++) {
        if (game->players[i]->ID != JIJ &&
            isHandFilled(game->players[i]->hand)) {
          return (maxBetEver[game->players[i]->ID] - totalBet + 1);
        }
      }
      return (-1);
      break;
    case Jonas: {
      PokerRank mijnHandRank = getMyHandRank(player->hand);
      PokerRank tafelRank = getMyHandRank(nullptr);

      if (table[0] != nullptr) {
        if (checkInitialHandForPockets(player->hand) == true) {
          return (300 - totalBet);
        } else {
          for (int i = 0; i < game->playersSize; i++) {
            if (game->players[i]->ID != Jonas &&
                isHandFilled(game->players[i]->hand)) {
              return (maxBetEver[game->players[i]->ID] - totalBet + 1);
            }
          }
        }
      }

      if (game->plays > 10 &&
          table[2] !=
              nullptr)  // Play to bluff (knowing when i have some bad cards)
      {
        if ((mijnHandRank.category >= TWO_PAIR &&
                 mijnHandRank.category > tafelRank.category ||
             mijnHandRank.category >= ONE_PAIR &&
                 mijnHandRank.category > tafelRank.category)) {
          return (30 - totalBet);  //(put bluff coins)
        }
      }
      if (game->plays > 10 && table[3] != nullptr)  // Play on flop
      {
        if ((mijnHandRank.category >= FULL_HOUSE &&
             mijnHandRank.category > tafelRank.category) ||
            (mijnHandRank.category >= FOUR_OF_A_KIND &&
             mijnHandRank.category > tafelRank.category)) {
          return (100 - totalBet);  // playing to win because chances with full
                                    // house on flop is high winrate
        }
      }
      if (game->plays > 10 && table[4] != nullptr)  // Play on river
      {
        if (mijnHandRank.category >= FLUSH &&
                mijnHandRank.category > tafelRank.category ||
            (mijnHandRank.category >= STRAIGHT_FLUSH &&
             mijnHandRank.category > tafelRank.category)) {
          if (totalBet >= 400) {
            return (350 - totalBet);
          } else {
            return (150 - totalBet);
          }
        } else if (mijnHandRank.category >= THREE_OF_A_KIND &&
                   mijnHandRank.category > tafelRank.category) {
          return (100000);
        }
      }
      if (totalBet > game->blind * 5) {
        return (-1);
      } else {
        return false;
      }
      return (0);
      break;
    }
    case ZIJ: {
      bool fold = true;
      for (int i = 0; !fold && i < game->playersSize; i++) {
        if (game->players[i]->ID != Jonas && game->players[i]->ID != ZIJ &&
            game->players[i]->hand->cards[0] != nullptr) {
          fold = false;
        }
        if (game->players[i]->ID == Jonas &&
            game->players[i]->hand->cards[0] == nullptr) {
          fold = false;
        }
      }
      if (fold) {
        return -1;
      }

      return (0);
      break;
    }
    case STUDENT_2023: {
      PokerRank rank = getMyHandRank(player->hand);
      if (rank.category >= ONE_PAIR) {
        return 0;
      }
      return -1;
    }
    case STUDENT_2022:
      PokerRank mijnHandRank = getMyHandRank(player->hand);
      if (table[0] == nullptr)  // Pre flop
      {
        if (player->hand->cards[0]->suit ==
            player->hand->cards[1]->suit) {  // suited hands
          int diffBetweenOrderedCards =
              mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
          if (diffBetweenOrderedCards == 1 ||
              diffBetweenOrderedCards == 13) {  // suited connected
            return (game->blind * 7) -
                   totalBet;  // max 7x blind and fold otherwise
          }
          return (game->blind * 3) -
                 totalBet;  // max 3x blind and fold otherwise
        }
        if (player->hand->cards[0]->rank ==
            player->hand->cards[1]->rank) {  // 1 pair to start
          return (game->blind * 5) -
                 totalBet;  // max 5x blind and fold otherwise
        }
        int diffBetweenOrderedCards =
            mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
        if (diffBetweenOrderedCards == 1 ||
            diffBetweenOrderedCards == 13) {  // unsuited connected
          return (game->blind * 3) -
                 totalBet;  // max 3x blind and fold otherwise
        }
        if (totalBet > game->blind * 2) {
          return -1;
        }
        return 0;
      } else if (table[3] == nullptr) {  // on flop
        return 0;
      } else if (table[4] == nullptr) {  // on turn
        return 0;
      } else {  // on river
        return 0;
      }
      break;
  }
  return (0);
}

int main(void) {
  Game game;
  makeNewDeck(&game);

  Player ik;
  strcpy(ik.name, "Ikke de beste");
  ik.ID = IK;

  Player jij;
  strcpy(jij.name, "Gijse zot");
  jij.ID = JIJ;

  Player MyAI;
  strcpy(MyAI.name, "Jonas Vanhulst!");
  MyAI.ID = Jonas;

  Player zij;
  strcpy(zij.name, "Zij speelt vals");
  zij.ID = ZIJ;

  Player student2022;
  strcpy(student2022.name, "student 2022 example");
  student2022.ID = STUDENT_2022;

  Player student2023;
  strcpy(student2023.name, "student 2022 example");
  student2023.ID = STUDENT_2023;

  addPlayerToGame(&game, &ik);
  addPlayerToGame(&game, &jij);
  addPlayerToGame(&game, &MyAI);
  addPlayerToGame(&game, &zij);
  addPlayerToGame(&game, &student2022);
  addPlayerToGame(&game, &student2023);

  playGame(&game, 1);
  printf("The winner is %s with %d chips !", game.players[0]->name,
         game.players[0]->chips);
  return 0;
}
