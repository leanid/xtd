#pragma once
/// @cond
#ifndef __XTD_FORMS_NATIVE_LIBRARY__
#error "Do not include this file: Internal use only"
#endif
/// @endcond

#include <xtd/cdebug.h>
#include <xtd/convert_string.h>
#include <xtd/drawing/system_colors.h>
#include <xtd/forms/create_params.h>
#include <xtd/forms/native/class_styles.h>
#include <xtd/forms/native/extended_window_styles.h>
#include <xtd/forms/native/window_styles.h>
#include <wx/app.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/settings.h>
#include "control_handler.h"

namespace xtd {
  namespace forms {
    namespace native {
      class wx_form;
      class wxMainPanel : public wxScrolled<wxPanel> {
        friend xtd::forms::native::wx_form;
      private:
        wxMainPanel(control_handler* control_handler, wxWindow* parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxScrolledWindowStyle, const wxString& name = wxPanelNameStr) : wxScrolled<wxPanel>(parent, winid, pos, size, style, name), control_handler_(control_handler) {}
        
        bool ProcessEvent(wxEvent& event) override {
          bool result = wxPanel::ProcessEvent(event);
          if (!GetParent()->IsShown()) return result;
          if (event.GetEventType() == wxEVT_LEFT_DOWN) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_MIDDLE_DOWN) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_RIGHT_DOWN) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_LEFT_UP) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_MIDDLE_UP) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_RIGHT_UP) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_MOTION) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_ENTER_WINDOW) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_LEAVE_WINDOW) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_LEFT_DCLICK) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_MIDDLE_DCLICK) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_RIGHT_DCLICK) wxPostEvent(GetParent(), event);
          //else if (event.GetEventType() == wxEVT_SET_FOCUS) wxPostEvent(GetParent(), event);
          //else if (event.GetEventType() == wxEVT_KILL_FOCUS) wxPostEvent(GetParent(), event);
          //else if (event.GetEventType() == wxEVT_CHILD_FOCUS) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_MOUSEWHEEL) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_AUX1_DOWN) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_AUX1_UP) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_AUX1_DCLICK) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_KEY_DOWN) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_CHAR) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_KEY_UP) wxPostEvent(GetParent(), event);
          else if (event.GetEventType() == wxEVT_PAINT) control_handler_->send_message(reinterpret_cast<intptr_t>(control_handler_), WM_PAINT, 0, 0, reinterpret_cast<intptr_t>(&event));
          return result;
        }
        
        control_handler* control_handler_ = nullptr;
      };
      
      class wx_form : public control_handler {
      public:
        explicit wx_form(const forms::create_params& create_params) {
          wxPoint location = wxPoint(create_params.x(), create_params.y());
          wxSize size = wxSize(create_params.width(), create_params.height());
          if (size.GetWidth() > -1 && size.GetWidth() < 75) size.SetWidth(75);
          if (size.GetHeight() > -1 && size.GetHeight() < 23) size.SetHeight(23);
          bool dialog = (create_params.ex_style() & WS_EX_MODALWINDOW) == WS_EX_MODALWINDOW || ((create_params.ex_style() & WS_EX_TOPMOST) != WS_EX_TOPMOST && create_params.parent() && (create_params.style() & WS_CHILD) != WS_CHILD);
          if (dialog) control_handler::create<wxDialog>(create_params.parent() ? (reinterpret_cast<control_handler*>(create_params.parent())->control()) : nullptr, wxID_ANY, wxString(xtd::convert_string::to_wstring(create_params.caption())), location, size, form_style_to_wx_style(create_params.style(), create_params.ex_style(), create_params.class_style(), create_params.parent()));
          else control_handler::create<wxFrame>(create_params.parent() && (create_params.ex_style() & WS_EX_TOPMOST) != WS_EX_TOPMOST ? (reinterpret_cast<control_handler*>(create_params.parent())->control()) : nullptr, wxID_ANY, wxString(xtd::convert_string::to_wstring(create_params.caption())), location, size, form_style_to_wx_style(create_params.style(), create_params.ex_style(), create_params.class_style(), create_params.parent()));
          #if defined(__WIN32__)
          if (xtd::drawing::system_colors::window().get_lightness() < 0.5) {
            control()->SetBackgroundColour(wxColour(xtd::drawing::system_colors::control().r(), xtd::drawing::system_colors::control().g(), xtd::drawing::system_colors::control().b(), xtd::drawing::system_colors::control().a()));
            control()->SetForegroundColour(wxColour(xtd::drawing::system_colors::control_text().r(), xtd::drawing::system_colors::control_text().g(), xtd::drawing::system_colors::control_text().b(), xtd::drawing::system_colors::control_text().a()));
          }
          #elif defined(__APPLE__)
          if (xtd::drawing::system_colors::window().get_lightness() < 0.5) {
            control()->SetBackgroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_BTNFACE));
            control()->SetForegroundColour(wxSystemSettings::GetColour(wxSystemColour::wxSYS_COLOUR_BTNFACE));
          }
          #endif
          boxSizer_ = new wxBoxSizer(wxVERTICAL);
          panel_ = new wxMainPanel(this, control(), wxID_ANY, wxDefaultPosition, wxDefaultSize, panel_style_to_wx_style(create_params.style(), create_params.ex_style(), create_params.class_style()));
          boxSizer_->Add(panel_, wxSizerFlags().Proportion(-1).Expand());
          control()->SetSizerAndFit(boxSizer_);
          #if defined(__WIN32__)
          if (xtd::drawing::system_colors::window().get_lightness() < 0.5) {
            panel_->SetBackgroundColour(wxColour(xtd::drawing::system_colors::control().r(), xtd::drawing::system_colors::control().g(), xtd::drawing::system_colors::control().b(), xtd::drawing::system_colors::control().a()));
            panel_->SetForegroundColour(wxColour(xtd::drawing::system_colors::control_text().r(), xtd::drawing::system_colors::control_text().g(), xtd::drawing::system_colors::control_text().b(), xtd::drawing::system_colors::control_text().a()));
          }
          #endif
        }
        
        static long form_style_to_wx_style(size_t style, size_t ex_style, size_t class_style, intptr_t parent) {
          long wx_style = 0;
          
          if ((style & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX) wx_style |= wxMAXIMIZE_BOX;
          if ((style & WS_MINIMIZEBOX) == WS_MINIMIZEBOX) wx_style |= wxMINIMIZE_BOX;
          if ((style & WS_SYSMENU) == WS_SYSMENU) wx_style |= wxSYSTEM_MENU;
          
          if ((style & WS_THICKFRAME) == WS_THICKFRAME) wx_style |= wxRESIZE_BORDER;
          
          if ((style & WS_CAPTION) == WS_CAPTION) wx_style |= wxCAPTION;
          if ((style & WS_CLIPCHILDREN) == WS_CLIPCHILDREN) wx_style |= wxCLIP_CHILDREN;
          
          if ((ex_style & WS_EX_APPWINDOW) != WS_EX_APPWINDOW) wx_style |= wxFRAME_NO_TASKBAR;
          if ((ex_style & WS_EX_TOOLWINDOW) == WS_EX_TOOLWINDOW) wx_style |= wxFRAME_TOOL_WINDOW;
          if ((ex_style & WS_EX_DLGMODALFRAME) == WS_EX_DLGMODALFRAME) wx_style &= ~(wxSYSTEM_MENU);
          
          if ((class_style & CS_NOCLOSE) != CS_NOCLOSE) wx_style |= wxCLOSE_BOX;
          
          if ((ex_style & WS_EX_TOPMOST) == WS_EX_TOPMOST) wx_style |= wxSTAY_ON_TOP;
          else if (parent && (style & WS_CHILD) != WS_CHILD) wx_style |= wxFRAME_FLOAT_ON_PARENT;
          
          //cdebug << ustring::format("style = 0x{:X}, ex_style = 0x{:X}, wx_style = 0x{:X}", style, ex_style, wx_style) << std::endl;
          
          return wx_style;
        }
        
        static long panel_style_to_wx_style(size_t style, size_t ex_style, size_t class_style) {
          long wx_style = wxTAB_TRAVERSAL | wxNO_BORDER;
          
          if ((style & WS_HSCROLL) == WS_HSCROLL) wx_style |= wxHSCROLL;
          if ((style & WS_VSCROLL) == WS_VSCROLL) wx_style |= wxVSCROLL;
          if (((style & WS_HSCROLL) == WS_HSCROLL || (style & WS_VSCROLL) == WS_VSCROLL) && (ex_style & WS_EX_AUTOSCROLL) != WS_EX_AUTOSCROLL) wx_style |= wxALWAYS_SHOW_SB;
          
          return wx_style;
        }
        
        wxWindow* main_control() const override {
          return panel_;
        }
        
        void SetBackgroundColour(const wxColour& colour) override {
          control_handler::SetBackgroundColour(colour);
          #if !defined(__APPLE__)
          panel_->SetBackgroundColour(colour);
          #endif
        }
        
        void SetCursor(const wxCursor& cursor) override {
          control_handler::SetCursor(cursor);
          panel_->SetCursor(cursor);
        }
        
        void SetForegroundColour(const wxColour& colour) override {
          control_handler::SetForegroundColour(colour);
          panel_->SetForegroundColour(colour);
        }
        
        void SetClientSize(int32_t width, int32_t height) override {
          #if defined(__APPLE__)
          if (width < 75) width = 75;
          if (height < 23) height = 23;
          #endif
          control()->SetClientSize(wxSize(width, height));
        }
        
        void SetSize(int32_t width, int32_t height) override {
          #if defined(__APPLE__)
          if (width < 75) width = 75;
          if (height < 23) height = 23;
          #endif
          control_handler::SetSize(width, height);
        }
        
      private:
        wxBoxSizer* boxSizer_;
        wxMainPanel* panel_;
      };
    }
  }
}
