#include <xtd/xtd>

using namespace std;
using namespace xtd;

int main() {
  string str;
  string nl = environment::new_line();
  
  console::write_line();
  //  <-- Keep this information secure! -->
  string query = "My system drive is %SystemDrive% and my system root is %SystemRoot%";
  str = environment::expand_environment_variables(query);
  console::write_line("expand_environment_variables: {0}  {1}", nl, str);
}

// This code produces the following output :
//
// expand_environment_variables:
//   My system drive is C: and my system root is C:\windows