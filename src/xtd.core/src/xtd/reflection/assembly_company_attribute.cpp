#include "../../../include/xtd/reflection/assembly_company_attribute.h"

using namespace std;
using namespace xtd;
using namespace xtd::reflection;

assembly_company_attribute::assembly_company_attribute(const ustring& company) : company_(company) {}

assembly_company_attribute::assembly_company_attribute(const ustring& company, const object& executing_assembly) : company_(company) {
  __assembly_company_attribute__() = make_shared<xtd::reflection::assembly_company_attribute>(company);
}

shared_ptr<object> assembly_company_attribute::get_type_id() const {
  return xtd::guid::new_guid().memberwise_clone<xtd::guid>();
}

shared_ptr<xtd::reflection::assembly_company_attribute>& __assembly_company_attribute__() {
  static shared_ptr<xtd::reflection::assembly_company_attribute> company;
  return company;
}
