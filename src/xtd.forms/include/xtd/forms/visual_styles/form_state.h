/// @file
/// @brief Contains xtd::forms::visual_styles::form_state enum class.
/// @copyright Copyright (c) 2022 Gammasoft. All rights reserved.
#pragma once
#include <xtd/ustring.h>

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    /// @brief The xtd::forms::visual_styles namespace contains classes for rendering controls and other windows user interface (UI) elements with visual styles in operating systems that support them.
    namespace visual_styles {
      /// @brief Specifies the visual state of a form that is drawn with visual styles.
      /// @par Namespace
      /// xtd::forms::visual_style
      /// @par Library
      /// xtd.forms
      /// @ingroup xtd_forms
      /// @remarks The form_state values correspond to the states of the visual_style_element objects exposed by the visual_style_element:form::form class. The form_state values are also used as an argument in the form_renderer.draw_form method.
      enum class form_state {
        /// @brief The form has the normal appearance.
        normal = 1,
        /// @brief The form is hot.
        hot,
        /// @brief The form is pressed.
        pressed,
        /// @brief The form is disabled.
        disabled,
      };
      
      /// @cond
      inline std::ostream& operator<<(std::ostream& os, form_state value) {return os << to_string(value, {{form_state::normal, "normal"}, {form_state::hot, "hot"}, {form_state::pressed, "pressed"}, {form_state::disabled, "disabled"}});}
      inline std::wostream& operator<<(std::wostream& os, form_state value) {return os << to_string(value, {{form_state::normal, L"normal"}, {form_state::hot, L"hot"}, {form_state::pressed, L"pressed"}, {form_state::disabled, L"disabled"}});}
      /// @endcond
    }
  }
}