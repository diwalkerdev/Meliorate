#include "TestFunctor.h"

using namespace MelioratePrivate;

TestFunctor::TestFunctor(int line, std::string id, Function fn_ptr)
        : line(line)
        , id(id)
        , func(fn_ptr)
{}

void TestFunctor::operator()() const {
    func();
}
