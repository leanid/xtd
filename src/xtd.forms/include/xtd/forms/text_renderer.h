/// @file
/// @brief Contains xtd::forms::style_sheets::text_renderer static class.
/// @copyright Copyright (c) 2022 Gammasoft. All rights reserved.
#pragma once
#include <memory>
#include <vector>
#include <xtd/static.h>
#include <xtd/ustring.h>
#include <xtd/drawing/graphics.h>
#include <xtd/drawing/rectangle.h>
#include "style_sheets/itext_model.h"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    class text_renderer static_ {
    public:
      static void draw_text(xtd::drawing::graphics& graphics, const xtd::drawing::rectangle& bounds, const xtd::ustring& text, const xtd::forms::style_sheets::itext_model& data);
      
    private:
      static xtd::ustring get_hotkey_prefix_locations(const xtd::ustring& str, std::vector<size_t>& locations);
    };
  }
}
