/// @file
/// @brief Contains xtd::forms::native::about_dialog API.
/// @copyright Copyright (c) 2021 Gammasoft. All rights reserved.
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <xtd/static.h>
#include <xtd/drawing/icon.h>
#include <xtd/forms_native_export.h>

namespace xtd {
  namespace forms {
    namespace native {
      /// @brief Contains about dialog native API.
      /// @par Library
      /// xtd.forms.native
      /// @ingroup xtd_forms_native
      /// @warning Internal use only
      class forms_native_export_ about_dialog final static_ {
      public:
        /// @brief Shows about dialog.
        /// @param hwnd Window handle.
        /// @param icon An icon value that specifies the icon to display.
        /// @param name A string that specifies the title bar caption to display.
        /// @param decription A string that specifies the text to display.
        /// @param version A string that specifies the version to display.
        /// @param long_version A string that specifies the long version to display.
        /// @param copyright A string that specifies the copyright to display.
        /// @param website A string that specifies the website url.
        /// @param website_label A string that specifies the website label to display.
        /// @param creators A creators_collection that specifies the creators collection.
        /// @param doc_writers A doc_writers_collection that specifies the documentation writers collection.
        /// @param translators A translators_collection that specifies the translators collection.
        /// @param designers A designers_collection that specifies the gesigners collection.
        /// @param license A string that specifies the license text to display.
        static void show(intptr_t hwnd, const xtd::drawing::icon& icon, const std::string& name, const std::string& description, const std::string& version, const std::string& long_version, const std::string& copyright, const std::string& website, const std::string& website_label, const std::vector<std::string>& creators, const std::vector<std::string>& designers, const std::vector<std::string>& doc_writers, const std::vector<std::string>& translators, const std::string& license);
      };
    }
  }
}
