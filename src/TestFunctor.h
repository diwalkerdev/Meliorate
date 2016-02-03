#ifndef MELIORATEPRIVATE_TESTFUNCTOR_H
#define MELIORATEPRIVATE_TESTFUNCTOR_H

#include <functional>

namespace MelioratePrivate {

struct TestFunctor {
    using Args = void(void);
    using Function = std::function<Args>;

    const int line;
    const std::string id;
    const Function func;

    TestFunctor(int line, std::string id, Function fn_ptr);
    void operator()() const;
};

}

#endif //MELIORATEPRIVATE_TESTFUNCTOR_H
