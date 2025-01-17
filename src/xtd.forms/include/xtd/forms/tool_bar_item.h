/// @file
/// @brief Contains xtd::forms::tool_bar_item compnent.
/// @copyright Copyright (c) 2022 Gammasoft. All rights reserved.
#pragma once
#include "component.h"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    /// @brief Represents a toolbar item.
    /// @par Namespace
    /// xtd::forms
    /// @par Library
    /// xtd.forms
    /// @ingroup xtd_forms
    class tool_bar_item : public xtd::forms::component {
    public:
      /// @name Constructors
      
      /// @{
      /// @brief Initialises a new instance of xtd::forms::tool_bar_item class.
      tool_bar_item() = default;
      /// @}
      
      /// @name Methods
      
      /// @{
      /// @brief Generates a click event for the xtd::forms::tool_bar_item.
      virtual void perform_click() = 0;
      /// @}
    };
    
    /// @brief Represents a xtd::forms::tool_bar_item reference.
    /// @par Namespace
    /// xtd::forms
    /// @par Library
    /// xtd.forms
    /// @ingroup xtd_forms
    using tool_bar_item_ref = std::reference_wrapper<tool_bar_item>;
  }
}
