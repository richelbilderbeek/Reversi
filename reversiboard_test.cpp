#include "reversiboard.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::reversi;

BOOST_AUTO_TEST_CASE(reversi_board)
{
  {
    Board r(4);
    assert(r.Get(1,1) == Square::player1);
    assert(r.Get(1,2) == Square::player2);
    assert(r.Get(2,1) == Square::player2);
    assert(r.Get(2,2) == Square::player1);
    assert(r.Get(0,0) == Square::empty);
    assert(r.Get(2,0) == Square::empty);
    assert(r.CanDoMove(2,0,Player::player1));
    assert(r.CanDoMove(3,1,Player::player1));
    assert(r.CanDoMove(0,2,Player::player1));
    assert(r.CanDoMove(1,3,Player::player1));
    assert(r.GetValidMoves(Player::player1).size() == 4);
  }
  //operator==
  {
    const Board r(5);
    Board s(5);
    assert(r == s);
    s.Set(0,0,Square::player1);
    assert(r != s);
  }
  //operator<<
  for (int sz=4; sz!=10; ++sz)
  {
    const Board r(sz);
    std::stringstream s;
    s << r;
    Board t;
    s >> t;
    assert(r == t);

  }
  {
    std::stringstream s;
    s << "1112." << '\n'
      << "111.." << '\n'
      << "112.." << '\n'
      << "1.2.." << '\n'
      << "1.2..";
    Board r;
    s >> r;
    assert( r.CanDoMove(4,0,Player::player1));
    assert( r.CanDoMove(3,2,Player::player1));
    assert( r.CanDoMove(3,3,Player::player1));
    assert( r.CanDoMove(3,4,Player::player1));
    assert(!r.CanDoMove(3,1,Player::player1));
  }
  //Play random games
  for (int sz = 4; sz != 10; ++sz)
  {
    Board r(sz);
    Player player = Player::player1;
    while (!r.GetValidMoves(player).empty())
    {
      std::vector<std::pair<int,int>> m {
        r.GetValidMoves(player)
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const std::pair<int,int> move = m[0];
      assert(r.CanDoMove(move.first,move.second,player));
      r.DoMove(move.first,move.second,player);
      player = GetOtherPlayer(player);
    }
  }
}
