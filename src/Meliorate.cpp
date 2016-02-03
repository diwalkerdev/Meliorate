#include "Meliorate.h"
#include "Melio.h"
#include "mono_ptr.h"

#include "TestFunctor.h"

using Meliorate = mono_ptr<Melio>;


int meliorate_register(int line, const char* name, std::function<void(void)> lambda) {
  auto t = ::MelioratePrivate::TestFunctor(line, name, lambda);
  // Meliorate()->push(t);
  Meliorate()->push({line, name, lambda});
  return 0;
}

int meliorate_run() {
    return Meliorate()->run();
}

// void meliorate_on_test_fail(int line, std::string message) {
//     Meliorate()->on_test_fail(line, message);
// }
