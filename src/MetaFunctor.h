#ifndef MELIORATE_PRIVATE_METAFUNCTOR_H
#define MELIORATE_PRIVATE_METAFUNCTOR_H

#include <functional>

namespace Meliorate {
namespace Private {

struct MetaFunctor {
    using Args = void(void);
    using Function = std::function<Args>;

    const int line;
    const std::string id;
    const Function func;

    MetaFunctor(int line, std::string id, Function fn_ptr)
            : line(line)
            , id(id)
            , func(fn_ptr)
    {}

    void operator()() const { func(); }
};

}  // end Private
}  // end Meliorate

#endif //MELIORATE_PRIVATE_METAFUNCTOR_H
