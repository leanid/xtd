#include <xtd/forms/style_sheets/background_image.h>
#include <xtd/drawing/system_colors.h>
#include <xtd/xtd.tunit>

using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::style_sheets;
using namespace xtd::tunit;

namespace unit_tests {
  class test_class_(test_image_data) {
  public:
    void test_method_(create_with_default_constructor) {
      background_image i;
      assert::are_equal(image_type::none, i.image_type(), csf_);
      assert::is_empty(i.url(), csf_);
      assert::are_equal(2U, i.colors().size(), csf_);
      collection_assert::are_equal({color::black, color::black}, i.colors(), csf_);
      assert::are_equal(180, i.angle(), csf_);
    }

    void test_method_(create_with_specified_url) {
      background_image i("arrow.png");
      assert::are_equal(image_type::url, i.image_type(), csf_);
      assert::are_equal("arrow.png", i.url(), csf_);
      assert::are_equal(2U, i.colors().size(), csf_);
      collection_assert::are_equal({color::black, color::black}, i.colors(), csf_);
      assert::are_equal(180, i.angle(), csf_);
    }
    
    void test_method_(create_with_specified_colors) {
      background_image i({color::blue, color::white});
      assert::are_equal(image_type::linear_gradient, i.image_type(), csf_);
      assert::is_empty(i.url(), csf_);
      assert::are_equal(2U, i.colors().size(), csf_);
      collection_assert::are_equal({color::blue, color::white}, i.colors(), csf_);
      assert::are_equal(180, i.angle(), csf_);
    }
    
    void test_method_(create_with_specified_image_type_linear_gradient_and_colors) {
      background_image i(image_type::linear_gradient, {color::blue, color::white});
      assert::are_equal(image_type::linear_gradient, i.image_type(), csf_);
      assert::is_empty(i.url(), csf_);
      assert::are_equal(2U, i.colors().size(), csf_);
      collection_assert::are_equal({color::blue, color::white}, i.colors(), csf_);
      assert::are_equal(180, i.angle(), csf_);
    }

    void test_method_(create_with_specified_image_type_linear_gradient_and_one_color) {
      assert::throws<argument_exception>([]{background_image i(image_type::linear_gradient, {color::blue});}, csf_);
    }
    
    void test_method_(create_with_specified_image_type_radial_gradient_and_colors) {
      assert::throws<not_supported_exception>([]{background_image i(image_type::radial_gradient, {color::blue, color::white});}, csf_);
    }
    
    void test_method_(create_with_specified_image_type_conic_gradient_and_colors) {
      assert::throws<not_supported_exception>([]{background_image i(image_type::conic_gradient, {color::blue, color::white});}, csf_);
    }
    
    void test_method_(create_with_specified_image_type_linear_gradient_colors_and_angle) {
      background_image i(image_type::linear_gradient, {color::blue, color::white}, 270);
      assert::are_equal(image_type::linear_gradient, i.image_type(), csf_);
      assert::is_empty(i.url(), csf_);
      assert::are_equal(2U, i.colors().size(), csf_);
      collection_assert::are_equal({color::blue, color::white}, i.colors(), csf_);
      assert::are_equal(270, i.angle(), csf_);
    }
    
    void test_method_(create_with_specified_image_type_linear_gradient_one_color_and_angle) {
      assert::throws<argument_exception>([]{background_image i(image_type::linear_gradient, {color::blue}, 270);}, csf_);
    }
    
    void test_method_(create_with_specified_image_type_radial_gradient_colors_and_angle) {
      assert::throws<not_supported_exception>([]{background_image i(image_type::radial_gradient, {color::blue, color::white}, 270);}, csf_);
    }
    
    void test_method_(create_with_specified_image_type_conic_gradient_colors_and_angle) {
      assert::throws<not_supported_exception>([]{background_image i(image_type::conic_gradient, {color::blue, color::white}, 270);}, csf_);
    }
  };
}