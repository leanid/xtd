/// @file
/// @brief Contains xtd::tunit::class_cleanup_attribute class.
#pragma once
#include "test.hpp"

/// @brief The xtd namespace contains all fundamental classes to access console.
namespace xtd {
  /// @brief The tunit namespace contains a unit test framework.
  namespace tunit {
    /// @brief This attribute is use to add cleaup class method to class cleanup attribute.
    struct class_cleanup_attribute {
    public:
      /// @brief Crrates new instance of class_cleanup_attribute attribute.
      /// @param name Name of attribute
      /// @param test_class xtd::tunit::class_test containing clean_up method.
      /// @param method Cleanup class method.
      template<typename TestClass>
      class_cleanup_attribute(const std::string& name, TestClass& test_class, void (*method)()) noexcept :  class_cleanup_attribute(name, test_class, method, xtd::tunit::line_info()) {}
      
      /// @brief Crrates new instance of class_cleanup_attribute attribute.
      /// @param name Name of attribute
      /// @param test_class xtd::tunit::class_test containing clean_up method.
      /// @param method Cleanup class method.
      /// @param line_info Contains information about current file and current line.
      template<typename TestClass>
      class_cleanup_attribute(const std::string& name, TestClass& test_class, void (*method)(), const xtd::tunit::line_info& line_info) noexcept {test_class.add_class_cleanup({name, method, line_info});}
    };
  }
}

#define class_cleanup_(method_name) \
  __##method_name##_static() {} \
  struct __class_cleanup_attribute : public xtd::tunit::class_cleanup_attribute { \
  template<typename test_class> __class_cleanup_attribute(test_class& test) : class_cleanup_attribute(#method_name, test, &method_name, {__func__, __FILE__, __LINE__}) {__##method_name##_static();} \
  } __class_cleanup_attribute {*this}; \
  static void method_name()

