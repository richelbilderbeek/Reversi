#ifndef REVERSIMENUDIALOG_H
#define REVERSIMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace reversi {

struct MenuDialog final : public ribi::MenuDialog
{
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIMENUDIALOG_H
