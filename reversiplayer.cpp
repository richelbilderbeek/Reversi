#include "reversiplayer.h"

#include <cassert>
#include <stdexcept>

std::string ribi::reversi::PlayerToStr(const Player player) noexcept
{
  switch (player)
  {
    case Player::player1: return "player1";
    case Player::player2: return "player2";
  }
  assert(!"Should not get here");
  return "";
}
