#pragma once
#include <xtd/forms/create_params.hpp>
#include <wx/app.h>
#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/button.h>
#include "control_handler.hpp"

namespace xtd {
  namespace forms {
    namespace native {
      class wx_form : public control_handler {
      public:
        wx_form(const forms::create_params& create_params) {
          wxPoint location = wxPoint(create_params.x(), create_params.y());
          wxSize size = wxSize(create_params.width(), create_params.height());
          if (size.GetWidth() > -1 && size.GetWidth() < 75) size.SetWidth(75);
          if (size.GetHeight() > -1 && size.GetHeight() < 23) size.SetHeight(23);
          this->modal_ = (create_params.ex_style() & WS_EX_MODALWINDOW) == WS_EX_MODALWINDOW;
          if (this->modal_)
            this->control_handler::create<wxDialog>(create_params.parent() ? ((control_handler*)create_params.parent())->control() : nullptr, wxID_ANY, create_params.caption().wstr(), location, size, style_to_wx_style(create_params.style(), create_params.ex_style()));
          else
            this->control_handler::create<wxFrame>(create_params.parent() ? ((control_handler*)create_params.parent())->control() : nullptr, wxID_ANY, create_params.caption().wstr(), location, size, style_to_wx_style(create_params.style(), create_params.ex_style()));
          this->button_ = new wxButton(this->control(), wxID_ANY);
          this->control()->SetBackgroundColour(this->button_->GetBackgroundColour());
          this->control()->SetForegroundColour(this->button_->GetForegroundColour());
          this->button_->Hide();
        }

        static long style_to_wx_style(size_t style, size_t ex_style) {
          long wx_style = wxDEFAULT_FRAME_STYLE;
          
          return wx_style; // | common_window_style_to_wx_style(style, ex_style);
        }

        void SetSize(int32_t width, int32_t height) override {
#if defined(__WXOSX__)
          if (width < 75) width = 75;
          if (height < 23) height = 23;
#endif
          this->control_handler::SetSize(width, height);
        }

        bool modal() const {return this->modal_;}
        
      private:
        wxButton* button_;
        bool modal_ = false;
      };
    }
  }
}
