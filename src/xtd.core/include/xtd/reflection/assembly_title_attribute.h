/// @file
/// @brief Contains xtd::reflection::assembly_title_attribute attribute.
#pragma once

#include "../attribute.h"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::reflection namespace contains types that retrieve information about assemblies, modules, members, parameters, and other entities in managed code by examining their metadata. These types also can be used to manipulate instances of loaded types, for example to hook up events or to invoke methods. To dynamically create types, use the System.Reflection.Emit namespace.
  namespace reflection {
    /// @par Library
    /// xtd.core
    /// @ingroup xtd_core
    class assembly_title_attribute final : public xtd::attribute {
    public:
      explicit assembly_title_attribute(const ustring& title);
      
      /// @cond
      /// Internal used only
      assembly_title_attribute(const ustring& title, const object& executing_assembly);
      /// @endcond
      
      const ustring& title() const {return title_;}
      
    protected:
      std::shared_ptr<object> get_type_id() const override;

    private:
      ustring title_;
    };
  }
}

/// @cond
std::shared_ptr<xtd::reflection::assembly_title_attribute>& __assembly_title_attribute__();
/// @endcond

#define assembly_title_(title) \
  xtd::reflection::assembly_title_attribute __assembly_title_attribute {title, xtd::object()}

