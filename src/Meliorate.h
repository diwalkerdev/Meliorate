#ifndef MELIORATE_MELIORATE_H
#define MELIORATE_MELIORATE_H

#include <functional>

// Meliorate API.
// -----------------------------------------------------------------------------
int meliorate_register(int line, const char* name, std::function<void(void)>);
int meliorate_run();


// Self Registering Test.
// The static int is just a hook to force the meliorate_register function to be
// called automatically.
// -----------------------------------------------------------------------------
#define TEST(name, lambda)                                                     \
static int UNIQUE(MeliorateTest) = meliorate_register(__LINE__, name, lambda)

#define UNIQUE(name)        UNIQUE2(name, __LINE__)
#define UNIQUE2(name, line) UNIQUE3(name, line)
#define UNIQUE3(name, line) name##line

#endif //MELIORATE_MELIORATE_H
