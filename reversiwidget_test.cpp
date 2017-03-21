#include "reversiwidget.h"

#include "reversiboard.h"

#include <boost/test/unit_test.hpp>


using namespace ribi::reversi;

BOOST_AUTO_TEST_CASE(reversi_widget)
{
  {
    Widget r(4);
    assert(r.GetCurrentPlayer() == Player::player1);
    assert(r.GetValidMoves().size() == 5); //4 place moves and one pass
  }
  /*
  // Play random games
  for (int sz = 4; sz != 6; ++sz)
  {
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      assert(r.GetWinner() == Winner::no_winner);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(r.CanDoMove(move));
      r.DoMove(move);
    }
  }
  */
  // Test copy constructor and operator== and operator!=
  {
    const int sz = 4;
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      assert(r.GetWinner() == Winner::no_winner);
      assert(r == r);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(move);
      assert(r.CanDoMove(move));
      Widget before(r);
      assert(r == before);

      r.DoMove(move);

      assert(before != r);
      assert(before.CanDoMove(move));

      before.DoMove(move);

      assert(before == r);
    }
  }
  // Test undo functionality in a single game
  {
    const int sz = 4;
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      assert(r.GetWinner() == Winner::no_winner);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(move);
      assert(r.CanDoMove(move));
      const Widget before(r);
      assert(before.CanDoMove(move));
      r.DoMove(move);
      assert(before != r);
      r.Undo();
      assert(before.GetCurrentPlayer() == r.GetCurrentPlayer());
      assert(*before.GetBoard() == *r.GetBoard());
      assert(before == r);
      assert(before.CanDoMove(move));
      assert(r.CanDoMove(move));
      r.DoMove(move);
    }
  }
}
