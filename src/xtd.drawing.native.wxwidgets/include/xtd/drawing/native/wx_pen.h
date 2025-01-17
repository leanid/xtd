#pragma once
/// @cond
#ifndef __XTD_DRAWING_NATIVE_LIBRARY__
#error "Do not include this file: Internal use only"
#endif
/// @endcond

#include <cstdint>
#include <wx/pen.h>
#include <wx/image.h>
#include <wx/graphics.h>
#include "wx_brush.h"

namespace xtd {
  namespace drawing {
    namespace native {
      class wx_pen {
      public:
        enum class pen_type {
          none,
          conical_gradient,
          hatch_fill,
          linear_gradient,
          radial_gradient,
          solid_color,
          texture_fill
        };
        
        struct conical_gradiant_pen {
          wx_brush brush;
          float width = 1.0f;
        };
        struct hatch_fill_pen {
          wx_brush brush;
          float width = 1.0f;
        };
        struct linear_gradiant_pen {
          wx_brush brush;
          float width = 1.0f;
        };
        struct radial_gradiant_pen {
          wx_brush brush;
          float width = 1.0f;
        };
        struct solid_color_pen {
          wxColour color;
          float width = 1.0f;
          float dash_offset = 0.0f;
          std::vector<int8_t> dashes;
        };
        struct texture_fill_pen {
          wx_brush brush;
          float width = 1.0f;
        };
        
        wx_pen() = default;
        
        void create_conical_gradient_pen(const wx_brush& brush, float width) {
          pen_type_ = pen_type::conical_gradient;
          conical_gradiant_pen_.brush = brush;
          conical_gradiant_pen_.width = width;
        }
        
        void create_hatch_fill_pen(const wx_brush& brush, float width) {
          pen_type_ = pen_type::hatch_fill;
          hatch_fill_pen_.brush = brush;
          hatch_fill_pen_.width = width;
        }

        void create_linear_gradient_pen(const wx_brush& brush, float width) {
          pen_type_ = pen_type::linear_gradient;
          linear_gradiant_pen_.brush = brush;
          linear_gradiant_pen_.width = width;
        }

        void create_radial_gradient_pen(const wx_brush& brush, float width) {
          pen_type_ = pen_type::radial_gradient;
          radial_gradiant_pen_.brush = brush;
          radial_gradiant_pen_.width = width;
        }

        void create_solid_color_pen(const wxColour& color, float width, float dash_offset, const std::vector<int8_t>& dashes) {
          pen_type_ = pen_type::solid_color;
          solid_color_pen_.color = color;
          solid_color_pen_.dash_offset = dash_offset;
          solid_color_pen_.dashes = dashes;
          solid_color_pen_.width = width;
        }
        
        void create_texture_fill_pen(const wx_brush& brush, float width) {
          pen_type_ = pen_type::texture_fill;
          texture_fill_pen_.brush = brush;
          texture_fill_pen_.width = width;
        }

        bool is_conical_gradiant_pen() const {return pen_type_ == pen_type::conical_gradient;}
        bool is_hatch_fill_pen() const {return pen_type_ == pen_type::hatch_fill;}
        bool is_linear_gradiant_pen() const {return pen_type_ == pen_type::linear_gradient;}
        bool is_radial_gradiant_pen() const {return pen_type_ == pen_type::radial_gradient;}
        bool is_solid_color_pen() const {return pen_type_ == pen_type::solid_color;}
        bool is_texture_fill_pen() const {return pen_type_ == pen_type::texture_fill;}
        
        const conical_gradiant_pen& get_conical_gradiant_pen() const {return conical_gradiant_pen_;}
        conical_gradiant_pen& get_conical_gradiant_pen() {return conical_gradiant_pen_;}
        
        const hatch_fill_pen& get_hatch_fill_pen() const {return hatch_fill_pen_;}
        hatch_fill_pen& get_hatch_fill_pen() {return hatch_fill_pen_;}

        const linear_gradiant_pen& get_linear_gradiant_pen() const {return linear_gradiant_pen_;}
        linear_gradiant_pen& get_linear_gradiant_pen() {return linear_gradiant_pen_;}
        
        const radial_gradiant_pen& get_radial_gradiant_pen() const {return radial_gradiant_pen_;}
        radial_gradiant_pen& get_radial_gradiant_pen() {return radial_gradiant_pen_;}
        
        const solid_color_pen& get_solid_color_pen() const {return solid_color_pen_;}
        solid_color_pen& get_solid_color_pen() {return solid_color_pen_;}
        
        const texture_fill_pen& get_texture_fill_pen() const {return texture_fill_pen_;}
        texture_fill_pen& get_texture_fill_pen() {return texture_fill_pen_;}
        
      private:
        pen_type pen_type_ = pen_type::none;
        conical_gradiant_pen conical_gradiant_pen_;
        hatch_fill_pen hatch_fill_pen_;
        linear_gradiant_pen linear_gradiant_pen_;
        radial_gradiant_pen radial_gradiant_pen_;
        solid_color_pen solid_color_pen_;
        texture_fill_pen texture_fill_pen_;
      };
    }
  }
}

