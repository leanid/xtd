#pragma once
#include "menu.hpp"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    class main_menu : public menu {
    public:      
      main_menu();
      
      /// @cond
      ~main_menu();
      /// @endcond
      
    protected:
      intptr_t create_menu_handle() override;
      void destroy_menu_handle(intptr_t handle) override;
    };
  }
}
