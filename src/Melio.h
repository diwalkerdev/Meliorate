#ifndef MELIORATE_MELIO_H
#define MELIORATE_MELIO_H

#include <vector>
#include <queue>
#include "MetaFunctor.h"

struct MelioImpl;

struct Melio {
    using TestInfo = std::tuple<int, std::string>;

    Melio();
    virtual ~Melio();

    Melio(Melio const& other)=delete;
    Melio(Melio && other)=delete;

    auto enable_stop_on_error() -> void;
    auto push(Meliorate::Private::MetaFunctor test) -> void;

    auto pre_execution(Meliorate::Private::MetaFunctor const& t) -> void;
    auto post_execution(Meliorate::Private::MetaFunctor const& t) -> void;

    auto finished() -> void;
    auto run() -> int;

private:
    MelioImpl *pimpl;
};

#endif /* MELIORATE_MELIO_H */
