#include <xtd/xtd>

using namespace std::chrono;
using namespace xtd;

class program {
public:
  static void main() {
    date_time date1(2008, 4, 1, 18, 7, 5);
    console::write_line(date1.to_string("a")); // PM
    console::write_line(date1.to_string("d")); // 04/01/2008
    console::write_line(date1.to_string("D")); // 4/01/2008
    console::write_line(date1.to_string("f")); // Tue Apr  1 18:07:05 2008
    console::write_line(date1.to_string("F")); // Tue Apr  1 18:07:05 2008
    console::write_line(date1.to_string("g")); // Tue Apr  1 18:07:05 2008
    console::write_line(date1.to_string("G")); // Tue Apr  1 18:07:05 2008
    console::write_line(date1.to_string("h")); // Tue
    console::write_line(date1.to_string("H")); // Tuesday
    console::write_line(date1.to_string("i")); // 01
    console::write_line(date1.to_string("I")); // 1
    console::write_line(date1.to_string("j")); // Apr
    console::write_line(date1.to_string("J")); // April
    console::write_line(date1.to_string("k")); // 04
    console::write_line(date1.to_string("K")); // 4
    console::write_line(date1.to_string("l")); // 08
    console::write_line(date1.to_string("L")); // 2008
    console::write_line(date1.to_string("m")); // April 1
    console::write_line(date1.to_string("M")); // April 1
    console::write_line(date1.to_string("n")); // Tuesday, 1 April 2008
    console::write_line(date1.to_string("N")); // Tuesday, 1 April 2008 18:07:05
    console::write_line(date1.to_string("o")); // 1 April 2008
    console::write_line(date1.to_string("O")); // 1 April 2008
    console::write_line(date1.to_string("s")); // 2008-04-01T18:07:05
    console::write_line(date1.to_string("t")); // 18:07:05
    console::write_line(date1.to_string("T")); // 18:07:05
    console::write_line(date1.to_string("u")); // 2008-04-01 18:07:05
    console::write_line(date1.to_string("U")); // Tuesday, 1 April 2008 18:07:05
    console::write_line(date1.to_string("v")); // 18:07
    console::write_line(date1.to_string("V")); // 18:07
    console::write_line(date1.to_string("w")); // 18
    console::write_line(date1.to_string("W")); // 18
    console::write_line(date1.to_string("x")); // 06
    console::write_line(date1.to_string("X")); // 6
    console::write_line(date1.to_string("y")); // April 8
    console::write_line(date1.to_string("Y")); // April 2008
    console::write_line(date1.to_string("z")); // UTC
    console::write_line(date1.to_string("Z")); // UTC
    
    // Other format generate a xtd::format_exception exception
  }
};

startup_(program);

// This code can produces the following output:
//
// PM
// 04/01/2008
// 4/01/2008
// Tue Apr  1 18:07:05 2008
// Tue Apr  1 18:07:05 2008
// Tue Apr  1 18:07:05 2008
// Tue Apr  1 18:07:05 2008
// Tue
// Tuesday
// 01
// 1
// Apr
// April
// 04
// 4
// 08
// 2008
// April 1
// April 1
// Tuesday, 1 April 2008
// Tuesday, 1 April 2008 18:07:05
// 1 April 2008
// 1 April 2008
// 2008-04-01T18:07:05
// 18:07:05
// 18:07:05
// 2008-04-01 18:07:05
// Tuesday, 1 April 2008 18:07:05
// 18:07
// 18:07
// 18
// 18
// 06
// 6
// April 8
// April 2008
// UTC
// UTC
