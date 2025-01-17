#include "../../../include/xtd/reflection/assembly_culture_attribute.h"

using namespace std;
using namespace xtd;
using namespace xtd::reflection;

assembly_culture_attribute::assembly_culture_attribute(const ustring& culture) : culture_(culture) {
}

assembly_culture_attribute::assembly_culture_attribute(const ustring& culture, const object& executing_assembly) : culture_(culture) {
  __assembly_culture_attribute__() = make_shared<xtd::reflection::assembly_culture_attribute>(culture);
}

shared_ptr<object> assembly_culture_attribute::get_type_id() const {
  return xtd::guid::new_guid().memberwise_clone<xtd::guid>();
}

shared_ptr<xtd::reflection::assembly_culture_attribute>& __assembly_culture_attribute__() {
  static shared_ptr<xtd::reflection::assembly_culture_attribute> culture;
  return culture;
}
