#pragma once
#include <stdexcept>
#include <xtd/forms/create_params.hpp>
#include <xtd/forms/native/static_styles.hpp>
#include <wx/statbmp.h>
#include "control_handler.hpp"
#include <wx/generic/statbmpg.h>

namespace xtd {
  namespace forms {
    namespace native {
      class wx_picture_box : public control_handler {
      public:
        wx_picture_box(const forms::create_params& create_params) {
          if (!create_params.parent()) throw std::invalid_argument("control must have a parent");
          if ((create_params.style() & SS_BITMAP_CENTER) == SS_BITMAP_CENTER) {
            this->control_handler::create<wxStaticBitmap>(reinterpret_cast<control_handler*>(create_params.parent())->control(), wxID_ANY, wxNullBitmap, wxPoint(create_params.x(), create_params.y()), wxSize(create_params.width(), create_params.height()), style_to_wx_style(create_params.style(), create_params.ex_style()));
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
            static_cast<wxStaticBitmap*>(this->control())->SetScaleMode(wxStaticBitmap::Scale_None);
#endif
          } else {
            this->control_handler::create<wxGenericStaticBitmap>(reinterpret_cast<control_handler*>(create_params.parent())->control(), wxID_ANY, wxNullBitmap, wxPoint(create_params.x(), create_params.y()), wxSize(create_params.width(), create_params.height()), style_to_wx_style(create_params.style(), create_params.ex_style()));
            if ((create_params.style() & SS_BITMAP_STRETCH) == SS_BITMAP_STRETCH) {
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
              static_cast<wxGenericStaticBitmap*>(this->control())->SetScaleMode(wxGenericStaticBitmap::Scale_Fill);
#endif
            } else if ((create_params.style() & SS_BITMAP_ZOOM) == SS_BITMAP_ZOOM) {
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
              static_cast<wxGenericStaticBitmap*>(this->control())->SetScaleMode(wxGenericStaticBitmap::Scale_AspectFit);
#endif
            } else {
              this->auto_size = (create_params.style() & SS_BITMAP_AUTOSIZE) == SS_BITMAP_AUTOSIZE;
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
              static_cast<wxGenericStaticBitmap*>(this->control())->SetScaleMode(wxGenericStaticBitmap::Scale_None);
#endif
            }
          }
          this->control()->SetSize(create_params.width(), create_params.height());
        }
        
        static long style_to_wx_style(size_t style, size_t ex_style) {
          long wx_style = wxST_NO_AUTORESIZE;

          if ((style & WS_BORDER) == WS_BORDER) wx_style |= wxBORDER_SIMPLE;
          else if ((ex_style & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE) wx_style |= wxBORDER_THEME;
          else wx_style |= wxBORDER_NONE;

          return wx_style;
        }
        
        bool auto_size = false;
      };
    }
  }
}
