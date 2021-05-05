#include <xtd/xtd.tunit>
#include <stdexcept>

using namespace xtd::tunit;

namespace unit_tests {
  // The class test must be declared with test_class_ helper.
  class test_class_(test) {
  public:
    void test_method_(test_case1) {
      assert::is_true(true);
    }
    
    void test_method_(test_case2) {
      assert::is_false(true);
    }
    
    void test_method_(test_case3) {
      assert::does_not_throw([] {throw std::range_error("error");});
    }
  };
}

int main() {
  return console_unit_test().run();
}

// This code can produce the following output:
//
// Start 3 tests from 1 test case
// Run tests:
//   SUCCEED test.test_case1 (0 ms total)
//   FAILED  test.test_case2 (0 ms total)
//     Expected: false
//     But was:  true
//     Stack Trace: in /Users/gammasoft/Projects/xtd/examples/xtd.tunit.examples/assert/src/assert.cpp:14
//   FAILED  test.test_case3 (0 ms total)
//     Expected: No Exception to be thrown
//     But was:  <std::range_error>
//     Stack Trace: in /Users/gammasoft/Projects/xtd/examples/xtd.tunit.examples/assert/src/assert.cpp:18
//
// Test results:
//   SUCCEED 1 test.
//   FAILED  2 tests.
// End 3 tests from 1 test case ran. (0 ms total)