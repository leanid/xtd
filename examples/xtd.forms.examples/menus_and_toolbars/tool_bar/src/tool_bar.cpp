#include <xtd/xtd>

using namespace xtd;
using namespace xtd::forms;

namespace examples {
  class form1 : public form {
  public:
    form1() {
      text("Toolbar example");
      client_size({820, 500});
      
      list_box1.parent(*this);
      list_box1.dock(dock_style::fill);
      
      tool_bar1.image_list().images().push_back_range({tool_bar_images::file_new(), tool_bar_images::file_open(), tool_bar_images::file_save(), tool_bar_images::file_print(), tool_bar_images::edit_cut(), tool_bar_images::edit_copy(), tool_bar_images::edit_paste(), tool_bar_images::help_about()});
      
      tool_bar1.items().push_back_range({new_tool_bar_button, open_tool_bar_button, save_tool_bar_button, print_tool_bar_button, tool_bar_separator1, cut_tool_bar_button, copy_tool_bar_button, paste_tool_bar_button, tool_bar_separator2, about_tool_bar_button});
      tool_bar1.parent(*this);
    }
    
  private:
    void on_tool_bar_item_click(object& sender, const event_args& e) {
      list_box1.items().push_back(ustring::format("{} clicked", as<tool_bar_button>(sender).text()));
      list_box1.selected_index(list_box1.items().size() - 1);
    }
    
    list_box list_box1;
    forms::tool_bar tool_bar1;
    
    tool_bar_button new_tool_bar_button {system_texts::new_(), 0, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_button open_tool_bar_button {system_texts::open(), 1, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_button save_tool_bar_button {system_texts::save(), 2, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_button print_tool_bar_button {system_texts::print(), 3, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_separator tool_bar_separator1;
    tool_bar_button cut_tool_bar_button {system_texts::cut(), 4, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_button copy_tool_bar_button {system_texts::copy(), 5, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_button paste_tool_bar_button {system_texts::paste(), 6, {*this, &form1::on_tool_bar_item_click}};
    tool_bar_separator tool_bar_separator2;
    tool_bar_button about_tool_bar_button {system_texts::about(), 7, {*this, &form1::on_tool_bar_item_click}};
  };
}

int main() {
  application::run(examples::form1());
}