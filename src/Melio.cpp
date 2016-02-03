#include <iostream>
#include "Melio.h"
// #include "fmt/format.h"
// #include "fmt/printf.h"
#include "snowhouse/snowhouse.h"
#include "snowhouse/assertionexception.h"

struct MelioImpl {
    using TestInfo = std::tuple<int, std::string>;

    auto enable_stop_on_error() -> void;
    auto push(MelioratePrivate::TestFunctor test) -> void;

    // auto on_test_fail(int line, std::string message) -> void;

    auto pre_execution(MelioratePrivate::TestFunctor const& t) -> void;
    auto post_execution(MelioratePrivate::TestFunctor const& t) -> void;

    auto finished() -> void;
    auto run() -> int;

    std::queue<MelioratePrivate::TestFunctor> queue;

    bool stop_on_error = false;
    bool all_tests_passed = true;
    bool current_test_passed = true;

    std::vector<TestInfo> messages;
};

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::enable_stop_on_error() -> void {
    stop_on_error = true;
}

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::push(MelioratePrivate::TestFunctor test) -> void {
    queue.push(std::move(test));
}

//////////////////////////////////////////////////////////////////////////////

// auto MelioImpl::on_test_fail(int line, std::string message) -> void {
//     all_tests_passed = false;
//     current_test_passed = false;
//     messages.push_back(std::make_tuple(line, std::move(message)));
// }

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::pre_execution(MelioratePrivate::TestFunctor const& t) -> void {
    printf("[RUN     ] %s\n", t.id.c_str());
}

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::post_execution(MelioratePrivate::TestFunctor const& t) -> void
{
    if (current_test_passed) {
        printf("[    PASS]\n");
    }
    else {
        printf("[    FAIL]\n");

        // for (auto const& message : messages) {
        //     printf("Assert error line %d\n"
        //             "  %s\n",
        //             std::get<0>(message),
        //             std::get<1>(message).c_str());
        // }
    }
}

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::run() -> int {
    printf("\n[MELIORATE]\n");

    int error_code = 0;
    while (!queue.empty()) {
        auto const &test = queue.front();

        pre_execution(test);

        current_test_passed = false;

        try {
          test();
          current_test_passed = true;
        }
        catch (snowhouse::AssertionException const& ex) {
          std::cerr << ex.GetMessage() << std::endl;

        }
        catch (...) {
          auto exptr = std::current_exception();
          try {
            if (exptr) { std::rethrow_exception(exptr); }
            else { std::cerr << "An exception was thrown but it became invalid during its handling." << std::endl; }
          }
          catch(std::exception const& ex) {
              std::cerr << ex.what() << std::endl;
          }
        }

        post_execution(test);

        if (!current_test_passed) {
            error_code = -1;

            if (stop_on_error) {
                break;
            }
            else {
            }
        }
        queue.pop();
        messages.clear();
    }

    finished();
    return error_code;
}

//////////////////////////////////////////////////////////////////////////////

auto MelioImpl::finished() -> void {
    printf("[ FINISH ]\n");
    if (!all_tests_passed) {
        printf( "****************************\n"
                "*** NOT ALL TESTS PASSED ***\n"
                "****************************\n");
    }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Melio::Melio() {
    pimpl = new MelioImpl;
}

Melio::~Melio() {
    delete pimpl;
}

auto Melio::enable_stop_on_error() -> void {
    pimpl->enable_stop_on_error();
}

auto Melio::push(MelioratePrivate::TestFunctor test) -> void {
    pimpl->push(test);
}

// auto Melio::on_test_fail(int line, std::string message) -> void {
//     pimpl->on_test_fail(line, message);
// }

auto Melio::pre_execution(MelioratePrivate::TestFunctor const& t) -> void {
    pimpl->pre_execution(t);
}

auto Melio::post_execution(MelioratePrivate::TestFunctor const& t) -> void {
    pimpl->post_execution(t);
}

auto Melio::finished() -> void {
    pimpl->finished();
}

auto Melio::run() -> int {
    return pimpl->run();
}
