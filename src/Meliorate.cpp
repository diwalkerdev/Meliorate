#include "Meliorate.h"
#include "Melio.h"
#include "mono_ptr.h"


int meliorate_register(int line, const char* name, std::function<void(void)> lambda) {
  mono_ptr<Melio>()->push({line, name, lambda});
  return 0;
}

int meliorate_run() {
    return mono_ptr<Melio>()->run();
}
