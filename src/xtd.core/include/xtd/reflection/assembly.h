/// @file
/// @brief Contains xtd::reflection::assembly class.
#pragma once

#include "../object.h"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::reflection namespace contains types that retrieve information about assemblies, modules, members, parameters, and other entities in managed code by examining their metadata. These types also can be used to manipulate instances of loaded types, for example to hook up events or to invoke methods. To dynamically create types, use the System.Reflection.Emit namespace.
  namespace reflection {
    /// @brief
    /// @par Library
    /// xtd.core
    /// @ingroup xtd_core
    class assembly : public object {
    public:
      /// @cond
      assembly() = default;
      assembly(const assembly&) = default;
      assembly(assembly&&) = default;
      assembly& operator=(const assembly&) = default;
      /// @endcond
    };
  }
}