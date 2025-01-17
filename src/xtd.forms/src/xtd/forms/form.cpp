#include <random>
#include <stdexcept>
#include <xtd/as.h>
#include <xtd/invalid_operation_exception.h>
#include <xtd/is.h>
#include <xtd/literals.h>
#include <xtd/drawing/system_colors.h>
#include <xtd/drawing/system_icons.h>
#define __XTD_FORMS_NATIVE_LIBRARY__
#include <xtd/forms/native/class_styles.h>
#include <xtd/forms/native/control.h>
#include <xtd/forms/native/extended_window_styles.h>
#include <xtd/forms/native/form.h>
#include <xtd/forms/native/window_styles.h>
#undef __XTD_FORMS_NATIVE_LIBRARY__
#include <xtd/forms/window_messages.h>
#include "../../../include/xtd/forms/application.h"
#include "../../../include/xtd/forms/form.h"
#include "../../../include/xtd/forms/screen.h"
#include "../../../include/xtd/forms/style_sheets/style_sheet.h"

using namespace std;
using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms;

std::optional<std::reference_wrapper<form>> form::active_form_;

form::form() {
  set_auto_size_mode(forms::auto_size_mode::grow_only);
  icon_ = system_icons::xtd_forms_logo();
  font(default_font());
  set_state(state::visible, false);
  set_state(state::top_level, true);
  
  if (!application::style_sheet().is_system_style_sheet()) {
    back_color(default_back_color());
    fore_color(default_fore_color());
  }
  create_control();
}

form& form::accept_button(const ibutton_control& accept_button) {
  if (!accept_button_.has_value() || &accept_button_.value().get() != &accept_button) {
    if (accept_button_.has_value()) accept_button_.value().get().notify_default(false);
    accept_button_ = const_cast<ibutton_control&>(accept_button);
    accept_button_.value().get().notify_default(true);
  }
  return *this;
}

form& form::accept_button(nullptr_t) {
  if (accept_button_.has_value()) accept_button_.value().get().notify_default(false);
  accept_button_.reset();
  return *this;
}

form& form::cancel_button(const ibutton_control& cancel_button) {
  if (!cancel_button_.has_value() || &cancel_button_.value().get() != &cancel_button)
    cancel_button_ = const_cast<ibutton_control&>(cancel_button);
  return *this;
}

form& form::cancel_button(nullptr_t) {
  cancel_button_.reset();
  return *this;
}

form& form::auto_size_mode(forms::auto_size_mode value) {
  set_auto_size_mode(value);
  return *this;
}

form& form::close_box(bool value) {
  if (close_box_ != value) {
    close_box_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::control_box(bool value) {
  if (control_box_ != value) {
    control_box_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::dialog_result(forms::dialog_result value) {
  dialog_result_ = value;
  return *this;
}

form& form::form_border_style(forms::form_border_style value) {
  if (form_border_style_ != value) {
    form_border_style_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::help_button(bool value) {
  if (help_button_ != value) {
    help_button_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::icon(const xtd::drawing::icon& value) {
  if (icon_ != value) {
    icon_ = value != drawing::icon::empty ? value : system_icons::xtd_forms_logo();
    if (is_handle_created() && show_icon_) native::form::icon(handle(), icon_);
  }
  return *this;
}

form& form::maximize_box(bool value) {
  if (maximize_box_ != value) {
    maximize_box_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::menu(const forms::main_menu& value) {
  if (!menu_.has_value() || &menu_.value().get() != &value) {
    menu_ = const_cast<forms::main_menu&>(value);
    if (is_handle_created()) create_system_menu();
  }
  return *this;
}

form& form::menu(nullptr_t) {
  if (menu_.has_value()) {
    if (is_handle_created()) destroy_system_menu();
    menu_.reset();
  }
  return *this;
}

form& form::minimize_box(bool value) {
  if (minimize_box_ != value) {
    minimize_box_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::owner(const control& value) {
  if (owner_ != value.handle()) {
    owner_ = value.handle();
    recreate_handle();
  }
  return *this;
}

control& form::parent(const control& parent) {
  throw invalid_operation_exception("Top-level control cannot be added to a control."_t, current_stack_frame_);
}

form& form::show_icon(bool value) {
  if (show_icon_ != value) {
    show_icon_ = value;
    recreate_handle();
  }
  
  return *this;
}

form& form::start_position(form_start_position start_position) {
  start_position_ = start_position;
  return *this;
}

form& form::top_level(bool top_level) {
  if (!get_state(state::top_level) != top_level)
    set_state(state::top_level, top_level);
  return *this;
}

form& form::tool_bar(const forms::tool_bar& value) {
  if (!tool_bar_.has_value() || &tool_bar_.value().get() != &value) {
    tool_bar_ = const_cast<forms::tool_bar&>(value);
    tool_bar_.value().get().is_system_tool_bar(true);
  }
  return *this;
}

form& form::tool_bar(nullptr_t) {
  if (tool_bar_.has_value()) {
    tool_bar_.value().get().is_system_tool_bar(false);
    tool_bar_.reset();
  }
  return *this;
}

form& form::top_most(bool value) {
  if (top_most_ != value) {
    top_most_ = value;
    recreate_handle();
  }
  return *this;
}

form& form::opacity(double opacity) {
  if (opacity_ != opacity) {
    opacity_ = opacity;
    if (is_handle_created()) native::form::opacity(handle(), opacity_);
  }
  return *this;
}

control& form::visible(bool visible) {
  std::optional<forms::form_window_state> current_window_state;
  if (!previous_screen_) {
    current_window_state = window_state_;
    previous_screen_ = std::make_shared<screen>(screen::from_control(*this));
    recreate_handle();
  }
  container_control::visible(visible);
  if (active_form().has_value() && active_form().value().get().handle() == handle() && active_control_.has_value())
    active_control_.value().get().focus();
    
  if (current_window_state.has_value())
    window_state(current_window_state.value());
  internal_set_window_state();
  if (visible) can_close_ = false;
  if (visible && accept_button_.has_value()) accept_button_.value().get().notify_default(true);
  return *this;
}

form& form::window_state(form_window_state value) {
  if (window_state_ != value) {
    window_state_ = value;
    internal_set_window_state();
  }
  return *this;
}

void form::activate() {
  if (is_handle_created()) native::form::activate(handle());
}

void form::bring_to_front() {
  activate();
  control::focus();
}

void form::center_to_screen() {
  screen screen = screen::from_control(*this);
  left((screen.working_area().width() - width()) / 2);
  top((screen.working_area().height() - height()) / 2);
}

void form::close() {
  if (is_handle_created()) native::form::close(handle());
}

bool form::pre_process_message(xtd::forms::message& message) {
  if (message.msg() == WM_KEYUP) {
    key_event_args key_event_args(static_cast<keys>(message.wparam()));
    if (key_event_args.key_data() == keys::enter && accept_button_.has_value()) {
      accept_button_.value().get().perform_click();
      return true;
    } else if (key_event_args.key_data() == keys::escape && cancel_button_.has_value()) {
      cancel_button_.value().get().perform_click();
      return true;
    }
  }
  
  return container_control::pre_process_message(message);
}
forms::dialog_result form::show_dialog() {
  set_state(state::modal, true);
  previous_screen_ = std::make_shared<screen>(screen::from_control(*this));
  recreate_handle();
  dialog_result_ = forms::dialog_result::none;
  application::raise_enter_thread_modal(event_args::empty);
  forms::dialog_result result = is_handle_created() ? static_cast<forms::dialog_result>(native::form::show_dialog(handle())) : dialog_result::cancel;
  application::raise_leave_thread_modal(event_args::empty);
  set_state(state::modal, false);
  return result;
}

forms::dialog_result form::show_dialog(const iwin32_window& owner) {
  parent_before_show_dialog_ = parent().has_value() ? parent().value().get().handle() : 0;
  set_state(state::modal, true);
  if (owner.handle() != handle()) set_parent(owner.handle());
  previous_screen_ = std::make_shared<screen>(screen::from_control(*this));
  recreate_handle();
  dialog_result_ = forms::dialog_result::none;
  application::raise_enter_thread_modal(event_args::empty);
  return is_handle_created() ? static_cast<forms::dialog_result>(native::form::show_dialog(handle())) : dialog_result::cancel;
}

void form::show_sheet(const iwin32_window& owner) {
  parent_before_show_dialog_ = parent().has_value() ? parent().value().get().handle() : 0;
  set_state(state::modal, true);
  if (owner.handle() != handle()) set_parent(owner.handle());
  previous_screen_ = std::make_shared<screen>(screen::from_control(*this));
  recreate_handle();
  dialog_result_ = forms::dialog_result::none;
  application::raise_enter_thread_modal(event_args::empty);
  if (is_handle_created()) native::form::show_sheet(handle());
}

forms::dialog_result form::show_sheet_dialog(const iwin32_window& owner) {
  parent_before_show_dialog_ = parent().has_value() ? parent().value().get().handle() : 0;
  set_state(state::modal, true);
  if (owner.handle() != handle()) set_parent(owner.handle());
  previous_screen_ = std::make_shared<screen>(screen::from_control(*this));
  recreate_handle();
  dialog_result_ = forms::dialog_result::none;
  application::raise_enter_thread_modal(event_args::empty);
  return is_handle_created() ? static_cast<forms::dialog_result>(native::form::show_sheet_dialog(handle())) : dialog_result::cancel;
}

forms::create_params form::create_params() const {
  forms::create_params create_params = container_control::create_params();
  create_params.style(create_params.style() & ~WS_CHILD);
  static int32_t default_location = 0;
  if (default_location == 0) {
    std::random_device rand;
    default_location = std::uniform_int_distribution<int32_t> {4, 20}(rand) * 10;
  }
  
  create_params.class_name("form");
  
  create_params.style(create_params.style() | WS_CLIPCHILDREN);
  
  switch (form_border_style_) {
    case forms::form_border_style::none: break;
    case forms::form_border_style::fixed_single: create_params.style(create_params.style() | WS_BORDER); break;
    case forms::form_border_style::sizable: create_params.style(create_params.style() | WS_BORDER | WS_THICKFRAME); break;
    case forms::form_border_style::fixed_3d: create_params.style(create_params.style() | WS_BORDER); create_params.ex_style(create_params.ex_style() | WS_EX_CLIENTEDGE); break;
    case forms::form_border_style::fixed_dialog: create_params.style(create_params.style() | WS_BORDER); create_params.ex_style(create_params.ex_style() | WS_EX_DLGMODALFRAME); break;
    case forms::form_border_style::fixed_tool_window: create_params.style(create_params.style() | WS_BORDER); create_params.ex_style(create_params.ex_style() | WS_EX_TOOLWINDOW); break;
    case forms::form_border_style::sizable_tool_window: create_params.style(create_params.style() | WS_BORDER | WS_THICKFRAME); create_params.ex_style(create_params.ex_style() | WS_EX_TOOLWINDOW); break;
    default: break;
  }
  
  switch (window_state_) {
    case form_window_state::maximized: create_params.style(create_params.style() | WS_MAXIMIZE); break;
    case form_window_state::minimized: create_params.style(create_params.style() | WS_MINIMIZE); break;
    default: break;
  }
  
  if (form_border_style_ != form_border_style::none) create_params.style(create_params.style() | WS_CAPTION);
  
  if (control_box_) create_params.style(create_params.style() | WS_SYSMENU);
  if (maximize_box_) create_params.style(create_params.style() | WS_MAXIMIZEBOX);
  if (minimize_box_) create_params.style(create_params.style() | WS_MINIMIZEBOX);
  if (help_button_ && !maximize_box_ && !minimize_box_) create_params.ex_style(create_params.ex_style() | WS_EX_CONTEXTHELP);
  
  if (!close_box_) create_params.class_style(create_params.class_style() | CS_NOCLOSE);
  
  if (show_in_taskbar_) create_params.ex_style(create_params.ex_style() | WS_EX_APPWINDOW);
  
  if (!show_icon_ && (form_border_style_ == forms::form_border_style::sizable || form_border_style_ == forms::form_border_style::fixed_3d || form_border_style_ == forms::form_border_style::fixed_single)) create_params.ex_style(create_params.ex_style() | WS_EX_DLGMODALFRAME);
  
  if (get_state(state::modal)) create_params.ex_style(create_params.ex_style() | WS_EX_MODALWINDOW);
  
  if (owner_ != 0) create_params.parent(owner_);
  
  if (top_most_) create_params.ex_style(create_params.ex_style() | WS_EX_TOPMOST);
  
  if (previous_screen_) {
    switch (start_position_) {
      case form_start_position::manual:
        create_params.location(location());
        create_params.size(size());
        if (application::open_forms().size() == 1) default_location = 40;
        break;
      case form_start_position::center_screen:
        create_params.location({(previous_screen_->working_area().width() - width()) / 2, (previous_screen_->working_area().height() - height()) / 2});
        create_params.size(size());
        break;
      case form_start_position::windows_default_location:
        create_params.location({default_location, default_location});
        create_params.size(size());
        break;
      case form_start_position::windows_default_bounds:
        create_params.location({default_location, default_location});
        create_params.size({previous_screen_->working_area().width() / 4 * 3, previous_screen_->working_area().height() / 4 * 3});
        break;
      case form_start_position::center_parent:
        if (parent().has_value())
          create_params.location({parent().value().get().left() + (parent().value().get().width() - width()) / 2, parent().value().get().top() + (parent().value().get().height() - height()) / 2});
        else
          create_params.location({default_location, default_location});
        create_params.size(size());
        break;
    }
    
    if (start_position_ == form_start_position::windows_default_location || start_position_ == form_start_position::windows_default_bounds || (start_position_ == form_start_position::center_parent && parent().has_value()))
      default_location = default_location < 200 ? default_location + 20 : 40;
  }
  
  //diagnostics::debug::write_line("create_params = {}", create_params);
  
  return create_params;
}

void form::wnd_proc(message& message) {
  switch (message.msg()) {
    case WM_ACTIVATE: wm_activate(message); break;
    case WM_CLOSE: wm_close(message); break;
    case WM_MENUCOMMAND: if (menu_.has_value()) menu_.value().get().wm_click(message); break;
    case WM_SYSCOLORCHANGE: wm_syscolor_change(message); break;
    case WM_RECREATE: wm_recreate(message); break;
    default: container_control::wnd_proc(message); break;
  }
}

void form::wm_activate(message& message) {
  if (message.lparam() == WA_INACTIVE && active_form_.has_value() && &active_form_.value().get() == this) {
    active_form_.reset();
    on_deactivate(event_args::empty);
  } else {
    active_form_ = *this;
    on_activated(event_args::empty);
  }
}

void form::wm_close(message& message) {
  form_closing_event_args event_args;
  on_form_closing(event_args);
  message.result(event_args.cancel() == true);
  if (event_args.cancel() != true) {
    can_close_ = true;
    hide();
    if (!get_state(state::modal))
      destroy_control();
    else {
      if (dialog_result_ == forms::dialog_result::none) dialog_result_ = forms::dialog_result::cancel;
      native::form::end_dialog(handle(), static_cast<int32_t>(dialog_result_));
      application::raise_leave_thread_modal(event_args::empty);
      set_parent(parent_before_show_dialog_);
      set_state(state::modal, false);
    }
    on_form_closed(form_closed_event_args());
  }
}

void form::wm_recreate(message& message) {
  auto current_location = location();
  recreate_handle();
  location(current_location);
}

void form::wm_syscolor_change(message& message) {
  def_wnd_proc(message);
  on_system_colors_changed(event_args::empty);
  if (&application::open_forms()[0].get() == this) style_sheets::style_sheet::on_system_colors_changed(event_args::empty);
}

void form::on_handle_created(const event_args& e) {
  container_control::on_handle_created(e);
  if (show_icon_ && icon_ != drawing::icon::empty) native::form::icon(handle(), icon_);
  if (accept_button_.has_value()) accept_button_.value().get().notify_default(true);
  if (opacity_ != 1.0) native::form::opacity(handle(), opacity_);
  
  if (menu_.has_value()) create_system_menu();
}

void form::on_handle_destroyed(const event_args& e) {
  container_control::on_handle_destroyed(e);
  destroy_system_menu();
}

void form::on_layout(const event_args& e) {
  scrollable_control::on_layout(e);
  if (is_handle_created() && auto_scroll()) native::form::virtual_size(handle(), display_rectangle().size());
}

void form::on_location_changed(const event_args& e) {
  if (handle() && top() < screen::get_working_area(handle()).top()) top(screen::get_working_area(handle()).top());
  container_control::on_location_changed(e);
}

void form::on_resize(const event_args& e) {
  if (is_handle_created()) {
    if (native::form::minimize(handle()))
      window_state_ = forms::form_window_state::minimized;
    else if (native::form::maximize(handle()))
      window_state_ = forms::form_window_state::maximized;
    else if (native::form::full_screen(handle()))
      window_state_ = forms::form_window_state::full_screen;
    else
      window_state_ = forms::form_window_state::normal;
  }
  container_control::on_resize(e);
}

void form::on_system_colors_changed(const event_args& e) {
  if (can_raise_events()) system_colors_changed(*this, e);
}

void form::internal_set_window_state() {
  if (!previous_screen_)
    recreate_handle();
  else if (is_handle_created()) {
    switch (window_state_) {
      case form_window_state::normal: native::form::restore(handle()); break;
      case form_window_state::maximized: native::form::maximize(handle(), true); break;
      case form_window_state::minimized: native::form::minimize(handle(), true); break;
      case form_window_state::full_screen: native::form::full_screen(handle(), true); break;
      default: break;
    }
  }
}

void form::create_system_menu() {
  if (!menu_.has_value()) return;
  
  // Workaround : Get client size because afer changing tool bar to system, the client size does not correct.
  auto prev_client_size = client_size();
  
  native::form::menu(handle(), menu_.value().get().handle());
  
  // Workaround : Force the client size with the previously saved client size.
  client_size(prev_client_size);
}

void form::destroy_system_menu() {
  if (!menu_) return;
  
  // Workaround : Get client size because afer changing tool bar to system, the client size does not correct.
  auto prev_client_size = client_size();
  
  native::form::menu(handle(), 0);
  
  // Workaround : Force the client size with the previously saved client size.
  client_size(prev_client_size);
}
