#include "../../../include/xtd/reflection/assembly_title_attribute.h"

using namespace std;
using namespace xtd;
using namespace xtd::reflection;

assembly_title_attribute::assembly_title_attribute(const ustring& title) : title_(title) {
}

assembly_title_attribute::assembly_title_attribute(const ustring& title, const object& executing_assembly) : title_(title) {
  __assembly_title_attribute__() = make_shared<xtd::reflection::assembly_title_attribute>(title);
}

shared_ptr<object> assembly_title_attribute::get_type_id() const {
  return xtd::guid::new_guid().memberwise_clone<xtd::guid>();
}

shared_ptr<xtd::reflection::assembly_title_attribute>& __assembly_title_attribute__() {
  static shared_ptr<xtd::reflection::assembly_title_attribute> title;
  return title;
}