#ifndef MELIORATE_H
#define MELIORATE_H

#include <stdio.h>
#include <iostream>
#include <exception>

extern int MELIORATE_NUM_TEST_FUNCTIONS;

extern void (*meliorate_test_functions[])();
extern const char* meliorate_test_names[];

extern bool meliorate_stop_on_error;


template <typename T>
void handle_exception(T const& exception)
{
    std::cerr << exception.what() << std::endl;
}


template <typename T>
int meliorate_run()
{
    bool was_exception;
    int tests_failed_counter = 0;

    for (int i=0; i < MELIORATE_NUM_TEST_FUNCTIONS; ++i)
    {
        was_exception = false;

        printf("[RUN     ] %s\n", meliorate_test_names[i]);
        try 
        {
            (*meliorate_test_functions[i])();
        }
        catch(T const& the_exception)
        {
            was_exception = true;
            ++tests_failed_counter;

            handle_exception(the_exception);
            printf("[  FAILED]\n");
            
            if (meliorate_stop_on_error) 
            {
                break;
            }
        }

        if (!was_exception)
        {
            printf("[  PASSED]\n");
        }
    }

    if (tests_failed_counter)
    {
        printf("%d tests FAILED out of %d\n", tests_failed_counter, MELIORATE_NUM_TEST_FUNCTIONS);
    }
    else
    {
        printf("All tests passed.\n");
    }
    return tests_failed_counter;
}

#endif