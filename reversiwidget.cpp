#include "reversiwidget.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

#pragma GCC diagnostic push




#include "reversimove.h"
#include "reversiboard.h"
#include "reversiplayer.h"
#include "textcanvas.h"
#pragma GCC diagnostic pop

ribi::reversi::Widget::Widget(const int size)
  : m_board(new Board(size)),
    m_current_player(Player::player1),
    m_undo{},
    m_x{size/2},
    m_y{size/2}
{
  assert(size > 0);
  assert(size == m_board->GetSize());

  #ifndef NDEBUG
  const int x = size / 2 - 1;
  const int y = size / 2 - 1;
  assert(m_board->Get(x  ,y  ) == Square::player1);
  assert(m_board->Get(x+1,y  ) == Square::player2);
  assert(m_board->Get(x  ,y+1) == Square::player2);
  assert(m_board->Get(x+1,y+1) == Square::player1);
  #endif
}

ribi::reversi::Widget::Widget(const Widget& other)
  : m_board(boost::shared_ptr<Board>(new Board(*other.m_board))),
    m_current_player(other.m_current_player),
    m_undo(other.m_undo),
    m_x{other.m_x},
    m_y{other.m_y}
{
  assert(m_board);
  assert(*m_board == *other.m_board && "Must be a copy");
  assert( m_board !=  other.m_board && "Must be a deep copy");
  assert(m_current_player == other.m_current_player);
  assert(*this == other && "Must be a copy");
}

ribi::reversi::Widget& ribi::reversi::Widget::operator=(const Widget& other)
{
  m_board = boost::shared_ptr<Board>(new Board(*other.m_board));
  m_current_player = other.m_current_player;
  m_undo = other.m_undo;

  assert(m_board);
  assert(*m_board == *other.m_board && "Must be a copy");
  assert( m_board !=  other.m_board && "Must be a deep copy");
  assert(m_current_player == other.m_current_player);
  assert(*this == other && "Must be a copy");
  return *this;
}

bool ribi::reversi::Widget::CanDoMove(const boost::shared_ptr<const ribi::reversi::Move> move) const noexcept
{
  assert(move);
  if (boost::dynamic_pointer_cast<const ribi::reversi::MovePass>(move))
  {
    //Can always pass for now
    return true;
  }
  const boost::shared_ptr<const ribi::reversi::MovePlacePiece> place {
    boost::dynamic_pointer_cast<const ribi::reversi::MovePlacePiece>(move)
  };
  assert(place);
  assert(move);
  return CanDoMove(place->GetX(),place->GetY());
}

bool ribi::reversi::Widget::CanDoMove(const int x, const int y) const noexcept
{
  return m_board->CanDoMove(x,y,GetCurrentPlayer());
}

void ribi::reversi::Widget::DoMove(const boost::shared_ptr<const ribi::reversi::Move> move) noexcept
{
  assert(move);
  assert(CanDoMove(move));

  //Undo
  {
    const boost::shared_ptr<Widget> prev_widget {
      new Widget(*this)
    };
    m_undo.push_back(std::make_pair(prev_widget,move));
    assert(prev_widget->GetCurrentPlayer() == this->GetCurrentPlayer());
  }
  //Actually do the move
  assert(move);
  if (boost::dynamic_pointer_cast<const ribi::reversi::MovePass>(move))
  {
    DoMovePass();
  }
  else
  {
    const boost::shared_ptr<const ribi::reversi::MovePlacePiece> place {
      boost::dynamic_pointer_cast<const ribi::reversi::MovePlacePiece>(move)
    };
    assert(place);
    assert(CanDoMove(place->GetX(),place->GetY()));
    DoMove(place->GetX(),place->GetY());
  }
}

void ribi::reversi::Widget::DoMove(const int x, const int y) noexcept
{
  assert(GetBoard()->CanDoMove(x,y,GetCurrentPlayer()));
  m_board->DoMove(x,y,GetCurrentPlayer());
  TogglePlayer();
}

void ribi::reversi::Widget::DoMovePass() noexcept
{
  TogglePlayer();
}

ribi::reversi::Player ribi::reversi::Widget::GetOtherPlayer() const noexcept
{
  switch (GetCurrentPlayer())
  {
    case Player::player1: return Player::player2;
    case Player::player2: return Player::player1;
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  return Player::player1;
}

const std::vector<boost::shared_ptr<ribi::reversi::Move>> ribi::reversi::Widget::GetValidMoves() const noexcept
{
  std::vector<boost::shared_ptr<Move>> moves;
  for (const std::pair<int,int> p: m_board->GetValidMoves(GetCurrentPlayer()))
  {
    const boost::shared_ptr<Move> move {
      new MovePlacePiece(p.first,p.second)
    };
    assert(move);
    moves.push_back(move);
  }
  const boost::shared_ptr<Move> move_pass {
    new MovePass
  };
  moves.push_back(move_pass);
  return moves;
}

std::string ribi::reversi::Widget::GetVersion() noexcept
{
  return "1.1";
}


std::vector<std::string> ribi::reversi::Widget::GetVersionHistory() noexcept
{
  return {
    "2013-12-19: version 1.0: split off from Reversi",
    "2014-02-14: version 1.1: use enum classes, added ToTextCanvas"
  };
}

ribi::reversi::Winner ribi::reversi::Widget::GetWinner() const noexcept
{
  //static_assert(std::is_same<ribi::reversi::Widget::player1,Board::player1>(),"");
  //If both players cannot do moves, count the tiles
  if (GetBoard()->GetValidMoves(GetCurrentPlayer()).empty())
  {
    Board r(*m_board);
    const Player other_player = GetOtherPlayer();
    if (!r.GetValidMoves(other_player).empty())
    {
      const int n_1 { r.Count(Square::player1) };
      const int n_2 { r.Count(Square::player2) };
      if (n_1 > n_2) return Winner::player1;
      if (n_2 > n_1) return Winner::player2;
      assert(n_1 == n_2);
      return Winner::draw;
    }
  }
  return Winner::no_winner;
}

void ribi::reversi::Widget::TogglePlayer()
{
  switch (GetCurrentPlayer())
  {
    case Player::player1: m_current_player = Player::player2; return;
    case Player::player2: m_current_player = Player::player1; return;
    default: assert(!"Should not get here");
  }
}

const boost::shared_ptr<ribi::TextCanvas> ribi::reversi::Widget::ToTextCanvas() const noexcept
{
  const int n_rows = m_board->GetSize();

  if (n_rows == 0)
  {
    return nullptr;
  }

  boost::shared_ptr<TextCanvas> canvas {
    m_board->ToTextCanvas()
  };

  const char c = canvas->GetChar(m_x,m_y);
  char d = ' ';
  switch (c)
  {
    case ' ': d = '.'; break;
    case '.': d = ' '; break;
    case 'O': d = 'o'; break;
    case 'X': d = 'x'; break;
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
  }
  assert(canvas->IsInRange(m_x,m_y));
  canvas->PutChar(m_x,m_y,d);
  return canvas;
}

void ribi::reversi::Widget::Undo()
{
  assert(!m_undo.empty());
  this->m_board = (m_undo.back().first)->GetBoard();
  assert(*m_board == *(m_undo.back().first)->GetBoard());
  assert(this->m_current_player != (m_undo.back().first)->GetCurrentPlayer());
  this->m_current_player = (m_undo.back().first)->GetCurrentPlayer();
  m_undo.pop_back();
}

bool ribi::reversi::operator==(const ribi::reversi::Widget& lhs, const ribi::reversi::Widget& rhs)
{
  if (*lhs.GetBoard() != *rhs.GetBoard()) return false;
  if (lhs.GetCurrentPlayer() != rhs.GetCurrentPlayer()) return false;
  if (lhs.m_undo.size() != rhs.m_undo.size()) return false;
  return std::equal(
    std::begin(lhs.m_undo),
    std::end(lhs.m_undo),
    std::begin(rhs.m_undo),
    [](
      const auto& lhs_here,
      const auto& rhs_here
    )
    {
      return *(lhs_here.first) == *(rhs_here.first)
        && lhs_here.second->ToStr() == rhs_here.second->ToStr();
    }
  );
}

bool ribi::reversi::operator!=(const ribi::reversi::Widget& lhs, const ribi::reversi::Widget& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::reversi::operator<<(std::ostream& os, const ribi::reversi::Widget& r)
{
  os << *r.GetBoard()
    << '\n'
    << PlayerToStr(r.GetCurrentPlayer());

  return os;
}
