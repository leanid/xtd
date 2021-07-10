#include <xtd/xtd>

using namespace std;
using namespace xtd;
using namespace xtd::diagnostics;
using namespace xtd::forms;

namespace examples {
  class form1 : public form {
  public:
    form1() {
      text("Link label example");

      link_label1.location({10, 10});
      link_label1.auto_size(true);
      link_label1.parent(*this);
      link_label1.text("Gammasoft presents xtd framework");
      link_label1.links().push_back({0, 9, "https://gammasoft71.wixsite.com/gammasoft"_s});
      link_label1.links().push_back({19, 3, "https://gammasoft71.wixsite.com/xtdpro"_s});
      link_label1.link_clicked += [](control& sender, link_label_clicked_event_args& e) {
        e.visited(true);
        process::start(as<string>(e.link().link_data()));
      };
    }
    
  private:
    link_label link_label1;
  };
}

int main() {
  application::run(examples::form1());
}
