#include "main_form.h"
#include "key_control.h"
#include "key_press_control.h"
#include "../properties/resources.h"
#include "../properties/settings.h"

using namespace std;
using namespace xtd;
using namespace xtd::forms;
using namespace keycodes;

void main_form::main() {
  application::run(main_form());
}

main_form::main_form() {
  size(properties::settings::default_settings().size());
  location(properties::settings::default_settings().location());
  if (properties::settings::default_settings().menu_visible()) {
    menu({
      {system_texts::file(), {
        {system_texts::clear(), {*this, &main_form::on_clear_button_click}, menu_images::from_name("edit-delete"), shortcut::cmd_del},
        {"-"},
        {system_texts::exit(), {overload_<>(&application::exit)}, menu_images::file_exit(), shortcut::alt_f4},
      }},
      {system_texts::help(), {
        {system_texts::about(), {*this, &main_form::show_about_dialog}, menu_images::help_about()},
      }},
    });
  }
  minimum_size({340, 340});
  start_position(form_start_position::manual);
  top_most(true);
  text("Key codes");
  location_changed += {*this, &main_form::on_form_location_changed};
  resize += {*this, &main_form::on_form_resize};

  main_panel_.auto_scroll(true);
  main_panel_.dock(dock_style::fill);
  main_panel_.parent(*this);

  line_panel_.back_color(application::theme().theme_colors().gray_text());
  line_panel_.dock(dock_style::top);
  line_panel_.height(2);
  line_panel_.parent(*this);

  top_panel_.dock(dock_style::top);
  top_panel_.height(35);
  top_panel_.parent(*this);

  show_key_down_check_box_.appearance(forms::appearance::button);
  show_key_down_check_box_.checked(properties::settings::default_settings().show_key_down());
  show_key_down_check_box_.location({10, 5});
  show_key_down_check_box_.parent(top_panel_);
  show_key_down_check_box_.text("Key down"_t);
  show_key_down_check_box_.text_align(content_alignment::middle_center);
  show_key_down_check_box_.click += {*this, &main_form::on_show_key_down_check_box_click};

  show_key_press_check_box_.appearance(forms::appearance::button);
  show_key_press_check_box_.checked(properties::settings::default_settings().show_key_press());
  show_key_press_check_box_.location({120, 5});
  show_key_press_check_box_.parent(top_panel_);
  show_key_press_check_box_.text("Key press"_t);
  show_key_press_check_box_.text_align(content_alignment::middle_center);
  show_key_press_check_box_.click += {*this, &main_form::on_show_key_press_check_box_click};;

  clear_button_.image(button_images::from_name("edit-delete"));
  clear_button_.location({230, 5});
  clear_button_.width(100);
  clear_button_.image_align(content_alignment::middle_left);
  clear_button_.parent(top_panel_);
  clear_button_.text("clear"_t);
  clear_button_.click += {*this, &main_form::on_clear_button_click};
}

bool main_form::pre_process_message(xtd::forms::message& message) {
  switch (message.msg()) {
    case WM_KEYDOWN: on_message_key_down(key_event_args(static_cast<keys>(message.wparam()))); break;
    case WM_CHAR: on_message_key_press(key_press_event_args(static_cast<int>(message.wparam()))); break;
    case WM_KEYUP: on_message_key_up(key_event_args(static_cast<keys>(message.wparam()))); break;
    default: break;
  }
  return false;
}

void main_form::on_clear_button_click(xtd::object& sender, const xtd::event_args& e){
  main_panel_.controls().clear();
  key_controls_.clear();
}

void main_form::on_form_location_changed(xtd::object& sender, const xtd::event_args& e) {
  properties::settings::default_settings().location(location());
  properties::settings::default_settings().save();
}

void main_form::on_form_resize(xtd::object& sender, const xtd::event_args& e) {
  properties::settings::default_settings().size(size());
  properties::settings::default_settings().save();
}

void main_form::on_message_key_down(const xtd::forms::key_event_args& e) {
  if (!properties::settings::default_settings().show_key_down()) return;
  auto key_control = make_shared<keycodes::key_control>();
  key_control->parent(main_panel_);
  key_control->dock(xtd::forms::dock_style::top);
  key_control->key_event("Key down"_t);
  key_control->key_code(ustring::format("{}", e.key_code()));
  key_control->key_data(ustring::format("{}", e.key_data()));
  key_control->key_value(ustring::format("{0} (0x{0:X4})", e.key_value()));
  key_control->key_modfiers(ustring::format("{}", e.modifiers()));
  key_controls_.emplace_back(key_control);
  handled_key_press_ = false; // Prevents receive more than one WM_CHAR event.
}

void main_form::on_message_key_press(const xtd::forms::key_press_event_args& e) {
  if (handled_key_press_ || !properties::settings::default_settings().show_key_press()) return;
  auto key_press_control = make_shared<keycodes::key_press_control>();
  key_press_control->parent(main_panel_);
  key_press_control->dock(xtd::forms::dock_style::top);
  key_press_control->key_char(ustring::format("{} (0x{:X2})", e.key_char(), static_cast<int>(e.key_char())));
  key_controls_.emplace_back(key_press_control);
  handled_key_press_ = true; // Prevents receive more than one WM_CHAR event.
}

void main_form::on_message_key_up(const xtd::forms::key_event_args& e) {
  auto key_control = make_shared<keycodes::key_control>();
  key_control->parent(main_panel_);
  key_control->dock(xtd::forms::dock_style::top);
  key_control->key_event("Key up"_t);
  key_control->key_code(ustring::format("{}", e.key_code()));
  key_control->key_data(ustring::format("{}", e.key_data()));
  key_control->key_value(ustring::format("{0} (0x{0:X4})", e.key_value()));
  key_control->key_modfiers(ustring::format("{}", e.modifiers()));
  key_control->line_visible(e.modifiers() == keys::none);
  key_controls_.emplace_back(key_control);
}

void main_form::on_show_key_down_check_box_click(xtd::object& sender, const xtd::event_args& e) {
  properties::settings::default_settings().show_key_down(!properties::settings::default_settings().show_key_down());
  properties::settings::default_settings().save();
}

void main_form::on_show_key_press_check_box_click(xtd::object& sender, const xtd::event_args& e) {
  properties::settings::default_settings().show_key_press(!properties::settings::default_settings().show_key_press());
  properties::settings::default_settings().save();
}

void main_form::show_about_dialog() {
  about_dialog dialog;
  dialog.icon(properties::resources::key_codes());
  dialog.name("key-codes");
  dialog.version(environment::version().to_string(2));
  dialog.long_version(environment::version().to_string(3));
  dialog.description("Displays information about the keys entered");
  dialog.copyright("Copyright (c) 2021 Gammasoft.\nAll rights reserved.");
  dialog.website("https://gammasoft71.wixsite.com/gammasoft");
  dialog.website_label("gammasoft website");
  dialog.authors({"Gammasoft", "Bader", "Contributors"});
  dialog.translators({"Gammasoft", "Contributors"});
  dialog.artists({"Gammasoft"});
  dialog.license("MIT License\n"
                 "\n"
                 "Copyright (c) 2021 Gammasoft.\n"
                 "\n"
                 "Permission is hereby granted, free of charge, to any person obtaining\n"
                 "a copy of this software and associated documentation files (the\n"
                 "\"Software\"), to deal in the Software without restriction, including\n"
                 "without limitation the rights to use, copy, modify, merge, publish,\n"
                 "distribute, sublicense, and/or sell copies of the Software, and to\n"
                 "permit persons to whom the Software is furnished to do so, subject\n"
                 "to the following conditions:\n"
                 "\n"
                 "The above copyright notice and this permission notice shall be\n"
                 "included in all copies or substantial portions of the Software.\n"
                 "\n"
                 "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF\n"
                 "ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO\n"
                 "THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A\n"
                 "PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT\n"
                 "SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR\n"
                 "ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN\n"
                 "ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                 "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE\n"
                 "OR OTHER DEALINGS IN THE SOFTWARE.\n");
  dialog.show();
}