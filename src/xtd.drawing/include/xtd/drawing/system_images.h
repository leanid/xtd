/// @file
/// @brief Contains xtd::drawing::system_images factory.
/// @copyright Copyright (c) 2022 Gammasoft. All rights reserved.
#pragma once
#include <map>
#include <xtd/static.h>
#include "../drawing_export.h"
#include "bitmap.h"
#include "size.h"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::drawing namespace provides access to GDI+ basic graphics functionality. More advanced functionality is provided in the xtd::drawing::drawing2d, xtd::drawing::imaging, and xtd::drawing::text namespaces.
  namespace drawing {
    /// @cond
    class system_icons;
    /// @endcond
    
    /// @brief Each property of the xtd::drawing::system_images class is an xtd::drawing::image object for Windows system-wide images. This class cannot be inherited.
    /// @par Namespace
    /// xtd::drawing
    /// @par Library
    /// xtd.drawing
    /// @ingroup xtd_drawing drawing
    /// @remarks Each property of the system_fonts class returns a Font used to display text in a particular Windows display element, such as the title bar of a window. These fonts reflect the current settings in Control Panel.
    class drawing_export_ system_images final static_ {
    public:
      /// @name Properties
      
      /// @{
      /// @brief Gets system image from specified name.
      /// @return The default size in pixels (32 x 32).
      static xtd::drawing::size default_size() {return {32, 32};}
      static xtd::drawing::image image_loading() {return image_loading(default_size());}
      static xtd::drawing::image image_loading(const xtd::drawing::size& size) {return system_images::from_name("image-loading", size);}
      static xtd::drawing::image image_missing() {return image_missing(default_size());}
      static xtd::drawing::image image_missing(const xtd::drawing::size& size) {return from_name("image-missing", size);}
      
      static std::vector<xtd::ustring> contexts();
      static std::map<xtd::ustring, std::vector<xtd::ustring>> context_names();
      static std::vector<xtd::ustring> names();
      static std::vector<xtd::ustring> names(const xtd::ustring& context) {return context_names()[context];}
      static std::vector<xtd::drawing::size> sizes();
      /// @}
      
      /// @name Methods
      
      /// @{
      /// @brief Gets system image from specified name.
      /// @param name The system image name.
      /// @return The system image from specified name.
      /// @remarks The theme is the default system theme.
      /// @remarks The size is the default size (32 x 32).
      static xtd::drawing::image from_name(const xtd::ustring& name) {return from_name(default_theme(), name, default_size());}
      /// @brief Gets system image from specified name and size.
      /// @param name The system image name.
      /// @param size The system image size in pixels.
      /// @return The system image from specified name.
      /// @remarks The theme is the default system theme.
      static xtd::drawing::image from_name(const xtd::ustring& name, const xtd::drawing::size& size) {return from_name(default_theme(), name, size);}
      /// @brief Gets system image from specified them and name.
      /// @param theme The system image theme.
      /// @param name The system image name.
      /// @return The system image from specified name.
      /// @remarks The size is the default size in pixels (32 x 32).
      static xtd::drawing::image from_name(const xtd::ustring& theme, const xtd::ustring& name) {return from_name(theme, name, default_size());}
      /// @brief Gets system image from specified theme, name and size.
      /// @param theme The system image theme.
      /// @param name The system image name.
      /// @param size The system image size in pixels.
      /// @return The system image from specified name.
      static xtd::drawing::image from_name(const xtd::ustring& theme, const xtd::ustring& name, const xtd::drawing::size& size);
      /// @}
      
    private:
      friend class system_icons;
      static xtd::ustring default_theme();
      static xtd::ustring fallback_theme();
      static std::vector<xtd::ustring> themes();
    };
  }
}

